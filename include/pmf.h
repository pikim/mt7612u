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

    Abstract:
        IEEE P802.11w

 */
#ifndef __PMF_H
#define __PMF_H
#ifdef DOT11W_PMF_SUPPORT

VOID PMF_PeerAction(
	IN Pstruct rtmp_adapter pAd,
	IN MLME_QUEUE_ELEM *Elem);

VOID PMF_MlmeSAQueryReq(
        IN Pstruct rtmp_adapter pAd,
        IN MAC_TABLE_ENTRY *pEntry);

VOID PMF_PeerSAQueryReqAction(
	IN Pstruct rtmp_adapter pAd,
	IN MLME_QUEUE_ELEM *Elem);

VOID PMF_PeerSAQueryRspAction(
	IN Pstruct rtmp_adapter pAd,
	IN MLME_QUEUE_ELEM *Elem);

VOID PMF_DerivePTK(
	IN Pstruct rtmp_adapter pAd,
	IN UCHAR *PMK,
	IN UCHAR *ANonce,
	IN UCHAR *AA,
	IN UCHAR *SNonce,
	IN UCHAR *SA,
	OUT UCHAR *output,
	IN UINT len);

VOID PMF_DeriveIGTK(
	IN Pstruct rtmp_adapter pAd,
        OUT UCHAR *output);

VOID PMF_InsertIGTKKDE(
	IN Pstruct rtmp_adapter pAd,
	IN INT apidx,
	IN u8 *pFrameBuf,
	OUT PULONG pFrameLen);

BOOLEAN PMF_ExtractIGTKKDE(
	IN Pstruct rtmp_adapter pAd,
	IN u8 *pBuf,
	IN INT buf_len);

VOID PMF_MakeRsnIeGMgmtCipher(
	IN Pstruct rtmp_adapter pAd,
	IN UCHAR ElementID,
	IN UCHAR apidx,
	OUT u8 *pRsnIe,
	OUT UCHAR *rsn_len);

NTSTATUS PMF_RsnCapableValidation(
        IN Pstruct rtmp_adapter pAd,
        IN uint8_t * pRsnie,
        IN UINT rsnie_len,
        IN BOOLEAN self_MFPC,
	IN BOOLEAN self_MFPR,
        IN PMAC_TABLE_ENTRY	pEntry);

BOOLEAN	PMF_PerformTxFrameAction(
	IN Pstruct rtmp_adapter pAd,
	OUT struct sk_buff *pPacket);

BOOLEAN	PMF_PerformRxFrameAction(
	IN Pstruct rtmp_adapter pAd,
	IN RX_BLK *pRxBlk);

void rtmp_read_pmf_parameters_from_file(
	IN Pstruct rtmp_adapter pAd,
	IN char *tmpbuf,
	IN char *pBuffer);

INT Set_PMFMFPC_Proc (
	IN Pstruct rtmp_adapter pAd,
	IN PCHAR arg);

INT Set_PMFMFPR_Proc (
	IN Pstruct rtmp_adapter pAd,
	IN PCHAR arg);

INT Set_PMFSHA256_Proc (
	IN Pstruct rtmp_adapter pAd,
	IN PCHAR arg);

#endif /* DOT11W_PMF_SUPPORT */

#endif /* __PMF_H */

