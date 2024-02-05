# nDPI-NETFILTER
Kernel implementation of the DPI
## The major differences from the original [nDPI](https://github.com/betolj/ndpi-netfilter)
### Features implemented by https://github.com/vel21ripn/nDPI

1. Using the tracking system connections (flows) conntrack/netfilter instead of a similar system in nDPI. The tracking system connections implemented in the conntrack/netfilter more accurate.

2. Added the ability to parse the DHT messages BitTorrent protocol to detect connections with encryption. It uses hash-table. To enable analysis of DHT messages, when the module is loaded xt_ndpi specify two parameters: bt_hash_size and bt_hash_timeout.
By default analysis DHT messages off.

3. Added interface for getting connection data (see FLOW_INFO.txt)

### Additional features:
1. Implemented dkms
2. Added netlink interface for using via nftables