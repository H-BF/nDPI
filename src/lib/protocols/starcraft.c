/*
* starcraft.c
* 
* Copyright (C) 2015 - Matteo Bracci <matteobracci1@gmail.com>
* Copyright (C) 2015-22 - ntop.org
*
* nDPI is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* nDPI is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with nDPI.  If not, see <http://www.gnu.org/licenses/>.
*
*/

#include "ndpi_protocol_ids.h"

#define NDPI_CURRENT_PROTO NDPI_PROTOCOL_STARCRAFT

#include "ndpi_api.h"
#include "ndpi_private.h"


/* Sender or receiver are one of the known login portals? */
static u_int8_t sc2_match_logon_ip(struct ndpi_packet_struct* packet)
{
  u_int32_t source_ip, dest_ip;
  if (packet->iph == NULL)
    return 0;

  source_ip = ntohl(packet->iph->saddr);
  dest_ip = ntohl(packet->iph->daddr);
  return (ndpi_ips_match(source_ip, dest_ip, 0xD5F87F82, 32)		// EU 213.248.127.130
	  || ndpi_ips_match(source_ip, dest_ip, 0x0C81CE82, 32)		// US 12.129.206.130
	  || ndpi_ips_match(source_ip, dest_ip, 0x79FEC882, 32)		// KR 121.254.200.130
	  || ndpi_ips_match(source_ip, dest_ip, 0xCA09424C, 32)		// SG 202.9.66.76
	  || ndpi_ips_match(source_ip, dest_ip, 0x0C81ECFE, 32));		// BETA 12.129.236.254
}

/*
  The main TCP flow starts with the user login and stays alive until the logout.
  Although hard to read, judging from what happens elsewhere this flow probably contains all the data
  transfer generated by the user interaction with the client, e.g. chatting or looking at someone's
  match history. The current way to detect this is plain dumb packet matching.
*/
static u_int8_t ndpi_check_starcraft_tcp(struct ndpi_detection_module_struct* ndpi_struct, struct ndpi_flow_struct* flow)
{
  struct ndpi_packet_struct* packet = ndpi_get_packet_struct(ndpi_struct);

  if (sc2_match_logon_ip(packet)
      && packet->tcp->dest == htons(1119)	//bnetgame port
      && (ndpi_match_strprefix(packet->payload, packet->payload_packet_len, "\x4a\x00\x00\x0a\x66\x02\x0a\xed\x2d\x66") 
	  || ndpi_match_strprefix(packet->payload, packet->payload_packet_len, "\x49\x00\x00\x0a\x66\x02\x0a\xed\x2d\x66")))
    return 1;
  else
    return -1;
}

/*
  UPD traffic is the actual game data and it uses a port owned by Blizzard itself, 1119. Therefore the
  real key point here is to make sure that it's actually Starcraft 2 that is using the port and not
  some other Blizzard software.
  The flow is taken if a pattern in the size of some subsequent packets is found.
*/
static u_int8_t ndpi_check_starcraft_udp(struct ndpi_detection_module_struct* ndpi_struct, struct ndpi_flow_struct* flow)
{
  struct ndpi_packet_struct* packet = ndpi_get_packet_struct(ndpi_struct);

  /* First off, filter out any traffic not using port 1119, removing the chance of any false positive if we assume that non allowed protocols don't use the port */
  if (packet->udp->source != htons(1119) && packet->udp->dest != htons(1119))
    return -1;

  /* Then try to detect the size pattern */
  switch (flow->starcraft_udp_stage)
    {
    case 0:
      if (packet->payload_packet_len == 20)
	flow->starcraft_udp_stage = 1;
      break;
    case 1:
      if (packet->payload_packet_len == 20)
	flow->starcraft_udp_stage = 2;
      break;
    case 2:
      if (packet->payload_packet_len == 75 || packet->payload_packet_len == 85)
	flow->starcraft_udp_stage = 3;
      break;
    case 3:
      if (packet->payload_packet_len == 20)
	flow->starcraft_udp_stage = 4;
      break;
    case 4:
      if (packet->payload_packet_len == 548)
	flow->starcraft_udp_stage = 5;
      break;
    case 5:
      if (packet->payload_packet_len == 548)
	flow->starcraft_udp_stage = 6;
      break;
    case 6:
      if (packet->payload_packet_len == 548)
	flow->starcraft_udp_stage = 7;
      break;
    case 7:
      if (packet->payload_packet_len == 484)
	return 1;
      break;
    }

  return(0);
}

static void ndpi_search_starcraft(struct ndpi_detection_module_struct* ndpi_struct, struct ndpi_flow_struct* flow)
{
  struct ndpi_packet_struct* packet = ndpi_get_packet_struct(ndpi_struct);

  NDPI_LOG_DBG(ndpi_struct, "search Starcraft\n");
  if (flow->detected_protocol_stack[0] != NDPI_PROTOCOL_STARCRAFT) {
    int8_t result = 0;

    if (packet->udp != NULL) {
      result = ndpi_check_starcraft_udp(ndpi_struct, flow);
      if (result == 1) {
	NDPI_LOG_INFO(ndpi_struct, "Found Starcraft 2 [Game, UDP]\n");
        ndpi_set_detected_protocol(ndpi_struct, flow, NDPI_PROTOCOL_STARCRAFT, NDPI_PROTOCOL_UNKNOWN, NDPI_CONFIDENCE_DPI);
	return;
      }
    }
    else if (packet->tcp != NULL) {
      result = ndpi_check_starcraft_tcp(ndpi_struct, flow);
      if (result == 1) {
	NDPI_LOG_INFO(ndpi_struct, "Found Starcraft 2 [Client, TCP]\n");
        ndpi_set_detected_protocol(ndpi_struct, flow, NDPI_PROTOCOL_STARCRAFT, NDPI_PROTOCOL_UNKNOWN, NDPI_CONFIDENCE_DPI);
	return;
      }
    }

    if (result == -1) {
      NDPI_EXCLUDE_PROTO(ndpi_struct, flow);
    }
  }
}

void init_starcraft_dissector(struct ndpi_detection_module_struct *ndpi_struct, u_int32_t *id)
{
  ndpi_set_bitmask_protocol_detection("Starcraft", ndpi_struct, *id,
				      NDPI_PROTOCOL_STARCRAFT, ndpi_search_starcraft,
				      NDPI_SELECTION_BITMASK_PROTOCOL_V4_V6_TCP_OR_UDP_WITH_PAYLOAD_WITHOUT_RETRANSMISSION,
				      SAVE_DETECTION_BITMASK_AS_UNKNOWN,
				      ADD_TO_DETECTION_BITMASK);

  *id += 1;
}

