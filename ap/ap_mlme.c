/****************************************************************************
 * Ralink Tech Inc.
 * 4F, No. 2 Technology 5th Rd.
 * Science-based Industrial Park
 * Hsin-chu, Taiwan, R.O.C.
 * (c) Copyright 2002, Ralink Technology, Inc.
 *
 * All rights reserved. Ralink's source code is an unpublished work and the
 * use of a copyright notice does not imply otherwise. This source code
 * contains confidential trade secret material of Ralink Tech. Any attemp
 * or participation in deciphering, decoding, reverse engineering or in any
 * way altering the source code is stricitly prohibited, unless the prior
 * written consent of Ralink Technology, Inc. is obtained.
 ****************************************************************************

    Module Name:
    mlme.c

    Abstract:
    Major MLME state machiones here

    Revision History:
    Who         When          What
    --------    ----------    ----------------------------------------------
    John Chang  08-04-2003    created for 11g soft-AP
 */

#include "rt_config.h"
#include <stdarg.h>

extern UCHAR  ZeroSsid[32];

int DetectOverlappingPeriodicRound;


VOID Bss2040CoexistTimeOut(
	IN PVOID SystemSpecific1,
	IN PVOID FunctionContext,
	IN PVOID SystemSpecific2,
	IN PVOID SystemSpecific3)
{
	int apidx;
	struct rtmp_adapter *pAd = (struct rtmp_adapter *)FunctionContext;

	DBGPRINT(RT_DEBUG_TRACE, ("Bss2040CoexistTimeOut(): Recovery to original setting!\n"));

	/* Recovery to original setting when next DTIM Interval. */
	pAd->CommonCfg.Bss2040CoexistFlag &= (~BSS_2040_COEXIST_TIMER_FIRED);
	memset(&pAd->CommonCfg.LastBSSCoexist2040, 0, sizeof(BSS_2040_COEXIST_IE));
	pAd->CommonCfg.Bss2040CoexistFlag |= BSS_2040_COEXIST_INFO_SYNC;

	if (pAd->CommonCfg.bBssCoexEnable == FALSE)
	{
		/* TODO: Find a better way to handle this when the timer is fired and we disable the bBssCoexEable support!! */
		DBGPRINT(RT_DEBUG_TRACE, ("Bss2040CoexistTimeOut(): bBssCoexEnable is FALSE, return directly!\n"));
		return;
	}

	for (apidx = 0; apidx < pAd->ApCfg.BssidNum; apidx++)
		SendBSS2040CoexistMgmtAction(pAd, MCAST_WCID, apidx, 0);

}



VOID APDetectOverlappingExec(
	IN PVOID SystemSpecific1,
	IN PVOID FunctionContext,
	IN PVOID SystemSpecific2,
	IN PVOID SystemSpecific3)
{
	struct rtmp_adapter *pAd = (struct rtmp_adapter *)FunctionContext;

	if (DetectOverlappingPeriodicRound == 0)
	{
		/* switch back 20/40 */
		if ((pAd->CommonCfg.Channel <=14) && (pAd->CommonCfg.HtCapability.HtCapInfo.ChannelWidth == BW_40))
		{
			pAd->CommonCfg.AddHTInfo.AddHtInfo.RecomWidth = 1;
			pAd->CommonCfg.AddHTInfo.AddHtInfo.ExtChanOffset = pAd->CommonCfg.RegTransmitSetting.field.EXTCHA;
		}
	}
	else
	{
		if ((DetectOverlappingPeriodicRound == 25) || (DetectOverlappingPeriodicRound == 1))
		{
   			if ((pAd->CommonCfg.Channel <=14) && (pAd->CommonCfg.HtCapability.HtCapInfo.ChannelWidth==BW_40))
			{
				SendBeaconRequest(pAd, 1);
				SendBeaconRequest(pAd, 2);
                		SendBeaconRequest(pAd, 3);
			}

		}
		DetectOverlappingPeriodicRound--;
	}
}


/*
    ==========================================================================
    Description:
        This routine is executed every second -
        1. Decide the overall channel quality
        2. Check if need to upgrade the TX rate to any client
        3. perform MAC table maintenance, including ageout no-traffic clients,
           and release packet buffer in PSQ is fail to TX in time.
    ==========================================================================
 */
VOID APMlmePeriodicExec(
    struct rtmp_adapter *pAd)
{
    /*
		Reqeust by David 2005/05/12
		It make sense to disable Adjust Tx Power on AP mode, since we can't
		take care all of the client's situation
		ToDo: need to verify compatibility issue with WiFi product.
	*/

	RTMP_CHIP_HIGH_POWER_TUNING(pAd, &pAd->ApCfg.RssiSample);


	/* Disable Adjust Tx Power for WPA WiFi-test. */
	/* Because high TX power results in the abnormal disconnection of Intel BG-STA. */
/*#ifndef WIFI_TEST */
/*	if (pAd->CommonCfg.bWiFiTest == FALSE) */
	/* for SmartBit 64-byte stream test */
	/* removed based on the decision of Ralink congress at 2011/7/06 */
/*	if (pAd->MacTab.Size > 0) */
	AsicAdjustTxPower(pAd);
/*#endif // WIFI_TEST */

#ifdef THERMAL_PROTECT_SUPPORT
	thermal_protection(pAd);
#endif /* THERMAL_PROTECT_SUPPORT */

	RTMP_CHIP_ASIC_TEMPERATURE_COMPENSATION(pAd);

    /* walk through MAC table, see if switching TX rate is required */

    /* MAC table maintenance */
	if (pAd->Mlme.PeriodicRound % MLME_TASK_EXEC_MULTIPLE == 0)
	{
		/* one second timer */
	    MacTableMaintenance(pAd);


		RTMPMaintainPMKIDCache(pAd);



	}

#ifdef AP_SCAN_SUPPORT
	AutoChannelSelCheck(pAd);
#endif /* AP_SCAN_SUPPORT */

	APUpdateCapabilityAndErpIe(pAd);

#ifdef APCLI_SUPPORT
	if (pAd->Mlme.OneSecPeriodicRound % 2 == 0)
		ApCliIfMonitor(pAd);

	if (pAd->Mlme.OneSecPeriodicRound % 2 == 1)
#ifdef APCLI_AUTO_CONNECT_SUPPORT
		if (pAd->ApCfg.ApCliAutoConnectChannelSwitching == FALSE)
#endif /* APCLI_AUTO_CONNECT_SUPPORT */
		ApCliIfUp(pAd);

	{
		INT loop;
		ULONG Now32;
#ifdef APCLI_CERT_SUPPORT
		BOOLEAN IsUseBA = TRUE;
#endif /* APCLI_CERT_SUPPORT */

		NdisGetSystemUpTime(&Now32);
		for (loop = 0; loop < MAX_APCLI_NUM; loop++)
		{
			PAPCLI_STRUCT pApCliEntry = &pAd->ApCfg.ApCliTab[loop];
			if (pAd->ApCfg.ApCliTab[loop].bBlockAssoc ==TRUE && pAd->ApCfg.ApCliTab[loop].bBlockAssoc &&
				RTMP_TIME_AFTER(Now32, pAd->ApCfg.ApCliTab[loop].LastMicErrorTime + (60*OS_HZ)))
		    		pAd->ApCfg.ApCliTab[loop].bBlockAssoc = FALSE;


			if ((pApCliEntry->Valid == TRUE)
				&& (pApCliEntry->MacTabWCID < MAX_LEN_OF_MAC_TABLE))
			{
				/* update channel quality for Roaming and UI LinkQuality display */
				MlmeCalculateChannelQuality(pAd,
					&pAd->MacTab.Content[pApCliEntry->MacTabWCID], Now32);
				/* WPA MIC error should block association attempt for 60 seconds*/
#ifdef APCLI_CERT_SUPPORT
				if (pAd->bApCliCertTest == TRUE)
				{
					PMAC_TABLE_ENTRY pEntry = &pAd->MacTab.Content[pApCliEntry->MacTabWCID];
					struct rtmp_wifi_dev *wdev = NULL;
					wdev = &pApCliEntry->wdev;

					if (pEntry->RXBAbitmap == 0 && pEntry->TXBAbitmap == 0)
						IsUseBA = FALSE;

					if( wdev->DesiredHtPhyInfo.bHtEnable &&
						IsUseBA == FALSE   )
					{
						EDCA_AC_CFG_STRUC   Ac2Cfg, Ac1Cfg;

						RTMP_IO_READ32(pAd, EDCA_AC2_CFG, &Ac2Cfg.word);
						RTMP_IO_READ32(pAd, EDCA_AC1_CFG, &Ac1Cfg.word);

						if ((pAd->RalinkCounters.OneSecOsTxCount[QID_AC_VO] == 0) &&
							(pAd->RalinkCounters.OneSecOsTxCount[QID_AC_BK] >= 1000) &&
							(pAd->RalinkCounters.OneSecOsTxCount[QID_AC_VI] == 0))
						{
							/*5.2.27 T7 */
							if (Ac1Cfg.field.Aifsn!=0x1)
							{
									Ac1Cfg.field.Aifsn = 0x1;
									RTMP_IO_WRITE32(pAd, EDCA_AC1_CFG, Ac1Cfg.word);
									printk("Change EDCA_AC1_CFG to %x \n", Ac1Cfg.word);
							}
						}
						else if ((pAd->RalinkCounters.OneSecOsTxCount[QID_AC_VO] == 0) &&
							(pAd->RalinkCounters.OneSecOsTxCount[QID_AC_BK] == 0) &&
							(pAd->RalinkCounters.OneSecOsTxCount[QID_AC_VI] == 0) &&
							(pAd->RalinkCounters.OneSecOsTxCount[QID_AC_BE] < 10))
						{
							/* restore default parameter of BK*/
							if (Ac1Cfg.field.Aifsn!=0x7)
							{
								Ac1Cfg.field.Aifsn = 0x7;
								RTMP_IO_WRITE32(pAd, EDCA_AC1_CFG, Ac1Cfg.word);
								printk("Restore EDCA_AC1_CFG to %x \n", Ac1Cfg.word);
							}
						}

						pAd->RalinkCounters.OneSecOsTxCount[QID_AC_BE] = 0;
						pAd->RalinkCounters.OneSecOsTxCount[QID_AC_BK] = 0;
						pAd->RalinkCounters.OneSecOsTxCount[QID_AC_VI] = 0;
						pAd->RalinkCounters.OneSecOsTxCount[QID_AC_VO] = 0;

					}
				}
#endif /* APCLI_CERT_SUPPORT */
			}
		}
	}
#endif /* APCLI_SUPPORT */

    if (pAd->CommonCfg.bHTProtect)
    {
    	/*APUpdateCapabilityAndErpIe(pAd); */
    	APUpdateOperationMode(pAd);
		if (pAd->CommonCfg.IOTestParm.bRTSLongProtOn == FALSE)
		{
        	AsicUpdateProtect(pAd, (USHORT)pAd->CommonCfg.AddHTInfo.AddHtInfo2.OperaionMode, ALLN_SETPROTECT, FALSE, pAd->MacTab.fAnyStationNonGF);
    	}
    }

	if ( (pAd->CommonCfg.Channel > 14)
		&& (pAd->CommonCfg.bIEEE80211H == 1)
		)
	{
		pAd->Dot11_H.InServiceMonitorCount++;
		if (pAd->Dot11_H.RDMode == RD_SILENCE_MODE)
		{
			if (pAd->Dot11_H.RDCount++ > pAd->Dot11_H.ChMovingTime)
			{
				AsicEnableBssSync(pAd);
				pAd->Dot11_H.RDMode = RD_NORMAL_MODE;
			}
		}
		}

#ifdef APCLI_SUPPORT
#ifdef APCLI_CERT_SUPPORT
	/* Perform 20/40 BSS COEX scan every Dot11BssWidthTriggerScanInt	*/
	if (APCLI_IF_UP_CHECK(pAd, 0) && (pAd->bApCliCertTest == TRUE))
	{
		if ((OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_SCAN_2040)) &&
			(pAd->CommonCfg.Dot11BssWidthTriggerScanInt != 0) &&
			((pAd->Mlme.OneSecPeriodicRound % pAd->CommonCfg.Dot11BssWidthTriggerScanInt) == (pAd->CommonCfg.Dot11BssWidthTriggerScanInt-1)))
		{
			DBGPRINT(RT_DEBUG_TRACE, ("MMCHK - LastOneSecTotalTxCount/LastOneSecRxOkDataCnt  = %d/%d \n",
									pAd->RalinkCounters.LastOneSecTotalTxCount,
									pAd->RalinkCounters.LastOneSecRxOkDataCnt));

			/* Check last scan time at least 30 seconds from now. 		*/
			/* Check traffic is less than about 1.5~2Mbps.*/
			/* it might cause data lost if we enqueue scanning.*/
			/* This criteria needs to be considered*/
			if ((pAd->RalinkCounters.LastOneSecTotalTxCount < 70) && (pAd->RalinkCounters.LastOneSecRxOkDataCnt < 70)
				/*&& ((pAd->StaCfg.LastScanTime + 10 * OS_HZ) < pAd->Mlme.Now32) */)
			{
				MLME_SCAN_REQ_STRUCT            ScanReq;
				/* Fill out stuff for scan request and kick to scan*/
				ScanParmFill(pAd, &ScanReq, ZeroSsid, 0, BSS_ANY, SCAN_2040_BSS_COEXIST);

		/* Before scan, reset trigger event table. */
				TriEventInit(pAd);


		MlmeEnqueue(pAd, AP_SYNC_STATE_MACHINE, APMT2_MLME_SCAN_REQ, sizeof(MLME_SCAN_REQ_STRUCT), &ScanReq, 0);

				/* Set InfoReq = 1, So after scan , alwats sebd 20/40 Coexistence frame to AP*/
				pAd->CommonCfg.BSSCoexist2040.field.InfoReq = 1;
				RTMP_MLME_HANDLER(pAd);
	}

			DBGPRINT(RT_DEBUG_TRACE, (" LastOneSecTotalTxCount/LastOneSecRxOkDataCnt  = %d/%d \n",
								pAd->RalinkCounters.LastOneSecTotalTxCount,
								pAd->RalinkCounters.LastOneSecRxOkDataCnt));
		}
	}
#endif /* APCLI_CERT_SUPPORT */
#endif /* APCLI_SUPPORT */
}


/*! \brief   To substitute the message type if the message is coming from external
 *  \param  *Fr            The frame received
 *  \param  *Machine       The state machine
 *  \param  *MsgType       the message type for the state machine
 *  \return TRUE if the substitution is successful, FALSE otherwise
 *  \pre
 *  \post
 */
BOOLEAN APMsgTypeSubst(
    IN struct rtmp_adapter *pAd,
    IN PFRAME_802_11 pFrame,
    OUT INT *Machine,
    OUT INT *MsgType)
{
    USHORT Seq;
    UCHAR  EAPType;
    BOOLEAN     Return = FALSE;

/*
	TODO:
		only PROBE_REQ can be broadcast, all others must be unicast-to-me && is_mybssid;
		otherwise, ignore this frame
*/

    /* wpa EAPOL PACKET */
    if (pFrame->Hdr.FC.Type == FC_TYPE_DATA)
    {
        if (!Return)
        {
	        *Machine = WPA_STATE_MACHINE;
        	EAPType = *((UCHAR*)pFrame + LENGTH_802_11 + LENGTH_802_1_H + 1);
	        Return = WpaMsgTypeSubst(EAPType, (INT *) MsgType);
        }
        return Return;
    }

    if (pFrame->Hdr.FC.Type != FC_TYPE_MGMT)
        return FALSE;

    switch (pFrame->Hdr.FC.SubType)
    {
        case SUBTYPE_ASSOC_REQ:
            *Machine = AP_ASSOC_STATE_MACHINE;
            *MsgType = APMT2_PEER_ASSOC_REQ;

            break;
/*
		case SUBTYPE_ASSOC_RSP:
			*Machine = AP_ASSOC_STATE_MACHINE;
			*MsgType = APMT2_PEER_ASSOC_RSP;
			break;
*/
        case SUBTYPE_REASSOC_REQ:
            *Machine = AP_ASSOC_STATE_MACHINE;
            *MsgType = APMT2_PEER_REASSOC_REQ;
            break;
/*
		case SUBTYPE_REASSOC_RSP:
			*Machine = AP_ASSOC_STATE_MACHINE;
			*MsgType = APMT2_PEER_REASSOC_RSP;
			break;
*/
        case SUBTYPE_PROBE_REQ:
            *Machine = AP_SYNC_STATE_MACHINE;
            *MsgType = APMT2_PEER_PROBE_REQ;
            break;

		/* For Active Scan */
		case SUBTYPE_PROBE_RSP:
          *Machine = AP_SYNC_STATE_MACHINE;
          *MsgType = APMT2_PEER_PROBE_RSP;
          break;
        case SUBTYPE_BEACON:
            *Machine = AP_SYNC_STATE_MACHINE;
            *MsgType = APMT2_PEER_BEACON;
            break;
/*
		case SUBTYPE_ATIM:
			*Machine = AP_SYNC_STATE_MACHINE;
			*MsgType = APMT2_PEER_ATIM;
			break;
*/
        case SUBTYPE_DISASSOC:
            *Machine = AP_ASSOC_STATE_MACHINE;
            *MsgType = APMT2_PEER_DISASSOC_REQ;
            break;
        case SUBTYPE_AUTH:
            /* get the sequence number from payload 24 Mac Header + 2 bytes algorithm */
            memmove(&Seq, &pFrame->Octet[2], sizeof(USHORT));

			*Machine = AP_AUTH_STATE_MACHINE;
			if (Seq == 1)
				*MsgType = APMT2_PEER_AUTH_REQ;
			else if (Seq == 3)
				*MsgType = APMT2_PEER_AUTH_CONFIRM;
            else
            {
                DBGPRINT(RT_DEBUG_TRACE,("wrong AUTH seq=%d Octet=%02x %02x %02x %02x %02x %02x %02x %02x\n", Seq,
                    pFrame->Octet[0], pFrame->Octet[1], pFrame->Octet[2], pFrame->Octet[3],
                    pFrame->Octet[4], pFrame->Octet[5], pFrame->Octet[6], pFrame->Octet[7]));
                return FALSE;
            }
            break;

        case SUBTYPE_DEAUTH:
            *Machine = AP_AUTH_STATE_MACHINE; /*AP_AUTH_RSP_STATE_MACHINE;*/
            *MsgType = APMT2_PEER_DEAUTH;
            break;

	case SUBTYPE_ACTION:
	case SUBTYPE_ACTION_NO_ACK:
		*Machine = ACTION_STATE_MACHINE;
		/*  Sometimes Sta will return with category bytes with MSB = 1, if they receive catogory out of their support */
		if ((pFrame->Octet[0]&0x7F) > MAX_PEER_CATE_MSG)
		{
			*MsgType = MT2_ACT_INVALID;
		}
		else
		{
			*MsgType = (pFrame->Octet[0]&0x7F);
		}
		break;

        default:
            return FALSE;
            break;
    }

    return TRUE;
}


/*
    ========================================================================
    Routine Description:
        Periodic evaluate antenna link status

    Arguments:
        pAd         - Adapter pointer

    Return Value:
        None

    ========================================================================
*/
VOID APAsicEvaluateRxAnt(
	IN struct rtmp_adapter *pAd)
{
	ULONG	TxTotalCnt;

#ifdef RT8592
	// TODO: shiang-6590, for 8592, this EvaaluateRxAnt still need??
	if (IS_RT8592(pAd))
		return;
#endif /* RT8592 */

#ifdef RT65xx
	if (IS_RT65XX(pAd))
		return;
#endif /* RT76x0 */

#ifdef GREENAP_SUPPORT
	if (pAd->ApCfg.bGreenAPActive == TRUE)
		bbp_set_rxpath(pAd, 1);
	else
#endif /* GREENAP_SUPPORT */
		bbp_set_rxpath(pAd, pAd->Antenna.field.RxPath);

	TxTotalCnt = pAd->RalinkCounters.OneSecTxNoRetryOkCount +
					pAd->RalinkCounters.OneSecTxRetryOkCount +
					pAd->RalinkCounters.OneSecTxFailCount;

	if (TxTotalCnt > 50)
	{
		RTMPSetTimer(&pAd->Mlme.RxAntEvalTimer, 20);
		pAd->Mlme.bLowThroughput = FALSE;
	}
	else
	{
		RTMPSetTimer(&pAd->Mlme.RxAntEvalTimer, 300);
		pAd->Mlme.bLowThroughput = TRUE;
	}
}

/*
    ========================================================================
    Routine Description:
        After evaluation, check antenna link status

    Arguments:
        pAd         - Adapter pointer

    Return Value:
        None

    ========================================================================
*/
VOID APAsicRxAntEvalTimeout(struct rtmp_adapter *pAd)
{
	CHAR rssi0, rssi1, rssi2;

	/* if the traffic is low, use average rssi as the criteria */
	if (pAd->Mlme.bLowThroughput == TRUE)
	{
		rssi0 = pAd->ApCfg.RssiSample.LastRssi0;
		rssi1 = pAd->ApCfg.RssiSample.LastRssi1;
		rssi2 = pAd->ApCfg.RssiSample.LastRssi2;
	}
	else
	{
		rssi0 = pAd->ApCfg.RssiSample.AvgRssi0;
		rssi1 = pAd->ApCfg.RssiSample.AvgRssi1;
		rssi2 = pAd->ApCfg.RssiSample.AvgRssi2;
	}

#ifdef DOT11N_SS3_SUPPORT
	if(pAd->Antenna.field.RxPath == 3)
	{
		CHAR larger = -127;

		larger = max(rssi0, rssi1);
		if (pAd->CommonCfg.RxStream >= 3)
			pAd->Mlme.RealRxPath = 3;
		else
		{
		if (larger > (rssi2 + 20))
			pAd->Mlme.RealRxPath = 2;
		else
			pAd->Mlme.RealRxPath = 3;
		}
	}
#endif /* DOT11N_SS3_SUPPORT */

	/* Disable the below to fix 1T/2R issue. It's suggested by Rory at 2007/7/11. */

#ifdef GREENAP_SUPPORT
	if (pAd->ApCfg.bGreenAPActive == TRUE)
		bbp_set_rxpath(pAd, 1);
	else
#endif /* GREENAP_SUPPORT */
		bbp_set_rxpath(pAd, pAd->Mlme.RealRxPath);


}

/*
    ========================================================================
    Routine Description:
        After evaluation, check antenna link status

    Arguments:
        pAd         - Adapter pointer

    Return Value:
        None

    ========================================================================
*/
VOID	APAsicAntennaAvg(
	IN	struct rtmp_adapter *pAd,
	IN	UCHAR	              AntSelect,
	IN	SHORT*	              RssiAvg)
{
		    SHORT	realavgrssi;
		    LONG         realavgrssi1;
		    ULONG	recvPktNum = pAd->RxAnt.RcvPktNum[AntSelect];

		    realavgrssi1 = pAd->RxAnt.Pair1AvgRssiGroup1[AntSelect];

		    if(realavgrssi1 == 0)
		    {
		        *RssiAvg = 0;
		        return;
		    }

		    realavgrssi = (SHORT) (realavgrssi1 / recvPktNum);

		    pAd->RxAnt.Pair1AvgRssiGroup1[0] = 0;
		    pAd->RxAnt.Pair1AvgRssiGroup1[1] = 0;
		    pAd->RxAnt.Pair1AvgRssiGroup2[0] = 0;
		    pAd->RxAnt.Pair1AvgRssiGroup2[1] = 0;
		    pAd->RxAnt.RcvPktNum[0] = 0;
		    pAd->RxAnt.RcvPktNum[1] = 0;
		    *RssiAvg = realavgrssi - 256;
}

