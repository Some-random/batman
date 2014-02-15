/* Copyright (C) 2007-2014 B.A.T.M.A.N. contributors:
 *
 * Marek Lindner, Simon Wunderlich
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _NET_BATMAN_ADV_PACKET_H_
#define _NET_BATMAN_ADV_PACKET_H_

/**
 * enum batadv_packettype - types for batman-adv encapsulated packets
 * @BATADV_IV_OGM: originator messages for B.A.T.M.A.N. IV
 * @BATADV_BCAST: broadcast packets carrying broadcast payload
 * @BATADV_CODED: network coded packets
 *
 * @BATADV_UNICAST: unicast packets carrying unicast payload traffic
 * @BATADV_UNICAST_FRAG: unicast packets carrying a fragment of the original
 *     payload packet
 * @BATADV_UNICAST_4ADDR: unicast packet including the originator address of
 *     the sender
 * @BATADV_ICMP: unicast packet like IP ICMP used for ping or traceroute
 * @BATADV_UNICAST_TVLV: unicast packet carrying TVLV containers
 */
enum batadv_packettype {
	/* 0x00 - 0x3f: local packets or special rules for handling */
	BATADV_IV_OGM           = 0x00,
	BATADV_BCAST            = 0x01,
	BATADV_CODED            = 0x02,
	/* 0x40 - 0x7f: unicast */
#define BATADV_UNICAST_MIN     0x40
	BATADV_UNICAST          = 0x40,
	BATADV_UNICAST_FRAG     = 0x41,
	BATADV_UNICAST_4ADDR    = 0x42,
	BATADV_ICMP             = 0x43,
	BATADV_UNICAST_TVLV     = 0x44,
#define BATADV_UNICAST_MAX     0x7f
	/* 0x80 - 0xff: reserved */
};

/**
 * enum batadv_subtype - packet subtype for unicast4addr
 * @BATADV_P_DATA: user payload
 * @BATADV_P_DAT_DHT_GET: DHT request message
 * @BATADV_P_DAT_DHT_PUT: DHT store message
 * @BATADV_P_DAT_CACHE_REPLY: ARP reply generated by DAT
 */
enum batadv_subtype {
	BATADV_P_DATA			= 0x01,
	BATADV_P_DAT_DHT_GET		= 0x02,
	BATADV_P_DAT_DHT_PUT		= 0x03,
	BATADV_P_DAT_CACHE_REPLY	= 0x04,
};

/* this file is included by batctl which needs these defines */
#define BATADV_COMPAT_VERSION 15

/**
 * enum batadv_iv_flags - flags used in B.A.T.M.A.N. IV OGM packets
 * @BATADV_NOT_BEST_NEXT_HOP: flag is set when ogm packet is forwarded and was
 *     previously received from someone else than the best neighbor.
 * @BATADV_PRIMARIES_FIRST_HOP: flag is set when the primary interface address
 *     is used, and the packet travels its first hop.
 * @BATADV_DIRECTLINK: flag is for the first hop or if rebroadcasted from a
 *     one hop neighbor on the interface where it was originally received.
 */
enum batadv_iv_flags {
	BATADV_NOT_BEST_NEXT_HOP   = BIT(0),
	BATADV_PRIMARIES_FIRST_HOP = BIT(1),
	BATADV_DIRECTLINK          = BIT(2),
};

/* ICMP message types */
enum batadv_icmp_packettype {
	BATADV_ECHO_REPLY	       = 0,
	BATADV_DESTINATION_UNREACHABLE = 3,
	BATADV_ECHO_REQUEST	       = 8,
	BATADV_TTL_EXCEEDED	       = 11,
	BATADV_PARAMETER_PROBLEM       = 12,
};

/* tt data subtypes */
#define BATADV_TT_DATA_TYPE_MASK 0x0F

/**
 * enum batadv_tt_data_flags - flags for tt data tvlv
 * @BATADV_TT_OGM_DIFF: TT diff propagated through OGM
 * @BATADV_TT_REQUEST: TT request message
 * @BATADV_TT_RESPONSE: TT response message
 * @BATADV_TT_FULL_TABLE: contains full table to replace existing table
 */
enum batadv_tt_data_flags {
	BATADV_TT_OGM_DIFF   = BIT(0),
	BATADV_TT_REQUEST    = BIT(1),
	BATADV_TT_RESPONSE   = BIT(2),
	BATADV_TT_FULL_TABLE = BIT(4),
};

/* BATADV_TT_CLIENT flags.
 * Flags from BIT(0) to BIT(7) are sent on the wire, while flags from BIT(8) to
 * BIT(15) are used for local computation only.
 * Flags from BIT(4) to BIT(7) are kept in sync with the rest of the network.
 */
enum batadv_tt_client_flags {
	BATADV_TT_CLIENT_DEL     = BIT(0),
	BATADV_TT_CLIENT_ROAM    = BIT(1),
	BATADV_TT_CLIENT_WIFI    = BIT(4),
	BATADV_TT_CLIENT_ISOLA	 = BIT(5),
	BATADV_TT_CLIENT_NOPURGE = BIT(8),
	BATADV_TT_CLIENT_NEW     = BIT(9),
	BATADV_TT_CLIENT_PENDING = BIT(10),
	BATADV_TT_CLIENT_TEMP	 = BIT(11),
};

/**
 * batadv_vlan_flags - flags for the four MSB of any vlan ID field
 * @BATADV_VLAN_HAS_TAG: whether the field contains a valid vlan tag or not
 */
enum batadv_vlan_flags {
	BATADV_VLAN_HAS_TAG	= BIT(15),
};

/* claim frame types for the bridge loop avoidance */
enum batadv_bla_claimframe {
	BATADV_CLAIM_TYPE_CLAIM		= 0x00,
	BATADV_CLAIM_TYPE_UNCLAIM	= 0x01,
	BATADV_CLAIM_TYPE_ANNOUNCE	= 0x02,
	BATADV_CLAIM_TYPE_REQUEST	= 0x03,
};

/**
 * enum batadv_tvlv_type - tvlv type definitions
 * @BATADV_TVLV_GW: gateway tvlv
 * @BATADV_TVLV_DAT: distributed arp table tvlv
 * @BATADV_TVLV_NC: network coding tvlv
 * @BATADV_TVLV_TT: translation table tvlv
 * @BATADV_TVLV_ROAM: roaming advertisement tvlv
 * @BATADV_TVLV_MCAST: multicast capability tvlv
 */
enum batadv_tvlv_type {
	BATADV_TVLV_GW		= 0x01,
	BATADV_TVLV_DAT		= 0x02,
	BATADV_TVLV_NC		= 0x03,
	BATADV_TVLV_TT		= 0x04,
	BATADV_TVLV_ROAM	= 0x05,
	BATADV_TVLV_MCAST	= 0x06,
};

#pragma pack(2)
/* the destination hardware field in the ARP frame is used to
 * transport the claim type and the group id
 */
struct batadv_bla_claim_dst {
	uint8_t magic[3];	/* FF:43:05 */
	uint8_t type;		/* bla_claimframe */
	__be16 group;		/* group id */
};
#pragma pack()

/**
 * struct batadv_ogm_packet - ogm (routing protocol) packet
 * @packet_type: batman-adv packet type, part of the general header
 * @version: batman-adv protocol version, part of the genereal header
 * @ttl: time to live for this packet, part of the genereal header
 * @flags: contains routing relevant flags - see enum batadv_iv_flags
 * @tvlv_len: length of tvlv data following the ogm header
 */
struct batadv_ogm_packet {
	uint8_t  packet_type;
	uint8_t  version;
	uint8_t  ttl;
	uint8_t  flags;
	__be32   seqno;
	uint8_t  orig[ETH_ALEN];
	uint8_t  prev_sender[ETH_ALEN];
	uint8_t  reserved;
	uint8_t  tq;
	__be16   tvlv_len;
	/* __packed is not needed as the struct size is divisible by 4,
	 * and the largest data type in this struct has a size of 4.
	 */
};

#define BATADV_OGM_HLEN sizeof(struct batadv_ogm_packet)

/**
 * batadv_icmp_header - common members among all the ICMP packets
 * @packet_type: batman-adv packet type, part of the general header
 * @version: batman-adv protocol version, part of the genereal header
 * @ttl: time to live for this packet, part of the genereal header
 * @msg_type: ICMP packet type
 * @dst: address of the destination node
 * @orig: address of the source node
 * @uid: local ICMP socket identifier
 * @align: not used - useful for alignment purposes only
 *
 * This structure is used for ICMP packets parsing only and it is never sent
 * over the wire. The alignment field at the end is there to ensure that
 * members are padded the same way as they are in real packets.
 */
struct batadv_icmp_header {
	uint8_t  packet_type;
	uint8_t  version;
	uint8_t  ttl;
	uint8_t  msg_type; /* see ICMP message types above */
	uint8_t  dst[ETH_ALEN];
	uint8_t  orig[ETH_ALEN];
	uint8_t  uid;
	uint8_t  align[3];
};

/**
 * batadv_icmp_packet - ICMP packet
 * @packet_type: batman-adv packet type, part of the general header
 * @version: batman-adv protocol version, part of the genereal header
 * @ttl: time to live for this packet, part of the genereal header
 * @msg_type: ICMP packet type
 * @dst: address of the destination node
 * @orig: address of the source node
 * @uid: local ICMP socket identifier
 * @reserved: not used - useful for alignment
 * @seqno: ICMP sequence number
 */
struct batadv_icmp_packet {
	uint8_t  packet_type;
	uint8_t  version;
	uint8_t  ttl;
	uint8_t  msg_type; /* see ICMP message types above */
	uint8_t  dst[ETH_ALEN];
	uint8_t  orig[ETH_ALEN];
	uint8_t  uid;
	uint8_t  reserved;
	__be16   seqno;
};

#define BATADV_RR_LEN 16

/**
 * batadv_icmp_packet_rr - ICMP RouteRecord packet
 * @packet_type: batman-adv packet type, part of the general header
 * @version: batman-adv protocol version, part of the genereal header
 * @ttl: time to live for this packet, part of the genereal header
 * @msg_type: ICMP packet type
 * @dst: address of the destination node
 * @orig: address of the source node
 * @uid: local ICMP socket identifier
 * @rr_cur: number of entries the rr array
 * @seqno: ICMP sequence number
 * @rr: route record array
 */
struct batadv_icmp_packet_rr {
	uint8_t  packet_type;
	uint8_t  version;
	uint8_t  ttl;
	uint8_t  msg_type; /* see ICMP message types above */
	uint8_t  dst[ETH_ALEN];
	uint8_t  orig[ETH_ALEN];
	uint8_t  uid;
	uint8_t  rr_cur;
	__be16   seqno;
	uint8_t  rr[BATADV_RR_LEN][ETH_ALEN];
};

#define BATADV_ICMP_MAX_PACKET_SIZE	sizeof(struct batadv_icmp_packet_rr)

/* All packet headers in front of an ethernet header have to be completely
 * divisible by 2 but not by 4 to make the payload after the ethernet
 * header again 4 bytes boundary aligned.
 *
 * A packing of 2 is necessary to avoid extra padding at the end of the struct
 * caused by a structure member which is larger than two bytes. Otherwise
 * the structure would not fulfill the previously mentioned rule to avoid the
 * misalignment of the payload after the ethernet header. It may also lead to
 * leakage of information when the padding it not initialized before sending.
 */
#pragma pack(2)

/**
 * struct batadv_unicast_packet - unicast packet for network payload
 * @packet_type: batman-adv packet type, part of the general header
 * @version: batman-adv protocol version, part of the genereal header
 * @ttl: time to live for this packet, part of the genereal header
 * @ttvn: translation table version number
 * @dest: originator destination of the unicast packet
 */
struct batadv_unicast_packet {
	uint8_t  packet_type;
	uint8_t  version;
	uint8_t  ttl;
	uint8_t  ttvn; /* destination translation table version number */
	uint8_t  dest[ETH_ALEN];
	/* "4 bytes boundary + 2 bytes" long to make the payload after the
	 * following ethernet header again 4 bytes boundary aligned
	 */
};

/**
 * struct batadv_unicast_4addr_packet - extended unicast packet
 * @u: common unicast packet header
 * @src: address of the source
 * @subtype: packet subtype
 */
struct batadv_unicast_4addr_packet {
	struct batadv_unicast_packet u;
	uint8_t src[ETH_ALEN];
	uint8_t subtype;
	uint8_t reserved;
	/* "4 bytes boundary + 2 bytes" long to make the payload after the
	 * following ethernet header again 4 bytes boundary aligned
	 */
};

/**
 * struct batadv_frag_packet - fragmented packet
 * @packet_type: batman-adv packet type, part of the general header
 * @version: batman-adv protocol version, part of the genereal header
 * @ttl: time to live for this packet, part of the genereal header
 * @dest: final destination used when routing fragments
 * @orig: originator of the fragment used when merging the packet
 * @no: fragment number within this sequence
 * @reserved: reserved byte for alignment
 * @seqno: sequence identification
 * @total_size: size of the merged packet
 */
struct batadv_frag_packet {
	uint8_t packet_type;
	uint8_t version;  /* batman version field */
	uint8_t ttl;
#if defined(__BIG_ENDIAN_BITFIELD)
	uint8_t no:4;
	uint8_t reserved:4;
#elif defined(__LITTLE_ENDIAN_BITFIELD)
	uint8_t reserved:4;
	uint8_t no:4;
#else
#error "unknown bitfield endianess"
#endif
	uint8_t dest[ETH_ALEN];
	uint8_t orig[ETH_ALEN];
	__be16  seqno;
	__be16  total_size;
};

/**
 * struct batadv_bcast_packet - broadcast packet for network payload
 * @packet_type: batman-adv packet type, part of the general header
 * @version: batman-adv protocol version, part of the genereal header
 * @ttl: time to live for this packet, part of the genereal header
 * @reserved: reserved byte for alignment
 * @seqno: sequence identification
 * @orig: originator of the broadcast packet
 */
struct batadv_bcast_packet {
	uint8_t  packet_type;
	uint8_t  version;  /* batman version field */
	uint8_t  ttl;
	uint8_t  reserved;
	__be32   seqno;
	uint8_t  orig[ETH_ALEN];
	/* "4 bytes boundary + 2 bytes" long to make the payload after the
	 * following ethernet header again 4 bytes boundary aligned
	 */
};

/**
 * struct batadv_coded_packet - network coded packet
 * @packet_type: batman-adv packet type, part of the general header
 * @version: batman-adv protocol version, part of the genereal header
 * @ttl: time to live for this packet, part of the genereal header
 * @reserved: Align following fields to 2-byte boundaries
 * @first_source: original source of first included packet
 * @first_orig_dest: original destinal of first included packet
 * @first_crc: checksum of first included packet
 * @first_ttvn: tt-version number of first included packet
 * @second_ttl: ttl of second packet
 * @second_dest: second receiver of this coded packet
 * @second_source: original source of second included packet
 * @second_orig_dest: original destination of second included packet
 * @second_crc: checksum of second included packet
 * @second_ttvn: tt version number of second included packet
 * @coded_len: length of network coded part of the payload
 */
struct batadv_coded_packet {
	uint8_t  packet_type;
	uint8_t  version;  /* batman version field */
	uint8_t  ttl;
	uint8_t  first_ttvn;
	/* uint8_t  first_dest[ETH_ALEN]; - saved in mac header destination */
	uint8_t  first_source[ETH_ALEN];
	uint8_t  first_orig_dest[ETH_ALEN];
	__be32   first_crc;
	uint8_t  second_ttl;
	uint8_t  second_ttvn;
	uint8_t  second_dest[ETH_ALEN];
	uint8_t  second_source[ETH_ALEN];
	uint8_t  second_orig_dest[ETH_ALEN];
	__be32   second_crc;
	__be16   coded_len;
};

#pragma pack()

/**
 * struct batadv_unicast_tvlv - generic unicast packet with tvlv payload
 * @packet_type: batman-adv packet type, part of the general header
 * @version: batman-adv protocol version, part of the genereal header
 * @ttl: time to live for this packet, part of the genereal header
 * @reserved: reserved field (for packet alignment)
 * @src: address of the source
 * @dst: address of the destination
 * @tvlv_len: length of tvlv data following the unicast tvlv header
 * @align: 2 bytes to align the header to a 4 byte boundry
 */
struct batadv_unicast_tvlv_packet {
	uint8_t  packet_type;
	uint8_t  version;  /* batman version field */
	uint8_t  ttl;
	uint8_t  reserved;
	uint8_t  dst[ETH_ALEN];
	uint8_t  src[ETH_ALEN];
	__be16   tvlv_len;
	uint16_t align;
};

/**
 * struct batadv_tvlv_hdr - base tvlv header struct
 * @type: tvlv container type (see batadv_tvlv_type)
 * @version: tvlv container version
 * @len: tvlv container length
 */
struct batadv_tvlv_hdr {
	uint8_t type;
	uint8_t version;
	__be16  len;
};

/**
 * struct batadv_tvlv_gateway_data - gateway data propagated through gw tvlv
 *  container
 * @bandwidth_down: advertised uplink download bandwidth
 * @bandwidth_up: advertised uplink upload bandwidth
 */
struct batadv_tvlv_gateway_data {
	__be32 bandwidth_down;
	__be32 bandwidth_up;
};

/**
 * struct batadv_tvlv_tt_data - tt data propagated through the tt tvlv container
 * @flags: translation table flags (see batadv_tt_data_flags)
 * @ttvn: translation table version number
 * @vlan_num: number of announced VLANs. In the TVLV this struct is followed by
 *  one batadv_tvlv_tt_vlan_data object per announced vlan
 */
struct batadv_tvlv_tt_data {
	uint8_t flags;
	uint8_t ttvn;
	__be16  num_vlan;
};

/**
 * struct batadv_tvlv_tt_vlan_data - vlan specific tt data propagated through
 *  the tt tvlv container
 * @crc: crc32 checksum of the entries belonging to this vlan
 * @vid: vlan identifier
 * @reserved: unused, useful for alignment purposes
 */
struct batadv_tvlv_tt_vlan_data {
	__be32	crc;
	__be16	vid;
	uint16_t reserved;
};

/**
 * struct batadv_tvlv_tt_change - translation table diff data
 * @flags: status indicators concerning the non-mesh client (see
 *  batadv_tt_client_flags)
 * @reserved: reserved field - useful for alignment purposes only
 * @addr: mac address of non-mesh client that triggered this tt change
 * @vid: VLAN identifier
 */
struct batadv_tvlv_tt_change {
	uint8_t flags;
	uint8_t reserved[3];
	uint8_t addr[ETH_ALEN];
	__be16 vid;
};

/**
 * struct batadv_tvlv_roam_adv - roaming advertisement
 * @client: mac address of roaming client
 * @vid: VLAN identifier
 */
struct batadv_tvlv_roam_adv {
	uint8_t  client[ETH_ALEN];
	__be16 vid;
};

/**
 * struct batadv_tvlv_mcast_data - payload of a multicast tvlv
 * @flags: multicast flags announced by the orig node
 * @reserved: reserved field
 */
struct batadv_tvlv_mcast_data {
	uint8_t	flags;
	uint8_t reserved[3];
};

#endif /* _NET_BATMAN_ADV_PACKET_H_ */
