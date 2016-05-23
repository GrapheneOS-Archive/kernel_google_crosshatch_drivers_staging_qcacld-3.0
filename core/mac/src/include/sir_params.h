/*
 * Copyright (c) 2012-2016 The Linux Foundation. All rights reserved.
 *
 * Previously licensed under the ISC license by Qualcomm Atheros, Inc.
 *
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * This file was originally distributed by Qualcomm Atheros, Inc.
 * under proprietary terms before Copyright ownership was assigned
 * to the Linux Foundation.
 */

/*
 * This file sir_params.h contains the common parameter definitions, which
 * are not dependent on threadX API. These can be used by all Firmware
 * modules.
 *
 * Author:      Sandesh Goel
 * Date:        04/13/2002
 * History:-
 * Date            Modified by    Modification Information
 * --------------------------------------------------------------------
 */

#ifndef __SIRPARAMS_H
#define __SIRPARAMS_H

#include "sir_types.h"

/* defines for WPS config states */
#define       SAP_WPS_DISABLED             0
#define       SAP_WPS_ENABLED_UNCONFIGURED 1
#define       SAP_WPS_ENABLED_CONFIGURED   2


/* Firmware wide constants */

#define SIR_MAX_PACKET_SIZE     512
#define SIR_MAX_NUM_CHANNELS    64
#define SIR_MAX_NUM_STA_IN_IBSS 16
#define SIR_ESE_MAX_MEAS_IE_REQS   8

typedef enum {
	PHY_SINGLE_CHANNEL_CENTERED = 0,        /* 20MHz IF bandwidth centered on IF carrier */
	PHY_DOUBLE_CHANNEL_LOW_PRIMARY = 1,     /* 40MHz IF bandwidth with lower 20MHz supporting the primary channel */
	PHY_DOUBLE_CHANNEL_HIGH_PRIMARY = 3,    /* 40MHz IF bandwidth with higher 20MHz supporting the primary channel */
	PHY_QUADRUPLE_CHANNEL_20MHZ_LOW_40MHZ_CENTERED = 4,     /* 20/40MHZ offset LOW 40/80MHZ offset CENTERED */
	PHY_QUADRUPLE_CHANNEL_20MHZ_CENTERED_40MHZ_CENTERED = 5,        /* 20/40MHZ offset CENTERED 40/80MHZ offset CENTERED */
	PHY_QUADRUPLE_CHANNEL_20MHZ_HIGH_40MHZ_CENTERED = 6,    /* 20/40MHZ offset HIGH 40/80MHZ offset CENTERED */
	PHY_QUADRUPLE_CHANNEL_20MHZ_LOW_40MHZ_LOW = 7,  /* 20/40MHZ offset LOW 40/80MHZ offset LOW */
	PHY_QUADRUPLE_CHANNEL_20MHZ_HIGH_40MHZ_LOW = 8, /* 20/40MHZ offset HIGH 40/80MHZ offset LOW */
	PHY_QUADRUPLE_CHANNEL_20MHZ_LOW_40MHZ_HIGH = 9, /* 20/40MHZ offset LOW 40/80MHZ offset HIGH */
	PHY_QUADRUPLE_CHANNEL_20MHZ_HIGH_40MHZ_HIGH = 10,       /* 20/40MHZ offset-HIGH 40/80MHZ offset HIGH */
	PHY_CHANNEL_BONDING_STATE_MAX = 11
} ePhyChanBondState;

#define MAX_BONDED_CHANNELS 8

typedef enum {
	MCC = 0,
	P2P = 1,
	DOT11AC = 2,
	SLM_SESSIONIZATION = 3,
	DOT11AC_OPMODE = 4,
	SAP32STA = 5,
	TDLS = 6,
	P2P_GO_NOA_DECOUPLE_INIT_SCAN = 7,
	WLANACTIVE_OFFLOAD = 8,
#ifdef FEATURE_WLAN_EXTSCAN
	EXTENDED_SCAN = 9,
#endif
#ifdef FEATURE_WLAN_SCAN_PNO
	PNO = 10,
#endif
#ifdef WLAN_FEATURE_NAN
	NAN = 11,
#endif
	RTT = 12,
	WOW = 22,
	WLAN_ROAM_SCAN_OFFLOAD = 23,
	IBSS_HEARTBEAT_OFFLOAD = 26,
	WLAN_PERIODIC_TX_PTRN = 28,
#ifdef FEATURE_WLAN_TDLS
	ADVANCE_TDLS = 29,
	TDLS_OFF_CHANNEL = 30,
#endif

	/* MAX_FEATURE_SUPPORTED = 128 */
} placeHolderInCapBitmap;

typedef enum eSriLinkState {
	eSIR_LINK_IDLE_STATE = 0,
	eSIR_LINK_PREASSOC_STATE = 1,
	eSIR_LINK_POSTASSOC_STATE = 2,
	eSIR_LINK_AP_STATE = 3,
	eSIR_LINK_IBSS_STATE = 4,
	eSIR_LINK_DOWN_STATE = 5,
} tSirLinkState;

/* / Message queue structure used across Sirius project. */
/* / NOTE: this structure should be multiples of a word size (4bytes) */
/* / as this is used in tx_queue where it expects to be multiples of 4 bytes. */
typedef struct sSirMsgQ {
	uint16_t type;
	/*
	 * This field can be used as sequence number/dialog token for matching
	 * requests and responses.
	 */
	uint16_t reserved;
	/**
	 * Based on the type either a bodyptr pointer into
	 * memory or bodyval as a 32 bit data is used.
	 * bodyptr: is always a freeable pointer, one should always
	 * make sure that bodyptr is always freeable.
	 *
	 * Messages should use either bodyptr or bodyval; not both !!!.
	 */
	void *bodyptr;
	uint32_t bodyval;

	/*
	 * Some messages provide a callback function.  The function signature
	 * must be agreed upon between the two entities exchanging the message
	 */
	void *callback;

} tSirMsgQ, *tpSirMsgQ;

/* / Mailbox Message Structure Define */
typedef struct sSirMbMsg {
	uint16_t type;

	/**
	 * This length includes 4 bytes of header, that is,
	 * 2 bytes type + 2 bytes msgLen + n*4 bytes of data.
	 * This field is byte length.
	 */
	uint16_t msgLen;

	/**
	 * This is the first data word in the mailbox message.
	 * It is followed by n words of data.
	 * NOTE: data[1] is not a place holder to store data
	 * instead to dereference the message body.
	 */
	uint32_t data[1];
} tSirMbMsg, *tpSirMbMsg;

/* / Mailbox Message Structure for P2P */
typedef struct sSirMbMsgP2p {
	uint16_t type;

	/**
	 * This length includes 4 bytes of header, that is,
	 * 2 bytes type + 2 bytes msgLen + n*4 bytes of data.
	 * This field is byte length.
	 */
	uint16_t msgLen;

	uint8_t sessionId;
	uint8_t noack;
	uint16_t wait;
	uint16_t channel_freq;
	uint32_t scan_id;

	/**
	 * This is the first data word in the mailbox message.
	 * It is followed by n words of data.
	 * NOTE: data[1] is not a place holder to store data
	 * instead to dereference the message body.
	 */
	uint32_t data[1];
} tSirMbMsgP2p, *tpSirMbMsgP2p;

/* ******************************************* *
*                                             *
*         SIRIUS MESSAGE TYPES                *
*                                             *
* ******************************************* */

/*
 * The following message types have bounds defined for each module for
 * inter thread/module communications.
 * Each module will get 256 message types in total.
 * Note that message type definitions for mailbox messages for
 * communication with Host are in wni_api.h file.
 *
 * Any addition/deletion to this message list should also be
 * reflected in the halUtil_getMsgString() routine.
 */

/* HAL message types */
#define SIR_HAL_MSG_TYPES_BEGIN            (SIR_HAL_MODULE_ID << 8)
#define SIR_HAL_ITC_MSG_TYPES_BEGIN        (SIR_HAL_MSG_TYPES_BEGIN+0x20)
#define SIR_HAL_RADAR_DETECTED_IND         SIR_HAL_ITC_MSG_TYPES_BEGIN

/*
 * New Taurus related messages
 */
#define SIR_HAL_ADD_STA_REQ                (SIR_HAL_ITC_MSG_TYPES_BEGIN + 1)
#define SIR_HAL_ADD_STA_RSP                (SIR_HAL_ITC_MSG_TYPES_BEGIN + 2)
#define SIR_HAL_DELETE_STA_REQ             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 3)
#define SIR_HAL_DELETE_STA_RSP             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 4)
#define SIR_HAL_ADD_BSS_REQ                (SIR_HAL_ITC_MSG_TYPES_BEGIN + 5)
#define SIR_HAL_ADD_BSS_RSP                (SIR_HAL_ITC_MSG_TYPES_BEGIN + 6)
#define SIR_HAL_DELETE_BSS_REQ             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 7)
#define SIR_HAL_DELETE_BSS_RSP             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 8)
#define SIR_HAL_INIT_SCAN_REQ              (SIR_HAL_ITC_MSG_TYPES_BEGIN + 9)
#define SIR_HAL_INIT_SCAN_RSP              (SIR_HAL_ITC_MSG_TYPES_BEGIN + 10)
#define SIR_HAL_START_SCAN_REQ             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 11)
#define SIR_HAL_START_SCAN_RSP             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 12)
#define SIR_HAL_END_SCAN_REQ               (SIR_HAL_ITC_MSG_TYPES_BEGIN + 13)
#define SIR_HAL_END_SCAN_RSP               (SIR_HAL_ITC_MSG_TYPES_BEGIN + 14)
#define SIR_HAL_FINISH_SCAN_REQ            (SIR_HAL_ITC_MSG_TYPES_BEGIN + 15)
#define SIR_HAL_FINISH_SCAN_RSP            (SIR_HAL_ITC_MSG_TYPES_BEGIN + 16)
#define SIR_HAL_SEND_BEACON_REQ            (SIR_HAL_ITC_MSG_TYPES_BEGIN + 17)

#define SIR_HAL_SET_BSSKEY_REQ             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 18)
#define SIR_HAL_SET_BSSKEY_RSP             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 19)
#define SIR_HAL_SET_STAKEY_REQ             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 20)
#define SIR_HAL_SET_STAKEY_RSP             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 21)
#define SIR_HAL_UPDATE_EDCA_PROFILE_IND    (SIR_HAL_ITC_MSG_TYPES_BEGIN + 22)

#define SIR_HAL_UPDATE_BEACON_IND          (SIR_HAL_ITC_MSG_TYPES_BEGIN + 23)
#define SIR_HAL_UPDATE_CF_IND              (SIR_HAL_ITC_MSG_TYPES_BEGIN + 24)
#define SIR_HAL_CHNL_SWITCH_REQ            (SIR_HAL_ITC_MSG_TYPES_BEGIN + 25)
#define SIR_HAL_ADD_TS_REQ                 (SIR_HAL_ITC_MSG_TYPES_BEGIN + 26)
#define SIR_HAL_DEL_TS_REQ                 (SIR_HAL_ITC_MSG_TYPES_BEGIN + 27)

#define SIR_HAL_MISSED_BEACON_IND          (SIR_HAL_ITC_MSG_TYPES_BEGIN + 34)

#define SIR_HAL_SWITCH_CHANNEL_RSP         (SIR_HAL_ITC_MSG_TYPES_BEGIN + 35)
#define SIR_HAL_PWR_SAVE_CFG               (SIR_HAL_ITC_MSG_TYPES_BEGIN + 36)

#define SIR_HAL_REGISTER_PE_CALLBACK       (SIR_HAL_ITC_MSG_TYPES_BEGIN + 37)

#define SIR_HAL_IBSS_STA_ADD               (SIR_HAL_ITC_MSG_TYPES_BEGIN + 43)
#define SIR_HAL_TIMER_ADJUST_ADAPTIVE_THRESHOLD_IND \
					   (SIR_HAL_ITC_MSG_TYPES_BEGIN + 44)
#define SIR_HAL_SET_LINK_STATE             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 45)

/*
 * (SIR_HAL_ITC_MSG_TYPES_BEGIN + 46) to
 * (SIR_HAL_ITC_MSG_TYPES_BEGIN + 57) are unused
 */

#define SIR_HAL_SET_STA_BCASTKEY_REQ       (SIR_HAL_ITC_MSG_TYPES_BEGIN + 58)
#define SIR_HAL_SET_STA_BCASTKEY_RSP       (SIR_HAL_ITC_MSG_TYPES_BEGIN + 59)
#define SIR_HAL_ADD_TS_RSP                 (SIR_HAL_ITC_MSG_TYPES_BEGIN + 60)
#define SIR_HAL_DPU_MIC_ERROR              (SIR_HAL_ITC_MSG_TYPES_BEGIN + 61)
#define SIR_HAL_TIMER_CHIP_MONITOR_TIMEOUT (SIR_HAL_ITC_MSG_TYPES_BEGIN + 63)
#define SIR_HAL_TIMER_TRAFFIC_ACTIVITY_REQ (SIR_HAL_ITC_MSG_TYPES_BEGIN + 64)
#define SIR_HAL_TIMER_ADC_RSSI_STATS       (SIR_HAL_ITC_MSG_TYPES_BEGIN + 65)
/* (SIR_HAL_ITC_MSG_TYPES_BEGIN + 66) is unused */
#define SIR_HAL_SET_MIMOPS_REQ             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 67)
#define SIR_HAL_SET_MIMOPS_RSP             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 68)
#define SIR_HAL_SYS_READY_IND              (SIR_HAL_ITC_MSG_TYPES_BEGIN + 69)
#define SIR_HAL_SET_TX_POWER_REQ           (SIR_HAL_ITC_MSG_TYPES_BEGIN + 70)
#define SIR_HAL_SET_TX_POWER_RSP           (SIR_HAL_ITC_MSG_TYPES_BEGIN + 71)
#define SIR_HAL_GET_TX_POWER_REQ           (SIR_HAL_ITC_MSG_TYPES_BEGIN + 72)
#define SIR_HAL_GET_TX_POWER_RSP           (SIR_HAL_ITC_MSG_TYPES_BEGIN + 73)
#define SIR_HAL_GET_NOISE_RSP              (SIR_HAL_ITC_MSG_TYPES_BEGIN + 74)

/* Messages to support transmit_halt and transmit_resume */
#define SIR_HAL_TRANSMISSION_CONTROL_IND   (SIR_HAL_ITC_MSG_TYPES_BEGIN + 75)

#define SIR_HAL_LOW_RSSI_IND               (SIR_HAL_ITC_MSG_TYPES_BEGIN + 80)
#define SIR_HAL_BEACON_FILTER_IND          (SIR_HAL_ITC_MSG_TYPES_BEGIN + 81)
/* / PE <-> HAL WOWL messages */
#define SIR_HAL_WOW_ADD_PTRN               (SIR_HAL_ITC_MSG_TYPES_BEGIN + 82)
#define SIR_HAL_WOW_DEL_PTRN               (SIR_HAL_ITC_MSG_TYPES_BEGIN + 83)
#define SIR_HAL_WOWL_ENTER_REQ             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 84)
#define SIR_HAL_WOWL_ENTER_RSP             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 85)
#define SIR_HAL_WOWL_EXIT_REQ              (SIR_HAL_ITC_MSG_TYPES_BEGIN + 86)
#define SIR_HAL_WOWL_EXIT_RSP              (SIR_HAL_ITC_MSG_TYPES_BEGIN + 87)
/* / PE <-> HAL statistics messages */
#define SIR_HAL_GET_STATISTICS_REQ         (SIR_HAL_ITC_MSG_TYPES_BEGIN + 88)
#define SIR_HAL_GET_STATISTICS_RSP         (SIR_HAL_ITC_MSG_TYPES_BEGIN + 89)
#define SIR_HAL_SET_KEY_DONE               (SIR_HAL_ITC_MSG_TYPES_BEGIN + 90)

/* / PE <-> HAL BTC messages */
#define SIR_HAL_BTC_SET_CFG                (SIR_HAL_ITC_MSG_TYPES_BEGIN + 91)
/* (SIR_HAL_ITC_MSG_TYPES_BEGIN + 92) is unused */
#define SIR_HAL_HANDLE_FW_MBOX_RSP         (SIR_HAL_ITC_MSG_TYPES_BEGIN + 93)
#define SIR_HAL_SEND_PROBE_RSP_TMPL        (SIR_HAL_ITC_MSG_TYPES_BEGIN + 94)

/* PE <-> HAL addr2 mismatch message */
#define SIR_LIM_ADDR2_MISS_IND             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 95)
#ifdef FEATURE_OEM_DATA_SUPPORT
/* PE <-> HAL OEM_DATA RELATED MESSAGES */
#define SIR_HAL_START_OEM_DATA_REQ         (SIR_HAL_ITC_MSG_TYPES_BEGIN + 96)
#define SIR_HAL_START_OEM_DATA_RSP         (SIR_HAL_ITC_MSG_TYPES_BEGIN + 97)
#endif

#define SIR_HAL_SET_MAX_TX_POWER_REQ       (SIR_HAL_ITC_MSG_TYPES_BEGIN + 98)
#define SIR_HAL_SET_MAX_TX_POWER_RSP       (SIR_HAL_ITC_MSG_TYPES_BEGIN + 99)

/* / PE <-> HAL Host Offload message */
#define SIR_HAL_SET_HOST_OFFLOAD           (SIR_HAL_ITC_MSG_TYPES_BEGIN + 100)

#define SIR_HAL_ADD_STA_SELF_REQ           (SIR_HAL_ITC_MSG_TYPES_BEGIN + 101)
#define SIR_HAL_ADD_STA_SELF_RSP           (SIR_HAL_ITC_MSG_TYPES_BEGIN + 102)
#define SIR_HAL_DEL_STA_SELF_REQ           (SIR_HAL_ITC_MSG_TYPES_BEGIN + 103)
#define SIR_HAL_DEL_STA_SELF_RSP           (SIR_HAL_ITC_MSG_TYPES_BEGIN + 104)

#define SIR_HAL_CFG_RXP_FILTER_REQ         (SIR_HAL_ITC_MSG_TYPES_BEGIN + 106)

#define SIR_HAL_AGGR_ADD_TS_REQ            (SIR_HAL_ITC_MSG_TYPES_BEGIN + 107)
#define SIR_HAL_AGGR_ADD_TS_RSP            (SIR_HAL_ITC_MSG_TYPES_BEGIN + 108)
#define SIR_HAL_AGGR_QOS_REQ               (SIR_HAL_ITC_MSG_TYPES_BEGIN + 109)
#define SIR_HAL_AGGR_QOS_RSP               (SIR_HAL_ITC_MSG_TYPES_BEGIN + 110)

/* P2P <-> HAL P2P msg */
#define SIR_HAL_SET_P2P_GO_NOA_REQ         (SIR_HAL_ITC_MSG_TYPES_BEGIN + 111)
#define SIR_HAL_P2P_NOA_ATTR_IND           (SIR_HAL_ITC_MSG_TYPES_BEGIN + 112)
#define SIR_HAL_P2P_NOA_START_IND          (SIR_HAL_ITC_MSG_TYPES_BEGIN + 113)

#define SIR_HAL_SET_LINK_STATE_RSP         (SIR_HAL_ITC_MSG_TYPES_BEGIN + 114)

#define SIR_HAL_WLAN_SUSPEND_IND           (SIR_HAL_ITC_MSG_TYPES_BEGIN + 115)
#define SIR_HAL_WLAN_RESUME_REQ            (SIR_HAL_ITC_MSG_TYPES_BEGIN + 116)

/* / PE <-> HAL Keep Alive message */
#define SIR_HAL_SET_KEEP_ALIVE             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 117)

#ifdef WLAN_NS_OFFLOAD
#define SIR_HAL_SET_NS_OFFLOAD             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 118)
#endif /* WLAN_NS_OFFLOAD */

#ifdef FEATURE_WLAN_SCAN_PNO
#define SIR_HAL_SET_PNO_REQ                (SIR_HAL_ITC_MSG_TYPES_BEGIN + 119)
#endif /* FEATURE_WLAN_SCAN_PNO */

#define SIR_HAL_SOC_ANTENNA_MODE_REQ        (SIR_HAL_ITC_MSG_TYPES_BEGIN + 120)
#define SIR_HAL_SOC_ANTENNA_MODE_RESP       (SIR_HAL_ITC_MSG_TYPES_BEGIN + 121)

/* (SIR_HAL_ITC_MSG_TYPES_BEGIN + 122) is unused */

#ifdef WLAN_FEATURE_PACKET_FILTERING
#define SIR_HAL_8023_MULTICAST_LIST_REQ \
					   (SIR_HAL_ITC_MSG_TYPES_BEGIN + 123)
#define SIR_HAL_RECEIVE_FILTER_SET_FILTER_REQ \
					   (SIR_HAL_ITC_MSG_TYPES_BEGIN + 124)
#define SIR_HAL_PACKET_COALESCING_FILTER_MATCH_COUNT_REQ \
					   (SIR_HAL_ITC_MSG_TYPES_BEGIN + 125)
#define SIR_HAL_PACKET_COALESCING_FILTER_MATCH_COUNT_RSP \
					   (SIR_HAL_ITC_MSG_TYPES_BEGIN + 126)
#define SIR_HAL_RECEIVE_FILTER_CLEAR_FILTER_REQ \
					   (SIR_HAL_ITC_MSG_TYPES_BEGIN + 127)
#endif /* WLAN_FEATURE_PACKET_FILTERING */

/* (SIR_HAL_ITC_MSG_TYPES_BEGIN + 128) is unused */

#ifdef WLAN_FEATURE_GTK_OFFLOAD
#define SIR_HAL_GTK_OFFLOAD_REQ            (SIR_HAL_ITC_MSG_TYPES_BEGIN + 129)
#define SIR_HAL_GTK_OFFLOAD_GETINFO_REQ    (SIR_HAL_ITC_MSG_TYPES_BEGIN + 130)
#define SIR_HAL_GTK_OFFLOAD_GETINFO_RSP    (SIR_HAL_ITC_MSG_TYPES_BEGIN + 131)
#endif /* WLAN_FEATURE_GTK_OFFLOAD */

#ifdef FEATURE_WLAN_ESE
#define SIR_HAL_TSM_STATS_REQ              (SIR_HAL_ITC_MSG_TYPES_BEGIN + 132)
#define SIR_HAL_TSM_STATS_RSP              (SIR_HAL_ITC_MSG_TYPES_BEGIN + 133)
#endif

#define SIR_HAL_SET_TM_LEVEL_REQ           (SIR_HAL_ITC_MSG_TYPES_BEGIN + 134)

#define SIR_HAL_UPDATE_OP_MODE             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 135)

#ifdef FEATURE_WLAN_TDLS
/* / PE <-> HAL TDLS messages */
#define SIR_HAL_TDLS_LINK_ESTABLISH        (SIR_HAL_ITC_MSG_TYPES_BEGIN + 136)
#define SIR_HAL_TDLS_LINK_TEARDOWN         (SIR_HAL_ITC_MSG_TYPES_BEGIN + 137)
#endif
#define SIR_HAL_ROAM_SCAN_OFFLOAD_REQ      (SIR_HAL_ITC_MSG_TYPES_BEGIN + 138)

#define SIR_HAL_TRAFFIC_STATS_IND          (SIR_HAL_ITC_MSG_TYPES_BEGIN + 141)

#ifdef WLAN_FEATURE_11W
#define SIR_HAL_EXCLUDE_UNENCRYPTED_IND    (SIR_HAL_ITC_MSG_TYPES_BEGIN + 142)
#endif
#ifdef FEATURE_WLAN_TDLS
/* / PE <-> HAL TDLS messages */
#define SIR_HAL_TDLS_LINK_ESTABLISH_REQ     (SIR_HAL_ITC_MSG_TYPES_BEGIN + 143)
#define SIR_HAL_TDLS_LINK_ESTABLISH_REQ_RSP (SIR_HAL_ITC_MSG_TYPES_BEGIN + 144)
#define SIR_HAL_TDLS_IND                    (SIR_HAL_ITC_MSG_TYPES_BEGIN + 145)
#endif

#define SIR_HAL_STOP_SCAN_OFFLOAD_REQ      (SIR_HAL_ITC_MSG_TYPES_BEGIN + 146)
#define SIR_HAL_RX_SCAN_EVENT              (SIR_HAL_ITC_MSG_TYPES_BEGIN + 147)
#define SIR_HAL_DHCP_START_IND             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 148)
#define SIR_HAL_DHCP_STOP_IND              (SIR_HAL_ITC_MSG_TYPES_BEGIN + 149)
#define SIR_HAL_IBSS_PEER_INACTIVITY_IND   (SIR_HAL_ITC_MSG_TYPES_BEGIN + 150)

#define SIR_HAL_LPHB_CONF_IND              (SIR_HAL_ITC_MSG_TYPES_BEGIN + 151)

#define SIR_HAL_ADD_PERIODIC_TX_PTRN_IND   (SIR_HAL_ITC_MSG_TYPES_BEGIN + 152)
#define SIR_HAL_DEL_PERIODIC_TX_PTRN_IND   (SIR_HAL_ITC_MSG_TYPES_BEGIN + 153)

/* Messages between 156 to 157 are not used */
#define SIR_HAL_PDEV_DUAL_MAC_CFG_REQ      (SIR_HAL_ITC_MSG_TYPES_BEGIN + 154)
#define SIR_HAL_PDEV_MAC_CFG_RESP          (SIR_HAL_ITC_MSG_TYPES_BEGIN + 155)

/* For IBSS peer info related messages */
#define SIR_HAL_IBSS_PEER_INFO_REQ         (SIR_HAL_ITC_MSG_TYPES_BEGIN + 158)

#define SIR_HAL_RATE_UPDATE_IND            (SIR_HAL_ITC_MSG_TYPES_BEGIN + 159)

#define SIR_HAL_FLUSH_LOG_TO_FW            (SIR_HAL_ITC_MSG_TYPES_BEGIN + 160)

#define SIR_HAL_PDEV_SET_PCL_TO_FW         (SIR_HAL_ITC_MSG_TYPES_BEGIN + 161)

/* 162 unused */

#define SIR_HAL_CLI_SET_CMD                (SIR_HAL_ITC_MSG_TYPES_BEGIN + 163)
#ifndef REMOVE_PKT_LOG
#define SIR_HAL_PKTLOG_ENABLE_REQ          (SIR_HAL_ITC_MSG_TYPES_BEGIN + 164)
#endif
#ifdef FEATURE_WLAN_SCAN_PNO
#define SIR_HAL_SME_SCAN_CACHE_UPDATED     (SIR_HAL_ITC_MSG_TYPES_BEGIN + 165)
#endif
#define SIR_HAL_START_SCAN_OFFLOAD_REQ     (SIR_HAL_ITC_MSG_TYPES_BEGIN + 166)
#define SIR_HAL_UPDATE_CHAN_LIST_REQ       (SIR_HAL_ITC_MSG_TYPES_BEGIN + 167)
#define SIR_CSA_OFFLOAD_EVENT               (SIR_HAL_ITC_MSG_TYPES_BEGIN + 169)

#define SIR_HAL_SET_MAX_TX_POWER_PER_BAND_REQ \
					    (SIR_HAL_ITC_MSG_TYPES_BEGIN + 170)

#define SIR_HAL_TX_FAIL_MONITOR_IND         (SIR_HAL_ITC_MSG_TYPES_BEGIN + 171)

#define SIR_HAL_UPDATE_MEMBERSHIP           (SIR_HAL_ITC_MSG_TYPES_BEGIN + 172)
#define SIR_HAL_UPDATE_USERPOS              (SIR_HAL_ITC_MSG_TYPES_BEGIN + 173)

#ifdef FEATURE_WLAN_TDLS
#define SIR_HAL_UPDATE_FW_TDLS_STATE        (SIR_HAL_ITC_MSG_TYPES_BEGIN + 174)
#define SIR_HAL_UPDATE_TDLS_PEER_STATE      (SIR_HAL_ITC_MSG_TYPES_BEGIN + 175)
#define SIR_HAL_TDLS_SHOULD_DISCOVER        (SIR_HAL_ITC_MSG_TYPES_BEGIN + 176)
#define SIR_HAL_TDLS_SHOULD_TEARDOWN        (SIR_HAL_ITC_MSG_TYPES_BEGIN + 177)
#define SIR_HAL_TDLS_PEER_DISCONNECTED      (SIR_HAL_ITC_MSG_TYPES_BEGIN + 178)
#endif

/* Handling of beacon tx indication from FW */
#define SIR_HAL_BEACON_TX_SUCCESS_IND       (SIR_HAL_ITC_MSG_TYPES_BEGIN + 179)
#define SIR_HAL_DFS_RADAR_IND               (SIR_HAL_ITC_MSG_TYPES_BEGIN + 180)

#define SIR_HAL_IBSS_CESIUM_ENABLE_IND      (SIR_HAL_ITC_MSG_TYPES_BEGIN + 181)

#define SIR_HAL_RMC_ENABLE_IND              (SIR_HAL_ITC_MSG_TYPES_BEGIN + 182)
#define SIR_HAL_RMC_DISABLE_IND             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 183)
#define SIR_HAL_RMC_ACTION_PERIOD_IND       (SIR_HAL_ITC_MSG_TYPES_BEGIN + 184)
#define SIR_HAL_INIT_THERMAL_INFO_CMD       (SIR_HAL_ITC_MSG_TYPES_BEGIN + 185)
#define SIR_HAL_SET_THERMAL_LEVEL           (SIR_HAL_ITC_MSG_TYPES_BEGIN + 186)

#ifdef FEATURE_WLAN_ESE
#define SIR_HAL_SET_PLM_REQ                 (SIR_HAL_ITC_MSG_TYPES_BEGIN + 187)
#endif

#define SIR_HAL_SET_TX_POWER_LIMIT          (SIR_HAL_ITC_MSG_TYPES_BEGIN + 188)
#define SIR_HAL_SET_SAP_INTRABSS_DIS        (SIR_HAL_ITC_MSG_TYPES_BEGIN + 189)

#define SIR_HAL_MODEM_POWER_STATE_IND       (SIR_HAL_ITC_MSG_TYPES_BEGIN + 190)

#define SIR_HAL_DISASSOC_TX_COMP            (SIR_HAL_ITC_MSG_TYPES_BEGIN + 191)
#define SIR_HAL_DEAUTH_TX_COMP              (SIR_HAL_ITC_MSG_TYPES_BEGIN + 192)

#define SIR_HAL_UPDATE_RX_NSS               (SIR_HAL_ITC_MSG_TYPES_BEGIN + 193)

#ifdef WLAN_FEATURE_STATS_EXT
#define SIR_HAL_STATS_EXT_REQUEST           (SIR_HAL_ITC_MSG_TYPES_BEGIN + 194)
#define SIR_HAL_STATS_EXT_EVENT             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 195)
#endif /* WLAN_FEATURE_STATS_EXT */

#define SIR_HAL_HIDE_SSID_VDEV_RESTART      (SIR_HAL_ITC_MSG_TYPES_BEGIN + 196)

#define SIR_HAL_GET_LINK_SPEED              (SIR_HAL_ITC_MSG_TYPES_BEGIN + 197)

#ifdef FEATURE_WLAN_EXTSCAN
#define SIR_HAL_EXTSCAN_GET_CAPABILITIES_REQ (SIR_HAL_ITC_MSG_TYPES_BEGIN + 198)
#define SIR_HAL_EXTSCAN_START_REQ            (SIR_HAL_ITC_MSG_TYPES_BEGIN + 199)
#define SIR_HAL_EXTSCAN_STOP_REQ             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 200)
#define SIR_HAL_EXTSCAN_SET_BSS_HOTLIST_REQ  (SIR_HAL_ITC_MSG_TYPES_BEGIN + 201)
#define SIR_HAL_EXTSCAN_RESET_BSS_HOTLIST_REQ \
					     (SIR_HAL_ITC_MSG_TYPES_BEGIN + 202)
#define SIR_HAL_EXTSCAN_SET_SIGNF_CHANGE_REQ (SIR_HAL_ITC_MSG_TYPES_BEGIN + 203)
#define SIR_HAL_EXTSCAN_RESET_SIGNF_CHANGE_REQ \
					     (SIR_HAL_ITC_MSG_TYPES_BEGIN + 204)
#define SIR_HAL_EXTSCAN_GET_CACHED_RESULTS_REQ \
					     (SIR_HAL_ITC_MSG_TYPES_BEGIN + 205)
#endif /* FEATURE_WLAN_EXTSCAN */

#ifdef FEATURE_WLAN_CH_AVOID
#define SIR_HAL_CH_AVOID_UPDATE_REQ          (SIR_HAL_ITC_MSG_TYPES_BEGIN + 206)
#endif

#ifdef WLAN_FEATURE_LINK_LAYER_STATS
#define SIR_HAL_LL_STATS_CLEAR_REQ           (SIR_HAL_ITC_MSG_TYPES_BEGIN + 207)
#define SIR_HAL_LL_STATS_SET_REQ             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 208)
#define SIR_HAL_LL_STATS_GET_REQ             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 209)
#define SIR_HAL_LL_STATS_RESULTS_RSP         (SIR_HAL_ITC_MSG_TYPES_BEGIN + 210)
#endif /* WLAN_FEATURE_LINK_LAYER_STATS */

#ifdef WLAN_FEATURE_ROAM_OFFLOAD
#define SIR_HAL_ROAM_OFFLOAD_SYNCH_CNF       (SIR_HAL_ITC_MSG_TYPES_BEGIN + 211)
#endif
#ifdef WLAN_FEATURE_NAN
#define SIR_HAL_NAN_REQUEST                  (SIR_HAL_ITC_MSG_TYPES_BEGIN + 212)
#endif /* WLAN_FEATURE_NAN */

#ifdef FEATURE_WLAN_AUTO_SHUTDOWN
#define SIR_HAL_SET_AUTO_SHUTDOWN_TIMER_REQ  (SIR_HAL_ITC_MSG_TYPES_BEGIN + 213)
#endif

#define SIR_HAL_SET_BASE_MACADDR_IND         (SIR_HAL_ITC_MSG_TYPES_BEGIN + 214)

#define SIR_HAL_UNIT_TEST_CMD                (SIR_HAL_ITC_MSG_TYPES_BEGIN + 215)

#define SIR_HAL_LINK_STATUS_GET_REQ          (SIR_HAL_ITC_MSG_TYPES_BEGIN + 216)

#ifdef WLAN_FEATURE_EXTWOW_SUPPORT
#define SIR_HAL_CONFIG_EXT_WOW               (SIR_HAL_ITC_MSG_TYPES_BEGIN + 217)
#define SIR_HAL_CONFIG_APP_TYPE1_PARAMS      (SIR_HAL_ITC_MSG_TYPES_BEGIN + 218)
#define SIR_HAL_CONFIG_APP_TYPE2_PARAMS      (SIR_HAL_ITC_MSG_TYPES_BEGIN + 219)
#endif

#define SIR_HAL_GET_TEMPERATURE_REQ          (SIR_HAL_ITC_MSG_TYPES_BEGIN + 220)
#define SIR_HAL_SET_SCAN_MAC_OUI_REQ         (SIR_HAL_ITC_MSG_TYPES_BEGIN + 221)
#ifdef DHCP_SERVER_OFFLOAD
#define SIR_HAL_SET_DHCP_SERVER_OFFLOAD      (SIR_HAL_ITC_MSG_TYPES_BEGIN + 222)
#endif /* DHCP_SERVER_OFFLOAD */
#define SIR_HAL_LED_FLASHING_REQ             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 223)
#define SIR_HAL_PROCESS_FW_EVENT             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 224)

#ifdef WLAN_FEATURE_ROAM_OFFLOAD
#define SIR_HAL_ROAM_OFFLOAD_SYNCH_IND       (SIR_HAL_ITC_MSG_TYPES_BEGIN + 225)
#define SIR_HAL_ROAM_OFFLOAD_SYNCH_FAIL      (SIR_HAL_ITC_MSG_TYPES_BEGIN + 226)
#define SIR_HAL_ROAM_INVOKE                  (SIR_HAL_ITC_MSG_TYPES_BEGIN + 227)
#endif

#ifdef FEATURE_WLAN_TDLS
#define SIR_HAL_TDLS_SET_OFFCHAN_MODE        (SIR_HAL_ITC_MSG_TYPES_BEGIN + 228)
#endif

#define SIR_HAL_SET_MAS                    (SIR_HAL_ITC_MSG_TYPES_BEGIN + 229)
#define SIR_HAL_SET_MIRACAST               (SIR_HAL_ITC_MSG_TYPES_BEGIN + 230)
#ifdef FEATURE_AP_MCC_CH_AVOIDANCE
#define SIR_HAL_UPDATE_Q2Q_IE_IND          (SIR_HAL_ITC_MSG_TYPES_BEGIN + 231)
#endif /* FEATURE_AP_MCC_CH_AVOIDANCE */
#define SIR_HAL_CONFIG_STATS_FACTOR        (SIR_HAL_ITC_MSG_TYPES_BEGIN + 232)
#define SIR_HAL_CONFIG_GUARD_TIME          (SIR_HAL_ITC_MSG_TYPES_BEGIN + 233)
#define SIR_HAL_IPA_OFFLOAD_ENABLE_DISABLE (SIR_HAL_ITC_MSG_TYPES_BEGIN + 234)

#define SIR_HAL_ENTER_PS_REQ                 (SIR_HAL_ITC_MSG_TYPES_BEGIN + 235)
#define SIR_HAL_EXIT_PS_REQ                  (SIR_HAL_ITC_MSG_TYPES_BEGIN + 236)
#define SIR_HAL_ENABLE_UAPSD_REQ             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 237)
#define SIR_HAL_DISABLE_UAPSD_REQ            (SIR_HAL_ITC_MSG_TYPES_BEGIN + 238)
#define SIR_HAL_GATEWAY_PARAM_UPDATE_REQ    (SIR_HAL_ITC_MSG_TYPES_BEGIN + 239)

#define SIR_HAL_RUNTIME_PM_SUSPEND_IND	(SIR_HAL_ITC_MSG_TYPES_BEGIN + 308)
#define SIR_HAL_RUNTIME_PM_RESUME_IND	(SIR_HAL_ITC_MSG_TYPES_BEGIN + 309)

#define SIR_HAL_SET_EPNO_LIST_REQ          (SIR_HAL_ITC_MSG_TYPES_BEGIN + 313)
#define SIR_HAL_SET_PASSPOINT_LIST_REQ     (SIR_HAL_ITC_MSG_TYPES_BEGIN + 316)
#define SIR_HAL_RESET_PASSPOINT_LIST_REQ   (SIR_HAL_ITC_MSG_TYPES_BEGIN + 317)
#define SIR_HAL_EXTSCAN_SET_SSID_HOTLIST_REQ (SIR_HAL_ITC_MSG_TYPES_BEGIN + 318)

#define SIR_HAL_OCB_SET_CONFIG_CMD          (SIR_HAL_ITC_MSG_TYPES_BEGIN + 319)
#define SIR_HAL_OCB_SET_UTC_TIME_CMD        (SIR_HAL_ITC_MSG_TYPES_BEGIN + 320)
#define SIR_HAL_OCB_START_TIMING_ADVERT_CMD (SIR_HAL_ITC_MSG_TYPES_BEGIN + 321)
#define SIR_HAL_OCB_STOP_TIMING_ADVERT_CMD  (SIR_HAL_ITC_MSG_TYPES_BEGIN + 322)
#define SIR_HAL_OCB_GET_TSF_TIMER_CMD       (SIR_HAL_ITC_MSG_TYPES_BEGIN + 323)
#define SIR_HAL_DCC_GET_STATS_CMD           (SIR_HAL_ITC_MSG_TYPES_BEGIN + 324)
#define SIR_HAL_DCC_CLEAR_STATS_CMD         (SIR_HAL_ITC_MSG_TYPES_BEGIN + 325)
#define SIR_HAL_DCC_UPDATE_NDL_CMD          (SIR_HAL_ITC_MSG_TYPES_BEGIN + 326)

#define SIR_HAL_FW_MEM_DUMP_REQ            (SIR_HAL_ITC_MSG_TYPES_BEGIN + 327)
#define SIR_HAL_START_STOP_LOGGING           (SIR_HAL_ITC_MSG_TYPES_BEGIN + 328)
#define SIR_HAL_PDEV_SET_HW_MODE             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 329)
#define SIR_HAL_PDEV_SET_HW_MODE_RESP        (SIR_HAL_ITC_MSG_TYPES_BEGIN + 330)
#define SIR_HAL_PDEV_HW_MODE_TRANS_IND       (SIR_HAL_ITC_MSG_TYPES_BEGIN + 331)

#define SIR_HAL_SET_RSSI_MONITOR_REQ        (SIR_HAL_ITC_MSG_TYPES_BEGIN + 333)
#define SIR_HAL_SET_IE_INFO                 (SIR_HAL_ITC_MSG_TYPES_BEGIN + 334)

#define SIR_HAL_LRO_CONFIG_CMD              (SIR_HAL_ITC_MSG_TYPES_BEGIN + 335)

#define SIR_HAL_SET_EGAP_CONF_PARAMS        (SIR_HAL_ITC_MSG_TYPES_BEGIN + 336)
#define SIR_HAL_HT40_OBSS_SCAN_IND          (SIR_HAL_ITC_MSG_TYPES_BEGIN + 337)

#define SIR_HAL_TSF_GPIO_PIN_REQ            (SIR_HAL_ITC_MSG_TYPES_BEGIN + 338)

#define SIR_HAL_ADD_BCN_FILTER_CMDID        (SIR_HAL_ITC_MSG_TYPES_BEGIN + 339)
#define SIR_HAL_REMOVE_BCN_FILTER_CMDID     (SIR_HAL_ITC_MSG_TYPES_BEGIN + 340)

#define SIR_HAL_BPF_GET_CAPABILITIES_REQ     (SIR_HAL_ITC_MSG_TYPES_BEGIN + 341)
#define SIR_HAL_BPF_SET_INSTRUCTIONS_REQ    (SIR_HAL_ITC_MSG_TYPES_BEGIN + 342)

#define SIR_HAL_SET_WISA_PARAMS             (SIR_HAL_ITC_MSG_TYPES_BEGIN + 343)
#define SIR_HAL_MSG_TYPES_END                (SIR_HAL_MSG_TYPES_BEGIN + 0x1FF)

/* CFG message types */
#define SIR_CFG_MSG_TYPES_BEGIN        (SIR_CFG_MODULE_ID << 8)
#define SIR_CFG_ITC_MSG_TYPES_BEGIN    (SIR_CFG_MSG_TYPES_BEGIN+0xB0)
#define SIR_CFG_PARAM_UPDATE_IND       (SIR_CFG_ITC_MSG_TYPES_BEGIN)
#define SIR_CFG_DOWNLOAD_COMPLETE_IND  (SIR_CFG_ITC_MSG_TYPES_BEGIN + 1)
#define SIR_CFG_MSG_TYPES_END          (SIR_CFG_MSG_TYPES_BEGIN+0xFF)

/* LIM message types */
#define SIR_LIM_MSG_TYPES_BEGIN        (SIR_LIM_MODULE_ID << 8)
#define SIR_LIM_ITC_MSG_TYPES_BEGIN    (SIR_LIM_MSG_TYPES_BEGIN+0xB0)

/* Messages to/from HAL */
/* Removed as part of moving HAL down to FW */

/* Message from ISR upon TFP retry interrupt */
#define SIR_LIM_RETRY_INTERRUPT_MSG        (SIR_LIM_ITC_MSG_TYPES_BEGIN + 3)
/* Message from BB Transport */
#define SIR_BB_XPORT_MGMT_MSG              (SIR_LIM_ITC_MSG_TYPES_BEGIN + 4)
/* UNUSED                                  SIR_LIM_ITC_MSG_TYPES_BEGIN + 6 */
/* Message from ISR upon SP's Invalid session key interrupt */
#define SIR_LIM_INV_KEY_INTERRUPT_MSG      (SIR_LIM_ITC_MSG_TYPES_BEGIN + 7)
/* Message from ISR upon SP's Invalid key ID interrupt */
#define SIR_LIM_KEY_ID_INTERRUPT_MSG       (SIR_LIM_ITC_MSG_TYPES_BEGIN + 8)
/* Message from ISR upon SP's Replay threshold reached interrupt */
#define SIR_LIM_REPLAY_THRES_INTERRUPT_MSG (SIR_LIM_ITC_MSG_TYPES_BEGIN + 9)
/* Message from HDD after the TD dummy packet is cleaned up */
#define SIR_LIM_TD_DUMMY_CALLBACK_MSG      (SIR_LIM_ITC_MSG_TYPES_BEGIN + 0xA)
/* Message from SCH when the STA is ready to be deleted */
#define SIR_LIM_SCH_CLEAN_MSG              (SIR_LIM_ITC_MSG_TYPES_BEGIN + 0xB)
/* Message from ISR upon Radar Detection */
#define SIR_LIM_RADAR_DETECT_IND           (SIR_LIM_ITC_MSG_TYPES_BEGIN + 0xC)
/* Message id 0xD available */

/* Message from Hal to send out a DEL-TS indication */
#define SIR_LIM_DEL_TS_IND                  (SIR_LIM_ITC_MSG_TYPES_BEGIN + 0xE)
/* Indication from HAL to delete Station context */
#define SIR_LIM_DELETE_STA_CONTEXT_IND      (SIR_LIM_ITC_MSG_TYPES_BEGIN + 0x11)
/* Indication from HAL to delete BA */
#define SIR_LIM_UPDATE_BEACON               (SIR_LIM_ITC_MSG_TYPES_BEGIN + 0x13)

/* LIM Timeout messages */
#define SIR_LIM_TIMEOUT_MSG_START      ((SIR_LIM_MODULE_ID << 8) + 0xD0)
#define SIR_LIM_JOIN_FAIL_TIMEOUT      (SIR_LIM_TIMEOUT_MSG_START + 2)
#define SIR_LIM_AUTH_FAIL_TIMEOUT      (SIR_LIM_TIMEOUT_MSG_START + 3)
#define SIR_LIM_AUTH_RSP_TIMEOUT       (SIR_LIM_TIMEOUT_MSG_START + 4)
#define SIR_LIM_ASSOC_FAIL_TIMEOUT     (SIR_LIM_TIMEOUT_MSG_START + 5)
#define SIR_LIM_REASSOC_FAIL_TIMEOUT   (SIR_LIM_TIMEOUT_MSG_START + 6)
#define SIR_LIM_HEART_BEAT_TIMEOUT     (SIR_LIM_TIMEOUT_MSG_START + 7)
/* currently unused                    SIR_LIM_TIMEOUT_MSG_START + 0x8 */
/* Link Monitoring Messages */
#define SIR_LIM_PROBE_HB_FAILURE_TIMEOUT (SIR_LIM_TIMEOUT_MSG_START + 0xB)
#define SIR_LIM_ADDTS_RSP_TIMEOUT        (SIR_LIM_TIMEOUT_MSG_START + 0xC)
#define SIR_LIM_LINK_TEST_DURATION_TIMEOUT (SIR_LIM_TIMEOUT_MSG_START + 0x13)
#define SIR_LIM_HASH_MISS_THRES_TIMEOUT  (SIR_LIM_TIMEOUT_MSG_START + 0x16)
#define SIR_LIM_CNF_WAIT_TIMEOUT         (SIR_LIM_TIMEOUT_MSG_START + 0x17)
/* currently unused			(SIR_LIM_TIMEOUT_MSG_START + 0x18) */
#define SIR_LIM_UPDATE_OLBC_CACHEL_TIMEOUT (SIR_LIM_TIMEOUT_MSG_START + 0x19)
#define SIR_LIM_CHANNEL_SWITCH_TIMEOUT   (SIR_LIM_TIMEOUT_MSG_START + 0x1A)
#define SIR_LIM_QUIET_TIMEOUT            (SIR_LIM_TIMEOUT_MSG_START + 0x1B)
#define SIR_LIM_QUIET_BSS_TIMEOUT        (SIR_LIM_TIMEOUT_MSG_START + 0x1C)

#define SIR_LIM_WPS_OVERLAP_TIMEOUT      (SIR_LIM_TIMEOUT_MSG_START + 0x1D)
#define SIR_LIM_FT_PREAUTH_RSP_TIMEOUT   (SIR_LIM_TIMEOUT_MSG_START + 0x1E)
#define SIR_LIM_REMAIN_CHN_TIMEOUT       (SIR_LIM_TIMEOUT_MSG_START + 0x1F)
#define SIR_LIM_INSERT_SINGLESHOT_NOA_TIMEOUT (SIR_LIM_TIMEOUT_MSG_START + 0x20)

#define SIR_LIM_BEACON_GEN_IND          (SIR_LIM_TIMEOUT_MSG_START + 0x23)
#define SIR_LIM_PERIODIC_PROBE_REQ_TIMEOUT    (SIR_LIM_TIMEOUT_MSG_START + 0x24)

/* currently unused                     (SIR_LIM_TIMEOUT_MSG_START + 0x25) */

#define SIR_LIM_DISASSOC_ACK_TIMEOUT       (SIR_LIM_TIMEOUT_MSG_START + 0x26)
#define SIR_LIM_DEAUTH_ACK_TIMEOUT       (SIR_LIM_TIMEOUT_MSG_START + 0x27)
#define SIR_LIM_PERIODIC_JOIN_PROBE_REQ_TIMEOUT \
					 (SIR_LIM_TIMEOUT_MSG_START + 0x28)

#define SIR_LIM_CONVERT_ACTIVE_CHANNEL_TO_PASSIVE \
					 (SIR_LIM_TIMEOUT_MSG_START + 0x2C)
#define SIR_LIM_AUTH_RETRY_TIMEOUT     (SIR_LIM_TIMEOUT_MSG_START + 0x2D)

#define SIR_LIM_MSG_TYPES_END            (SIR_LIM_MSG_TYPES_BEGIN+0xFF)

/* SCH message types */
#define SIR_SCH_MSG_TYPES_BEGIN        (SIR_SCH_MODULE_ID << 8)
#define SIR_SCH_CHANNEL_SWITCH_REQUEST (SIR_SCH_MSG_TYPES_BEGIN)
#define SIR_SCH_START_SCAN_REQ         (SIR_SCH_MSG_TYPES_BEGIN + 1)
#define SIR_SCH_START_SCAN_RSP         (SIR_SCH_MSG_TYPES_BEGIN + 2)
#define SIR_SCH_END_SCAN_NTF           (SIR_SCH_MSG_TYPES_BEGIN + 3)
#define SIR_SCH_MSG_TYPES_END          (SIR_SCH_MSG_TYPES_BEGIN+0xFF)

/* PMM message types */
#define SIR_PMM_MSG_TYPES_BEGIN        (SIR_PMM_MODULE_ID << 8)
#define SIR_PMM_CHANGE_PM_MODE         (SIR_PMM_MSG_TYPES_BEGIN)
#define SIR_PMM_MSG_TYPES_END          (SIR_PMM_MSG_TYPES_BEGIN+0xFF)

/* MNT message types */
#define SIR_MNT_MSG_TYPES_BEGIN        (SIR_MNT_MODULE_ID << 8)
#define SIR_MNT_RELEASE_BD             (SIR_MNT_MSG_TYPES_BEGIN + 0)
#define SIR_MNT_MSG_TYPES_END          (SIR_MNT_MSG_TYPES_BEGIN + 0xFF)

/* PTT message types */
#define SIR_PTT_MSG_TYPES_BEGIN            0x3000
#define SIR_PTT_MSG_TYPES_END              0x3300

/* ****************************************** *
*                                            *
*         EVENT TYPE Defintions              *
*                                            *
* ****************************************** */

/* MMH Events that are used in other modules to post events to MMH */
#define SIR_HSTEMUL_TXMB_DONE_EVT         0x00000100
#define SIR_HSTEMUL_RXMB_READY_EVT        0x00000200
#define SIR_HSTEMUL_MSGQ_NE_EVT           0x00000400

#define SIR_TST_XMIT_MSG_QS_EMPTY_EVT     0x00000080

/* added for OBSS */

/* Param Change Bitmap sent to HAL */
#define PARAM_BCN_INTERVAL_CHANGED                      (1 << 0)
#define PARAM_SHORT_PREAMBLE_CHANGED                 (1 << 1)
#define PARAM_SHORT_SLOT_TIME_CHANGED                 (1 << 2)
#define PARAM_llACOEXIST_CHANGED                            (1 << 3)
#define PARAM_llBCOEXIST_CHANGED                            (1 << 4)
#define PARAM_llGCOEXIST_CHANGED                            (1 << 5)
#define PARAM_HT20MHZCOEXIST_CHANGED                  (1<<6)
#define PARAM_NON_GF_DEVICES_PRESENT_CHANGED (1<<7)
#define PARAM_RIFS_MODE_CHANGED                            (1<<8)
#define PARAM_LSIG_TXOP_FULL_SUPPORT_CHANGED   (1<<9)
#define PARAM_OBSS_MODE_CHANGED                               (1<<10)
#define PARAM_BEACON_UPDATE_MASK    (PARAM_BCN_INTERVAL_CHANGED | \
				     PARAM_SHORT_PREAMBLE_CHANGED | \
				     PARAM_SHORT_SLOT_TIME_CHANGED | \
				     PARAM_llACOEXIST_CHANGED | \
				     PARAM_llBCOEXIST_CHANGED | \
				     PARAM_llGCOEXIST_CHANGED | \
				     PARAM_HT20MHZCOEXIST_CHANGED | \
				     PARAM_NON_GF_DEVICES_PRESENT_CHANGED | \
				     PARAM_RIFS_MODE_CHANGED | \
				     PARAM_LSIG_TXOP_FULL_SUPPORT_CHANGED | \
				     PARAM_OBSS_MODE_CHANGED)

#endif
