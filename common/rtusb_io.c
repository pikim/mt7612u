/*
 ***************************************************************************
 * Ralink Tech Inc.
 * 4F, No. 2 Technology	5th	Rd.
 * Science-based Industrial	Park
 * Hsin-chu, Taiwan, R.O.C.
 *
 * (c) Copyright 2002-2006, Ralink Technology, Inc.
 *
 * All rights reserved.	Ralink's source	code is	an unpublished work	and	the
 * use of a	copyright notice does not imply	otherwise. This	source code
 * contains	confidential trade secret material of Ralink Tech. Any attemp
 * or participation	in deciphering,	decoding, reverse engineering or in	any
 * way altering	the	source code	is stricitly prohibited, unless	the	prior
 * written consent of Ralink Technology, Inc. is obtained.
 ***************************************************************************

 	Module Name:
	rtusb_io.c

	Abstract:

	Revision History:
	Who			When	    What
	--------	----------  ----------------------------------------------
	Name		Date	    Modification logs
	Paul Lin    06-25-2004  created
*/

#ifdef RTMP_MAC_USB


#include	"rt_config.h"

#define MAX_VENDOR_REQ_RETRY_COUNT  10

/*
	========================================================================

	Routine Description: NIC initialization complete

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
#ifdef RLT_MAC

#ifdef MT76x2
// For MT7662 and newer
void usb_cfg_read_v3(struct rtmp_adapter *ad, u32 *value)
{
	int ret;
	u32 io_value;

	ret = RTUSB_VendorRequest(ad,
							  DEVICE_VENDOR_REQUEST_IN,
							  0x47,
							  0,
							  U3DMA_WLCFG,
							  &io_value,
							  4);

	*value = le2cpu32(io_value);

	if (ret)
		*value = 0xffffffff;
}

// For MT7662 and newer
void usb_cfg_write_v3(struct rtmp_adapter *ad, u32 value)
{
	int ret;
	u32 io_value;


	io_value = cpu2le32(value);

	ret = RTUSB_VendorRequest(ad,
							  DEVICE_VENDOR_REQUEST_OUT,
							  0x46,
							  0,
							  U3DMA_WLCFG,
							  &io_value,
							  4);


	if (ret) {
		DBGPRINT(RT_DEBUG_ERROR, ("usb cfg write fail\n"));
		return;
	}
}
#endif /* MT76x2 */
#endif /* RLT_MAC */

static NTSTATUS RTUSBFirmwareRun(struct rtmp_adapter *pAd)
{
	NTSTATUS Status;

	Status = RTUSB_VendorRequest(
		pAd,
		DEVICE_VENDOR_REQUEST_OUT,
		0x01,
		0x8,
		0,
		NULL,
		0);

	return Status;
}



/*
	========================================================================

	Routine Description: Get current firmware operation mode (Return Value)

	Arguments:

	Return Value:
		0 or 1 = Downloaded by host driver
		others = Driver doesn't download firmware

	IRQL =

	Note:

	========================================================================
*/
NTSTATUS RTUSBFirmwareOpmode(struct rtmp_adapter *pAd, uint32_t *pValue)
{
	NTSTATUS	Status;

	Status = RTUSB_VendorRequest(
		pAd,
		DEVICE_VENDOR_REQUEST_IN,
		0x1,
		0x11,
		0,
		pValue,
		4);
	return Status;
}


/*
	========================================================================

	Routine Description: Write Firmware to NIC.

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
NTSTATUS RTUSBFirmwareWrite(struct rtmp_adapter *pAd, UCHAR *pFwImage, ULONG FwLen)
{
	uint32_t MacReg;
	NTSTATUS Status;
	USHORT writeLen;

	Status = RTUSBReadMACRegister(pAd, MAC_CSR0, &MacReg);


	/* write firmware */
	writeLen = FwLen;
#ifdef USB_FIRMWARE_MULTIBYTE_WRITE
	DBGPRINT(RT_DEBUG_TRACE, ("USB_FIRMWARE_MULTIBYTE_WRITE defined! Write_Bytes = %d\n", MULTIWRITE_BYTES));
	RTUSBMultiWrite_nBytes(pAd, FIRMWARE_IMAGE_BASE, pFwImage, writeLen, MULTIWRITE_BYTES);
#else
	DBGPRINT(RT_DEBUG_TRACE, ("USB_FIRMWARE_MULTIBYTE_WRITE not defined!\n"));
	RTUSBMultiWrite(pAd, FIRMWARE_IMAGE_BASE, pFwImage, writeLen, FALSE);
#endif
	Status = RTUSBWriteMACRegister(pAd, 0x7014, 0xffffffff, FALSE);
	Status = RTUSBWriteMACRegister(pAd, 0x701c, 0xffffffff, FALSE);

	/* change 8051 from ROM to RAM */
	Status = RTUSBFirmwareRun(pAd);


	return Status;
}


NTSTATUS RTUSBVenderReset(struct rtmp_adapter *pAd)
{
	NTSTATUS Status;
	DBGPRINT_RAW(RT_DEBUG_ERROR, ("-->RTUSBVenderReset\n"));
	Status = RTUSB_VendorRequest(
		pAd,
		DEVICE_VENDOR_REQUEST_OUT,
		0x01,
		0x1,
		0,
		NULL,
		0);

	DBGPRINT_RAW(RT_DEBUG_ERROR, ("<--RTUSBVenderReset\n"));
	return Status;
}


/*
	========================================================================

	Routine Description: Read various length data from RT2573

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
NTSTATUS RTUSBMultiRead(struct rtmp_adapter *pAd, USHORT addr, UCHAR *buf, USHORT len)
{
	return RTUSB_VendorRequest(pAd, DEVICE_VENDOR_REQUEST_IN,
								0x7, 0, addr, buf, len);
}


/*
	========================================================================

	Routine Description: Write various length data to RT USB Wifi device, the maxima length should not large than 65535 bytes.

	Arguments:

	Return Value:

	IRQL =

	Note:
		Use this funciton carefully cause it may not stable in some special USB host controllers.

	========================================================================
*/
NTSTATUS RTUSBMultiWrite_nBytes(
	IN struct rtmp_adapter *pAd,
	IN USHORT Offset,
	IN UCHAR *buf,
	IN USHORT len,
	IN USHORT batchLen)
{
	NTSTATUS Status = STATUS_SUCCESS;
	USHORT index = Offset, actLen = batchLen, leftLen = len;
	UCHAR *pSrc = buf;


	do
	{
		actLen = (actLen > batchLen ? batchLen : actLen);
		Status = RTUSB_VendorRequest(
			pAd,
			DEVICE_VENDOR_REQUEST_OUT,
			0x6,
			0,
			index,
			pSrc,
			actLen);

		if (Status != STATUS_SUCCESS)
		{
			DBGPRINT(RT_DEBUG_ERROR, ("VendrCmdMultiWrite_nBytes failed!\n"));
			break;
		}

		index += actLen;
		leftLen -= actLen;
		pSrc = pSrc + actLen;
	}while(leftLen > 0);

	return Status;
}


/*
	========================================================================

	Routine Description: Write various length data to RT2573

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
NTSTATUS RTUSBMultiWrite_OneByte(struct rtmp_adapter *pAd, USHORT Offset, UCHAR *pData)
{
	/* TODO: In 2870, use this funciton carefully cause it's not stable.*/
	return RTUSB_VendorRequest(pAd, DEVICE_VENDOR_REQUEST_OUT,
								0x6, 0, Offset, pData, 1);
}

NTSTATUS RTUSBMultiWrite(
	IN struct rtmp_adapter *pAd,
	IN USHORT Offset,
	IN UCHAR *pData,
	IN USHORT length,
	IN BOOLEAN bWriteHigh)
{
	NTSTATUS Status;
	USHORT index = 0,Value;
	UCHAR *pSrc = pData;
	USHORT resude = 0;

	resude = length % 2;
	length  += resude;
	do
	{
		Value =(USHORT)( *pSrc  | (*(pSrc + 1) << 8));
		Status = RTUSBSingleWrite(pAd,Offset + index, Value, bWriteHigh);
		index +=2;
		length -= 2;
		pSrc = pSrc + 2;
	}while(length > 0);

	return Status;
}


NTSTATUS RTUSBSingleWrite(
	IN 	struct rtmp_adapter *pAd,
	IN	USHORT Offset,
	IN	USHORT Value,
	IN	BOOLEAN WriteHigh)
{
	return RTUSB_VendorRequest(pAd, DEVICE_VENDOR_REQUEST_OUT,
								(WriteHigh == TRUE) ? 0x10 : 0x2,
								Value, Offset, NULL, 0);
}


/*
	========================================================================

	Routine Description: Read 32-bit MAC register

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
NTSTATUS RTUSBReadMACRegister(struct rtmp_adapter *pAd, USHORT Offset, uint32_t *pValue)
{
	NTSTATUS Status = 0;
	uint32_t localVal;

	Status = RTUSB_VendorRequest(
		pAd,
		DEVICE_VENDOR_REQUEST_IN,
		0x7,
		0,
		Offset,
		&localVal,
		4);

	*pValue = le2cpu32(localVal);


	if (Status != 0)
		*pValue = 0xffffffff;

	return Status;
}


/*
	========================================================================

	Routine Description: Write 32-bit MAC register

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
NTSTATUS RTUSBWriteMACRegister(
	IN struct rtmp_adapter *pAd,
	IN USHORT Offset,
	IN uint32_t Value,
	IN BOOLEAN bWriteHigh)
{
	NTSTATUS Status;
	uint32_t localVal;

	localVal = Value;

	/* MT76xx HW has 4 byte alignment constrained */
	if (IS_MT76xx(pAd))
	{
		Status = RTUSBMultiWrite_nBytes(
		pAd,
		Offset,
		&Value,
		4,
		4);
	}
	else
	{
		Status = RTUSBSingleWrite(pAd, Offset, (USHORT)(localVal & 0xffff), bWriteHigh);
		Status = RTUSBSingleWrite(pAd, Offset + 2, (USHORT)((localVal & 0xffff0000) >> 16), bWriteHigh);
	}

	return Status;
}


int write_reg(struct rtmp_adapter *ad, uint32_t base, uint16_t offset, uint32_t val)
{
	NTSTATUS ret;
	UINT8 req;
	uint32_t io_value;

	if (base == 0x40)
		req = 0x46;

	io_value = cpu2le32(val);

	ret = RTUSB_VendorRequest(ad,
							  DEVICE_VENDOR_REQUEST_OUT,
							  req,
							  0,
							  offset,
							  &io_value,
							  4);


	if (ret) {
		DBGPRINT(RT_DEBUG_ERROR, ("write reg fail\n"));
	}

	return ret;
}


int read_reg(struct rtmp_adapter *ad, uint32_t base, uint16_t offset, uint32_t *value)
{
	NTSTATUS ret;
	UINT8 req;
	uint32_t io_value;

	if (base == 0x40)
		req = 0x47;
	else if (base == 0x41)
		req = 0x7;

	ret = RTUSB_VendorRequest(ad,
							  DEVICE_VENDOR_REQUEST_IN,
							  req,
							  0,
							  offset,
							  &io_value,
							  4);

	*value = le2cpu32(io_value);

	if (ret)
		*value = 0xffffffff;

	return ret;
}

/*
	========================================================================

	Routine Description:

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
NTSTATUS RTUSBReadEEPROM(struct rtmp_adapter *pAd, USHORT adr, UCHAR *buf, USHORT len)
{
	return RTUSB_VendorRequest(pAd, DEVICE_VENDOR_REQUEST_IN,
								0x9, 0, adr, buf, len);
}

/*
	========================================================================

	Routine Description:

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
NTSTATUS RTUSBWriteEEPROM(struct rtmp_adapter *pAd, USHORT adr, UCHAR *buf, USHORT len)
{
	return RTUSB_VendorRequest(pAd, DEVICE_VENDOR_REQUEST_OUT,
								0x8, 0, adr, buf, len);
}


NTSTATUS RTUSBReadEEPROM16(struct rtmp_adapter *pAd, USHORT offset, USHORT *pData)
{
	NTSTATUS status;
	USHORT  localData;

	status = RTUSBReadEEPROM(pAd, offset, (u8 *)(&localData), 2);
	if (status == STATUS_SUCCESS)
		*pData = le2cpu16(localData);

	return status;

}


NTSTATUS RTUSBWriteEEPROM16(struct rtmp_adapter *pAd, USHORT offset, USHORT value)
{
	USHORT tmpVal;

	tmpVal = cpu2le16(value);
	return RTUSBWriteEEPROM(pAd, offset, (u8 *)&(tmpVal), 2);
}


/*
	========================================================================

	Routine Description:

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
VOID RTUSBPutToSleep(struct rtmp_adapter *pAd)
{
	uint32_t value;

	/* Timeout 0x40 x 50us*/
	value = (SLEEPCID<<16)+(OWNERMCU<<24)+ (0x40<<8)+1;
	RTUSBWriteMACRegister(pAd, 0x7010, value, FALSE);
	RTUSBWriteMACRegister(pAd, 0x404, 0x30, FALSE);
	DBGPRINT_RAW(RT_DEBUG_ERROR, ("Sleep Mailbox testvalue %x\n", value));
}


/*
	========================================================================

	Routine Description:

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
NTSTATUS RTUSBWakeUp(struct rtmp_adapter *pAd)
{
	return RTUSB_VendorRequest(pAd, DEVICE_VENDOR_REQUEST_OUT,
								0x01, 0x09, 0, NULL, 0);
}


/*
	========================================================================

	Routine Description:

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
int RTUSBEnqueueCmdFromNdis(
	IN	struct rtmp_adapter *pAd,
	IN	NDIS_OID		Oid,
	IN	BOOLEAN			SetInformation,
	IN	PVOID			pInformationBuffer,
	IN	uint32_t 		InformationBufferLength)
{
	int status;
	PCmdQElmt	cmdqelmt = NULL;
	RTMP_OS_TASK	*pTask = &pAd->cmdQTask;


	RTMP_OS_TASK_LEGALITY(pTask)
		;
	else
		return (NDIS_STATUS_RESOURCES);

	cmdqelmt = kmalloc(sizeof(CmdQElmt), GFP_ATOMIC);
	if (cmdqelmt == NULL)
		return (NDIS_STATUS_RESOURCES);

	cmdqelmt->buffer = NULL;
	if (pInformationBuffer != NULL) {
		cmdqelmt->buffer = kmalloc(InformationBufferLength, GFP_ATOMIC);
		if (cmdqelmt->buffer == NULL) {
			kfree(cmdqelmt);
			return (NDIS_STATUS_RESOURCES);
		}
		else
		{
			memmove(cmdqelmt->buffer, pInformationBuffer, InformationBufferLength);
			cmdqelmt->bufferlength = InformationBufferLength;
		}
	}
	else
		cmdqelmt->bufferlength = 0;

	cmdqelmt->command = Oid;
	cmdqelmt->CmdFromNdis = TRUE;
	if (SetInformation == TRUE)
		cmdqelmt->SetOperation = TRUE;
	else
		cmdqelmt->SetOperation = FALSE;

	NdisAcquireSpinLock(&pAd->CmdQLock);
	if (pAd->CmdQ.CmdQState & RTMP_TASK_CAN_DO_INSERT)
	{
		EnqueueCmd((&pAd->CmdQ), cmdqelmt);
		status = NDIS_STATUS_SUCCESS;
	}
	else
	{
		status = NDIS_STATUS_FAILURE;
	}
	NdisReleaseSpinLock(&pAd->CmdQLock);

	if (status == NDIS_STATUS_FAILURE)
	{
		if (cmdqelmt->buffer)
			kfree(cmdqelmt->buffer);
		kfree(cmdqelmt);
	}
	else
	RTCMDUp(&pAd->cmdQTask);


    return(NDIS_STATUS_SUCCESS);
}


/*
    ========================================================================
 	Routine Description:
		RTUSB_VendorRequest - Builds a ralink specific request, sends it off to USB endpoint zero and waits for completion

	Arguments:
		@pAd:
	  	@TransferFlags:
	  	@RequestType: USB message request type value
	  	@Request: USB message request value
	  	@Value: USB message value
	  	@Index: USB message index value
	  	@TransferBuffer: USB data to be sent
	  	@TransferBufferLength: Lengths in bytes of the data to be sent

	Context: ! in atomic context

	Return Value:
		NDIS_STATUS_SUCCESS
		NDIS_STATUS_FAILURE

	Note:
		This function sends a simple control message to endpoint zero
		and waits for the message to complete, or CONTROL_TIMEOUT_JIFFIES timeout.
		Because it is synchronous transfer, so don't use this function within an atomic context,
		otherwise system will hang, do be careful.

		TransferBuffer may located in stack region which may not in DMA'able region in some embedded platforms,
		so need to copy TransferBuffer to UsbVendorReqBuf allocated by kmalloc to do DMA transfer.
		Use UsbVendorReq_semaphore to protect this region which may be accessed by multi task.
		Normally, coherent issue is resloved by low-level HC driver, so do not flush this zone by RTUSB_VendorRequest.

	========================================================================
*/
NTSTATUS RTUSB_VendorRequest(
	IN	struct rtmp_adapter *pAd,
	IN	UCHAR			RequestType,
	IN	UCHAR			Request,
	IN	USHORT			Value,
	IN	USHORT			Index,
	IN	PVOID			TransferBuffer,
	IN	uint32_t 		TransferBufferLength)
{
	int				RET = 0;
	struct os_cookie *	pObj = pAd->OS_Cookie;

	if(in_interrupt())
	{
		DBGPRINT(RT_DEBUG_ERROR, ("BUG: RTUSB_VendorRequest is called from invalid context\n"));
		return NDIS_STATUS_FAILURE;
	}

#ifdef CONFIG_STA_SUPPORT
#ifdef CONFIG_PM
#ifdef USB_SUPPORT_SELECTIVE_SUSPEND
	if(RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_SUSPEND))
	{
		return NDIS_STATUS_FAILURE;
	}
#endif /* USB_SUPPORT_SELECTIVE_SUSPEND */
#endif /* CONFIG_PM */
#endif /* CONFIG_STA_SUPPORT */

	if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))
	{
		/*DBGPRINT(RT_DEBUG_ERROR, ("WIFI device has been disconnected\n"));*/
		return NDIS_STATUS_FAILURE;
	}
	else if (RTMP_TEST_PSFLAG(pAd, fRTMP_PS_MCU_SLEEP))
	{
		DBGPRINT(RT_DEBUG_ERROR, ("MCU has entered sleep mode\n"));
		return NDIS_STATUS_FAILURE;
	}
	else
	{
		int RetryCount = 0; /* RTUSB_CONTROL_MSG retry counts*/
		ASSERT(TransferBufferLength <MAX_PARAM_BUFFER_SIZE);

		RTMP_SEM_EVENT_WAIT(&(pAd->UsbVendorReq_semaphore), RET);
		if (RET != 0)
		{
			DBGPRINT(RT_DEBUG_ERROR, ("UsbVendorReq_semaphore get failed\n"));
			return NDIS_STATUS_FAILURE;
		}

		if ((TransferBufferLength > 0) && ((RequestType == DEVICE_VENDOR_REQUEST_OUT) || (RequestType == DEVICE_CLASS_REQUEST_OUT)))
			memmove(pAd->UsbVendorReqBuf, TransferBuffer, TransferBufferLength);

		do {
			RTUSB_CONTROL_MSG(pObj->pUsb_Dev, 0, Request, RequestType, Value,
								Index, pAd->UsbVendorReqBuf, TransferBufferLength,
								CONTROL_TIMEOUT_JIFFIES, RET);

			if (RET < 0) {
				DBGPRINT(RT_DEBUG_OFF, ("#\n"));
				if (RET == RTMP_USB_CONTROL_MSG_ENODEV)
				{
					RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST);
					break;
				}
				RetryCount++;
				RtmpusecDelay(5000); /* wait for 5ms*/
			}
		} while((RET < 0) && (RetryCount < MAX_VENDOR_REQ_RETRY_COUNT));

	  	if ( (!(RET < 0)) && (TransferBufferLength > 0) && (RequestType == DEVICE_VENDOR_REQUEST_IN))
			memmove(TransferBuffer, pAd->UsbVendorReqBuf, TransferBufferLength);

	  	RTMP_SEM_EVENT_UP(&(pAd->UsbVendorReq_semaphore));

        	if (RET < 0) {
			DBGPRINT(RT_DEBUG_ERROR, ("RTUSB_VendorRequest failed(%d), ReqType=%s, Req=0x%x, Idx=0x%x,pAd->Flags=0x%lx\n",
						RET, (RequestType == DEVICE_VENDOR_REQUEST_OUT ? "OUT" : "IN"), Request, Index, pAd->Flags));
			if (Request == 0x2)
				DBGPRINT(RT_DEBUG_ERROR, ("\tRequest Value=0x%04x!\n", Value));

			if ((!TransferBuffer) && (TransferBufferLength > 0))
				hex_dump("Failed TransferBuffer value", TransferBuffer, TransferBufferLength);

			if (RET == RTMP_USB_CONTROL_MSG_ENODEV)
					RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST);

		}

	}

	if (RET < 0)
		return NDIS_STATUS_FAILURE;
	else
		return NDIS_STATUS_SUCCESS;

}


/*
	========================================================================

	Routine Description:
	  Creates an IRP to submite an IOCTL_INTERNAL_USB_RESET_PORT
	  synchronously. Callers of this function must be running at
	  PASSIVE LEVEL.

	Arguments:

	Return Value:

	Note:

	========================================================================
*/
NTSTATUS RTUSB_ResetDevice(struct rtmp_adapter *pAd)
{
	return NDIS_STATUS_SUCCESS;
}


NTSTATUS CheckGPIOHdlr(struct rtmp_adapter *pAd, PCmdQElmt CMDQelmt)
{
#ifdef CONFIG_STA_SUPPORT
		IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
		{
			uint32_t data;

			/* Read GPIO pin2 as Hardware controlled radio state*/
			RTUSBReadMACRegister( pAd, GPIO_CTRL_CFG, &data);
			pAd->StaCfg.bHwRadio = (data & 0x04) ? TRUE : FALSE;

			if (pAd->StaCfg.bRadio != (pAd->StaCfg.bHwRadio && pAd->StaCfg.bSwRadio))
			{
				pAd->StaCfg.bRadio = (pAd->StaCfg.bHwRadio && pAd->StaCfg.bSwRadio);
				DBGPRINT_RAW(RT_DEBUG_ERROR, ("!!! Radio %s !!!\n",
								(pAd->StaCfg.bRadio == TRUE ? "On" : "Off")));
				if (pAd->StaCfg.bRadio == TRUE)
				{
					MlmeRadioOn(pAd);
					pAd->ExtraInfo = EXTRA_INFO_CLEAR;
				}
				else
				{
					MlmeRadioOff(pAd);
					pAd->ExtraInfo = HW_RADIO_OFF;
				}
			}
		}
#endif /* CONFIG_STA_SUPPORT */

	return NDIS_STATUS_SUCCESS;
}


static NTSTATUS ResetBulkOutHdlr(IN struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt)
{
	int32_t MACValue = 0;
	UCHAR Index = 0;
	int ret=0;
	PHT_TX_CONTEXT	pHTTXContext;
	unsigned long IrqFlags;

	DBGPRINT(RT_DEBUG_TRACE, ("CMDTHREAD_RESET_BULK_OUT(ResetPipeid=0x%0x)===>\n", pAd->bulkResetPipeid));

	/* All transfers must be aborted or cancelled before attempting to reset the pipe. */
	/*RTUSBCancelPendingBulkOutIRP(pAd);*/
	/* Wait 10ms to let previous packet that are already in HW FIFO to clear. by MAXLEE 12-25-2007*/
	do
	{
		if(RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))
			break;

		RTUSBReadMACRegister(pAd, TXRXQ_PCNT, &MACValue);
		if ((MACValue & 0xf00000/*0x800000*/) == 0)
			break;

		Index++;
		RtmpusecDelay(10000);
	}while(Index < 100);

	USB_CFG_READ(pAd, &MACValue);

	/* 2nd, to prevent Read Register error, we check the validity.*/
	if ((MACValue & 0xc00000) == 0)
		USB_CFG_READ(pAd, &MACValue);

	/* 3rd, to prevent Read Register error, we check the validity.*/
	if ((MACValue & 0xc00000) == 0)
		USB_CFG_READ(pAd, &MACValue);

	MACValue |= 0x80000;
	USB_CFG_WRITE(pAd, MACValue);

	/* Wait 1ms to prevent next URB to bulkout before HW reset. by MAXLEE 12-25-2007*/
	RtmpusecDelay(1000);

	MACValue &= (~0x80000);
	USB_CFG_WRITE(pAd, MACValue);
	DBGPRINT(RT_DEBUG_TRACE, ("\tSet 0x2a0 bit19. Clear USB DMA TX path\n"));

	/* Wait 5ms to prevent next URB to bulkout before HW reset. by MAXLEE 12-25-2007*/
	/*RtmpusecDelay(5000);*/

	if ((pAd->bulkResetPipeid & BULKOUT_MGMT_RESET_FLAG) == BULKOUT_MGMT_RESET_FLAG)
	{
		RTMP_CLEAR_FLAG(pAd, fRTMP_ADAPTER_BULKOUT_RESET);

		if (pAd->MgmtRing.TxSwFreeIdx < MGMT_RING_SIZE /* pMLMEContext->bWaitingBulkOut == TRUE */)
			RTUSB_SET_BULK_FLAG(pAd, fRTUSB_BULK_OUT_MLME);

		RTUSBKickBulkOut(pAd);
		DBGPRINT(RT_DEBUG_TRACE, ("\tTX MGMT RECOVER Done!\n"));
	}
	else
	{
		pHTTXContext = &(pAd->TxContext[pAd->bulkResetPipeid]);

		/*NdisAcquireSpinLock(&pAd->BulkOutLock[pAd->bulkResetPipeid]);*/
		RTMP_INT_LOCK(&pAd->BulkOutLock[pAd->bulkResetPipeid], IrqFlags);
		if ( pAd->BulkOutPending[pAd->bulkResetPipeid] == FALSE)
		{
			pAd->BulkOutPending[pAd->bulkResetPipeid] = TRUE;
			pHTTXContext->IRPPending = TRUE;
			pAd->watchDogTxPendingCnt[pAd->bulkResetPipeid] = 1;

			/* no matter what, clean the flag*/
			RTMP_CLEAR_FLAG(pAd, fRTMP_ADAPTER_BULKOUT_RESET);

			/*NdisReleaseSpinLock(&pAd->BulkOutLock[pAd->bulkResetPipeid]);*/
			RTMP_INT_UNLOCK(&pAd->BulkOutLock[pAd->bulkResetPipeid], IrqFlags);

			{
				RTUSBInitHTTxDesc(pAd, pHTTXContext, pAd->bulkResetPipeid,
													pHTTXContext->BulkOutSize,
													RtmpUsbBulkOutDataPacketComplete);

				if ((ret = RTUSB_SUBMIT_URB(pHTTXContext->pUrb))!=0)
				{
						RTMP_INT_LOCK(&pAd->BulkOutLock[pAd->bulkResetPipeid], IrqFlags);
						pAd->BulkOutPending[pAd->bulkResetPipeid] = FALSE;
						pHTTXContext->IRPPending = FALSE;
						pAd->watchDogTxPendingCnt[pAd->bulkResetPipeid] = 0;
						RTMP_INT_UNLOCK(&pAd->BulkOutLock[pAd->bulkResetPipeid], IrqFlags);

						DBGPRINT(RT_DEBUG_ERROR, ("CMDTHREAD_RESET_BULK_OUT:Submit Tx URB failed %d\n", ret));
				}
				else
				{
						RTMP_INT_LOCK(&pAd->BulkOutLock[pAd->bulkResetPipeid], IrqFlags);

						DBGPRINT(RT_DEBUG_TRACE,("\tCMDTHREAD_RESET_BULK_OUT: TxContext[%d]:CWPos=%ld, NBPos=%ld, ENBPos=%ld, bCopy=%d, pending=%d!\n",
											pAd->bulkResetPipeid, pHTTXContext->CurWritePosition, pHTTXContext->NextBulkOutPosition,
											pHTTXContext->ENextBulkOutPosition, pHTTXContext->bCopySavePad,
											pAd->BulkOutPending[pAd->bulkResetPipeid]));
						DBGPRINT(RT_DEBUG_TRACE,("\t\tBulkOut Req=0x%lx, Complete=0x%lx, Other=0x%lx\n",
											pAd->BulkOutReq, pAd->BulkOutComplete, pAd->BulkOutCompleteOther));

						RTMP_INT_UNLOCK(&pAd->BulkOutLock[pAd->bulkResetPipeid], IrqFlags);

						DBGPRINT(RT_DEBUG_TRACE, ("\tCMDTHREAD_RESET_BULK_OUT: Submit Tx DATA URB for failed BulkReq(0x%lx) Done, status=%d!\n",
											pAd->bulkResetReq[pAd->bulkResetPipeid],
											RTMP_USB_URB_STATUS_GET(pHTTXContext->pUrb)));
				}
			}
		}
		else
		{
			/*NdisReleaseSpinLock(&pAd->BulkOutLock[pAd->bulkResetPipeid]);*/
			/*RTMP_INT_UNLOCK(&pAd->BulkOutLock[pAd->bulkResetPipeid], IrqFlags);*/

			DBGPRINT(RT_DEBUG_ERROR, ("CmdThread : TX DATA RECOVER FAIL for BulkReq(0x%lx) because BulkOutPending[%d] is TRUE!\n",
								pAd->bulkResetReq[pAd->bulkResetPipeid], pAd->bulkResetPipeid));

			if (pAd->bulkResetPipeid == 0)
			{
				UCHAR	pendingContext = 0;
				PHT_TX_CONTEXT pHTTXContext = (PHT_TX_CONTEXT)(&pAd->TxContext[pAd->bulkResetPipeid ]);
				PTX_CONTEXT pMLMEContext = (PTX_CONTEXT)(pAd->MgmtRing.Cell[pAd->MgmtRing.TxDmaIdx].AllocVa);
				PTX_CONTEXT pNULLContext = (PTX_CONTEXT)(&pAd->PsPollContext);
				PTX_CONTEXT pPsPollContext = (PTX_CONTEXT)(&pAd->NullContext);

				if (pHTTXContext->IRPPending)
					pendingContext |= 1;
				else if (pMLMEContext->IRPPending)
					pendingContext |= 2;
				else if (pNULLContext->IRPPending)
					pendingContext |= 4;
				else if (pPsPollContext->IRPPending)
					pendingContext |= 8;
				else
					pendingContext = 0;

				DBGPRINT(RT_DEBUG_ERROR, ("\tTX Occupied by %d!\n", pendingContext));
			}

			/* no matter what, clean the flag*/
			RTMP_CLEAR_FLAG(pAd, fRTMP_ADAPTER_BULKOUT_RESET);

			RTMP_INT_UNLOCK(&pAd->BulkOutLock[pAd->bulkResetPipeid], IrqFlags);

			RTUSB_SET_BULK_FLAG(pAd, (fRTUSB_BULK_OUT_DATA_NORMAL << pAd->bulkResetPipeid));
		}

		RTMPDeQueuePacket(pAd, FALSE, NUM_OF_TX_RING, MAX_TX_PROCESS);
		/*RTUSBKickBulkOut(pAd);*/
	}

	DBGPRINT_RAW(RT_DEBUG_TRACE, ("CmdThread : CMDTHREAD_RESET_BULK_OUT<===\n"));
	return NDIS_STATUS_SUCCESS;


}


/* All transfers must be aborted or cancelled before attempting to reset the pipe.*/
static NTSTATUS ResetBulkInHdlr(IN struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt)
{
	uint32_t MACValue;
	NTSTATUS ntStatus;

	DBGPRINT_RAW(RT_DEBUG_TRACE, ("CmdThread : CMDTHREAD_RESET_BULK_IN === >\n"));

#ifdef CONFIG_STA_SUPPORT
	if(RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_IDLE_RADIO_OFF))
	{
		RTMP_CLEAR_FLAG(pAd, fRTMP_ADAPTER_BULKIN_RESET);
		return NDIS_STATUS_SUCCESS;
	}
#endif /* CONFIG_STA_SUPPORT */

	{
		/*while ((atomic_read(&pAd->PendingRx) > 0) && (!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))) */
		if((pAd->PendingRx > 0) && (!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST)))
		{
			DBGPRINT_RAW(RT_DEBUG_ERROR, ("BulkIn IRP Pending!!!\n"));
			RTUSBCancelPendingBulkInIRP(pAd);
			RtmpusecDelay(100000);
			pAd->PendingRx = 0;
		}
	}

	/* Wait 10ms before reading register.*/
	RtmpusecDelay(10000);
	ntStatus = RTUSBReadMACRegister(pAd, MAC_CSR0, &MACValue);

	/* It must be removed. Or ATE will have no RX success. */
	if ((NT_SUCCESS(ntStatus) == TRUE) &&
				(!(RTMP_TEST_FLAG(pAd, (fRTMP_ADAPTER_RESET_IN_PROGRESS | fRTMP_ADAPTER_RADIO_OFF |
												fRTMP_ADAPTER_HALT_IN_PROGRESS | fRTMP_ADAPTER_NIC_NOT_EXIST)))))
	{
		UCHAR	i;

		if (RTMP_TEST_FLAG(pAd, (fRTMP_ADAPTER_RESET_IN_PROGRESS | fRTMP_ADAPTER_RADIO_OFF |
									fRTMP_ADAPTER_HALT_IN_PROGRESS | fRTMP_ADAPTER_NIC_NOT_EXIST)))
			return NDIS_STATUS_SUCCESS;

		pAd->NextRxBulkInPosition = pAd->RxContext[pAd->NextRxBulkInIndex].BulkInOffset;

		DBGPRINT(RT_DEBUG_TRACE, ("BULK_IN_RESET: NBIIdx=0x%x,NBIRIdx=0x%x, BIRPos=0x%lx. BIReq=x%lx, BIComplete=0x%lx, BICFail0x%lx\n",
					pAd->NextRxBulkInIndex,  pAd->NextRxBulkInReadIndex, pAd->NextRxBulkInPosition, pAd->BulkInReq, pAd->BulkInComplete, pAd->BulkInCompleteFail));

		for (i = 0; i < RX_RING_SIZE; i++)
		{
 			DBGPRINT(RT_DEBUG_TRACE, ("\tRxContext[%d]: IRPPending=%d, InUse=%d, Readable=%d!\n"
							, i, pAd->RxContext[i].IRPPending, pAd->RxContext[i].InUse, pAd->RxContext[i].Readable));
		}

		RTMP_CLEAR_FLAG(pAd, fRTMP_ADAPTER_BULKIN_RESET);

		for (i = 0; i < pAd->CommonCfg.NumOfBulkInIRP; i++)
		{
			/*RTUSBBulkReceive(pAd);*/
			PRX_CONTEXT		pRxContext;
			PURB			pUrb;
			int				ret = 0;
			unsigned long	IrqFlags;

			RTMP_IRQ_LOCK(&pAd->BulkInLock, IrqFlags);
			pRxContext = &(pAd->RxContext[pAd->NextRxBulkInIndex]);

			if ((pAd->PendingRx > 0) || (pRxContext->Readable == TRUE) || (pRxContext->InUse == TRUE))
			{
				RTMP_IRQ_UNLOCK(&pAd->BulkInLock, IrqFlags);
				return NDIS_STATUS_SUCCESS;
			}

			pRxContext->InUse = TRUE;
			pRxContext->IRPPending = TRUE;
			pAd->PendingRx++;
			pAd->BulkInReq++;
			RTMP_IRQ_UNLOCK(&pAd->BulkInLock, IrqFlags);

			/* Init Rx context descriptor*/
			RTUSBInitRxDesc(pAd, pRxContext);
			pUrb = pRxContext->pUrb;
			if ((ret = RTUSB_SUBMIT_URB(pUrb))!=0)
			{	/* fail*/
				RTMP_IRQ_LOCK(&pAd->BulkInLock, IrqFlags);
				pRxContext->InUse = FALSE;
				pRxContext->IRPPending = FALSE;
				pAd->PendingRx--;
				pAd->BulkInReq--;
				RTMP_IRQ_UNLOCK(&pAd->BulkInLock, IrqFlags);
				DBGPRINT(RT_DEBUG_ERROR, ("CMDTHREAD_RESET_BULK_IN: Submit Rx URB failed(%d), status=%d\n", ret, RTMP_USB_URB_STATUS_GET(pUrb)));
			}
			else
			{	/* success*/
				/*DBGPRINT(RT_DEBUG_TRACE, ("BIDone, Pend=%d,BIIdx=%d,BIRIdx=%d!\n", */
				/*							pAd->PendingRx, pAd->NextRxBulkInIndex, pAd->NextRxBulkInReadIndex));*/
				DBGPRINT_RAW(RT_DEBUG_TRACE, ("CMDTHREAD_RESET_BULK_IN: Submit Rx URB Done, status=%d!\n", RTMP_USB_URB_STATUS_GET(pUrb)));
				ASSERT((pRxContext->InUse == pRxContext->IRPPending));
			}
		}

	}
	else
	{
		/* Card must be removed*/
		if (NT_SUCCESS(ntStatus) != TRUE)
		{
			RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST);
			DBGPRINT_RAW(RT_DEBUG_ERROR, ("CMDTHREAD_RESET_BULK_IN: Read Register Failed!Card must be removed!!\n\n"));
		}
		else
			DBGPRINT_RAW(RT_DEBUG_ERROR, ("CMDTHREAD_RESET_BULK_IN: Cannot do bulk in because flags(0x%lx) on !\n", pAd->Flags));
	}

	DBGPRINT_RAW(RT_DEBUG_TRACE, ("CmdThread : CMDTHREAD_RESET_BULK_IN <===\n"));
	return NDIS_STATUS_SUCCESS;
}


static NTSTATUS SetAsicWcidHdlr(IN struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt)
{
	RT_SET_ASIC_WCID	SetAsicWcid;
	USHORT		offset;
	uint32_t 	MACValue, MACRValue = 0;
	SetAsicWcid = *((PRT_SET_ASIC_WCID)(CMDQelmt->buffer));

	if (SetAsicWcid.WCID >= MAX_LEN_OF_MAC_TABLE)
		return NDIS_STATUS_FAILURE;

	offset = MAC_WCID_BASE + ((UCHAR)SetAsicWcid.WCID)*HW_WCID_ENTRY_SIZE;

	DBGPRINT_RAW(RT_DEBUG_TRACE, ("CmdThread : CMDTHREAD_SET_ASIC_WCID : WCID = %ld, SetTid  = %lx, DeleteTid = %lx.\n",
						SetAsicWcid.WCID, SetAsicWcid.SetTid, SetAsicWcid.DeleteTid));

	MACValue = (pAd->MacTab.Content[SetAsicWcid.WCID].Addr[3]<<24)+(pAd->MacTab.Content[SetAsicWcid.WCID].Addr[2]<<16)+(pAd->MacTab.Content[SetAsicWcid.WCID].Addr[1]<<8)+(pAd->MacTab.Content[SetAsicWcid.WCID].Addr[0]);

	DBGPRINT_RAW(RT_DEBUG_TRACE, ("1-MACValue= %x,\n", MACValue));
	RTUSBWriteMACRegister(pAd, offset, MACValue, FALSE);
	/* Read bitmask*/
	RTUSBReadMACRegister(pAd, offset+4, &MACRValue);
	if ( SetAsicWcid.DeleteTid != 0xffffffff)
		MACRValue &= (~SetAsicWcid.DeleteTid);
	if (SetAsicWcid.SetTid != 0xffffffff)
		MACRValue |= (SetAsicWcid.SetTid);

	MACRValue &= 0xffff0000;
	MACValue = (pAd->MacTab.Content[SetAsicWcid.WCID].Addr[5]<<8)+pAd->MacTab.Content[SetAsicWcid.WCID].Addr[4];
	MACValue |= MACRValue;
	RTUSBWriteMACRegister(pAd, offset+4, MACValue, FALSE);

	DBGPRINT_RAW(RT_DEBUG_TRACE, ("2-MACValue= %x,\n", MACValue));

	return NDIS_STATUS_SUCCESS;
}

static NTSTATUS DelAsicWcidHdlr(IN struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt)
{
	RT_SET_ASIC_WCID SetAsicWcid;
	SetAsicWcid = *((PRT_SET_ASIC_WCID)(CMDQelmt->buffer));

	if (SetAsicWcid.WCID >= MAX_LEN_OF_MAC_TABLE)
		return NDIS_STATUS_FAILURE;

        AsicDelWcidTab(pAd, (UCHAR)SetAsicWcid.WCID);

        return NDIS_STATUS_SUCCESS;
}

static NTSTATUS SetWcidSecInfoHdlr(IN struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt)
{
	PRT_ASIC_WCID_SEC_INFO pInfo;

	pInfo = (PRT_ASIC_WCID_SEC_INFO)CMDQelmt->buffer;
	RTMPSetWcidSecurityInfo(pAd,
							 pInfo->BssIdx,
							 pInfo->KeyIdx,
							 pInfo->CipherAlg,
							 pInfo->Wcid,
							 pInfo->KeyTabFlag);

	return NDIS_STATUS_SUCCESS;
}


static NTSTATUS SetAsicWcidIVEIVHdlr(IN struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt)
{
	PRT_ASIC_WCID_IVEIV_ENTRY pInfo;

	pInfo = (PRT_ASIC_WCID_IVEIV_ENTRY)CMDQelmt->buffer;
	AsicUpdateWCIDIVEIV(pAd,
						  pInfo->Wcid,
						  pInfo->Iv,
						  pInfo->Eiv);

	return NDIS_STATUS_SUCCESS;
}


static NTSTATUS SetAsicWcidAttrHdlr(IN struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt)
{
	PRT_ASIC_WCID_ATTR_ENTRY pInfo;

	pInfo = (PRT_ASIC_WCID_ATTR_ENTRY)CMDQelmt->buffer;
	AsicUpdateWcidAttributeEntry(pAd,
								  pInfo->BssIdx,
								  pInfo->KeyIdx,
								  pInfo->CipherAlg,
								  pInfo->Wcid,
								  pInfo->KeyTabFlag);

	return NDIS_STATUS_SUCCESS;
}

static NTSTATUS SETAsicSharedKeyHdlr(IN struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt)
{
	PRT_ASIC_SHARED_KEY pInfo;

	pInfo = (PRT_ASIC_SHARED_KEY)CMDQelmt->buffer;
	AsicAddSharedKeyEntry(pAd,
						       pInfo->BssIndex,
							pInfo->KeyIdx,
							&pInfo->CipherKey);

	return NDIS_STATUS_SUCCESS;
}

static NTSTATUS SetAsicPairwiseKeyHdlr(IN struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt)
{
	PRT_ASIC_PAIRWISE_KEY pInfo;

	pInfo = (PRT_ASIC_PAIRWISE_KEY)CMDQelmt->buffer;
	AsicAddPairwiseKeyEntry(pAd,
							 pInfo->WCID,
							 &pInfo->CipherKey);

	return NDIS_STATUS_SUCCESS;
}

#ifdef CONFIG_STA_SUPPORT
static NTSTATUS SetPortSecuredHdlr(IN struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt)
{
	STA_PORT_SECURED(pAd);
	return NDIS_STATUS_SUCCESS;
}
#endif /* CONFIG_STA_SUPPORT */


static NTSTATUS RemovePairwiseKeyHdlr(IN struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt)
{
	UCHAR Wcid = *((u8 *)(CMDQelmt->buffer));

	AsicRemovePairwiseKeyEntry(pAd, Wcid);
	return NDIS_STATUS_SUCCESS;
}


static NTSTATUS SetClientMACEntryHdlr(IN struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt)
{
	PRT_SET_ASIC_WCID pInfo;

	pInfo = (PRT_SET_ASIC_WCID)CMDQelmt->buffer;
	AsicUpdateRxWCIDTable(pAd, pInfo->WCID, pInfo->Addr);
	return NDIS_STATUS_SUCCESS;
}


static NTSTATUS UpdateProtectHdlr(IN struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt)
{
	PRT_ASIC_PROTECT_INFO pAsicProtectInfo;

	pAsicProtectInfo = (PRT_ASIC_PROTECT_INFO)CMDQelmt->buffer;
	AsicUpdateProtect(pAd, pAsicProtectInfo->OperationMode, pAsicProtectInfo->SetMask,
							pAsicProtectInfo->bDisableBGProtect, pAsicProtectInfo->bNonGFExist);

	return NDIS_STATUS_SUCCESS;
}



#ifdef CONFIG_AP_SUPPORT
static NTSTATUS APUpdateCapabilityAndErpieHdlr(IN struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt)
{
	APUpdateCapabilityAndErpIe(pAd);
	return NDIS_STATUS_SUCCESS;
}
#endif /* CONFIG_AP_SUPPORT */


#ifdef CONFIG_AP_SUPPORT
static NTSTATUS _802_11_CounterMeasureHdlr(IN struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt)
{
	IF_DEV_CONFIG_OPMODE_ON_AP(pAd)
	{
		MAC_TABLE_ENTRY *pEntry;

		pEntry = (MAC_TABLE_ENTRY *)CMDQelmt->buffer;
		HandleCounterMeasure(pAd, pEntry);
	}

	return NDIS_STATUS_SUCCESS;
}
#endif /* CONFIG_AP_SUPPORT */


#ifdef CONFIG_STA_SUPPORT
static NTSTATUS SetPSMBitHdlr(IN struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt)
{
	IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
	{
		USHORT *pPsm = (USHORT *)CMDQelmt->buffer;
		MlmeSetPsmBit(pAd, *pPsm);
	}

	return NDIS_STATUS_SUCCESS;
}


static NTSTATUS ForceWakeUpHdlr(IN struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt)
{
	IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
		AsicForceWakeup(pAd, TRUE);

	return NDIS_STATUS_SUCCESS;
}


static NTSTATUS ForceSleepAutoWakeupHdlr(IN struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt)
{
	USHORT  TbttNumToNextWakeUp;
	USHORT  NextDtim = pAd->StaCfg.DtimPeriod;
	ULONG   Now;

	NdisGetSystemUpTime(&Now);
	NextDtim -= (USHORT)(Now - pAd->StaCfg.LastBeaconRxTime)/pAd->CommonCfg.BeaconPeriod;

	TbttNumToNextWakeUp = pAd->StaCfg.DefaultListenCount;
	if (OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_RECEIVE_DTIM) && (TbttNumToNextWakeUp > NextDtim))
		TbttNumToNextWakeUp = NextDtim;

	RTMP_SET_PSM_BIT(pAd, PWR_SAVE);

	/* if WMM-APSD is failed, try to disable following line*/
	AsicSleepThenAutoWakeup(pAd, TbttNumToNextWakeUp);

	return NDIS_STATUS_SUCCESS;
}


NTSTATUS QkeriodicExecutHdlr(IN struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt)
{
	StaQuickResponeForRateUpExec(NULL, pAd, NULL, NULL);
	return NDIS_STATUS_SUCCESS;
}
#endif /* CONFIG_STA_SUPPORT*/


#ifdef CONFIG_AP_SUPPORT
static NTSTATUS APEnableTXBurstHdlr(IN struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt)
{
	IF_DEV_CONFIG_OPMODE_ON_AP(pAd)
	{
		EDCA_AC_CFG_STRUC Ac0Cfg;
		DBGPRINT(RT_DEBUG_TRACE, ("CmdThread::CMDTHREAD_AP_ENABLE_TX_BURST  \n"));

		RTUSBReadMACRegister(pAd, EDCA_AC0_CFG, &Ac0Cfg.word);
		Ac0Cfg.field.AcTxop = 0x20;
		RTUSBWriteMACRegister(pAd, EDCA_AC0_CFG, Ac0Cfg.word, FALSE);
	}

	return NDIS_STATUS_SUCCESS;
}


static NTSTATUS APDisableTXBurstHdlr(IN struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt)
{
	IF_DEV_CONFIG_OPMODE_ON_AP(pAd)
	{
		EDCA_AC_CFG_STRUC Ac0Cfg;
		DBGPRINT(RT_DEBUG_TRACE, ("CmdThread::CMDTHREAD_AP_DISABLE_TX_BURST  \n"));

		RTUSBReadMACRegister(pAd, EDCA_AC0_CFG, &Ac0Cfg.word);
		Ac0Cfg.field.AcTxop = 0x0;
		RTUSBWriteMACRegister(pAd, EDCA_AC0_CFG, Ac0Cfg.word, FALSE);
	}

	return NDIS_STATUS_SUCCESS;
}


static NTSTATUS APAdjustEXPAckTimeHdlr(IN struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt)
{
	IF_DEV_CONFIG_OPMODE_ON_AP(pAd)
	{
		DBGPRINT(RT_DEBUG_TRACE, ("CmdThread::CMDTHREAD_AP_ADJUST_EXP_ACK_TIME  \n"));
		RTUSBWriteMACRegister(pAd, EXP_ACK_TIME, 0x005400ca, FALSE);
	}

	return NDIS_STATUS_SUCCESS;
}


static NTSTATUS APRecoverEXPAckTimeHdlr(IN struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt)
{
	IF_DEV_CONFIG_OPMODE_ON_AP(pAd)
	{
		DBGPRINT(RT_DEBUG_TRACE, ("CmdThread::CMDTHREAD_AP_RECOVER_EXP_ACK_TIME  \n"));
		RTUSBWriteMACRegister(pAd, EXP_ACK_TIME, 0x002400ca, FALSE);
	}

	return NDIS_STATUS_SUCCESS;
}
#endif /* CONFIG_AP_SUPPORT */





#ifdef CONFIG_AP_SUPPORT
static NTSTATUS ChannelRescanHdlr(IN struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt)
{
	DBGPRINT(RT_DEBUG_TRACE, ("cmd> Re-scan channel! \n"));

	pAd->CommonCfg.Channel = AP_AUTO_CH_SEL(pAd, TRUE);
	/* If WMODE_CAP_N(phymode) and BW=40 check extension channel, after select channel  */
	N_ChannelCheck(pAd);

	DBGPRINT(RT_DEBUG_TRACE, ("cmd> Switch to %d! \n", pAd->CommonCfg.Channel));
	APStop(pAd);
	APStartUp(pAd);

#ifdef AP_QLOAD_SUPPORT
	QBSS_LoadAlarmResume(pAd);
#endif /* AP_QLOAD_SUPPORT */

	return NDIS_STATUS_SUCCESS;
}
#endif /* CONFIG_AP_SUPPORT*/


#ifdef LINUX
#ifdef RT_CFG80211_SUPPORT
static NTSTATUS RegHintHdlr (struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt)
{
	RT_CFG80211_CRDA_REG_HINT(pAd, CMDQelmt->buffer, CMDQelmt->bufferlength);
	return NDIS_STATUS_SUCCESS;
}

static NTSTATUS RegHint11DHdlr(struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt)
{
	RT_CFG80211_CRDA_REG_HINT11D(pAd, CMDQelmt->buffer, CMDQelmt->bufferlength);
	return NDIS_STATUS_SUCCESS;
}

static NTSTATUS RT_Mac80211_ScanEnd(struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt)
{
	RT_CFG80211_SCAN_END(pAd, FALSE);
	return NDIS_STATUS_SUCCESS;
}

static NTSTATUS RT_Mac80211_ConnResultInfom(struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt)
{
#ifdef CONFIG_STA_SUPPORT
	RT_CFG80211_CONN_RESULT_INFORM(pAd, pAd->MlmeAux.Bssid,
								pAd->StaCfg.ReqVarIEs, pAd->StaCfg.ReqVarIELen,
								CMDQelmt->buffer, CMDQelmt->bufferlength,
								TRUE);
#endif /*CONFIG_STA_SUPPORT*/
	return NDIS_STATUS_SUCCESS;
}
#endif /* RT_CFG80211_SUPPORT */
#endif /* LINUX */



#ifdef STREAM_MODE_SUPPORT
static NTSTATUS UpdateTXChainAddress(struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt)
{
	AsicUpdateTxChainAddress(pAd, CMDQelmt->buffer);
	return NDIS_STATUS_SUCCESS;
}
#endif /* STREAM_MODE_SUPPORT */



typedef NTSTATUS (*CMDHdlr)(struct rtmp_adapter *pAd, IN PCmdQElmt CMDQelmt);

static CMDHdlr CMDHdlrTable[] = {
	ResetBulkOutHdlr,				/* CMDTHREAD_RESET_BULK_OUT*/
	ResetBulkInHdlr,					/* CMDTHREAD_RESET_BULK_IN*/
	CheckGPIOHdlr,					/* CMDTHREAD_CHECK_GPIO	*/
	SetAsicWcidHdlr,					/* CMDTHREAD_SET_ASIC_WCID*/
	DelAsicWcidHdlr,					/* CMDTHREAD_DEL_ASIC_WCID*/
	SetClientMACEntryHdlr,			/* CMDTHREAD_SET_CLIENT_MAC_ENTRY*/

#ifdef CONFIG_STA_SUPPORT
	SetPSMBitHdlr,					/* CMDTHREAD_SET_PSM_BIT*/
	ForceWakeUpHdlr,				/* CMDTHREAD_FORCE_WAKE_UP*/
	ForceSleepAutoWakeupHdlr,		/* CMDTHREAD_FORCE_SLEEP_AUTO_WAKEUP*/
	QkeriodicExecutHdlr,				/* CMDTHREAD_QKERIODIC_EXECUT*/
#else
	NULL,
	NULL,
	NULL,
	NULL,
#endif /* CONFIG_STA_SUPPORT */

#ifdef CONFIG_AP_SUPPORT
	APUpdateCapabilityAndErpieHdlr,	/* CMDTHREAD_AP_UPDATE_CAPABILITY_AND_ERPIE*/
	APEnableTXBurstHdlr,			/* CMDTHREAD_AP_ENABLE_TX_BURST*/
	APDisableTXBurstHdlr,			/* CMDTHREAD_AP_DISABLE_TX_BURST*/
	APAdjustEXPAckTimeHdlr,		/* CMDTHREAD_AP_ADJUST_EXP_ACK_TIME*/
	APRecoverEXPAckTimeHdlr,		/* CMDTHREAD_AP_RECOVER_EXP_ACK_TIME*/
	ChannelRescanHdlr,				/* CMDTHREAD_CHAN_RESCAN*/
#else
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
#endif /* CONFIG_AP_SUPPORT */

    NULL,

	NULL,

	/* Security related */
	SetWcidSecInfoHdlr,				/* CMDTHREAD_SET_WCID_SEC_INFO*/
	SetAsicWcidIVEIVHdlr,			/* CMDTHREAD_SET_ASIC_WCID_IVEIV*/
	SetAsicWcidAttrHdlr,				/* CMDTHREAD_SET_ASIC_WCID_ATTR*/
	SETAsicSharedKeyHdlr,			/* CMDTHREAD_SET_ASIC_SHARED_KEY*/
	SetAsicPairwiseKeyHdlr,			/* CMDTHREAD_SET_ASIC_PAIRWISE_KEY*/
	RemovePairwiseKeyHdlr,			/* CMDTHREAD_REMOVE_PAIRWISE_KEY*/

#ifdef CONFIG_STA_SUPPORT
	SetPortSecuredHdlr,				/* CMDTHREAD_SET_PORT_SECURED*/
#else
	NULL,
#endif /* CONFIG_STA_SUPPORT */

#ifdef CONFIG_AP_SUPPORT
	_802_11_CounterMeasureHdlr,	/* CMDTHREAD_802_11_COUNTER_MEASURE*/
#else
	NULL,
#endif /* CONFIG_AP_SUPPORT */

	UpdateProtectHdlr,				/* CMDTHREAD_UPDATE_PROTECT*/


#ifdef LINUX
#ifdef RT_CFG80211_SUPPORT
	RegHintHdlr,
	RegHint11DHdlr,
	RT_Mac80211_ScanEnd,
	RT_Mac80211_ConnResultInfom,
#else
	NULL,
	NULL,
	NULL,
	NULL,
#endif /* RT_CFG80211_SUPPORT */

#else
	NULL,
	NULL,
	NULL,
	NULL,
#endif /* LINUX */

	NULL,

	NULL,

#ifdef STREAM_MODE_SUPPORT
	UpdateTXChainAddress, /* CMDTHREAD_UPDATE_TX_CHAIN_ADDRESS */
#else
	NULL,
#endif

	NULL,
};


static inline BOOLEAN ValidCMD(IN PCmdQElmt CMDQelmt)
{
	SHORT CMDIndex = CMDQelmt->command - CMDTHREAD_FIRST_CMD_ID;
	USHORT CMDHdlrTableLength= sizeof(CMDHdlrTable) / sizeof(CMDHdlr);

	if ( (CMDIndex >= 0) && (CMDIndex < CMDHdlrTableLength))
	{
		if (CMDHdlrTable[CMDIndex] > 0)
			return TRUE;
		else
		{
			DBGPRINT(RT_DEBUG_ERROR, ("No corresponding CMDHdlr for this CMD(%x)\n",  CMDQelmt->command));
			return FALSE;
		}
	}
	else
	{
		DBGPRINT(RT_DEBUG_ERROR, ("CMD(%x) is out of boundary\n", CMDQelmt->command));
		return FALSE;
	}
}


VOID CMDHandler(struct rtmp_adapter *pAd)
{
	PCmdQElmt		cmdqelmt;
	int 	NdisStatus = NDIS_STATUS_SUCCESS;
	NTSTATUS		ntStatus;
/*	unsigned long	IrqFlags;*/

	while (pAd && pAd->CmdQ.size > 0)
	{
		NdisStatus = NDIS_STATUS_SUCCESS;

		NdisAcquireSpinLock(&pAd->CmdQLock);
		RTThreadDequeueCmd(&pAd->CmdQ, &cmdqelmt);
		NdisReleaseSpinLock(&pAd->CmdQLock);

		if (cmdqelmt == NULL)
			break;


		if(!(RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST) || RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_HALT_IN_PROGRESS)))
		{
			if(ValidCMD(cmdqelmt))
				ntStatus = (*CMDHdlrTable[cmdqelmt->command - CMDTHREAD_FIRST_CMD_ID])(pAd, cmdqelmt);
		}

		if (cmdqelmt->CmdFromNdis == TRUE)
		{
			if (cmdqelmt->buffer != NULL)
				kfree(cmdqelmt->buffer);
			kfree(cmdqelmt);
		}
		else
		{
			if ((cmdqelmt->buffer != NULL) && (cmdqelmt->bufferlength != 0))
				kfree(cmdqelmt->buffer);
			kfree(cmdqelmt);
		}
	}	/* end of while */
}


VOID RTUSBWatchDog(struct rtmp_adapter *pAd)
{
	PHT_TX_CONTEXT pHTTXContext;
	int idx;
	ULONG irqFlags;
	PURB pUrb;
	BOOLEAN needDumpSeq = FALSE;
	uint32_t MACValue;

	if(RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))
		return;

#ifdef CONFIG_STA_SUPPORT
	if(RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_IDLE_RADIO_OFF))
		return;
#endif /* CONFIG_STA_SUPPORT */

	return;
}

#endif /* RTMP_MAC_USB */

