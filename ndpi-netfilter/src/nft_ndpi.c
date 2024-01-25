#include <linux/netfilter.h>
#include <linux/tcp.h>
#include <linux/version.h>
#include <net/netfilter/nf_conntrack.h>
#include "nft_ndpi.h"
#include "xt_ndpi.h"
#include "ndpi_strcol.h"
#include "ndpi_flow_info.h"
#include "ndpi_main_netfilter.h"
#include "ndpi_main_common.h"
#include "../libre/regexp.h"

extern bool ndpi_match_proc(
	const struct sk_buff *skb, const struct xt_ndpi_mtinfo *info,
	const struct net *par_net, const struct net_device *net_in, const struct net_device *net_out);

extern void ndpi_enable_protocols(struct ndpi_net *n);
extern struct ndpi_net *ndpi_pernet(struct net *net);

#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 11, 0)
/**
 * nla_strscpy - Copy string attribute payload into a sized buffer
 * @dst: Where to copy the string to.
 * @nla: Attribute to copy the string from.
 * @dstsize: Size of destination buffer.
 *
 * Copies at most dstsize - 1 bytes into the destination buffer.
 * Unlike strlcpy the destination buffer is always padded out.
 *
 * Return:
 * * srclen - Returns @nla length (not including the trailing %NUL).
 * * -E2BIG - If @dstsize is 0 or greater than U16_MAX or @nla length greater
 *            than @dstsize.
 */
ssize_t nla_strscpy(char *dst, const struct nlattr *nla, size_t dstsize)
{
	size_t srclen = nla_len(nla);
	char *src = nla_data(nla);
	ssize_t ret;
	size_t len;

	if (dstsize == 0 || WARN_ON_ONCE(dstsize > U16_MAX))
		return -E2BIG;

	if (srclen > 0 && src[srclen - 1] == '\0')
		srclen--;

	if (srclen >= dstsize)
	{
		len = dstsize - 1;
		ret = -E2BIG;
	}
	else
	{
		len = srclen;
		ret = len;
	}

	memcpy(dst, src, len);
	/* Zero pad end of dst. */
	memset(dst + len, 0, dstsize - len);

	return ret;
}
#endif

static const struct nla_policy nft_ndpi_policy[NFTA_NDPI_MAX + 1] = {
	[NFTA_NDPI_PROTO] = {.type = NLA_BINARY, .len = sizeof(NDPI_PROTOCOL_BITMASK)},
	[NFTA_NDPI_FLAGS] = {.type = NLA_U16},
	[NFTA_NDPI_HOSTNAME] = {.type = NLA_STRING, .len = NFT_NDPI_HOSTNAME_LEN_MAX},
};

static int nft_ndpi_init(const struct nft_ctx *ctx, const struct nft_expr *expr, const struct nlattr *const tb[])
{
	struct xt_ndpi_mtinfo *priv = nft_expr_priv(expr);
	const struct nlattr *nla;

	if (tb[NFTA_NDPI_FLAGS] == NULL && tb[NFTA_NDPI_HOSTNAME] == NULL && tb[NFTA_NDPI_PROTO] == NULL)
	{
		pr_err("xt_ndpi: no nft params\n");
		return -EINVAL;
	}

	nla = tb[NFTA_NDPI_HOSTNAME];
	if (nla != NULL)
	{
		nla_strscpy(priv->hostname, nla, nla_len(nla) + 1);
		priv->host = 1;
	}

	if (_DBG_TRACE_MATCH)
		pr_info("hostname %s\n", priv->hostname);

	nla = tb[NFTA_NDPI_PROTO];
	if (nla != NULL)
	{
		memset(&priv->flags, 0, sizeof(priv->flags));
		memcpy(&priv->flags, nla_data(nla), sizeof(priv->flags));
		if (_DBG_TRACE_MATCH)
		{
			pr_info("protos: ");

			{
				int i;
				for (i = 0; i < NDPI_NUM_FDS_BITS; i++)
					pr_info("%x ", priv->flags.fds_bits[i]);
			}
		}
	}

	nla = tb[NFTA_NDPI_FLAGS];
	if (nla != NULL)
	{
		priv->cflg |= ntohl(nla_get_be32(nla));
	}
	priv->empty = NDPI_BITMASK_IS_ZERO(priv->flags);
	if (_DBG_TRACE_MATCH)
		pr_info("flags %x\n", priv->cflg);

	if (priv->hostname[0] && priv->re)
	{
		char re_buf[sizeof(priv->hostname)];
		int re_len = strlen(priv->hostname);
		if (re_len < 3 || priv->hostname[0] != '/' ||
			priv->hostname[re_len - 1] != '/')
		{
			pr_info("Invalid REGEXP\n");
			return -EINVAL;
		}
		re_len -= 2;
		strncpy(re_buf, &priv->hostname[1], re_len);
		re_buf[re_len] = '\0';
		priv->reg_data = ndpi_regcomp(re_buf, &re_len);
		if (!priv->reg_data)
		{
			pr_info("regcomp failed\n");
			return -EINVAL;
		}
		if (_DBG_TRACE_MATCH)
			pr_info("regcomp '%s' success\n", re_buf);
	}
	else
	{
		priv->reg_data = NULL;
	}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 11, 0)
	{
		int ret;

		ret = nf_ct_netns_get(ctx->net, ctx->family);
		if (ret < 0)
		{
			pr_info("cannot load conntrack support for proto=%u\n",
					ctx->family);
			return ret;
		}
	}
#endif
	ndpi_enable_protocols(ndpi_pernet(ctx->net));

	return 0;
}

static void nft_ndpi_destroy(const struct nft_ctx *ctx,
							 const struct nft_expr *expr)
{
	struct xt_ndpi_mtinfo *priv = nft_expr_priv(expr);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 11, 0)
	nf_ct_netns_put(ctx->net, ctx->family);
#endif
	if (priv->reg_data)
		kfree(priv->reg_data);
}

static int nft_ndpi_dump(struct sk_buff *skb, const struct nft_expr *expr)
{
	const struct xt_ndpi_mtinfo *priv = nft_expr_priv(expr);

	if (priv->hostname[0])
	{
		if (nla_put_string(skb, NFTA_NDPI_HOSTNAME, priv->hostname))
			goto nla_put_failure;
	}

	if (priv->cflg)
	{
		if (nla_put_be32(skb, NFTA_NDPI_FLAGS, htonl(priv->cflg)))
			goto nla_put_failure;
	}

	if (!priv->empty)
	{
		if (nla_put(skb, NFTA_NDPI_PROTO, sizeof(priv->flags), &priv->flags))
			goto nla_put_failure;
	}

	return 0;

nla_put_failure:
	pr_err("xt_ndpi: nft dump fail\n");
	return -1;
}

static void nft_ndpi_eval(const struct nft_expr *expr, struct nft_regs *regs, const struct nft_pktinfo *pkt)
{
	struct xt_ndpi_mtinfo *priv = nft_expr_priv(expr);

	if (ndpi_match_proc(pkt->skb, priv, nft_net(pkt), nft_in(pkt), nft_out(pkt)))
	{
		regs->verdict.code = NFT_CONTINUE;
		if (_DBG_TRACE_MATCH)
			pr_info("NFT_CONTINUE\n");
	}
	else
	{
		regs->verdict.code = NFT_BREAK;
		if (_DBG_TRACE_MATCH)
			pr_info("NFT_BREAK\n");
	}
}

struct nft_expr_type nft_ndpi_type;
static const struct nft_expr_ops nft_ndpi_op = {
	.eval = nft_ndpi_eval,
	.size = NFT_EXPR_SIZE(sizeof(struct xt_ndpi_mtinfo)),
	.init = nft_ndpi_init,
	.destroy = nft_ndpi_destroy,
	.dump = nft_ndpi_dump,
	.type = &nft_ndpi_type,
};
struct nft_expr_type nft_ndpi_type __read_mostly = {
	.ops = &nft_ndpi_op,
	.name = "ndpi",
	.owner = THIS_MODULE,
	.policy = nft_ndpi_policy,
	.maxattr = NFTA_NDPI_MAX,
};
