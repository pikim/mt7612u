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
	ap_cfg.c

    Abstract:
    IOCTL related subroutines

    Revision History:
    Who          When          What
    ---------    ----------    ----------------------------------------------
*/


#include "rt_config.h"


#define A_BAND_REGION_0				0
#define A_BAND_REGION_1				1
#define A_BAND_REGION_2				2
#define A_BAND_REGION_3				3
#define A_BAND_REGION_4				4
#define A_BAND_REGION_5				5
#define A_BAND_REGION_6				6
#define A_BAND_REGION_7				7
#define A_BAND_REGION_8				8
#define A_BAND_REGION_9				9
#define A_BAND_REGION_10			10

#define G_BAND_REGION_0				0
#define G_BAND_REGION_1				1
#define G_BAND_REGION_2				2
#define G_BAND_REGION_3				3
#define G_BAND_REGION_4				4
#define G_BAND_REGION_5				5
#define G_BAND_REGION_6				6

COUNTRY_CODE_TO_COUNTRY_REGION allCountry[] = {
	/* {Country Number, ISO Name, Country Name, Support 11A, 11A Country Region, Support 11G, 11G Country Region} */
	{0,		"DB",	"Debug",				TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_5},
	{8,		"AL",	"ALBANIA",				FALSE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{12,	"DZ",	"ALGERIA",				FALSE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{32,	"AR",	"ARGENTINA",			TRUE,	A_BAND_REGION_3,	TRUE,	G_BAND_REGION_1},
	{51,	"AM",	"ARMENIA",				TRUE,	A_BAND_REGION_2,	TRUE,	G_BAND_REGION_1},
	{36,	"AU",	"AUSTRALIA",			TRUE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{40,	"AT",	"AUSTRIA",				TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{31,	"AZ",	"AZERBAIJAN",			TRUE,	A_BAND_REGION_2,	TRUE,	G_BAND_REGION_1},
	{48,	"BH",	"BAHRAIN",				TRUE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{112,	"BY",	"BELARUS",				FALSE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{56,	"BE",	"BELGIUM",				TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{84,	"BZ",	"BELIZE",				TRUE,	A_BAND_REGION_4,	TRUE,	G_BAND_REGION_1},
	{68,	"BO",	"BOLIVIA",				TRUE,	A_BAND_REGION_4,	TRUE,	G_BAND_REGION_1},
	{76,	"BR",	"BRAZIL",				TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{96,	"BN",	"BRUNEI DARUSSALAM",	TRUE,	A_BAND_REGION_4,	TRUE,	G_BAND_REGION_1},
	{100,	"BG",	"BULGARIA",				TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{124,	"CA",	"CANADA",				TRUE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_0},
	{152,	"CL",	"CHILE",				TRUE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{156,	"CN",	"CHINA",				TRUE,	A_BAND_REGION_4,	TRUE,	G_BAND_REGION_1},
	{170,	"CO",	"COLOMBIA",				TRUE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_0},
	{188,	"CR",	"COSTA RICA",			FALSE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{191,	"HR",	"CROATIA",				TRUE,	A_BAND_REGION_2,	TRUE,	G_BAND_REGION_1},
	{196,	"CY",	"CYPRUS",				TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{203,	"CZ",	"CZECH REPUBLIC",		TRUE,	A_BAND_REGION_2,	TRUE,	G_BAND_REGION_1},
	{208,	"DK",	"DENMARK",				TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{214,	"DO",	"DOMINICAN REPUBLIC",	TRUE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_0},
	{218,	"EC",	"ECUADOR",				FALSE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{818,	"EG",	"EGYPT",				TRUE,	A_BAND_REGION_2,	TRUE,	G_BAND_REGION_1},
	{222,	"SV",	"EL SALVADOR",			FALSE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{233,	"EE",	"ESTONIA",				TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{246,	"FI",	"FINLAND",				TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{250,	"FR",	"FRANCE",				TRUE,	A_BAND_REGION_2,	TRUE,	G_BAND_REGION_1},
	{268,	"GE",	"GEORGIA",				TRUE,	A_BAND_REGION_2,	TRUE,	G_BAND_REGION_1},
	{276,	"DE",	"GERMANY",				TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{300,	"GR",	"GREECE",				TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{320,	"GT",	"GUATEMALA",			TRUE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_0},
	{340,	"HN",	"HONDURAS",				FALSE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{344,	"HK",	"HONG KONG",			TRUE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{348,	"HU",	"HUNGARY",				TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{352,	"IS",	"ICELAND",				TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{356,	"IN",	"INDIA",				TRUE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{360,	"ID",	"INDONESIA",			TRUE,	A_BAND_REGION_4,	TRUE,	G_BAND_REGION_1},
	{364,	"IR",	"IRAN",					TRUE,	A_BAND_REGION_4,	TRUE,	G_BAND_REGION_1},
	{372,	"IE",	"IRELAND",				TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{376,	"IL",	"ISRAEL",				FALSE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{380,	"IT",	"ITALY",				TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{392,	"JP",	"JAPAN",				TRUE,	A_BAND_REGION_9,	TRUE,	G_BAND_REGION_1},
	{400,	"JO",	"JORDAN",				TRUE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{398,	"KZ",	"KAZAKHSTAN",			FALSE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{408,	"KP",	"KOREA DEMOCRATIC PEOPLE'S REPUBLIC OF",TRUE,	A_BAND_REGION_5,	TRUE,	G_BAND_REGION_1},
	{410,	"KR",	"KOREA REPUBLIC OF",	TRUE,	A_BAND_REGION_5,	TRUE,	G_BAND_REGION_1},
	{414,	"KW",	"KUWAIT",				FALSE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{428,	"LV",	"LATVIA",				TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{422,	"LB",	"LEBANON",				FALSE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{438,	"LI",	"LIECHTENSTEIN",		TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{440,	"LT",	"LITHUANIA",			TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{442,	"LU",	"LUXEMBOURG",			TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{446,	"MO",	"MACAU",				TRUE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{807,	"MK",	"MACEDONIA",			FALSE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{458,	"MY",	"MALAYSIA",				TRUE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{484,	"MX",	"MEXICO",				TRUE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_0},
	{492,	"MC",	"MONACO",				TRUE,	A_BAND_REGION_2,	TRUE,	G_BAND_REGION_1},
	{504,	"MA",	"MOROCCO",				FALSE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{528,	"NL",	"NETHERLANDS",			TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{554,	"NZ",	"NEW ZEALAND",			TRUE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{578,	"NO",	"NORWAY",				TRUE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_0},
	{512,	"OM",	"OMAN",					TRUE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{586,	"PK",	"PAKISTAN",				FALSE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{591,	"PA",	"PANAMA",				TRUE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_0},
	{604,	"PE",	"PERU",					TRUE,	A_BAND_REGION_4,	TRUE,	G_BAND_REGION_1},
	{608,	"PH",	"PHILIPPINES",			TRUE,	A_BAND_REGION_4,	TRUE,	G_BAND_REGION_1},
	{616,	"PL",	"POLAND",				TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{620,	"PT",	"PORTUGAL",				TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{630,	"PR",	"PUERTO RICO",			TRUE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_0},
	{634,	"QA",	"QATAR",				FALSE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{642,	"RO",	"ROMANIA",				FALSE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{643,	"RU",	"RUSSIA FEDERATION",	FALSE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{682,	"SA",	"SAUDI ARABIA",			FALSE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{702,	"SG",	"SINGAPORE",			TRUE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{703,	"SK",	"SLOVAKIA",				TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{705,	"SI",	"SLOVENIA",				TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{710,	"ZA",	"SOUTH AFRICA",			TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{724,	"ES",	"SPAIN",				TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{752,	"SE",	"SWEDEN",				TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{756,	"CH",	"SWITZERLAND",			TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{760,	"SY",	"SYRIAN ARAB REPUBLIC",	FALSE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{158,	"TW",	"TAIWAN",				TRUE,	A_BAND_REGION_3,	TRUE,	G_BAND_REGION_0},
	{764,	"TH",	"THAILAND",				FALSE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{780,	"TT",	"TRINIDAD AND TOBAGO",	TRUE,	A_BAND_REGION_2,	TRUE,	G_BAND_REGION_1},
	{788,	"TN",	"TUNISIA",				TRUE,	A_BAND_REGION_2,	TRUE,	G_BAND_REGION_1},
	{792,	"TR",	"TURKEY",				TRUE,	A_BAND_REGION_2,	TRUE,	G_BAND_REGION_1},
	{804,	"UA",	"UKRAINE",				FALSE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{784,	"AE",	"UNITED ARAB EMIRATES",	FALSE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{826,	"GB",	"UNITED KINGDOM",		TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{840,	"US",	"UNITED STATES",		TRUE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_0},
	{858,	"UY",	"URUGUAY",				TRUE,	A_BAND_REGION_5,	TRUE,	G_BAND_REGION_1},
	{860,	"UZ",	"UZBEKISTAN",			TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_0},
	{862,	"VE",	"VENEZUELA",			TRUE,	A_BAND_REGION_5,	TRUE,	G_BAND_REGION_1},
	{704,	"VN",	"VIET NAM",				FALSE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{887,	"YE",	"YEMEN",				FALSE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{716,	"ZW",	"ZIMBABWE",				FALSE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{999,	"",	"",	0,	0,	0,	0}
};

#define NUM_OF_COUNTRIES	(sizeof(allCountry)/sizeof(COUNTRY_CODE_TO_COUNTRY_REGION))


INT Set_CountryString_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg);

INT Set_CountryCode_Proc(
    IN  struct rtmp_adapter *  pAdapter,
    IN  char *         arg);

#ifdef SPECIFIC_TX_POWER_SUPPORT
INT Set_AP_PKT_PWR(
    IN  struct rtmp_adapter *  pAdapter,
    IN  char *         arg);
#endif /* SPECIFIC_TX_POWER_SUPPORT */

INT Set_AP_PROBE_RSP_TIMES(
    IN  struct rtmp_adapter *  pAdapter,
    IN  char *         arg);

INT Set_AP_SSID_Proc(
    IN  struct rtmp_adapter *  pAdapter,
    IN  char *         arg);


INT Set_TxRate_Proc(
    IN  struct rtmp_adapter *  pAdapter,
    IN  char *         arg);


#ifdef DOT11_VHT_AC
INT Set_2G_256QAM_Proc(
	IN  struct rtmp_adapter *  pAdapter,
    IN  char *         arg);
#endif /* DOT11_VHT_AC */

INT	Set_OLBCDetection_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg);

INT	Set_AP_MaxStaNum_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg);

INT	Set_AP_IdleTimeout_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg);

INT Set_AP_AuthMode_Proc(
    IN  struct rtmp_adapter *  pAdapter,
    IN  char *         arg);

INT Set_AP_EncrypType_Proc(
    IN  struct rtmp_adapter *  pAdapter,
    IN  char *         arg);

INT Set_AP_WpaMixPairCipher_Proc(
    IN  struct rtmp_adapter *  pAdapter,
    IN  char *         arg);

INT Set_AP_RekeyInterval_Proc(
    IN  struct rtmp_adapter *  pAdapter,
    IN  char *         arg);

INT Set_AP_RekeyMethod_Proc(
    IN  struct rtmp_adapter *  pAdapter,
    IN  char *         arg);

INT Set_AP_PMKCachePeriod_Proc(
    IN  struct rtmp_adapter *  pAdapter,
    IN  char *         arg);

INT Set_AP_PACKET_FILTER_Proc(
    IN  struct rtmp_adapter *   pAd,
    IN  char *         arg);

INT Set_AP_PROBE_RSSI_THRESHOLD(
    IN  struct rtmp_adapter *   pAd,
    IN  char *         arg);

INT Set_AP_AUTH_FAIL_RSSI_THRESHOLD(
    IN  struct rtmp_adapter *   pAd,
    IN  char *         arg);

INT Set_AP_AUTH_NO_RSP_RSSI_THRESHOLD(
    IN  struct rtmp_adapter *   pAd,
    IN  char *         arg);

INT Set_AP_ASSOC_REQ_FAIL_RSSI_THRESHOLD(
    IN  struct rtmp_adapter *   pAd,
    IN  char *         arg);

INT Set_AP_ASSOC_REQ_NO_RSP_RSSI_THRESHOLD(
    IN  struct rtmp_adapter *   pAd,
    IN  char *         arg);

INT Set_AP_KickStaRssiLow_Proc(
    IN  struct rtmp_adapter *   pAd,
    IN  char *         arg);

INT Set_AP_DefaultKeyID_Proc(
    IN  struct rtmp_adapter *  pAdapter,
    IN  char *         arg);

INT Set_AP_Key1_Proc(
    IN  struct rtmp_adapter *  pAdapter,
    IN  char *         arg);

INT Set_AP_Key2_Proc(
    IN  struct rtmp_adapter *  pAdapter,
    IN  char *         arg);

INT Set_AP_Key3_Proc(
    IN  struct rtmp_adapter *  pAdapter,
    IN  char *         arg);

INT Set_AP_Key4_Proc(
    IN  struct rtmp_adapter *  pAdapter,
    IN  char *         arg);

INT Set_AP_WPAPSK_Proc(
    IN  struct rtmp_adapter *  pAdapter,
    IN  char *         arg);

INT Set_BasicRate_Proc(
	IN	struct rtmp_adapter *pAdapter,
	IN	char *		arg);

INT	Set_BeaconPeriod_Proc(
	IN	struct rtmp_adapter *pAdapter,
	IN	char *		arg);

INT	Set_DtimPeriod_Proc(
	IN	struct rtmp_adapter *pAdapter,
	IN	char *		arg);

INT	Set_NoForwarding_Proc(
	IN	struct rtmp_adapter *pAdapter,
	IN	char *		arg);

INT	Set_NoForwardingBTNSSID_Proc(
	IN	struct rtmp_adapter *pAdapter,
	IN	char *		arg);

INT	Set_NoForwardingMBCast_Proc(
	IN	struct rtmp_adapter *pAdapter,
	IN	char *		arg);

INT	Set_AP_WmmCapable_Proc(
	IN	struct rtmp_adapter *pAdapter,
	IN	char *		arg);

INT	Set_HideSSID_Proc(
	IN	struct rtmp_adapter *pAdapter,
	IN	char *		arg);

INT	Set_VLANID_Proc(
	IN	struct rtmp_adapter *pAdapter,
	IN	char *		arg);

INT	Set_VLANPriority_Proc(
	IN	struct rtmp_adapter *pAdapter,
	IN	char *		arg);

INT	Set_VLAN_TAG_Proc(
	IN	struct rtmp_adapter *pAdapter,
	IN	char *		arg);

INT	Set_AccessPolicy_Proc(
	IN	struct rtmp_adapter *pAdapter,
	IN	char *		arg);


INT	Set_ACLAddEntry_Proc(
	IN	struct rtmp_adapter *pAdapter,
	IN	char *		arg);

INT	Set_ACLDelEntry_Proc(
	IN	struct rtmp_adapter *pAdapter,
	IN	char *		arg);

INT	Set_ACLShowAll_Proc(
	IN	struct rtmp_adapter *pAdapter,
	IN	char *		arg);

INT	Set_ACLClearAll_Proc(
	IN	struct rtmp_adapter *pAdapter,
	IN	char *		arg);

INT	Set_RadioOn_Proc(
	IN	struct rtmp_adapter *pAdapter,
	IN	char *		arg);

INT Set_SiteSurvey_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg);

INT Set_AutoChannelSel_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg);

#ifdef AP_PARTIAL_SCAN_SUPPORT
INT Set_PartialScan_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *	arg);
#endif /* AP_PARTIAL_SCAN_SUPPORT */

#ifdef AP_SCAN_SUPPORT
INT Set_AutoChannelSelCheckTime_Proc(
   IN  struct rtmp_adapter *  pAd,
   IN  char *        arg);
#endif /* AP_SCAN_SUPPORT */

INT	Set_BADecline_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg);

INT	Show_StaCount_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg);

INT	Show_StaSecurityInfo_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg);

INT	Show_DriverInfo_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg);

INT	Show_BaTable_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg);

INT	Show_Sat_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg);

INT	Show_RAInfo_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg);

#ifdef DBG_DIAGNOSE
INT Set_DiagOpt_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg);

INT Set_BDInfo_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg);
#endif /* DBG_DAIGNOSE */

INT	Show_Sat_Reset_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg);

INT	Show_MATTable_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg);

#ifdef DOT1X_SUPPORT
VOID RTMPIoctlQueryRadiusConf(
	IN struct rtmp_adapter *pAd,
	IN RTMP_IOCTL_INPUT_STRUCT *wrq);

INT	Set_IEEE8021X_Proc(
	IN	struct rtmp_adapter *pAdapter,
	IN	char *		arg);

INT	Set_PreAuth_Proc(
	IN	struct rtmp_adapter *pAdapter,
	IN	char *		arg);

INT	Set_RADIUS_Server_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg);

INT	Set_RADIUS_Port_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg);

INT	Set_RADIUS_Key_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg);
#endif /* DOT1X_SUPPORT */

INT	Set_DisConnectSta_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg);

INT	Set_DisConnectAllSta_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg);


#ifdef APCLI_SUPPORT
INT Set_ApCli_Enable_Proc(IN struct rtmp_adapter *pAd, IN char *arg);
INT Set_ApCli_Ssid_Proc(IN struct rtmp_adapter *pAd, IN char *arg);
INT Set_ApCli_Bssid_Proc(IN struct rtmp_adapter *pAd, IN char *arg);
INT Set_ApCli_DefaultKeyID_Proc(IN struct rtmp_adapter *pAd, IN char *arg);
INT Set_ApCli_WPAPSK_Proc(IN struct rtmp_adapter *pAd, IN char *arg);
INT Set_ApCli_Key1_Proc(IN struct rtmp_adapter *pAd, IN char *arg);
INT Set_ApCli_Key2_Proc(IN struct rtmp_adapter *pAd, IN char *arg);
INT Set_ApCli_Key3_Proc(IN struct rtmp_adapter *pAd, IN char *arg);
INT Set_ApCli_Key4_Proc(IN struct rtmp_adapter *pAd, IN char *arg);
INT Set_ApCli_TxMode_Proc(IN struct rtmp_adapter *pAd, IN  char *arg);
INT Set_ApCli_TxMcs_Proc(IN struct rtmp_adapter *pAd, IN  char *arg);
#ifdef APCLI_AUTO_CONNECT_SUPPORT
INT Set_ApCli_AutoConnect_Proc(IN struct rtmp_adapter *pAd,	IN char *arg);
#endif /* APCLI_AUTO_CONNECT_SUPPORT */

#ifdef APCLI_CONNECTION_TRIAL
INT Set_ApCli_Trial_Ch_Proc(IN struct rtmp_adapter *pAd, IN char *arg);
#endif /* APCLI_CONNECTION_TRIAL */

#ifdef APCLI_WPA_SUPPLICANT_SUPPORT
INT Set_ApCli_Wpa_Support(IN struct rtmp_adapter *pAd, IN	char *arg);
INT	Set_ApCli_IEEE8021X_Proc(IN struct rtmp_adapter *pAd, IN char *arg);
#endif/*APCLI_WPA_SUPPLICANT_SUPPORT*/


#ifdef APCLI_CERT_SUPPORT
INT Set_ApCli_Cert_Enable_Proc(IN struct rtmp_adapter *pAd, IN	char *arg);
INT Set_ApCli_WMM_Enable_Proc(IN struct rtmp_adapter *pAd, IN	char *arg);
#endif /* APCLI_CERT_SUPPORT */
#endif /* APCLI_SUPPORT */
#ifdef UAPSD_SUPPORT
INT Set_UAPSD_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg);
#endif /* UAPSD_SUPPORT */



#ifdef CONFIG_AP_SUPPORT

INT Set_OBSSScanParam_Proc(struct rtmp_adapter *pAd, char *arg);
INT Set_AP2040ReScan_Proc(struct rtmp_adapter *pAd, char *arg);

INT Set_EntryLifeCheck_Proc(
	IN struct rtmp_adapter *	pAd,
	IN char *		arg);


#ifdef AP_QLOAD_SUPPORT
INT	Set_QloadClr_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg);

/* QLOAD ALARM */
INT	Set_QloadAlarmTimeThreshold_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		Arg);

INT	Set_QloadAlarmNumThreshold_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		Arg);
#endif /* AP_QLOAD_SUPPORT */
#endif /* CONFIG_AP_SUPPORT */


INT	Set_MemDebug_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg);

#ifdef CONFIG_AP_SUPPORT
INT	Set_PowerSaveLifeTime_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg);
#endif /* CONFIG_AP_SUPPORT */


#ifdef DYNAMIC_VGA_SUPPORT
INT	Set_AP_DyncVgaEnable_Proc(
	IN struct rtmp_adapter 	*pAd,
	IN	char *		arg);

INT set_dynamic_lna_trigger_timer_proc(
	IN struct rtmp_adapter 	*pAd,
	IN char *		arg);

INT set_false_cca_hi_th(struct rtmp_adapter *pAd, char *arg);
INT set_false_cca_low_th(struct rtmp_adapter *pAd, char *arg);
#endif /* DYNAMIC_VGA_SUPPORT */

#ifdef ED_MONITOR
//let run-time turn on/off
INT set_ed_chk_proc(struct rtmp_adapter *pAd, char *arg);

#ifdef CONFIG_AP_SUPPORT
INT set_ed_sta_count_proc(struct rtmp_adapter *pAd, char *arg);
INT set_ed_ap_count_proc(struct rtmp_adapter *pAd, char *arg);
#endif /* CONFIG_AP_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
INT set_ed_ap_scaned_count_proc(struct rtmp_adapter *pAd, char *arg);
INT set_ed_current_ch_ap_proc(struct rtmp_adapter *pAd, char *arg);
INT set_ed_current_rssi_threhold_proc(struct rtmp_adapter *pAd, char *arg);
#endif /* CONFIG_STA_SUPPORT */

INT set_ed_block_tx_thresh(struct rtmp_adapter *pAd, char *arg);
INT set_ed_false_cca_threshold(struct rtmp_adapter *pAd, char *arg);
INT set_ed_threshold(struct rtmp_adapter *pAd, char *arg);
INT show_ed_stat_proc(struct rtmp_adapter *pAd, char *arg);
#endif /* ED_MONITOR */

#ifdef THERMAL_PROTECT_SUPPORT
INT set_thermal_protection_criteria_proc(
	IN struct rtmp_adapter *pAd,
	IN char *arg);
#endif /* THERMAL_PROTECT_SUPPORT */

#define	ASSO_MAC_LINE_LEN	(1+19+4+4+4+4+8+7+7+7+10+6+6+6+6+7+7+7+1)
VOID RTMPAPGetAssoMacTable(
	IN struct rtmp_adapter *pAd,
	IN RTMP_IOCTL_INPUT_STRUCT *wrq)
{
	uint32_t DataRate=0;

	INT i;
	char *msg;

	msg = kmalloc(sizeof(CHAR)*(MAX_LEN_OF_MAC_TABLE*ASSO_MAC_LINE_LEN),
			GFP_ATOMIC);
	if (msg == NULL) {
		DBGPRINT(RT_DEBUG_ERROR, ("%s():Alloc memory failed\n", __FUNCTION__));
		return;
	}
	memset(msg, 0 ,MAX_LEN_OF_MAC_TABLE*ASSO_MAC_LINE_LEN );

	sprintf(msg+strlen(msg),"\n%-19s%-4s%-4s%-4s%-4s%-8s",
		   "MAC", "AID", "BSS", "PSM", "WMM", "MIMOPS");

        if (pAd->CommonCfg.RxStream == 3)
                sprintf(msg+strlen(msg),"%-7s%-7s%-7s","RSSI0", "RSSI1","RSSI2");
        else if (pAd->CommonCfg.RxStream == 2)
                sprintf(msg+strlen(msg),"%-7s%-7s", "RSSI0", "RSSI1");
        else
                sprintf(msg+strlen(msg),"%-7s", "RSSI0");

	sprintf(msg+strlen(msg),"%-10s%-6s%-6s%-6s%-6s%-7s%-7s%-7s\n", "PhMd", "BW", "MCS", "SGI", "STBC", "Idle", "Rate", "TIME");


	for (i=0; i<MAX_LEN_OF_MAC_TABLE; i++)
	{
		PMAC_TABLE_ENTRY pEntry = &pAd->MacTab.Content[i];
		if ((IS_ENTRY_CLIENT(pEntry) || (IS_ENTRY_APCLI(pEntry)
			))
			&& (pEntry->Sst == SST_ASSOC))
		{
			if((strlen(msg)+ASSO_MAC_LINE_LEN ) >= (MAX_LEN_OF_MAC_TABLE*ASSO_MAC_LINE_LEN) )
				break;

			DataRate=0;
			//getRate(pEntry->HTPhyMode, &DataRate);
			RtmpDrvRateGet(pAd, pEntry->HTPhyMode.field.MODE, pEntry->HTPhyMode.field.ShortGI,
		                          pEntry->HTPhyMode.field.BW, pEntry->HTPhyMode.field.MCS,
		                          newRateGetAntenna(pEntry->HTPhyMode.field.MCS), &DataRate);
			DataRate /= 500000;
			DataRate /= 2;

			sprintf(msg+strlen(msg),"%02X:%02X:%02X:%02X:%02X:%02X  ", PRINT_MAC(pEntry->Addr));
			sprintf(msg+strlen(msg),"%-4d", (int)pEntry->Aid);
			sprintf(msg+strlen(msg),"%-4d", (int)pEntry->apidx);
			sprintf(msg+strlen(msg),"%-4d", (int)pEntry->PsMode);
			sprintf(msg+strlen(msg),"%-4d", (int)CLIENT_STATUS_TEST_FLAG(pEntry, fCLIENT_STATUS_WMM_CAPABLE));
			sprintf(msg+strlen(msg),"%-8d", (int)pEntry->MmpsMode);

		        if (pAd->CommonCfg.RxStream == 3)
                		sprintf(msg+strlen(msg),"%-7d%-7d%-7d", pEntry->RssiSample.AvgRssi0, pEntry->RssiSample.AvgRssi1, pEntry->RssiSample.AvgRssi2);
		        else if (pAd->CommonCfg.RxStream == 2)
                		sprintf(msg+strlen(msg),"%-7d%-7d", pEntry->RssiSample.AvgRssi0, pEntry->RssiSample.AvgRssi1);
        		else
                		sprintf(msg+strlen(msg),"%-7d", pEntry->RssiSample.AvgRssi0);

			sprintf(msg+strlen(msg),"%-10s", get_phymode_str(pEntry->HTPhyMode.field.MODE));
			sprintf(msg+strlen(msg),"%-6s", get_bw_str(pEntry->HTPhyMode.field.BW));
#ifdef DOT11_VHT_AC
			if (pEntry->HTPhyMode.field.MODE == MODE_VHT)
				sprintf(msg+strlen(msg),"%dS-M%d", ((pEntry->HTPhyMode.field.MCS>>4) + 1), (pEntry->HTPhyMode.field.MCS & 0xf));
			else
#endif /* DOT11_VHT_AC */
			sprintf(msg+strlen(msg),"%-6d", pEntry->HTPhyMode.field.MCS);
			sprintf(msg+strlen(msg),"%-6d", pEntry->HTPhyMode.field.ShortGI);
			sprintf(msg+strlen(msg),"%-6d", pEntry->HTPhyMode.field.STBC);
			sprintf(msg+strlen(msg),"%-7d", (int)(pEntry->StaIdleTimeout - pEntry->NoDataIdleCount));
			sprintf(msg+strlen(msg),"%-7d", (int)DataRate);
			sprintf(msg+strlen(msg),"%-7d", (int)pEntry->StaConnectTime);
			sprintf(msg+strlen(msg),"%-10d, %d, %d%%\n", pEntry->DebugFIFOCount, pEntry->DebugTxCount,
						(pEntry->DebugTxCount) ? ((pEntry->DebugTxCount-pEntry->DebugFIFOCount)*100/pEntry->DebugTxCount) : 0);
//+++Add by shiang for debug
//---Add by shiang for debug
			sprintf(msg+strlen(msg),"\n");
		}
	}


	/* for compatible with old API just do the printk to console*/
	wrq->u.data.length = strlen(msg);
	if (copy_to_user(wrq->u.data.pointer, msg, wrq->u.data.length))
	{
		DBGPRINT(RT_DEBUG_OFF, ("%s", msg));
	}

	kfree(msg);
}

/*
    ==========================================================================
    Description:
        Set Country Code.
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT Set_CountryCode_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{

	if(strlen(arg) == 2)
	{
		memmove(pAd->CommonCfg.CountryCode, arg, 2);
		pAd->CommonCfg.bCountryFlag = TRUE;
	}
	else
	{
		memset(pAd->CommonCfg.CountryCode, 0, 3);
		pAd->CommonCfg.bCountryFlag = FALSE;
	}

#ifdef MT76x2
	if (IS_MT76x2(pAd))
		AsicSwitchChannel(pAd, pAd->hw_cfg.cent_ch, FALSE);
#endif /* MT76x2 */

	DBGPRINT(RT_DEBUG_TRACE, ("Set_CountryCode_Proc::(bCountryFlag=%d, CountryCode=%s)\n", pAd->CommonCfg.bCountryFlag, pAd->CommonCfg.CountryCode));

	return TRUE;
}


/*
    ==========================================================================
    Description:
        Set Country String.
        This command will not work, if the field of CountryRegion in eeprom is programmed.
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT Set_CountryString_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	INT   index = 0;
	INT   success = TRUE;
	STRING  name_buffer[40] = {0};

	if(strlen(arg) <= 38)
	{
		if (strlen(arg) < 4)
		{
			DBGPRINT(RT_DEBUG_ERROR, ("Set_CountryString_Proc::Parameter of CountryString are too short !\n"));
			return FALSE;
		}

		for (index = 0; index < strlen(arg); index++)
		{
			if ((arg[index] >= 'a') && (arg[index] <= 'z'))
				arg[index] = toupper(arg[index]);
		}

		for (index = 0; index < NUM_OF_COUNTRIES; index++)
		{
			memset(name_buffer, 0, 40);
			snprintf(name_buffer, sizeof(name_buffer), "\"%s\"", (char *) allCountry[index].pCountryName);

			if (strncmp((char *) allCountry[index].pCountryName, arg, strlen(arg)) == 0)
				break;
			else if (strncmp(name_buffer, arg, strlen(arg)) == 0)
				break;
		}

		if (index == NUM_OF_COUNTRIES)
			success = FALSE;
	}
	else
	{
		success = FALSE;
	}

	if (success == TRUE)
	{
		if (pAd->CommonCfg.CountryRegion & 0x80)
		{
			DBGPRINT(RT_DEBUG_ERROR, ("Set_CountryString_Proc::parameter of CountryRegion in eeprom is programmed \n"));
			success = FALSE;
		}
		else
		{
			success = FALSE;
			if (WMODE_CAP_2G(pAd->CommonCfg.PhyMode))
			{
				if (allCountry[index].SupportGBand == TRUE)
				{
					pAd->CommonCfg.CountryRegion = (UCHAR) allCountry[index].RegDomainNum11G;
					success = TRUE;
				}
				else
				{
					DBGPRINT(RT_DEBUG_TRACE, ("The Country are not Support G Band Channel\n"));
				}
			}

			if (WMODE_CAP_5G(pAd->CommonCfg.PhyMode))
			{
				if (allCountry[index].SupportABand == TRUE)
				{
					pAd->CommonCfg.CountryRegionForABand = (UCHAR) allCountry[index].RegDomainNum11A;
					success = TRUE;
				}
				else
				{
					DBGPRINT(RT_DEBUG_TRACE, ("The Country are not Support A Band Channel\n"));
				}
			}
		}
	}

	if (success == TRUE)
	{
		memset(pAd->CommonCfg.CountryCode, 0, 3);
		memmove(pAd->CommonCfg.CountryCode, allCountry[index].IsoName, 2);
		pAd->CommonCfg.CountryCode[2] = ' ';
		/* After Set ChGeography need invoke SSID change procedural again for Beacon update. */
		/* it's no longer necessary since APStartUp will rebuild channel again. */
		/*BuildChannelList(pAd); */

		pAd->CommonCfg.bCountryFlag = TRUE;

		/* if set country string, driver needs to be reset */
		DBGPRINT(RT_DEBUG_TRACE, ("Set_CountryString_Proc::(CountryString=%s CountryRegin=%d CountryCode=%s)\n",
							allCountry[index].pCountryName, pAd->CommonCfg.CountryRegion, pAd->CommonCfg.CountryCode));
	}
	else
	{
		DBGPRINT(RT_DEBUG_ERROR, ("Set_CountryString_Proc::Parameters out of range\n"));
	}

	return success;
}

#ifdef DOT11_VHT_AC
INT Set_2G_256QAM_Proc(
	IN  struct rtmp_adapter *  pAdapter,
    IN  char *         arg)
{
	INT   success = TRUE;
	pAdapter->CommonCfg.b256QAM_2G = (UCHAR) simple_strtol(arg, 0, 10);
	return success;

}
#endif /* DOT11_VHT_AC */


/*
    ==========================================================================
    Description:
        Set SSID
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_AP_SSID_Proc(struct rtmp_adapter *pAd, char *arg)
{
	INT success = FALSE;
	struct os_cookie *pObj = pAd->OS_Cookie;
	MULTISSID_STRUCT *mbss;

	if(((pObj->ioctl_if < HW_BEACON_MAX_NUM)) && (strlen(arg) <= MAX_LEN_OF_SSID))
	{
		mbss = &pAd->ApCfg.MBSSID[pObj->ioctl_if];

		memset(mbss->Ssid, 0, MAX_LEN_OF_SSID);
		memmove(mbss->Ssid, arg, strlen(arg));
		mbss->SsidLen = (UCHAR)strlen(arg);
		success = TRUE;

		{
			/* If in detection mode, need to stop detect first. */
			if (pAd->CommonCfg.bIEEE80211H == FALSE)
			{
				APStop(pAd);
				APStartUp(pAd);
			}
			else
			{
				/* each mode has different restart method */
				if (pAd->Dot11_H.RDMode == RD_SILENCE_MODE)
				{
					APStop(pAd);
					APStartUp(pAd);
				}
				else if (pAd->Dot11_H.RDMode == RD_SWITCHING_MODE)
				{
				}
				else if (pAd->Dot11_H.RDMode == RD_NORMAL_MODE)
				{
					APStop(pAd);
					APStartUp(pAd);
				}
			}

			DBGPRINT(RT_DEBUG_TRACE, ("I/F(ra%d) Set_SSID_Proc::(Len=%d,Ssid=%s)\n", pObj->ioctl_if,
				mbss->SsidLen, mbss->Ssid));
		}
	}
	else
		success = FALSE;

	return success;
}


/*
    ==========================================================================
    Description:
        Set TxRate
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT Set_TxRate_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	struct os_cookie *pObj = pAd->OS_Cookie;

	memset(pAd->ApCfg.MBSSID[pObj->ioctl_if].DesiredRates, 0, MAX_LEN_OF_SUPPORTED_RATES);

	pAd->ApCfg.MBSSID[pObj->ioctl_if].DesiredRatesIndex = simple_strtol(arg, 0, 10);
	/* todo RTMPBuildDesireRate(pAd, pObj->ioctl_if, pAd->ApCfg.MBSSID[pObj->ioctl_if].DesiredRatesIndex); */

	/*todo MlmeUpdateTxRates(pAd); */

	return TRUE;
}


/*
    ==========================================================================
    Description:
        Set BasicRate
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT Set_BasicRate_Proc(struct rtmp_adapter *pAd, char *arg)
{
	struct os_cookie *pObj = pAd->OS_Cookie;
	ULONG BasicRateBitmap;

	BasicRateBitmap = (ULONG) simple_strtol(arg, 0, 10);

	if (BasicRateBitmap > 4095) /* (2 ^ MAX_LEN_OF_SUPPORTED_RATES) -1 */
		return FALSE;

	pAd->CommonCfg.BasicRateBitmap = BasicRateBitmap;
	pAd->CommonCfg.BasicRateBitmapOld = BasicRateBitmap;

	MlmeUpdateTxRates(pAd, FALSE, (UCHAR)pObj->ioctl_if);

	DBGPRINT(RT_DEBUG_TRACE, ("Set_BasicRate_Proc::(BasicRateBitmap=0x%08lx)\n", pAd->CommonCfg.BasicRateBitmap));

	return TRUE;
}


/*
    ==========================================================================
    Description:
        Set Beacon Period
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_BeaconPeriod_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	USHORT BeaconPeriod;
	INT   success = FALSE;

	BeaconPeriod = (USHORT) simple_strtol(arg, 0, 10);
	if((BeaconPeriod >= 20) && (BeaconPeriod < 1024))
	{
		pAd->CommonCfg.BeaconPeriod = BeaconPeriod;
		success = TRUE;

#ifdef AP_QLOAD_SUPPORT
		/* re-calculate QloadBusyTimeThreshold */
		QBSS_LoadAlarmReset(pAd);
#endif /* AP_QLOAD_SUPPORT */
	}
	else
		success = FALSE;

	DBGPRINT(RT_DEBUG_TRACE, ("Set_BeaconPeriod_Proc::(BeaconPeriod=%d)\n", pAd->CommonCfg.BeaconPeriod));

	return success;
}

/*
    ==========================================================================
    Description:
        Set Dtim Period
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_DtimPeriod_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	USHORT DtimPeriod;
	INT   success = FALSE;

	DtimPeriod = (USHORT) simple_strtol(arg, 0, 10);
	if((DtimPeriod >= 1) && (DtimPeriod <= 255))
	{
		pAd->ApCfg.DtimPeriod = DtimPeriod;
		success = TRUE;
	}
	else
		success = FALSE;

	DBGPRINT(RT_DEBUG_TRACE, ("Set_DtimPeriod_Proc::(DtimPeriod=%d)\n", pAd->ApCfg.DtimPeriod));

	return success;
}



/*
    ==========================================================================
    Description:
        Disable/enable OLBC detection manually
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_OLBCDetection_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	switch (simple_strtol(arg, 0, 10))
	{
		case 0: /*enable OLBC detect */
			pAd->CommonCfg.DisableOLBCDetect = 0;
			break;
		case 1: /*disable OLBC detect */
			pAd->CommonCfg.DisableOLBCDetect = 1;
			break;
		default:  /*Invalid argument */
			return FALSE;
	}

	return TRUE;
}


#ifdef WMM_SUPPORT
/*
    ==========================================================================
    Description:
        Set WmmCapable Enable or Disable
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_AP_WmmCapable_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	BOOLEAN	bWmmCapable;
	struct os_cookie *pObj= pAd->OS_Cookie;

	bWmmCapable = simple_strtol(arg, 0, 10);

	if (bWmmCapable == 1)
		pAd->ApCfg.MBSSID[pObj->ioctl_if].wdev.bWmmCapable = TRUE;
	else if (bWmmCapable == 0)
		pAd->ApCfg.MBSSID[pObj->ioctl_if].wdev.bWmmCapable = FALSE;
	else
		return FALSE;  /*Invalid argument */

	pAd->ApCfg.MBSSID[pObj->ioctl_if].bWmmCapableOrg = \
								pAd->ApCfg.MBSSID[pObj->ioctl_if].wdev.bWmmCapable;

#ifdef RTL865X_FAST_PATH
	if (!isFastPathCapable(pAd)) {
		rtlairgo_fast_tx_unregister();
		rtl865x_extDev_unregisterUcastTxDev(pAd->net_dev);
	}
#endif

	/*Sync with the HT relate info. In N mode, we should re-enable it */
	SetCommonHT(pAd);

	DBGPRINT(RT_DEBUG_TRACE, ("IF(ra%d) Set_WmmCapable_Proc::(bWmmCapable=%d)\n",
		pObj->ioctl_if, pAd->ApCfg.MBSSID[pObj->ioctl_if].wdev.bWmmCapable));

	return TRUE;
}
#endif /* WMM_SUPPORT */


INT	Set_AP_MaxStaNum_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	struct os_cookie *pObj = pAd->OS_Cookie;
	INT			apidx = pObj->ioctl_if;

	return ApCfg_Set_MaxStaNum_Proc(pAd, apidx, arg);
}

/*
    ==========================================================================
    Description:
        Set session idle timeout
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_AP_IdleTimeout_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	return ApCfg_Set_IdleTimeout_Proc(pAd, arg);
}
/*
    ==========================================================================
    Description:
        Set No Forwarding Enable or Disable
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_NoForwarding_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	ULONG NoForwarding;

	struct os_cookie *pObj = pAd->OS_Cookie;

	NoForwarding = simple_strtol(arg, 0, 10);

	if (NoForwarding == 1)
		pAd->ApCfg.MBSSID[pObj->ioctl_if].IsolateInterStaTraffic = TRUE;
	else if (NoForwarding == 0)
		pAd->ApCfg.MBSSID[pObj->ioctl_if].IsolateInterStaTraffic = FALSE;
	else
		return FALSE;  /*Invalid argument */

	DBGPRINT(RT_DEBUG_TRACE, ("IF(ra%d) Set_NoForwarding_Proc::(NoForwarding=%ld)\n",
		pObj->ioctl_if, pAd->ApCfg.MBSSID[pObj->ioctl_if].IsolateInterStaTraffic));

	return TRUE;
}


INT	Set_NoForwardingMBCast_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	UCHAR NoForwardingMBCast;

	struct os_cookie *pObj = pAd->OS_Cookie;

	NoForwardingMBCast = simple_strtol(arg, 0, 10);

	if (NoForwardingMBCast == 1)
		pAd->ApCfg.MBSSID[pObj->ioctl_if].IsolateInterStaMBCast = TRUE;
	else if (NoForwardingMBCast == 0)
		pAd->ApCfg.MBSSID[pObj->ioctl_if].IsolateInterStaMBCast = FALSE;
	else
		return FALSE;  //Invalid argument

	DBGPRINT(RT_DEBUG_TRACE, ("IF(ra%d) Set_NoForwardingMBCast_Proc::(IsolateInterStaMBCast=%d)\n",
		pObj->ioctl_if, pAd->ApCfg.MBSSID[pObj->ioctl_if].IsolateInterStaMBCast));

	return TRUE;
}

/*
    ==========================================================================
    Description:
        Set No Forwarding between each SSID
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_NoForwardingBTNSSID_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	ULONG NoForwarding;

	NoForwarding = simple_strtol(arg, 0, 10);

	if (NoForwarding == 1)
		pAd->ApCfg.IsolateInterStaTrafficBTNBSSID = TRUE;
	else if (NoForwarding == 0)
		pAd->ApCfg.IsolateInterStaTrafficBTNBSSID = FALSE;
	else
		return FALSE;  /*Invalid argument */

	DBGPRINT(RT_DEBUG_TRACE, ("Set_NoForwardingBTNSSID_Proc::(NoForwarding=%ld)\n", pAd->ApCfg.IsolateInterStaTrafficBTNBSSID));

	return TRUE;
}


/*
    ==========================================================================
    Description:
        Set Hide SSID Enable or Disable
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_HideSSID_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	BOOLEAN bHideSsid;
	struct os_cookie *pObj = pAd->OS_Cookie;

	bHideSsid = simple_strtol(arg, 0, 10);

	if (bHideSsid == 1)
		bHideSsid = TRUE;
	else if (bHideSsid == 0)
		bHideSsid = FALSE;
	else
		return FALSE;  /*Invalid argument */

	if (pAd->ApCfg.MBSSID[pObj->ioctl_if].bHideSsid != bHideSsid)
	{
		pAd->ApCfg.MBSSID[pObj->ioctl_if].bHideSsid = bHideSsid;
	}


	DBGPRINT(RT_DEBUG_TRACE, ("IF(ra%d) Set_HideSSID_Proc::(HideSSID=%d)\n", pObj->ioctl_if, pAd->ApCfg.MBSSID[pObj->ioctl_if].bHideSsid));

	return TRUE;
}

/*
    ==========================================================================
    Description:
        Set VLAN's ID field
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_VLANID_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	struct os_cookie *pObj = pAd->OS_Cookie;
	struct rtmp_wifi_dev *wdev;


	wdev = &pAd->ApCfg.MBSSID[pObj->ioctl_if].wdev;
	wdev->VLAN_VID = simple_strtol(arg, 0, 10);

	DBGPRINT(RT_DEBUG_TRACE, ("IF(ra%d) Set_VLANID_Proc::(VLAN_VID=%d)\n",
				pObj->ioctl_if, wdev->VLAN_VID));

	return TRUE;
}


/*
    ==========================================================================
    Description:
        Set VLAN's priority field
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_VLANPriority_Proc(struct rtmp_adapter *pAd, char *arg)
{
	struct os_cookie *pObj = pAd->OS_Cookie;
	struct rtmp_wifi_dev *wdev = &pAd->ApCfg.MBSSID[pObj->ioctl_if].wdev;

	wdev->VLAN_Priority = simple_strtol(arg, 0, 10);

	DBGPRINT(RT_DEBUG_TRACE, ("IF(ra%d) Set_VLANPriority_Proc::(VLAN_Priority=%d)\n", pObj->ioctl_if, wdev->VLAN_Priority));

	return TRUE;
}


/*
    ==========================================================================
    Description:
        Set enable or disable carry VLAN in the air
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_VLAN_TAG_Proc(struct rtmp_adapter *pAd, char *arg)
{
	BOOLEAN	bVLAN_Tag;
	struct os_cookie *pObj = pAd->OS_Cookie;
	struct rtmp_wifi_dev *wdev;


	bVLAN_Tag = simple_strtol(arg, 0, 10);

	if (bVLAN_Tag == 1)
		bVLAN_Tag = TRUE;
	else if (bVLAN_Tag == 0)
		bVLAN_Tag = FALSE;
	else
		return FALSE;  //Invalid argument

	wdev = &pAd->ApCfg.MBSSID[pObj->ioctl_if].wdev;
	wdev->bVLAN_Tag = bVLAN_Tag;

	DBGPRINT(RT_DEBUG_TRACE, ("IF(ra%d) Set_VLAN_TAG_Proc::(VLAN_Tag=%d)\n",
				pObj->ioctl_if, wdev->bVLAN_Tag));

	return TRUE;
}


/*
    ==========================================================================
    Description:
        Set Authentication mode
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_AP_AuthMode_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	ULONG i;
	struct os_cookie *pObj = pAd->OS_Cookie;
	UCHAR apidx = pObj->ioctl_if;
	struct rtmp_wifi_dev *wdev;


	if (apidx >= pAd->ApCfg.BssidNum)
		return FALSE;

	/* Set Authentication mode */
	ApCfg_Set_AuthMode_Proc(pAd, apidx, arg);

	/* reset the portSecure for all entries */
	for (i=0; i<MAX_LEN_OF_MAC_TABLE; i++)
	{
		if (IS_ENTRY_CLIENT(&pAd->MacTab.Content[i]))
		{
			pAd->MacTab.Content[i].PortSecured  = WPA_802_1X_PORT_NOT_SECURED;
		}
	}

	wdev = &pAd->ApCfg.MBSSID[apidx].wdev;
	/* reset the PortSecure this BSS */
	wdev->PortSecured = WPA_802_1X_PORT_NOT_SECURED;

	/* Default key index is always 2 in WPA mode */
	if(wdev->AuthMode >= Ndis802_11AuthModeWPA)
		wdev->DefaultKeyId = 1;

	return TRUE;
}


/*
    ==========================================================================
    Description:
        Set Encryption Type
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_AP_EncrypType_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	struct os_cookie *pObj = pAd->OS_Cookie;
	UCHAR		apidx = pObj->ioctl_if;
	struct rtmp_wifi_dev *wdev;

	wdev = &pAd->ApCfg.MBSSID[apidx].wdev;
	if ((strcmp(arg, "NONE") == 0) || (strcmp(arg, "none") == 0))
		wdev->WepStatus = Ndis802_11WEPDisabled;
	else if ((strcmp(arg, "WEP") == 0) || (strcmp(arg, "wep") == 0))
		wdev->WepStatus = Ndis802_11WEPEnabled;
	else if ((strcmp(arg, "TKIP") == 0) || (strcmp(arg, "tkip") == 0))
		wdev->WepStatus = Ndis802_11Encryption2Enabled;
	else if ((strcmp(arg, "AES") == 0) || (strcmp(arg, "aes") == 0))
		wdev->WepStatus = Ndis802_11Encryption3Enabled;
	else if ((strcmp(arg, "TKIPAES") == 0) || (strcmp(arg, "tkipaes") == 0))
		wdev->WepStatus = Ndis802_11Encryption4Enabled;
	else
		return FALSE;

	if (wdev->WepStatus >= Ndis802_11Encryption2Enabled)
		wdev->DefaultKeyId = 1;

	/* decide the group key encryption type */
	if (wdev->WepStatus == Ndis802_11Encryption4Enabled)
		wdev->GroupKeyWepStatus = Ndis802_11Encryption2Enabled;
	else
		wdev->GroupKeyWepStatus = wdev->WepStatus;

	/* move to ap.c::APStartUp to process */
    /*RTMPMakeRSNIE(pAd, pAd->ApCfg.MBSSID[apidx].AuthMode, pAd->ApCfg.MBSSID[apidx].WepStatus, apidx); */
	DBGPRINT(RT_DEBUG_TRACE, ("IF(ra%d) Set_EncrypType_Proc::(EncrypType=%d)\n", apidx, wdev->WepStatus));

	return TRUE;
}


/*
    ==========================================================================
    Description:
        Set WPA pairwise mix-cipher combination
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_AP_WpaMixPairCipher_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	struct os_cookie *pObj = pAd->OS_Cookie;
	UCHAR		apidx = pObj->ioctl_if;
	struct rtmp_wifi_dev *wdev;

	/*
		In WPA-WPA2 mix mode, it provides a more flexible cipher combination.
		-	WPA-AES and WPA2-TKIP
		-	WPA-AES and WPA2-TKIPAES
		-	WPA-TKIP and WPA2-AES
		-	WPA-TKIP and WPA2-TKIPAES
		-	WPA-TKIPAES and WPA2-AES
		-	WPA-TKIPAES and WPA2-TKIP
		-	WPA-TKIPAES and WPA2-TKIPAES (default)
	 */
	 wdev = &pAd->ApCfg.MBSSID[apidx].wdev;
	if ((strncmp(arg, "WPA_AES_WPA2_TKIPAES", 20) == 0) || (strncmp(arg, "wpa_aes_wpa2_tkipaes", 20) == 0))
		wdev->WpaMixPairCipher = WPA_AES_WPA2_TKIPAES;
	else if ((strncmp(arg, "WPA_AES_WPA2_TKIP", 17) == 0) || (strncmp(arg, "wpa_aes_wpa2_tkip", 17) == 0))
		wdev->WpaMixPairCipher = WPA_AES_WPA2_TKIP;
	else if ((strncmp(arg, "WPA_TKIP_WPA2_AES", 17) == 0) || (strncmp(arg, "wpa_tkip_wpa2_aes", 17) == 0))
		wdev->WpaMixPairCipher = WPA_TKIP_WPA2_AES;
	else if ((strncmp(arg, "WPA_TKIP_WPA2_TKIPAES", 21) == 0) || (strncmp(arg, "wpa_tkip_wpa2_tkipaes", 21) == 0))
		wdev->WpaMixPairCipher = WPA_TKIP_WPA2_TKIPAES;
	else if ((strncmp(arg, "WPA_TKIPAES_WPA2_AES", 20) == 0) || (strncmp(arg, "wpa_tkipaes_wpa2_aes", 20) == 0))
		wdev->WpaMixPairCipher = WPA_TKIPAES_WPA2_AES;
	else if ((strncmp(arg, "WPA_TKIPAES_WPA2_TKIPAES", 24) == 0) || (strncmp(arg, "wpa_tkipaes_wpa2_tkipaes", 24) == 0))
		wdev->WpaMixPairCipher = WPA_TKIPAES_WPA2_TKIPAES;
	else if ((strncmp(arg, "WPA_TKIPAES_WPA2_TKIP", 21) == 0) || (strncmp(arg, "wpa_tkipaes_wpa2_tkip", 21) == 0))
		wdev->WpaMixPairCipher = WPA_TKIPAES_WPA2_TKIP;
	else
		return FALSE;

	DBGPRINT(RT_DEBUG_TRACE, ("I/F(ra%d) Set_AP_WpaMixPairCipher_Proc=0x%02x\n", apidx, wdev->WpaMixPairCipher));

	return TRUE;
}

/*
    ==========================================================================
    Description:
        Set WPA rekey interval value
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_AP_RekeyInterval_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	struct os_cookie *	pObj = pAd->OS_Cookie;
	UCHAR		apidx = pObj->ioctl_if;
	int32_t val;

	val = simple_strtol(arg, 0, 10);

	if((val >= 10) && (val < MAX_REKEY_INTER))
		pAd->ApCfg.MBSSID[apidx].WPAREKEY.ReKeyInterval = val;
	else /* Default */
		pAd->ApCfg.MBSSID[apidx].WPAREKEY.ReKeyInterval = 3600;

	DBGPRINT(RT_DEBUG_TRACE, ("I/F(ra%d) Set_AP_RekeyInterval_Proc=%ld\n",
								apidx, pAd->ApCfg.MBSSID[apidx].WPAREKEY.ReKeyInterval));

	return TRUE;
}

INT Set_AP_PROBE_RSP_TIMES(
    IN  struct rtmp_adapter *   pAd,
    IN  char *         arg)
{
        struct os_cookie *pObj = pAd->OS_Cookie;
        UCHAR           apidx = pObj->ioctl_if;
        INT input;
        input = simple_strtol(arg, 0, 10);

        if ((input >= 0) && (input <= 10))
                pAd->ApCfg.MBSSID[apidx].ProbeRspTimes = input;
        else
                DBGPRINT(RT_DEBUG_ERROR, ("AP[%d]->ProbeRspTimes: Out of Range\n", apidx));

	DBGPRINT(RT_DEBUG_TRACE, ("AP[%d]->ProbeRspTimes: %d\n", apidx, pAd->ApCfg.MBSSID[apidx].ProbeRspTimes));

	return TRUE;

}

#ifdef SPECIFIC_TX_POWER_SUPPORT
INT Set_AP_PKT_PWR(
    IN  struct rtmp_adapter *   pAd,
    IN  char *         arg)
{
        struct os_cookie *pObj = pAd->OS_Cookie;
        UCHAR           apidx = pObj->ioctl_if;
        INT input;
        input = simple_strtol(arg, 0, 10);

	/*
	  Tx_PWR_ADJ[3:0] From 0 to 7 is Positive & add with Tx Power (dB),
          From 8 to 15 is minus with Tx Power mapping to -16 to -2 (step by 2),
          Default value: 0.

	  [0x13BC]TX_ALC_MONITOR, 13:8
		  TX_ALC_REQ_ADJ TX ALC Req Saturated[5:0], unit (0.5dB)
	*/

	if ((input >= 0) && (input <= 15))
        	pAd->ApCfg.MBSSID[apidx].TxPwrAdj = input;
	else
		DBGPRINT(RT_DEBUG_ERROR, ("AP[%d]->PktPwr: Out of Range\n"));

	DBGPRINT(RT_DEBUG_TRACE, ("AP[%d]->PktPwr: %d\n", apidx, pAd->ApCfg.MBSSID[apidx].TxPwrAdj));

	return TRUE;
}
#endif /* SPECIFIC_TX_POWER_SUPPORT */
/*
    ==========================================================================
    Description:
        Set WPA rekey method
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_AP_RekeyMethod_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	struct os_cookie *	pObj = pAd->OS_Cookie;
	UCHAR		apidx = pObj->ioctl_if;
	PRT_WPA_REKEY	pInfo = &pAd->ApCfg.MBSSID[apidx].WPAREKEY;

	if ((strcmp(arg, "TIME") == 0) || (strcmp(arg, "time") == 0))
		pInfo->ReKeyMethod = TIME_REKEY;
	else if ((strcmp(arg, "PKT") == 0) || (strcmp(arg, "pkt") == 0))
		pInfo->ReKeyMethod = PKT_REKEY;
	else if ((strcmp(arg, "DISABLE") == 0) || (strcmp(arg, "disable") == 0))
		pInfo->ReKeyMethod = DISABLE_REKEY;
	else
		pInfo->ReKeyMethod = DISABLE_REKEY;

	DBGPRINT(RT_DEBUG_TRACE, ("I/F(ra%d) Set_AP_RekeyMethod_Proc=%ld\n",
								apidx, pInfo->ReKeyMethod));

	return TRUE;
}

/*
    ==========================================================================
    Description:
        Set PMK-cache period
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_AP_PMKCachePeriod_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	struct os_cookie *	pObj = pAd->OS_Cookie;
	UCHAR		apidx = pObj->ioctl_if;
	uint32_t val = simple_strtol(arg, 0, 10);

	pAd->ApCfg.MBSSID[apidx].PMKCachePeriod = val * 60 * OS_HZ;

	DBGPRINT(RT_DEBUG_TRACE, ("I/F(ra%d) Set_AP_PMKCachePeriod_Proc=%ld\n",
									apidx, pAd->ApCfg.MBSSID[apidx].PMKCachePeriod));

	return TRUE;
}


INT     Set_AP_PACKET_FILTER_Proc(
        IN  struct rtmp_adapter *   pAd,
        IN  char *         arg)
{
		struct os_cookie *pObj = pAd->OS_Cookie;
		UCHAR apidx = pObj->ioctl_if;
		CHAR  val;
		val = simple_strtol(arg, 0, 10);

        if (val == FILTER_NONE)
        {
                DBGPRINT(RT_DEBUG_TRACE, ("Disable AP_PACKET_FILTER\n"));
        }
        else if (val >= FILTER_TOTAL || val < FILTER_NONE)
        {
                DBGPRINT(RT_DEBUG_TRACE, ("Set_AP_PACKET_FILTER Value Error.\n"));
                return FALSE;
        }

		pAd->ApCfg.MBSSID[apidx].FilterUnusedPacket = val;

		return TRUE;
}

INT     Set_AP_PROBE_RSSI_THRESHOLD(
        IN  struct rtmp_adapter *   pAd,
        IN  char *         arg)
{
        struct os_cookie *pObj = pAd->OS_Cookie;
        UCHAR           apidx = pObj->ioctl_if;
        UINT j;
        CHAR rssi;
        rssi = simple_strtol(arg, 0, 10);

        if (rssi == 0)
        {
                DBGPRINT(RT_DEBUG_TRACE, ("Disable AP_PROBE_RSSI_THRESHOLD\n"));
        }
        else if (rssi > 0 || rssi < -100)
        {
                DBGPRINT(RT_DEBUG_TRACE, ("Set_AP_PROBE_RSSI_THRESHOLD Value Error.\n"));
                return FALSE;
        }

        pAd->ApCfg.MBSSID[apidx].ProbeRspRssiThreshold = rssi;
        DBGPRINT(RT_DEBUG_TRACE, ("I/F(%s) Set_AP_PROBE_RSSI_THRESHOLD=%d\n",
                                  pAd->ApCfg.MBSSID[apidx].wdev.if_dev->name,
                                  pAd->ApCfg.MBSSID[apidx].ProbeRspRssiThreshold));

        for(j = BSS0; j < pAd->ApCfg.BssidNum; j++)
        {
                DBGPRINT(RT_DEBUG_TRACE, ("%d. ==> %d\n", j, pAd->ApCfg.MBSSID[j].ProbeRspRssiThreshold ));
        }

        return TRUE;
}

INT     Set_AP_AUTH_FAIL_RSSI_THRESHOLD(
        IN  struct rtmp_adapter *   pAd,
        IN  char *         arg)
{
        struct os_cookie *pObj = pAd->OS_Cookie;
        UCHAR           apidx = pObj->ioctl_if;
        UINT j;
        CHAR rssi;
        rssi = simple_strtol(arg, 0, 10);

        if (rssi == 0)
        {
                DBGPRINT(RT_DEBUG_TRACE, ("Disable AP_AUTH_FAIL_RSSI_THRESHOLD\n"));
        }
        else if (rssi > 0 || rssi < -100)
        {
                DBGPRINT(RT_DEBUG_TRACE, ("Set_AP_AUTH_FAIL_RSSI_THRESHOLD Value Error.\n"));
                return FALSE;
        }

        pAd->ApCfg.MBSSID[apidx].AuthFailRssiThreshold = rssi;
        DBGPRINT(RT_DEBUG_TRACE, ("I/F(%s) Set_AP_AUTH_RSSI_THRESHOLD=%d\n",
				  pAd->ApCfg.MBSSID[apidx].wdev.if_dev->name,
                                  pAd->ApCfg.MBSSID[apidx].AuthFailRssiThreshold));

        for(j = BSS0; j < pAd->ApCfg.BssidNum; j++)
        {
        	DBGPRINT(RT_DEBUG_TRACE, ("%d. ==> %d\n", j, pAd->ApCfg.MBSSID[j].AuthFailRssiThreshold ));
        }

        return TRUE;
}

INT     Set_AP_AUTH_NO_RSP_RSSI_THRESHOLD(
        IN  struct rtmp_adapter *   pAd,
        IN  char *         arg)
{
        struct os_cookie *pObj = pAd->OS_Cookie;
        UCHAR           apidx = pObj->ioctl_if;
        UINT j;
        CHAR rssi;
        rssi = simple_strtol(arg, 0, 10);

        if (rssi == 0)
        {
                DBGPRINT(RT_DEBUG_TRACE, ("Disable AP_AUTH_NO_RSP_RSSI_THRESHOLD\n"));
        }
        else if (rssi > 0 || rssi < -100)
        {
                DBGPRINT(RT_DEBUG_TRACE, ("Set_AP_AUTH_NO_RSP_RSSI_THRESHOLD Value Error.\n"));
                return FALSE;
        }

        pAd->ApCfg.MBSSID[apidx].AuthNoRspRssiThreshold = rssi;
        DBGPRINT(RT_DEBUG_TRACE, ("I/F(%s) Set_AP_AUTH_NO_RSP_RSSI_THRESHOLD=%d\n",
                                  pAd->ApCfg.MBSSID[apidx].wdev.if_dev->name,
                                  pAd->ApCfg.MBSSID[apidx].AuthNoRspRssiThreshold));

        for(j = BSS0; j < pAd->ApCfg.BssidNum; j++)
        {
                DBGPRINT(RT_DEBUG_TRACE, ("%d. ==> %d\n", j, pAd->ApCfg.MBSSID[j].AuthNoRspRssiThreshold ));
        }

        return TRUE;
}


/*
    ==========================================================================
    Description:
        Set AssocReq RSSI Threshold to reject STA with weak signal.
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT Set_AP_ASSOC_REQ_FAIL_RSSI_THRESHOLD(
    IN  struct rtmp_adapter *   pAd,
    IN  char *         arg)
{
	struct os_cookie *pObj = pAd->OS_Cookie;
	UCHAR           apidx = pObj->ioctl_if;
	UINT j;
        CHAR rssi;
        rssi = simple_strtol(arg, 0, 10);

        if (rssi == 0)
        {
                DBGPRINT(RT_DEBUG_TRACE, ("Disable AP_ASSOC_REQ_FAIL_RSSI_THRESHOLD\n"));
        }
        else if (rssi > 0 || rssi < -100)
        {
                DBGPRINT(RT_DEBUG_TRACE, ("Set_AP_ASSOC_REQ_FAIL_RSSI_THRESHOLD Value Error.\n"));
                return FALSE;
        }

        pAd->ApCfg.MBSSID[apidx].AssocReqFailRssiThreshold = rssi;
        DBGPRINT(RT_DEBUG_TRACE, ("I/F(%s) Set_AP_ASSOC_REQ_FAIL_RSSI_THRESHOLD=%d\n",
				  pAd->ApCfg.MBSSID[apidx].wdev.if_dev->name,
                                  pAd->ApCfg.MBSSID[apidx].AssocReqFailRssiThreshold ));

	for(j = BSS0; j < pAd->ApCfg.BssidNum; j++)
	{
		DBGPRINT(RT_DEBUG_TRACE, ("%d. ==> %d\n", j, pAd->ApCfg.MBSSID[j].AssocReqFailRssiThreshold ));
	}

        return TRUE;
}


INT Set_AP_ASSOC_REQ_NO_RSP_RSSI_THRESHOLD(
    IN  struct rtmp_adapter *   pAd,
    IN  char *         arg)
{
        struct os_cookie *pObj = pAd->OS_Cookie;
        UCHAR           apidx = pObj->ioctl_if;
        UINT j;
        CHAR rssi;
        rssi = simple_strtol(arg, 0, 10);

        if (rssi == 0)
        {
                DBGPRINT(RT_DEBUG_TRACE, ("Disable AP_ASSOC_REQ_NO_RSP_RSSI_THRESHOLD\n"));
        }
        else if (rssi > 0 || rssi < -100)
        {
                DBGPRINT(RT_DEBUG_TRACE, ("Set_AP_ASSOC_REQ_NO_RSP_RSSI_THRESHOLD Value Error.\n"));
                return FALSE;
        }


        pAd->ApCfg.MBSSID[apidx].AssocReqNoRspRssiThreshold = rssi;
        DBGPRINT(RT_DEBUG_TRACE, ("I/F(%s) Set_AP_ASSOC_REQ_NO_RSP_RSSI_THRESHOLD=%d\n",
                                  pAd->ApCfg.MBSSID[apidx].wdev.if_dev->name,
                                  pAd->ApCfg.MBSSID[apidx].AssocReqNoRspRssiThreshold ));

        for(j = BSS0; j < pAd->ApCfg.BssidNum; j++)
        {
                DBGPRINT(RT_DEBUG_TRACE, ("%d. ==> %d\n", j, pAd->ApCfg.MBSSID[j].AssocReqNoRspRssiThreshold ));
        }

        return TRUE;
}

/*
    ==========================================================================
    Description:
        Set lower limit for AP kicking out a STA.
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT Set_AP_KickStaRssiLow_Proc(
    IN  struct rtmp_adapter *   pAd,
    IN  char *         arg)
{
        struct os_cookie *pObj = pAd->OS_Cookie;
        UCHAR           apidx = pObj->ioctl_if;
        UINT j;
        CHAR rssi;
        rssi = simple_strtol(arg, 0, 10);

        if (rssi == 0)
        {
                DBGPRINT(RT_DEBUG_TRACE, ("Disable RssiLowForStaKickOut Function\n"));
        }
        else if (rssi > 0 || rssi < -100)
        {
                DBGPRINT(RT_DEBUG_TRACE, ("RssiLowForStaKickOut Value Error.\n"));
                return FALSE;
        }


        pAd->ApCfg.MBSSID[apidx].RssiLowForStaKickOut = rssi;

        DBGPRINT(RT_DEBUG_TRACE, ("I/F(%s) RssiLowForStaKickOut=%d\n",
				  pAd->ApCfg.MBSSID[apidx].wdev.if_dev->name,
                                  pAd->ApCfg.MBSSID[apidx].RssiLowForStaKickOut));

        for(j = BSS0; j < pAd->ApCfg.BssidNum; j++)
        {
                DBGPRINT(RT_DEBUG_TRACE, ("%d. ==> %d\n", j, pAd->ApCfg.MBSSID[j].RssiLowForStaKickOut ));
        }

        return TRUE;
}


/*
    ==========================================================================
    Description:
        Set Default Key ID
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_AP_DefaultKeyID_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	ULONG KeyIdx;
	struct os_cookie *pObj = pAd->OS_Cookie;
	UCHAR	apidx = pObj->ioctl_if;


	KeyIdx = simple_strtol(arg, 0, 10);
	if((KeyIdx >= 1 ) && (KeyIdx <= 4))
		pAd->ApCfg.MBSSID[apidx].wdev.DefaultKeyId = (UCHAR) (KeyIdx - 1 );
	else
		return FALSE;  /* Invalid argument */

	DBGPRINT(RT_DEBUG_TRACE, ("IF(ra%d) Set_DefaultKeyID_Proc::(DefaultKeyID(0~3)=%d)\n", apidx, pAd->ApCfg.MBSSID[apidx].wdev.DefaultKeyId));

	return TRUE;
}


/*
    ==========================================================================
    Description:
        Set WEP KEY1
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_AP_Key1_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	struct os_cookie *pObj;
	UCHAR	apidx;
	CIPHER_KEY	*pSharedKey;
	INT		retVal;

	pObj = pAd->OS_Cookie;
	apidx = pObj->ioctl_if;
	pSharedKey = &pAd->SharedKey[apidx][0];
	retVal = RT_CfgSetWepKey(pAd, arg, pSharedKey, 0);
	if (retVal == TRUE)
	{
		/* Set keys (into ASIC) */
		if (pAd->ApCfg.MBSSID[apidx].wdev.AuthMode >= Ndis802_11AuthModeWPA)
			;   /* not support */
		else    /* Old WEP stuff */
		{
			AsicAddSharedKeyEntry(pAd, apidx, 0, pSharedKey);
		}
		DBGPRINT(RT_DEBUG_TRACE, ("IF(ra%d) Set_Key1_Proc::(Key1=%s) success!\n", apidx, arg));
	}

	return retVal;
}


/*
    ==========================================================================
    Description:
        Set WEP KEY2
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_AP_Key2_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	struct os_cookie *pObj;
	UCHAR	apidx;
	CIPHER_KEY	*pSharedKey;
	INT		retVal;

	pObj = pAd->OS_Cookie;
	apidx = pObj->ioctl_if;
	pSharedKey = &pAd->SharedKey[apidx][1];
	retVal = RT_CfgSetWepKey(pAd, arg, pSharedKey, 1);
	if (retVal == TRUE)
	{
		/* Set keys (into ASIC) */
		if (pAd->ApCfg.MBSSID[apidx].wdev.AuthMode >= Ndis802_11AuthModeWPA)
			;   /* not support */
		else    /* Old WEP stuff */
		{
			AsicAddSharedKeyEntry(pAd, apidx, 1, pSharedKey);
		}
		DBGPRINT(RT_DEBUG_TRACE, ("IF(ra%d) Set_Key2_Proc::(Key2=%s) success!\n", apidx, arg));
	}

	return retVal;
}


/*
    ==========================================================================
    Description:
        Set WEP KEY3
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_AP_Key3_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	struct os_cookie *pObj;
	UCHAR	apidx;
	CIPHER_KEY	*pSharedKey;
	INT		retVal;

	pObj = pAd->OS_Cookie;
	apidx = pObj->ioctl_if;
	pSharedKey = &pAd->SharedKey[apidx][2];
	retVal = RT_CfgSetWepKey(pAd, arg, pSharedKey, 2);
	if (retVal == TRUE)
	{
		/* Set keys (into ASIC) */
		if (pAd->ApCfg.MBSSID[apidx].wdev.AuthMode >= Ndis802_11AuthModeWPA)
			;   /* not support */
		else    /* Old WEP stuff */
		{
			AsicAddSharedKeyEntry(pAd, apidx, 2, pSharedKey);
		}
		DBGPRINT(RT_DEBUG_TRACE, ("IF(ra%d) Set_Key3_Proc::(Key3=%s) success!\n", apidx, arg));
	}

	return retVal;
}


/*
    ==========================================================================
    Description:
        Set WEP KEY4
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_AP_Key4_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{

	struct os_cookie *pObj;
	UCHAR	apidx;
	CIPHER_KEY	*pSharedKey;
	INT		retVal;

	pObj = pAd->OS_Cookie;
	apidx = pObj->ioctl_if;
	pSharedKey = &pAd->SharedKey[apidx][3];
	retVal = RT_CfgSetWepKey(pAd, arg, pSharedKey, 3);
	if (retVal == TRUE)
	{
		/* Set keys (into ASIC) */
		if (pAd->ApCfg.MBSSID[apidx].wdev.AuthMode >= Ndis802_11AuthModeWPA)
			;   /* not support */
		else    /* Old WEP stuff */
		{
			AsicAddSharedKeyEntry(pAd, apidx, 3, pSharedKey);
		}
		DBGPRINT(RT_DEBUG_TRACE, ("IF(ra%d) Set_Key4_Proc::(Key4=%s) success!\n", apidx, arg));
	}

	return retVal;
}


/*
    ==========================================================================
    Description:
        Set Access ctrol policy
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_AccessPolicy_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	struct os_cookie *pObj = pAd->OS_Cookie;

	switch (simple_strtol(arg, 0, 10))
	{
		case 0: /*Disable */
			pAd->ApCfg.MBSSID[pObj->ioctl_if].AccessControlList.Policy = 0;
			break;
		case 1: /* Allow All, and ACL is positive. */
			pAd->ApCfg.MBSSID[pObj->ioctl_if].AccessControlList.Policy = 1;
			break;
		case 2: /* Reject All, and ACL is negative. */
			pAd->ApCfg.MBSSID[pObj->ioctl_if].AccessControlList.Policy = 2;
			break;
		default: /*Invalid argument */
			DBGPRINT(RT_DEBUG_ERROR, ("Set_AccessPolicy_Proc::Invalid argument (=%s)\n", arg));
			return FALSE;
	}

	/* check if the change in ACL affects any existent association */
	ApUpdateAccessControlList(pAd, pObj->ioctl_if);
	DBGPRINT(RT_DEBUG_TRACE, ("IF(ra%d) Set_AccessPolicy_Proc::(AccessPolicy=%ld)\n", pObj->ioctl_if, pAd->ApCfg.MBSSID[pObj->ioctl_if].AccessControlList.Policy));

	return TRUE;
}


/* Replaced by Set_ACLAddEntry_Proc() and Set_ACLClearAll_Proc() */

/*
    ==========================================================================
    Description:
        Add one entry or several entries(if allowed to)
        	into Access control mac table list
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_ACLAddEntry_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	UCHAR					macAddr[MAC_ADDR_LEN];
/*	RT_802_11_ACL			acl; */
	RT_802_11_ACL			*pacl = NULL;
	char *				this_char;
	char *				value;
	INT						i, j;
	BOOLEAN					isDuplicate=FALSE;
	struct os_cookie *pObj = pAd->OS_Cookie;

	if (pAd->ApCfg.MBSSID[pObj->ioctl_if].AccessControlList.Num >= (MAX_NUM_OF_ACL_LIST - 1))
    {
		DBGPRINT(RT_DEBUG_WARN, ("The AccessControlList is full, and no more entry can join the list!\n"));
		return FALSE;
	}

	/* allocate memory */
	pacl = kmalloc(sizeof(RT_802_11_ACL), GFP_ATOMIC);
	if (pacl == NULL) {
		DBGPRINT(RT_DEBUG_ERROR, ("%s: Allocate memory fail!!!\n", __FUNCTION__));
		return FALSE;
	}

	memset(pacl, 0, sizeof(RT_802_11_ACL));
	memmove(pacl, &pAd->ApCfg.MBSSID[pObj->ioctl_if].AccessControlList, sizeof(RT_802_11_ACL));

	while ((this_char = strsep((char **)&arg, ";")) != NULL)
	{
		if (*this_char == '\0')
		{
			DBGPRINT(RT_DEBUG_WARN, ("An unnecessary delimiter entered!\n"));
			continue;
		}
		if (strlen(this_char) != 17)  /*Mac address acceptable format 01:02:03:04:05:06 length 17 */
		{
			DBGPRINT(RT_DEBUG_ERROR, ("illegal MAC address length!\n"));
			continue;
		}
        for (i=0, value = rstrtok(this_char,":"); value; value = rstrtok(NULL,":"))
		{
			if((strlen(value) != 2) || (!isxdigit(*value)) || (!isxdigit(*(value+1))) )
			{
				DBGPRINT(RT_DEBUG_ERROR, ("illegal MAC address format or octet!\n"));
				/* Do not use "continue" to replace "break" */
				break;
			}
			AtoH(value, &macAddr[i++], 1);
		}

		if (i != MAC_ADDR_LEN)
		{
			continue;
		}

		/* Check if this entry is duplicate. */
		isDuplicate = FALSE;
		for (j=0; j<pacl->Num; j++)
		{
			if (memcmp(pacl->Entry[j].Addr, &macAddr, 6) == 0)
			{
				isDuplicate = TRUE;
				DBGPRINT(RT_DEBUG_WARN, ("You have added an entry before :\n"));
	        	DBGPRINT(RT_DEBUG_WARN, ("The duplicate entry is %02x:%02x:%02x:%02x:%02x:%02x\n",
	        		macAddr[0],macAddr[1],macAddr[2],macAddr[3],macAddr[4],macAddr[5]));
			}
		}

		if (!isDuplicate)
		{
			memmove(pacl->Entry[pacl->Num++].Addr, &macAddr, MAC_ADDR_LEN);
		}

		if (pacl->Num == MAX_NUM_OF_ACL_LIST)
	    {
			DBGPRINT(RT_DEBUG_WARN, ("The AccessControlList is full, and no more entry can join the list!\n"));
        	DBGPRINT(RT_DEBUG_WARN, ("The last entry of ACL is %02x:%02x:%02x:%02x:%02x:%02x\n",
        		macAddr[0],macAddr[1],macAddr[2],macAddr[3],macAddr[4],macAddr[5]));
			break;
		}
	}

	ASSERT(pacl->Num < MAX_NUM_OF_ACL_LIST);

	memset(&pAd->ApCfg.MBSSID[pObj->ioctl_if].AccessControlList, 0, sizeof(RT_802_11_ACL));
	memmove(&pAd->ApCfg.MBSSID[pObj->ioctl_if].AccessControlList, pacl, sizeof(RT_802_11_ACL));

	/* check if the change in ACL affects any existent association */
	ApUpdateAccessControlList(pAd, pObj->ioctl_if);
	DBGPRINT(RT_DEBUG_TRACE, ("Set::%s(Policy=%ld, Entry#=%ld)\n",
		__FUNCTION__ , pAd->ApCfg.MBSSID[pObj->ioctl_if].AccessControlList.Policy, pAd->ApCfg.MBSSID[pObj->ioctl_if].AccessControlList.Num));

#ifdef DBG
	DBGPRINT(RT_DEBUG_TRACE, ("=============== Entry ===============\n"));
	for (i=0; i<pAd->ApCfg.MBSSID[pObj->ioctl_if].AccessControlList.Num; i++)
	{
		printk("Entry #%02d: ", i+1);
		for (j=0; j<MAC_ADDR_LEN; j++)
		   printk("%02X ", pAd->ApCfg.MBSSID[pObj->ioctl_if].AccessControlList.Entry[i].Addr[j]);
		printk("\n");
	}
#endif

	if (pacl != NULL)
		kfree(pacl);

	return TRUE;
}


/*
    ==========================================================================
    Description:
        Delete one entry or several entries(if allowed to)
        	from Access control mac table list
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_ACLDelEntry_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	UCHAR					macAddr[MAC_ADDR_LEN];
	UCHAR					nullAddr[MAC_ADDR_LEN];
	RT_802_11_ACL			acl;
	char *				this_char;
	char *				value;
	INT						i, j;
	BOOLEAN					isFound=FALSE;
	struct os_cookie *pObj = pAd->OS_Cookie;

	memset(&acl, 0, sizeof(RT_802_11_ACL));
	memmove(&acl, &pAd->ApCfg.MBSSID[pObj->ioctl_if].AccessControlList, sizeof(RT_802_11_ACL));
	memset(nullAddr, 0, MAC_ADDR_LEN);

	while ((this_char = strsep((char **)&arg, ";")) != NULL)
	{
		if (*this_char == '\0')
		{
			DBGPRINT(RT_DEBUG_WARN, ("An unnecessary delimiter entered!\n"));
			continue;
		}
		if (strlen(this_char) != 17)  /*Mac address acceptable format 01:02:03:04:05:06 length 17 */
		{
			DBGPRINT(RT_DEBUG_ERROR, ("illegal MAC address length!\n"));
			continue;
		}

		for (i=0, value = rstrtok(this_char,":"); value; value = rstrtok(NULL,":"))
		{
			if ((strlen(value) != 2) || (!isxdigit(*value)) || (!isxdigit(*(value+1))) )
			{
				DBGPRINT(RT_DEBUG_ERROR, ("illegal MAC address format or octet!\n"));
				/* Do not use "continue" to replace "break" */
				break;
			}
			AtoH(value, &macAddr[i++], 1);
		}

		if (i != MAC_ADDR_LEN)
		{
			continue;
		}

		/* Check if this entry existed. */
		isFound = FALSE;
		for (j=0; j<acl.Num; j++)
		{
			if (memcmp(acl.Entry[j].Addr, &macAddr, MAC_ADDR_LEN) == 0)
			{
				isFound = TRUE;
				memset(acl.Entry[j].Addr, 0, MAC_ADDR_LEN);
				DBGPRINT(RT_DEBUG_TRACE, ("The entry %02x:%02x:%02x:%02x:%02x:%02x founded will be deleted!\n",
	        		macAddr[0],macAddr[1],macAddr[2],macAddr[3],macAddr[4],macAddr[5]));
			}
		}

		if (!isFound)
		{
			DBGPRINT(RT_DEBUG_TRACE, ("The entry %02x:%02x:%02x:%02x:%02x:%02x is not in the list!\n",
        		macAddr[0],macAddr[1],macAddr[2],macAddr[3],macAddr[4],macAddr[5]));
		}
	}

	memset(&pAd->ApCfg.MBSSID[pObj->ioctl_if].AccessControlList, 0, sizeof(RT_802_11_ACL));
	pAd->ApCfg.MBSSID[pObj->ioctl_if].AccessControlList.Policy = acl.Policy;
	ASSERT(pAd->ApCfg.MBSSID[pObj->ioctl_if].AccessControlList.Num == 0);
	i = 0;

	for (j=0; j<acl.Num; j++)
	{
		if (memcmp(acl.Entry[j].Addr, &nullAddr, MAC_ADDR_LEN) == 0)
		{
			continue;
		}
		else
		{
			memmove(&(pAd->ApCfg.MBSSID[pObj->ioctl_if].AccessControlList.Entry[i++]), acl.Entry[j].Addr, MAC_ADDR_LEN);
		}
	}

	pAd->ApCfg.MBSSID[pObj->ioctl_if].AccessControlList.Num = i;
	ASSERT(acl.Num >= pAd->ApCfg.MBSSID[pObj->ioctl_if].AccessControlList.Num);

	/* check if the change in ACL affects any existent association */
	ApUpdateAccessControlList(pAd, pObj->ioctl_if);
	DBGPRINT(RT_DEBUG_TRACE, ("Set::%s(Policy=%ld, Entry#=%ld)\n",
		__FUNCTION__ , pAd->ApCfg.MBSSID[pObj->ioctl_if].AccessControlList.Policy, pAd->ApCfg.MBSSID[pObj->ioctl_if].AccessControlList.Num));

#ifdef DBG
	DBGPRINT(RT_DEBUG_TRACE, ("=============== Entry ===============\n"));
	for (i=0; i<pAd->ApCfg.MBSSID[pObj->ioctl_if].AccessControlList.Num; i++)
	{
		printk("Entry #%02d: ", i+1);
		for (j=0; j<MAC_ADDR_LEN; j++)
		   printk("%02X ", pAd->ApCfg.MBSSID[pObj->ioctl_if].AccessControlList.Entry[i].Addr[j]);
		printk("\n");
	}
#endif
	return TRUE;
}


/* for ACL policy message */
#define ACL_POLICY_TYPE_NUM	3
char const *pACL_PolicyMessage[ACL_POLICY_TYPE_NUM] = {
	"the Access Control feature is disabled",						/* 0 : Disable */
	"only the following entries are allowed to join this BSS",			/* 1 : Allow */
	"all the following entries are rejected to join this BSS",			/* 2 : Reject */
};


/*
    ==========================================================================
    Description:
        Dump all the entries in the Access control
        	mac table list of a specified BSS
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_ACLShowAll_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	RT_802_11_ACL			acl;
	BOOLEAN					bDumpAll=FALSE;
	struct os_cookie *pObj = pAd->OS_Cookie;
	INT						i, j;

	bDumpAll = simple_strtol(arg, 0, 10);

	if (bDumpAll == 1)
	{
		bDumpAll = TRUE;
	}
	else if (bDumpAll == 0)
	{
		bDumpAll = FALSE;
		DBGPRINT(RT_DEBUG_WARN, ("Your input is 0!\n"));
		DBGPRINT(RT_DEBUG_WARN, ("The Access Control List will not be dumped!\n"));
		return TRUE;
	}
	else
	{
		return FALSE;  /* Invalid argument */
	}

	memset(&acl, 0, sizeof(RT_802_11_ACL));
	memmove(&acl, &pAd->ApCfg.MBSSID[pObj->ioctl_if].AccessControlList, sizeof(RT_802_11_ACL));

	/* Check if the list is already empty. */
	if (acl.Num == 0)
	{
		DBGPRINT(RT_DEBUG_WARN, ("The Access Control List is empty!\n"));
		return TRUE;
	}

	ASSERT(((bDumpAll == 1) && (acl.Num > 0)));

	/* Show the corresponding policy first. */
	printk("=============== Access Control Policy ===============\n");
	printk("Policy is %ld : ", acl.Policy);
	printk("%s\n", pACL_PolicyMessage[acl.Policy]);

	/* Dump the entry in the list one by one */
	printk("===============  Access Control List  ===============\n");
	for (i=0; i<acl.Num; i++)
	{
		printk("Entry #%02d: ", i+1);
		for (j=0; j<MAC_ADDR_LEN; j++)
		   printk("%02X ", acl.Entry[i].Addr[j]);
		printk("\n");
	}

	return TRUE;
}


/*
    ==========================================================================
    Description:
        Clear all the entries in the Access control
        	mac table list of a specified BSS
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_ACLClearAll_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
/*	RT_802_11_ACL			acl; */
	RT_802_11_ACL			*pacl = NULL;
	BOOLEAN					bClearAll=FALSE;
	struct os_cookie *pObj = pAd->OS_Cookie;

	bClearAll = simple_strtol(arg, 0, 10);

	if (bClearAll == 1)
	{
		bClearAll = TRUE;
	}
	else if (bClearAll == 0)
	{
		bClearAll = FALSE;
		DBGPRINT(RT_DEBUG_WARN, ("Your input is 0!\n"));
		DBGPRINT(RT_DEBUG_WARN, ("The Access Control List will be kept unchanged!\n"));
		return TRUE;
	}
	else
	{
		return FALSE;  /* Invalid argument */
	}

	/* allocate memory */
	pacl = kmalloc(sizeof(RT_802_11_ACL), GFP_ATOMIC);
	if (pacl == NULL) {
		DBGPRINT(RT_DEBUG_ERROR, ("%s: Allocate memory fail!!!\n", __FUNCTION__));
		return FALSE;
	}

	memset(pacl, 0, sizeof(RT_802_11_ACL));
	memmove(pacl, &pAd->ApCfg.MBSSID[pObj->ioctl_if].AccessControlList, sizeof(RT_802_11_ACL));

	/* Check if the list is already empty. */
	if (pacl->Num == 0)
	{
		DBGPRINT(RT_DEBUG_WARN, ("The Access Control List is empty!\n"));
		DBGPRINT(RT_DEBUG_WARN, ("No need to clear the Access Control List!\n"));

		if (pacl != NULL)
			kfree(pacl);

		return TRUE;
	}

	ASSERT(((bClearAll == 1) && (pacl->Num > 0)));

	/* Clear the entry in the list one by one */
	/* Keep the corresponding policy unchanged. */
	do
	{
		memset(pacl->Entry[pacl->Num - 1].Addr, 0, MAC_ADDR_LEN);
		pacl->Num -= 1;
	}while (pacl->Num > 0);

	ASSERT(pacl->Num == 0);

	memset(&(pAd->ApCfg.MBSSID[pObj->ioctl_if].AccessControlList), 0, sizeof(RT_802_11_ACL));
	memmove(&(pAd->ApCfg.MBSSID[pObj->ioctl_if].AccessControlList), pacl, sizeof(RT_802_11_ACL));

	/* check if the change in ACL affects any existent association */
	ApUpdateAccessControlList(pAd, pObj->ioctl_if);

	if (pacl != NULL)
		kfree(pacl);

	DBGPRINT(RT_DEBUG_TRACE, ("Set::%s(Policy=%ld, Entry#=%ld)\n",
		__FUNCTION__, pAd->ApCfg.MBSSID[pObj->ioctl_if].AccessControlList.Policy, pAd->ApCfg.MBSSID[pObj->ioctl_if].AccessControlList.Num));

	return TRUE;
}

#ifdef DBG
static void _rtmp_hexdump(int level, const char *title, const UINT8 *buf,
			 size_t len, int show)
{
	size_t i;
	if (level < RTDebugLevel)
		return;
	printk("%s - hexdump(len=%lu):", title, (unsigned long) len);
	if (show) {
		for (i = 0; i < len; i++)
			printk(" %02x", buf[i]);
	} else {
		printk(" [REMOVED]");
	}
	printk("\n");
}

void rtmp_hexdump(int level, const char *title, const UINT8 *buf, size_t len)
{
	_rtmp_hexdump(level, title, buf, len, 1);
}
#endif



/*
    ==========================================================================
    Description:
        Set WPA PSK key

    Arguments:
        pAdapter            Pointer to our adapter
        arg                 WPA pre-shared key string

    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_AP_WPAPSK_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	struct os_cookie *pObj = pAd->OS_Cookie;
	UCHAR	apidx = pObj->ioctl_if;
	INT	retval;
	MULTISSID_STRUCT *pMBSSStruct;

	DBGPRINT(RT_DEBUG_TRACE, ("Set_WPAPSK_Proc::(WPAPSK=%s)\n", arg));

	pMBSSStruct = &pAd->ApCfg.MBSSID[apidx];
	retval = RT_CfgSetWPAPSKKey(pAd, arg, strlen(arg), (u8 *)pMBSSStruct->Ssid, pMBSSStruct->SsidLen, pMBSSStruct->PMK);
	if (retval == FALSE)
		return FALSE;

	/* Keep this key string */
	strcpy(pAd->ApCfg.MBSSID[apidx].WPAKeyString, arg);


	return TRUE;
}

/*
    ==========================================================================
    Description:
        Reset statistics counter

    Arguments:
        pAdapter            Pointer to our adapter
        arg

    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/

INT	Set_RadioOn_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	UCHAR radio;

	radio = simple_strtol(arg, 0, 10);

	if (radio)
	{
		MlmeRadioOn(pAd);
		DBGPRINT(RT_DEBUG_TRACE, ("==>Set_RadioOn_Proc (ON)\n"));
	}
	else
	{
		MlmeRadioOff(pAd);
		DBGPRINT(RT_DEBUG_TRACE, ("==>Set_RadioOn_Proc (OFF)\n"));
	}

	return TRUE;
}

#ifdef AP_SCAN_SUPPORT
/*
    ==========================================================================
    Description:
        Issue a site survey command to driver
	Arguments:
	    pAdapter                    Pointer to our adapter
	    wrq                         Pointer to the ioctl argument

    Return Value:
        None

    Note:
        Usage:
               1.) iwpriv ra0 set site_survey
    ==========================================================================
*/

/*
    ==========================================================================
    Description:
        Issue a Auto-Channel Selection command to driver
	Arguments:
	    pAdapter                    Pointer to our adapter
	    wrq                         Pointer to the ioctl argument

    Return Value:
        None

    Note:
        Usage:
               1.) iwpriv ra0 set AutoChannelSel=1
                   Ues the number of AP to choose
               2.) iwpriv ra0 set AutoChannelSel=2
                   Ues the False CCA count to choose
    ==========================================================================
*/
INT Set_AutoChannelSel_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *	arg)
{
	NDIS_802_11_SSID Ssid;


	memset(&Ssid, 0, sizeof(NDIS_802_11_SSID));
	if (strlen(arg) <= MAX_LEN_OF_SSID)
	{
		if (strlen(arg) != 0)
		{
			memmove(Ssid.Ssid, arg, strlen(arg));
			Ssid.SsidLength = strlen(arg);
		}
		else   /*ANY ssid */
		{
			Ssid.SsidLength = 0;
			memcpy(Ssid.Ssid, "", 0);
		}
	}
	if (strcmp(arg,"1") == 0)
		pAd->ApCfg.AutoChannelAlg = ChannelAlgApCnt;
	else if (strcmp(arg,"2") == 0)
		pAd->ApCfg.AutoChannelAlg = ChannelAlgCCA;
	else
	{
		DBGPRINT(RT_DEBUG_ERROR, ("Set_AutoChannelSel_Proc Alg isn't defined\n"));
		return FALSE;
	}
	DBGPRINT(RT_DEBUG_TRACE, ("Set_AutoChannelSel_Proc Alg=%d \n", pAd->ApCfg.AutoChannelAlg));
	if (Ssid.SsidLength == 0)
		ApSiteSurvey(pAd, &Ssid, SCAN_PASSIVE, TRUE);
	else
		ApSiteSurvey(pAd, &Ssid, SCAN_ACTIVE, TRUE);

    return TRUE;

}

#ifdef AP_PARTIAL_SCAN_SUPPORT
INT Set_PartialScan_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *	arg)
{
	UINT8 bPartialScanning = simple_strtol(arg, 0, 10);
	pAd->ApCfg.bPartialScanning = bPartialScanning ? TRUE:FALSE;
	DBGPRINT(RT_DEBUG_TRACE, ("%s(): bPartialScanning = %u \n", __FUNCTION__, pAd->ApCfg.bPartialScanning));
	return TRUE;
}
#endif /* AP_PARTIAL_SCAN_SUPPORT */

/*
    ==========================================================================
    Description:
        Set a periodic check time for auto channel selection (unit: hour)
   Arguments:
       pAdapter                    Pointer to our adapter

    Return Value:
        TRUE if success, FALSE otherwise

    Note:
        Usage:
               iwpriv ra0 set ACSCheckTime=3  (unit: hour)

    ==========================================================================
*/
INT Set_AutoChannelSelCheckTime_Proc(
   IN  struct rtmp_adapter *  pAd,
   IN  char *    arg)
{
   UINT8 Hour = simple_strtol(arg, 0, 10);

   pAd->ApCfg.ACSCheckTime = Hour*3600; /* Hour to second */
   pAd->ApCfg.ACSCheckCount = 0; /* Reset counter */
   DBGPRINT(RT_DEBUG_TRACE, ("%s(): ACSCheckTime=%u seconds(%u hours)\n",
                               __FUNCTION__, pAd->ApCfg.ACSCheckTime, Hour));
   return TRUE;
}
#endif /* AP_SCAN_SUPPORT */


INT Show_DriverInfo_Proc(struct rtmp_adapter *pAd, char *arg)
{
	DBGPRINT(RT_DEBUG_OFF, ("driver version: %s.\n", AP_DRIVER_VERSION));

	return TRUE;
}


INT	Show_StaCount_Proc(struct rtmp_adapter *pAd, char *arg)
{
	INT i;
    	uint32_t RegValue;

	printk("\n");
	RTMP_IO_READ32(pAd, BKOFF_SLOT_CFG, &RegValue);
	printk("BackOff Slot      : %s slot time, BKOFF_SLOT_CFG(0x1104) = 0x%08x\n",
			OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_SHORT_SLOT_INUSED) ? "short" : "long",
 			RegValue);

	printk("HT Operating Mode : %d\n", pAd->CommonCfg.AddHTInfo.AddHtInfo2.OperaionMode);
	printk("\n");

	printk("\n%-19s%-4s%-12s%-12s%-12s%-12s\n",
		   "MAC", "AID","TxPackets","RxPackets","TxBytes","RxBytes");

	for (i=0; i<MAX_LEN_OF_MAC_TABLE; i++)
	{
		PMAC_TABLE_ENTRY pEntry = &pAd->MacTab.Content[i];
		if ((IS_ENTRY_CLIENT(pEntry) || IS_ENTRY_APCLI(pEntry))
			&& (pEntry->Sst == SST_ASSOC))
		{
			printk("%02X:%02X:%02X:%02X:%02X:%02X  ",
				pEntry->Addr[0], pEntry->Addr[1], pEntry->Addr[2],
				pEntry->Addr[3], pEntry->Addr[4], pEntry->Addr[5]);
			printk("%-4d", (int)pEntry->Aid);
			printk("%-12ld",(ULONG)pEntry->TxPackets.QuadPart);
			printk("%-12ld", (ULONG)pEntry->RxPackets.QuadPart);
			printk("%-12ld", (ULONG)pEntry->TxBytes);
			printk("%-12ld", (ULONG)pEntry->RxBytes);
			printk("\n");
		}
	}

	return TRUE;
}


INT	Show_StaSecurityInfo_Proc(struct rtmp_adapter *pAd, char *arg)
{
	INT i;
	UCHAR apidx;
	struct rtmp_wifi_dev *wdev;

	if (pAd == NULL)
		return FALSE;

	printk("\n");
	for (apidx = 0; apidx < pAd->ApCfg.BssidNum; apidx++)
	{
		wdev = &pAd->ApCfg.MBSSID[apidx].wdev;
		printk(" BSS(%d) AuthMode(%d)=%s, WepStatus(%d)=%s, GroupWepStatus(%d)=%s, WPAMixPairCipher(0x%02X)\n",
							apidx,
							wdev->AuthMode, GetAuthMode(wdev->AuthMode),
							wdev->WepStatus, GetEncryptType(wdev->WepStatus),
							wdev->GroupKeyWepStatus, GetEncryptType(wdev->GroupKeyWepStatus),
							wdev->WpaMixPairCipher);
	}
	printk("\n");

	printk("\n%-19s%-4s%-4s%-15s%-12s\n",
		   "MAC", "AID", "BSS", "Auth", "Encrypt");

	for (i=0; i<MAX_LEN_OF_MAC_TABLE; i++)
	{
		PMAC_TABLE_ENTRY pEntry = &pAd->MacTab.Content[i];
		if (pEntry && IS_ENTRY_CLIENT(pEntry) && pEntry->Sst == SST_ASSOC)
		{
			printk("%02X:%02X:%02X:%02X:%02X:%02X  ",
				PRINT_MAC(pEntry->Addr));
			printk("%-4d", (int)pEntry->Aid);
			printk("%-4d", (int)pEntry->apidx);
			printk("%-15s", GetAuthMode(pEntry->AuthMode));
			printk("%-12s", GetEncryptType(pEntry->WepStatus));
			printk("\n");
		}
	}

	return TRUE;
}


INT	Show_BaTable_Proc(struct rtmp_adapter *pAd, char *arg)
{
	INT i, j;
	BA_ORI_ENTRY *pOriBAEntry;
	BA_REC_ENTRY *pRecBAEntry;
	STRING		 tmpBuf[8];

	for (i=0; i < MAX_LEN_OF_MAC_TABLE; i++)
	{
		PMAC_TABLE_ENTRY pEntry = &pAd->MacTab.Content[i];
		if (IS_ENTRY_NONE(pEntry))
			continue;

		if ((IS_ENTRY_CLIENT(pEntry) || IS_ENTRY_APCLI(pEntry))
			&& (pEntry->Sst != SST_ASSOC))
			continue;

		if (IS_ENTRY_APCLI(pEntry))
		{
			strcpy(tmpBuf, "ApCli");
		}
		else if (IS_ENTRY_WDS(pEntry))
			strcpy(tmpBuf, "WDS");
		else if (IS_ENTRY_MESH(pEntry))
			strcpy(tmpBuf, "Mesh");
		else
			strcpy(tmpBuf, "STA");

		printk("%02X:%02X:%02X:%02X:%02X:%02X (Aid = %d) (%s) -\n",
			PRINT_MAC(pEntry->Addr), pEntry->Aid, tmpBuf);

		printk("[Recipient]\n");
		for (j=0; j < NUM_OF_TID; j++)
		{
			if (pEntry->BARecWcidArray[j] != 0)
			{
				pRecBAEntry =&pAd->BATable.BARecEntry[pEntry->BARecWcidArray[j]];
				printk("TID=%d, BAWinSize=%d, LastIndSeq=%d, ReorderingPkts=%d\n", j, pRecBAEntry->BAWinSize, pRecBAEntry->LastIndSeq, pRecBAEntry->list.qlen);
			}
		}
		printk("\n");

		printk("[Originator]\n");
		for (j=0; j < NUM_OF_TID; j++)
		{
			if (pEntry->BAOriWcidArray[j] != 0)
			{
				pOriBAEntry =&pAd->BATable.BAOriEntry[pEntry->BAOriWcidArray[j]];
				printk("TID=%d, BAWinSize=%d, StartSeq=%d, CurTxSeq=%d\n", j, pOriBAEntry->BAWinSize, pOriBAEntry->Sequence, pEntry->TxSeq[j]);
			}
		}
		printk("\n\n");
	}

	return TRUE;
}


INT Show_RAInfo_Proc(struct rtmp_adapter *pAd, char *arg)
{
#ifdef PRE_ANT_SWITCH
	DBGPRINT(RT_DEBUG_OFF, ("PreAntSwitch: %d\n", pAd->CommonCfg.PreAntSwitch));
	DBGPRINT(RT_DEBUG_OFF, ("PreAntSwitchRSSI: %d\n", pAd->CommonCfg.PreAntSwitchRSSI));
#endif /* PRE_ANT_SWITCH */

#ifdef CFO_TRACK
	DBGPRINT(RT_DEBUG_OFF, ("CFOTrack: %d\n", pAd->CommonCfg.CFOTrack));
#endif /* CFO_TRACK */


#ifdef NEW_RATE_ADAPT_SUPPORT
	DBGPRINT(RT_DEBUG_OFF, ("LowTrafficThrd: %d\n", pAd->CommonCfg.lowTrafficThrd));
	DBGPRINT(RT_DEBUG_OFF, ("TrainUpRule: %d\n", pAd->CommonCfg.TrainUpRule));
	DBGPRINT(RT_DEBUG_OFF, ("TrainUpRuleRSSI: %d\n", pAd->CommonCfg.TrainUpRuleRSSI));
	DBGPRINT(RT_DEBUG_OFF, ("TrainUpLowThrd: %d\n", pAd->CommonCfg.TrainUpLowThrd));
	DBGPRINT(RT_DEBUG_OFF, ("TrainUpHighThrd: %d\n", pAd->CommonCfg.TrainUpHighThrd));
#endif /* NEW_RATE_ADAPT_SUPPORT */

#ifdef STREAM_MODE_SUPPORT
	DBGPRINT(RT_DEBUG_OFF, ("StreamMode: %d\n", pAd->CommonCfg.StreamMode));
	DBGPRINT(RT_DEBUG_OFF, ("StreamModeMCS: 0x%04x\n", pAd->CommonCfg.StreamModeMCS));
#endif /* STREAM_MODE_SUPPORT */
#ifdef TXBF_SUPPORT
	DBGPRINT(RT_DEBUG_OFF, ("ITxBfEn: %d\n", pAd->CommonCfg.RegTransmitSetting.field.ITxBfEn));
	DBGPRINT(RT_DEBUG_OFF, ("ITxBfTimeout: %ld\n", pAd->CommonCfg.ITxBfTimeout));
	DBGPRINT(RT_DEBUG_OFF, ("ETxBfTimeout: %ld\n", pAd->CommonCfg.ETxBfTimeout));
	DBGPRINT(RT_DEBUG_OFF, ("ETxBfEnCond: %ld\n", pAd->CommonCfg.ETxBfEnCond));
	DBGPRINT(RT_DEBUG_OFF, ("ETxBfNoncompress: %d\n", pAd->CommonCfg.ETxBfNoncompress));
	DBGPRINT(RT_DEBUG_OFF, ("ETxBfIncapable: %d\n", pAd->CommonCfg.ETxBfIncapable));
#endif /* TXBF_SUPPORT */

#ifdef DBG_CTRL_SUPPORT
	DBGPRINT(RT_DEBUG_OFF, ("DebugFlags: 0x%lx\n", pAd->CommonCfg.DebugFlags));
#endif /* DBG_CTRL_SUPPORT */

	return TRUE;
}


#ifdef DBG_DIAGNOSE
#endif /* DBG_DIAGNOSE */


INT	Show_Sat_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	/* Sanity check for calculation of sucessful count */
	printk("TransmitCountFromOS = %d\n", pAd->WlanCounters.TransmitCountFrmOs.u.LowPart);
	printk("TransmittedFragmentCount = %lld\n", pAd->WlanCounters.TransmittedFragmentCount.u.LowPart + pAd->WlanCounters.MulticastTransmittedFrameCount.QuadPart);
	printk("MulticastTransmittedFrameCount = %d\n", pAd->WlanCounters.MulticastTransmittedFrameCount.u.LowPart);
	printk("FailedCount = %d\n", pAd->WlanCounters.FailedCount.u.LowPart);
	printk("RetryCount = %d\n", pAd->WlanCounters.RetryCount.u.LowPart);
	printk("MultipleRetryCount = %d\n", pAd->WlanCounters.MultipleRetryCount.u.LowPart);
	printk("RTSSuccessCount = %d\n", pAd->WlanCounters.RTSSuccessCount.u.LowPart);
	printk("RTSFailureCount = %d\n", pAd->WlanCounters.RTSFailureCount.u.LowPart);
	printk("ACKFailureCount = %d\n", pAd->WlanCounters.ACKFailureCount.u.LowPart);
	printk("FrameDuplicateCount = %d\n", pAd->WlanCounters.FrameDuplicateCount.u.LowPart);
	printk("ReceivedFragmentCount = %d\n", pAd->WlanCounters.ReceivedFragmentCount.u.LowPart);
	printk("MulticastReceivedFrameCount = %d\n", pAd->WlanCounters.MulticastReceivedFrameCount.u.LowPart);
	printk("Rx drop due to out of resource  = %ld\n", (ULONG)pAd->Counters8023.RxNoBuffer);
#ifdef DBG
	printk("RealFcsErrCount = %d\n", pAd->RalinkCounters.RealFcsErrCount.u.LowPart);
#else
	printk("FCSErrorCount = %d\n", pAd->WlanCounters.FCSErrorCount.u.LowPart);
	printk("FrameDuplicateCount.LowPart = %d\n", pAd->WlanCounters.FrameDuplicateCount.u.LowPart / 100);
#endif
	printk("TransmittedFrameCount = %d\n", pAd->WlanCounters.TransmittedFragmentCount.u.LowPart);
	printk("WEPUndecryptableCount = %d\n", pAd->WlanCounters.WEPUndecryptableCount.u.LowPart);

	printk("\n===Some 11n statistics variables: \n");
	/* Some 11n statistics variables */
	printk("TransmittedAMSDUCount = %ld\n", (ULONG)pAd->RalinkCounters.TransmittedAMSDUCount.u.LowPart);
	printk("TransmittedOctetsInAMSDU = %ld\n", (ULONG)pAd->RalinkCounters.TransmittedOctetsInAMSDU.QuadPart);
	printk("ReceivedAMSDUCount = %ld\n", (ULONG)pAd->RalinkCounters.ReceivedAMSDUCount.u.LowPart);
	printk("ReceivedOctesInAMSDUCount = %ld\n", (ULONG)pAd->RalinkCounters.ReceivedOctesInAMSDUCount.QuadPart);
	printk("TransmittedAMPDUCount = %ld\n", (ULONG)pAd->RalinkCounters.TransmittedAMPDUCount.u.LowPart);
	printk("TransmittedMPDUsInAMPDUCount = %ld\n", (ULONG)pAd->RalinkCounters.TransmittedMPDUsInAMPDUCount.u.LowPart);
	printk("TransmittedOctetsInAMPDUCount = %ld\n", (ULONG)pAd->RalinkCounters.TransmittedOctetsInAMPDUCount.u.LowPart);
	printk("MPDUInReceivedAMPDUCount = %ld\n", (ULONG)pAd->RalinkCounters.MPDUInReceivedAMPDUCount.u.LowPart);
	printk("fAnyStaFortyIntolerant=%d\n", pAd->MacTab.fAnyStaFortyIntolerant);

{
	int apidx;

	for (apidx=0; apidx < pAd->ApCfg.BssidNum; apidx++)
	{
		printk("-- IF-ra%d -- \n", apidx);
		printk("Packets Received = %ld\n", (ULONG)pAd->ApCfg.MBSSID[apidx].RxCount);
		printk("Packets Sent = %ld\n", (ULONG)pAd->ApCfg.MBSSID[apidx].TxCount);
		printk("Bytes Received = %ld\n", (ULONG)pAd->ApCfg.MBSSID[apidx].ReceivedByteCount);
		printk("Byte Sent = %ld\n", (ULONG)pAd->ApCfg.MBSSID[apidx].TransmittedByteCount);
		printk("Error Packets Received = %ld\n", (ULONG)pAd->ApCfg.MBSSID[apidx].RxErrorCount);
		printk("Drop Received Packets = %ld\n", (ULONG)pAd->ApCfg.MBSSID[apidx].RxDropCount);


		printk("-- IF-ra%d end -- \n", apidx);
	}
}

{
	int i, j, k, maxMcs = MAX_MCS_SET -1;
	PMAC_TABLE_ENTRY pEntry;

#ifdef DOT11N_SS3_SUPPORT
	if (IS_RT2883(pAd) || IS_RT3883(pAd))
		maxMcs = 23;
#endif /* DOT11N_SS3_SUPPORT */

	for (i=0; i<MAX_LEN_OF_MAC_TABLE; i++)
	{
		pEntry = &pAd->MacTab.Content[i];
		if (IS_ENTRY_CLIENT(pEntry) && (pEntry->Sst == SST_ASSOC))
		{
			printk("\n%02x:%02x:%02x:%02x:%02x:%02x - ", PRINT_MAC(pEntry->Addr));
			printk("%-4d\n", (int)pEntry->Aid);

			for (j=maxMcs; j>=0; j--)
			{
				if ((pEntry->TXMCSExpected[j] != 0) || (pEntry->TXMCSFailed[j] !=0))
				{
					printk("MCS[%02d]: Expected %u, Successful %u (%d%%), Failed %u\n",
						   j, pEntry->TXMCSExpected[j], pEntry->TXMCSSuccessful[j],
						   pEntry->TXMCSExpected[j] ? (100*pEntry->TXMCSSuccessful[j])/pEntry->TXMCSExpected[j] : 0,
						   pEntry->TXMCSFailed[j]);
					for(k=maxMcs; k>=0; k--)
					{
						if (pEntry->TXMCSAutoFallBack[j][k] != 0)
						{
							printk("\t\t\tAutoMCS[%02d]: %u (%d%%)\n", k, pEntry->TXMCSAutoFallBack[j][k],
								   (100*pEntry->TXMCSAutoFallBack[j][k])/pEntry->TXMCSExpected[j]);
						}
					}
				}
			}
		}
	}

}

	/* Display Tx Aggregation statistics */
	DisplayTxAgg(pAd);

	return TRUE;
}



INT	Show_Sat_Reset_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	/* Sanity check for calculation of sucessful count */

	printk("TransmittedFragmentCount = %lld\n", pAd->WlanCounters.TransmittedFragmentCount.u.LowPart + pAd->WlanCounters.MulticastTransmittedFrameCount.QuadPart);
	printk("MulticastTransmittedFrameCount = %d\n", pAd->WlanCounters.MulticastTransmittedFrameCount.u.LowPart);
	printk("FailedCount = %d\n", pAd->WlanCounters.FailedCount.u.LowPart);
	printk("RetryCount = %d\n", pAd->WlanCounters.RetryCount.u.LowPart);
	printk("MultipleRetryCount = %d\n", pAd->WlanCounters.MultipleRetryCount.u.LowPart);
	printk("RTSSuccessCount = %d\n", pAd->WlanCounters.RTSSuccessCount.u.LowPart);
	printk("RTSFailureCount = %d\n", pAd->WlanCounters.RTSFailureCount.u.LowPart);
	printk("ACKFailureCount = %d\n", pAd->WlanCounters.ACKFailureCount.u.LowPart);
	printk("FrameDuplicateCount = %d\n", pAd->WlanCounters.FrameDuplicateCount.u.LowPart);
	printk("ReceivedFragmentCount = %d\n", pAd->WlanCounters.ReceivedFragmentCount.u.LowPart);
	printk("MulticastReceivedFrameCount = %d\n", pAd->WlanCounters.MulticastReceivedFrameCount.u.LowPart);
	printk("Rx drop due to out of resource  = %ld\n", (ULONG)pAd->Counters8023.RxNoBuffer);
#ifdef DBG
	printk("RealFcsErrCount = %d\n", pAd->RalinkCounters.RealFcsErrCount.u.LowPart);
#else
	printk("FCSErrorCount = %d\n", pAd->WlanCounters.FCSErrorCount.u.LowPart);
	printk("FrameDuplicateCount.LowPart = %d\n", pAd->WlanCounters.FrameDuplicateCount.u.LowPart / 100);
#endif
	printk("TransmittedFrameCount = %d\n", pAd->WlanCounters.TransmittedFrameCount.u.LowPart);
	printk("WEPUndecryptableCount = %d\n", pAd->WlanCounters.WEPUndecryptableCount.u.LowPart);

	pAd->WlanCounters.TransmittedFragmentCount.u.LowPart = 0;
	pAd->WlanCounters.MulticastTransmittedFrameCount.u.LowPart = 0;
	pAd->WlanCounters.FailedCount.u.LowPart = 0;
	pAd->WlanCounters.RetryCount.u.LowPart = 0;
	pAd->WlanCounters.MultipleRetryCount.u.LowPart = 0;
	pAd->WlanCounters.RTSSuccessCount.u.LowPart = 0;
	pAd->WlanCounters.RTSFailureCount.u.LowPart = 0;
	pAd->WlanCounters.ACKFailureCount.u.LowPart = 0;
	pAd->WlanCounters.FrameDuplicateCount.u.LowPart = 0;
	pAd->WlanCounters.ReceivedFragmentCount.u.LowPart = 0;
	pAd->WlanCounters.MulticastReceivedFrameCount.u.LowPart = 0;
	pAd->Counters8023.RxNoBuffer = 0;
#ifdef DBG
	pAd->RalinkCounters.RealFcsErrCount.u.LowPart = 0;
#else
	pAd->WlanCounters.FCSErrorCount.u.LowPart = 0;
	pAd->WlanCounters.FrameDuplicateCount.u.LowPart = 0;
#endif

	pAd->WlanCounters.TransmittedFrameCount.u.LowPart = 0;
	pAd->WlanCounters.WEPUndecryptableCount.u.LowPart = 0;

	{
		int i, j, k, maxMcs = 15;
		PMAC_TABLE_ENTRY pEntry;

#ifdef DOT11N_SS3_SUPPORT
		if (IS_RT2883(pAd) || IS_RT3883(pAd))
			maxMcs = 23;
#endif /* DOT11N_SS3_SUPPORT */

		for (i=0; i<MAX_LEN_OF_MAC_TABLE; i++)
		{
			pEntry = &pAd->MacTab.Content[i];
			if (IS_ENTRY_CLIENT(pEntry) && (pEntry->Sst == SST_ASSOC))
			{

				printk("\n%02X:%02X:%02X:%02X:%02X:%02X - ",
					   pEntry->Addr[0], pEntry->Addr[1], pEntry->Addr[2],
					   pEntry->Addr[3], pEntry->Addr[4], pEntry->Addr[5]);
				printk("%-4d\n", (int)pEntry->Aid);

				for (j = maxMcs; j >= 0; j--)
				{
					if ((pEntry->TXMCSExpected[j] != 0) || (pEntry->TXMCSFailed[j] !=0))
					{
						printk("MCS[%02d]: Expected %u, Successful %u (%d%%), Failed %u\n",
							   j, pEntry->TXMCSExpected[j], pEntry->TXMCSSuccessful[j],
							   pEntry->TXMCSExpected[j] ? (100*pEntry->TXMCSSuccessful[j])/pEntry->TXMCSExpected[j] : 0,
							   pEntry->TXMCSFailed[j]
							   );
						for(k = maxMcs; k >= 0; k--)
						{
							if (pEntry->TXMCSAutoFallBack[j][k] != 0)
							{
								printk("\t\t\tAutoMCS[%02d]: %u (%d%%)\n", k, pEntry->TXMCSAutoFallBack[j][k],
									   (100*pEntry->TXMCSAutoFallBack[j][k])/pEntry->TXMCSExpected[j]);
							}
						}
					}
				}
			}
			for (j = 0; j < (maxMcs + 1); j++)
			{
				pEntry->TXMCSExpected[j] = 0;
				pEntry->TXMCSSuccessful[j] = 0;
				pEntry->TXMCSFailed[j] = 0;
				for(k = maxMcs; k >= 0; k--)
				{
					pEntry->TXMCSAutoFallBack[j][k] = 0;
				}
			}
		}
	}
	/* Display Tx Aggregation statistics */
	DisplayTxAgg(pAd);

	return TRUE;
}




#ifdef DOT1X_SUPPORT
/*
    ==========================================================================
    Description:
        It only shall be queried by 802.1x daemon for querying radius configuration.
	Arguments:
	    pAd		Pointer to our adapter
	    wrq		Pointer to the ioctl argument
    ==========================================================================
*/
VOID RTMPIoctlQueryRadiusConf(
	IN struct rtmp_adapter *pAd,
	IN RTMP_IOCTL_INPUT_STRUCT *wrq)
{
	UCHAR	apidx, srv_idx, keyidx, KeyLen = 0;
	UCHAR	*mpool;
	PDOT1X_CMM_CONF	pConf;

	DBGPRINT(RT_DEBUG_TRACE, ("RTMPIoctlQueryRadiusConf==>\n"));

	/* Allocate memory */
	mpool = kmalloc(sizeof(DOT1X_CMM_CONF), GFP_ATOMIC);
	if (mpool == NULL) {
		DBGPRINT(RT_DEBUG_ERROR, ("!!!%s: out of resource!!!\n", __FUNCTION__));
		return;
	}

	memset(mpool, 0, sizeof(DOT1X_CMM_CONF));

	pConf = (PDOT1X_CMM_CONF)mpool;

	/* get MBSS number */
	pConf->mbss_num = pAd->ApCfg.BssidNum;

	/* get own ip address */
	pConf->own_ip_addr = pAd->ApCfg.own_ip_addr;

	/* get retry interval */
	pConf->retry_interval = pAd->ApCfg.retry_interval;

	/* get session timeout interval */
	pConf->session_timeout_interval = pAd->ApCfg.session_timeout_interval;

	/* Get the quiet interval */
	pConf->quiet_interval = pAd->ApCfg.quiet_interval;

	for (apidx = 0; apidx < pAd->ApCfg.BssidNum; apidx++)
	{
		PMULTISSID_STRUCT 	pMbss = &pAd->ApCfg.MBSSID[apidx];
		PDOT1X_BSS_INFO  	p1xBssInfo = &pConf->Dot1xBssInfo[apidx];

		p1xBssInfo->radius_srv_num = pMbss->radius_srv_num;

		/* prepare radius ip, port and key */
		for (srv_idx = 0; srv_idx < pMbss->radius_srv_num; srv_idx++)
		{
			if (pMbss->radius_srv_info[srv_idx].radius_ip != 0)
			{
				p1xBssInfo->radius_srv_info[srv_idx].radius_ip = pMbss->radius_srv_info[srv_idx].radius_ip;
				p1xBssInfo->radius_srv_info[srv_idx].radius_port = pMbss->radius_srv_info[srv_idx].radius_port;
				p1xBssInfo->radius_srv_info[srv_idx].radius_key_len = pMbss->radius_srv_info[srv_idx].radius_key_len;
				if (pMbss->radius_srv_info[srv_idx].radius_key_len > 0)
				{
					memmove(p1xBssInfo->radius_srv_info[srv_idx].radius_key,
									pMbss->radius_srv_info[srv_idx].radius_key,
									pMbss->radius_srv_info[srv_idx].radius_key_len);
				}
			}
		}

		p1xBssInfo->ieee8021xWEP = (pMbss->wdev.IEEE8021X) ? 1 : 0;

		if (p1xBssInfo->ieee8021xWEP)
		{
			/* Default Key index, length and material */
			keyidx = pMbss->wdev.DefaultKeyId;
			p1xBssInfo->key_index = keyidx;

			/* Determine if the key is valid. */
			KeyLen = pAd->SharedKey[apidx][keyidx].KeyLen;
			if (KeyLen == 5 || KeyLen == 13)
			{
				p1xBssInfo->key_length = KeyLen;
				memmove(p1xBssInfo->key_material, pAd->SharedKey[apidx][keyidx].Key, KeyLen);
			}
		}

		/* Get NAS-ID per BSS */
		if (pMbss->NasIdLen > 0)
		{
			p1xBssInfo->nasId_len = pMbss->NasIdLen;
			memmove(p1xBssInfo->nasId, pMbss->NasId, pMbss->NasIdLen);
		}

		/* get EAPifname */
		if (pAd->ApCfg.EAPifname_len[apidx] > 0)
		{
			pConf->EAPifname_len[apidx] = pAd->ApCfg.EAPifname_len[apidx];
			memmove(pConf->EAPifname[apidx], pAd->ApCfg.EAPifname[apidx], pAd->ApCfg.EAPifname_len[apidx]);
		}

		/* get PreAuthifname */
		if (pAd->ApCfg.PreAuthifname_len[apidx] > 0)
		{
			pConf->PreAuthifname_len[apidx] = pAd->ApCfg.PreAuthifname_len[apidx];
			memmove(pConf->PreAuthifname[apidx], pAd->ApCfg.PreAuthifname[apidx], pAd->ApCfg.PreAuthifname_len[apidx]);
		}

	}

	wrq->u.data.length = sizeof(DOT1X_CMM_CONF);
	if (copy_to_user(wrq->u.data.pointer, pConf, wrq->u.data.length))
	{
		DBGPRINT(RT_DEBUG_ERROR, ("%s: copy_to_user() fail\n", __FUNCTION__));
	}

	kfree(mpool);

}


/*
    ==========================================================================
    Description:
        UI should not call this function, it only used by 802.1x daemon
	Arguments:
	    pAd		Pointer to our adapter
	    wrq		Pointer to the ioctl argument
    ==========================================================================
*/
VOID RTMPIoctlRadiusData(
	IN	struct rtmp_adapter *pAd,
	IN	RTMP_IOCTL_INPUT_STRUCT	*wrq)
{
	struct os_cookie *pObj = pAd->OS_Cookie;
	struct rtmp_wifi_dev *wdev;


	if (pObj->ioctl_if > pAd->ApCfg.BssidNum)
	{
		DBGPRINT(RT_DEBUG_ERROR, ("%s():Invalid MBSSID index(%d)!\n",
						__FUNCTION__, pObj->ioctl_if));
		return;
	}

	wdev = &pAd->ApCfg.MBSSID[pObj->ioctl_if].wdev;
	if ((wdev->AuthMode == Ndis802_11AuthModeWPA)
    	|| (wdev->AuthMode == Ndis802_11AuthModeWPA2)
    	|| (wdev->AuthMode == Ndis802_11AuthModeWPA1WPA2)
    	|| (wdev->IEEE8021X == TRUE))
    	WpaSend(pAd, (u8 *)wrq->u.data.pointer, wrq->u.data.length);
}


/*
    ==========================================================================
    Description:
        UI should not call this function, it only used by 802.1x daemon
	Arguments:
	    pAd		Pointer to our adapter
	    wrq		Pointer to the ioctl argument
    ==========================================================================
*/
VOID RTMPIoctlAddWPAKey(
	IN	struct rtmp_adapter *pAd,
	IN	RTMP_IOCTL_INPUT_STRUCT	*wrq)
{
	NDIS_AP_802_11_KEY 	*pKey;
	ULONG				KeyIdx;
	MAC_TABLE_ENTRY  	*pEntry;
	UCHAR				apidx;

	struct os_cookie *pObj = pAd->OS_Cookie;
	apidx =	(UCHAR) pObj->ioctl_if;


	pKey = (PNDIS_AP_802_11_KEY) wrq->u.data.pointer;

	if (pAd->ApCfg.MBSSID[apidx].wdev.AuthMode >= Ndis802_11AuthModeWPA)
	{
		if ((pKey->KeyLength == 32) || (pKey->KeyLength == 64))
		{
			if ((pEntry = MacTableLookup(pAd, pKey->addr)) != NULL)
			{
				INT	k_offset = 0;


				memmove(pAd->ApCfg.MBSSID[apidx].PMK, pKey->KeyMaterial + k_offset, 32);
    	        DBGPRINT(RT_DEBUG_TRACE, ("RTMPIoctlAddWPAKey-IF(ra%d) : Add PMK=%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x....\n", apidx,
            	pAd->ApCfg.MBSSID[apidx].PMK[0],pAd->ApCfg.MBSSID[apidx].PMK[1],pAd->ApCfg.MBSSID[apidx].PMK[2],pAd->ApCfg.MBSSID[apidx].PMK[3],
            	pAd->ApCfg.MBSSID[apidx].PMK[4],pAd->ApCfg.MBSSID[apidx].PMK[5],pAd->ApCfg.MBSSID[apidx].PMK[6],pAd->ApCfg.MBSSID[apidx].PMK[7]));
			}
		}
	}
	else	/* Old WEP stuff */
	{
		UCHAR	CipherAlg;
    	u8 *Key;

		if(pKey->KeyLength > 16)
			return;

		KeyIdx = pKey->KeyIndex & 0x0fffffff;

		if (KeyIdx < 4)
		{
			/* it is a shared key */
			if (pKey->KeyIndex & 0x80000000)
			{
				UINT8	Wcid;

				DBGPRINT(RT_DEBUG_TRACE, ("RTMPIoctlAddWPAKey-IF(ra%d) : Set Group Key\n", apidx));

				/* Default key for tx (shared key) */
				pAd->ApCfg.MBSSID[apidx].wdev.DefaultKeyId = (UCHAR) KeyIdx;

				/* set key material and key length */
				if (pKey->KeyLength > 16)
				{
					DBGPRINT(RT_DEBUG_TRACE, ("RTMPIoctlAddWPAKey-IF(ra%d) : Key length too long %d\n", apidx, pKey->KeyLength));
					pKey->KeyLength = 16;
				}
				pAd->SharedKey[apidx][KeyIdx].KeyLen = (UCHAR) pKey->KeyLength;
				memmove(pAd->SharedKey[apidx][KeyIdx].Key, &pKey->KeyMaterial, pKey->KeyLength);

				/* Set Ciper type */
				if (pKey->KeyLength == 5)
					pAd->SharedKey[apidx][KeyIdx].CipherAlg = CIPHER_WEP64;
				else
					pAd->SharedKey[apidx][KeyIdx].CipherAlg = CIPHER_WEP128;

    			CipherAlg = pAd->SharedKey[apidx][KeyIdx].CipherAlg;
    			Key = pAd->SharedKey[apidx][KeyIdx].Key;

				/* Set Group key material to Asic */
				AsicAddSharedKeyEntry(pAd, apidx, (UINT8)KeyIdx, &pAd->SharedKey[apidx][KeyIdx]);

				/* Get a specific WCID to record this MBSS key attribute */
				GET_GroupKey_WCID(pAd, Wcid, apidx);

				RTMPSetWcidSecurityInfo(pAd, apidx,(UINT8)KeyIdx,
									CipherAlg, Wcid, SHAREDKEYTABLE);
			}
			else	/* For Pairwise key setting */
			{
				pEntry = MacTableLookup(pAd, pKey->addr);
				if (pEntry)
				{
					DBGPRINT(RT_DEBUG_TRACE, ("RTMPIoctlAddWPAKey-IF(ra%d) : Set Pair-wise Key\n", apidx));

					/* set key material and key length */
 					pEntry->PairwiseKey.KeyLen = (UCHAR)pKey->KeyLength;
					memmove(pEntry->PairwiseKey.Key, &pKey->KeyMaterial, pKey->KeyLength);

					/* set Cipher type */
					if (pKey->KeyLength == 5)
						pEntry->PairwiseKey.CipherAlg = CIPHER_WEP64;
					else
						pEntry->PairwiseKey.CipherAlg = CIPHER_WEP128;

					/* Add Pair-wise key to Asic */
					AsicAddPairwiseKeyEntry(
						pAd,
						(UCHAR)pEntry->wcid,
                				&pEntry->PairwiseKey);

					/* update WCID attribute table and IVEIV table for this entry */
					RTMPSetWcidSecurityInfo(pAd,
										pEntry->apidx,
										(UINT8)KeyIdx,
										pEntry->PairwiseKey.CipherAlg,
										pEntry->wcid,
										PAIRWISEKEYTABLE);

				}
			}
		}
	}
}


/*
    ==========================================================================
    Description:
        UI should not call this function, it only used by 802.1x daemon
	Arguments:
	    pAd		Pointer to our adapter
	    wrq		Pointer to the ioctl argument
    ==========================================================================
*/
VOID RTMPIoctlAddPMKIDCache(
	IN	struct rtmp_adapter *pAd,
	IN	RTMP_IOCTL_INPUT_STRUCT	*wrq)
{
	UCHAR				apidx;
	NDIS_AP_802_11_KEY 	*pKey;
	struct os_cookie *pObj = pAd->OS_Cookie;

	apidx =	(UCHAR) pObj->ioctl_if;

	pKey = (PNDIS_AP_802_11_KEY) wrq->u.data.pointer;

    if (pAd->ApCfg.MBSSID[apidx].wdev.AuthMode >= Ndis802_11AuthModeWPA2)
	{
		if(pKey->KeyLength == 32)
		{
			UCHAR	digest[80], PMK_key[20], macaddr[MAC_ADDR_LEN];

			/* Calculate PMKID */
			memmove(&PMK_key[0], "PMK Name", 8);
			memmove(&PMK_key[8], pAd->ApCfg.MBSSID[apidx].wdev.bssid, MAC_ADDR_LEN);
			memmove(&PMK_key[14], pKey->addr, MAC_ADDR_LEN);
			RT_HMAC_SHA1(pKey->KeyMaterial, PMK_LEN, PMK_key, 20, digest, SHA1_DIGEST_SIZE);

			memmove(macaddr, pKey->addr, MAC_ADDR_LEN);
			RTMPAddPMKIDCache(pAd, apidx, macaddr, digest, pKey->KeyMaterial);

			DBGPRINT(RT_DEBUG_TRACE, ("WPA2(pre-auth):(%02x:%02x:%02x:%02x:%02x:%02x)Calc PMKID=%02x:%02x:%02x:%02x:%02x:%02x\n",
				pKey->addr[0],pKey->addr[1],pKey->addr[2],pKey->addr[3],pKey->addr[4],pKey->addr[5],digest[0],digest[1],digest[2],digest[3],digest[4],digest[5]));
			DBGPRINT(RT_DEBUG_TRACE, ("PMK =%02x:%02x:%02x:%02x-%02x:%02x:%02x:%02x\n",pKey->KeyMaterial[0],pKey->KeyMaterial[1],
				pKey->KeyMaterial[2],pKey->KeyMaterial[3],pKey->KeyMaterial[4],pKey->KeyMaterial[5],pKey->KeyMaterial[6],pKey->KeyMaterial[7]));
		}
		else
            DBGPRINT(RT_DEBUG_ERROR, ("Set::RT_OID_802_11_WPA2_ADD_PMKID_CACHE ERROR or is wep key \n"));
	}

    DBGPRINT(RT_DEBUG_TRACE, ("<== RTMPIoctlAddPMKIDCache\n"));
}


/*
    ==========================================================================
    Description:
        UI should not call this function, it only used by 802.1x daemon
	Arguments:
	    pAd		Pointer to our adapter
	    wrq		Pointer to the ioctl argument
    ==========================================================================
*/
VOID RTMPIoctlStaticWepCopy(
	IN	struct rtmp_adapter *pAd,
	IN	RTMP_IOCTL_INPUT_STRUCT	*wrq)
{
	MAC_TABLE_ENTRY  *pEntry;
	UCHAR	MacAddr[MAC_ADDR_LEN];
	UCHAR			apidx;
	struct os_cookie *pObj = pAd->OS_Cookie;

	apidx =	(UCHAR) pObj->ioctl_if;

    DBGPRINT(RT_DEBUG_TRACE, ("RTMPIoctlStaticWepCopy-IF(ra%d)\n", apidx));

    if (wrq->u.data.length != sizeof(MacAddr))
    {
        DBGPRINT(RT_DEBUG_ERROR, ("RTMPIoctlStaticWepCopy: the length isn't match (%d)\n", wrq->u.data.length));
        return;
    }
    else
    {
    	uint32_t len;

        len = copy_from_user(&MacAddr, wrq->u.data.pointer, wrq->u.data.length);
        pEntry = MacTableLookup(pAd, MacAddr);
        if (!pEntry)
        {
            DBGPRINT(RT_DEBUG_ERROR, ("RTMPIoctlStaticWepCopy: the mac address isn't match\n"));
            return;
        }
        else
        {
            UCHAR	KeyIdx;

            KeyIdx = pAd->ApCfg.MBSSID[apidx].wdev.DefaultKeyId;

            /* need to copy the default shared-key to pairwise key table for this entry in 802.1x mode */
			if (pAd->SharedKey[apidx][KeyIdx].KeyLen == 0)
			{
				DBGPRINT(RT_DEBUG_ERROR, ("ERROR: Can not get Default shared-key (index-%d)\n", KeyIdx));
				return;
			}
			else
        	{
            	pEntry->PairwiseKey.KeyLen = pAd->SharedKey[apidx][KeyIdx].KeyLen;
            	memmove(pEntry->PairwiseKey.Key, pAd->SharedKey[apidx][KeyIdx].Key, pEntry->PairwiseKey.KeyLen);
            	pEntry->PairwiseKey.CipherAlg = pAd->SharedKey[apidx][KeyIdx].CipherAlg;

				/* Add Pair-wise key to Asic */
            	AsicAddPairwiseKeyEntry(
                		pAd,
                		(UCHAR)pEntry->wcid,
                		&pEntry->PairwiseKey);

				/* update WCID attribute table and IVEIV table for this entry */
				RTMPSetWcidSecurityInfo(pAd,
										pEntry->apidx,
										(UINT8)KeyIdx,
                						pEntry->PairwiseKey.CipherAlg,
										pEntry->wcid,
										PAIRWISEKEYTABLE);
        	}

        }
	}
    return;
}

/*
    ==========================================================================
    Description:
        UI should not call this function, it only used by 802.1x daemon
	Arguments:
	    pAd		Pointer to our adapter
	    wrq		Pointer to the ioctl argument
    ==========================================================================
*/
VOID RTMPIoctlSetIdleTimeout(
	IN	struct rtmp_adapter *pAd,
	IN	RTMP_IOCTL_INPUT_STRUCT	*wrq)
{
	MAC_TABLE_ENTRY  		*pEntry;
	PDOT1X_IDLE_TIMEOUT		pIdleTime;

	if (wrq->u.data.length != sizeof(DOT1X_IDLE_TIMEOUT))
	{
        DBGPRINT(RT_DEBUG_ERROR, ("%s : the length is mis-match\n", __FUNCTION__));
        return;
    }

	pIdleTime = (PDOT1X_IDLE_TIMEOUT)wrq->u.data.pointer;

	if ((pEntry = MacTableLookup(pAd, pIdleTime->StaAddr)) == NULL)
    {
        DBGPRINT(RT_DEBUG_ERROR, ("%s : the entry is empty\n", __FUNCTION__));
        return;
    }
	else
	{
		pEntry->NoDataIdleCount = 0;
		pEntry->StaIdleTimeout = pIdleTime->idle_timeout;
		DBGPRINT(RT_DEBUG_TRACE, ("%s : Update Idle-Timeout(%d) from dot1x daemon\n",
									__FUNCTION__, pEntry->StaIdleTimeout));
	}

	return;
}


VOID RTMPIoctlQueryStaAid(
        IN      struct rtmp_adapter *  pAd,
        IN      RTMP_IOCTL_INPUT_STRUCT *wrq)
{
	DOT1X_QUERY_STA_AID macBuf;
	MAC_TABLE_ENTRY *pEntry = NULL;

	if (wrq->u.data.length != sizeof(DOT1X_QUERY_STA_AID))
	{
		DBGPRINT(RT_DEBUG_ERROR, ("%s : the length is mis-match\n", __FUNCTION__));
        	return;
	}
	else
	{
		copy_from_user(&macBuf, wrq->u.data.pointer, wrq->u.data.length);
		pEntry = MacTableLookup(pAd, macBuf.StaAddr);

		if (pEntry != NULL)
		{
			wrq->u.data.length = sizeof(DOT1X_QUERY_STA_AID);
			macBuf.aid = pEntry->Aid;
			if (copy_to_user(wrq->u.data.pointer, &macBuf, wrq->u.data.length))
			{
				DBGPRINT(RT_DEBUG_ERROR, ("%s: copy_to_user() fail\n", __FUNCTION__));
			}

			DBGPRINT(RT_DEBUG_TRACE, ("Query::OID_802_DOT1X_QUERY_STA_AID(%02x:%02x:%02x:%02x:%02x:%02x, AID=%d)\n",
						PRINT_MAC(macBuf.StaAddr), macBuf.aid));
		}
		else
		{
			DBGPRINT(RT_DEBUG_TRACE, ("Query::OID_802_DOT1X_QUERY_STA_AID(%02x:%02x:%02x:%02x:%02x:%02x, Not Found)\n",
					PRINT_MAC(macBuf.StaAddr)));
		}
	}
}
#endif /* DOT1X_SUPPORT */


#if defined(DBG)

#ifdef MT_RF
VOID RTMPAPIoctlRF_mt(
	IN	struct rtmp_adapter *pAd,
	IN	RTMP_IOCTL_INPUT_STRUCT	*wrq)
{
	CHAR				*value;
	UINT				regRF = 0;
	CHAR				*mpool, *msg; /*msg[2048]; */
	BOOLEAN				bIsPrintAllRF = TRUE;
	UINT				rfidx =0, offset = 0;
	INT					memLen = sizeof(CHAR) * 9000; //(2048+256+12);

	DBGPRINT(RT_DEBUG_TRACE, ("==>RTMPIoctlRF\n"));

	mpool = kmalloc(memLen, GFP_ATOMIC);
	if (mpool == NULL) {
		return;
	}

	memset(mpool, 0, memLen);
	msg = (char *)((ULONG)(mpool+3) & (ULONG)~0x03);

	if (bIsPrintAllRF)
	{
		RTMPZeroMemory(msg, memLen);
		sprintf(msg, "\n");
		for (rfidx = 0; rfidx <= 1; rfidx++)
		{
			for (offset = 0; offset <= 0x3ff; offset+=4)
			{
				mt_rf_read(pAd, rfidx, offset, &regRF);
				sprintf(msg+strlen(msg), "%d %03x = %08X\n", rfidx, offset, regRF);
			}
			offset = 0xfff;
			mt_rf_read(pAd, rfidx, offset, &regRF);
			sprintf(msg+strlen(msg), "%d %03x = %08X\n", rfidx, offset, regRF);
		}
		RtmpDrvAllRFPrint(NULL, msg, strlen(msg));

		DBGPRINT(RT_DEBUG_TRACE, ("strlen(msg)=%d\n", (uint32_t)strlen(msg)));
		/* Copy the information into the user buffer */
#ifdef LINUX
		wrq->u.data.length = strlen("Dump to RFDump.txt");
		if (copy_to_user(wrq->u.data.pointer, "Dump to RFDump.txt", wrq->u.data.length))
		{
			DBGPRINT(RT_DEBUG_TRACE, ("%s: copy_to_user() fail\n", __FUNCTION__));
		}
#endif /* LINUX */
	}

	kfree(mpool);
	DBGPRINT(RT_DEBUG_TRACE, ("<==RTMPIoctlRF\n\n"));
}
#endif /* MT_RF */

#ifdef RLT_RF
VOID RTMPAPIoctlRF_rlt(struct rtmp_adapter *pAdapter, RTMP_IOCTL_INPUT_STRUCT *wrq)
{
	UCHAR				regRF = 0;
	char *			mpool, *msg;
	char *			arg;
	INT					rfId, maxRFIdx, bank_Id;
	BOOLEAN				bIsPrintAllRF = TRUE, bFromUI;
	INT					memLen = sizeof(CHAR) * (2048+256+12);
	INT					argLen;

	maxRFIdx = pAdapter->chipCap.MaxNumOfRfId;

	DBGPRINT(RT_DEBUG_TRACE, ("==>RTMPIoctlRF (maxRFIdx = %d)\n", maxRFIdx));

	memLen = 12*(maxRFIdx+1)*MAC_RF_BANK;
	mpool = kmalloc(memLen, GFP_ATOMIC);
	if (mpool == NULL) {
		return;
	}

	bFromUI = ((wrq->u.data.flags & RTPRIV_IOCTL_FLAG_UI) == RTPRIV_IOCTL_FLAG_UI) ? TRUE : FALSE;

	memset(mpool, memLen);
	msg = (char *)((ULONG)(mpool+3) & (ULONG)~0x03);
	arg = (char *)((ULONG)(msg+2048+3) & (ULONG)~0x03);
	argLen = strlen((char *)(wrq->u.data.pointer));
	if (bIsPrintAllRF)
	{
		RTMPZeroMemory(msg, memLen);
		sprintf(msg, "\n");
		for (bank_Id = 0; bank_Id <= MAC_RF_BANK; bank_Id++)
		{
			if (IS_MT76x0(pAdapter))
			{
				if ((bank_Id <=4) && (bank_Id >=1))
					continue;
			}
			for (rfId = 0; rfId <= maxRFIdx; rfId++)
			{
				rlt_rf_read(pAdapter, bank_Id, rfId, &regRF);
				sprintf(msg+strlen(msg), "%d %03d = %02X\n", bank_Id, rfId, regRF);
			}
		}
		RtmpDrvAllRFPrint(NULL, msg, strlen(msg));
		/* Copy the information into the user buffer */

#ifdef LINUX
		wrq->u.data.length = strlen("Dump to RFDump.txt");
		if (copy_to_user(wrq->u.data.pointer, "Dump to RFDump.txt", wrq->u.data.length))
		{
			DBGPRINT(RT_DEBUG_TRACE, ("%s: copy_to_user() fail\n", __FUNCTION__));
		}
#endif /* LINUX */
	}

	kfree(mpool);
	DBGPRINT(RT_DEBUG_TRACE, ("<==RTMPIoctlRF\n"));
}
#endif /* RLT_RF */

#ifdef RTMP_RF_RW_SUPPORT
/*
    ==========================================================================
    Description:
        Read / Write RF register
Arguments:
    pAdapter                    Pointer to our adapter
    wrq                         Pointer to the ioctl argument

    Return Value:
        None

    Note:
        Usage:
               1.) iwpriv ra0 rf		==> read all RF registers
               2.) iwpriv ra0 rf 1		==> read RF where RegID=1
               3.) iwpriv ra0 rf 1=10	==> write RF R1=0x10
    ==========================================================================
*/
VOID RTMPAPIoctlRF(
	IN	struct rtmp_adapter *pAdapter,
	IN	RTMP_IOCTL_INPUT_STRUCT	*wrq)
{
	char *			this_char;
	char *			value;
	UCHAR				regRF = 0;
	char *			mpool, *msg; /*msg[2048]; */
	char *			arg; /*arg[255]; */
	char *			ptr;
	INT					rfId, maxRFIdx;
	LONG				rfValue;
	BOOLEAN				bIsPrintAllRF = FALSE, bFromUI;
	INT					memLen = sizeof(CHAR) * (2048+256+12);

#ifdef RLT_RF
	if (IS_MT7601(pAdapter) || IS_MT76x0(pAdapter)) {
		RTMPAPIoctlRF_rlt(pAdapter, wrq);
		return;
	}
#endif /* RLT_RF */

#ifdef MT_RF
	if (IS_MT76x2(pAdapter)) {
		RTMPAPIoctlRF_mt(pAdapter, wrq);
		return;
	}
#endif /* MT_RF */

	maxRFIdx = pAdapter->chipCap.MaxNumOfRfId;

/*	mpool = (char *)kmalloc(memLen, MEM_ALLOC_FLAG); */
	mpool = kmalloc(memLen, GFP_ATOMIC);
	if (mpool == NULL) {
		return;
	}

	bFromUI = ((wrq->u.data.flags & RTPRIV_IOCTL_FLAG_UI) == RTPRIV_IOCTL_FLAG_UI) ? TRUE : FALSE;

	memset(mpool, 0, memLen);
	msg = (char *)((ULONG)(mpool+3) & (ULONG)~0x03);
	arg = (char *)((ULONG)(msg+2048+3) & (ULONG)~0x03);

	if ((wrq->u.data.length > 1) /* No parameters. */
		)
	{
		memmove(arg, wrq->u.data.pointer, (wrq->u.data.length > 255) ? 255 : wrq->u.data.length);
		ptr = arg;
		sprintf(msg, "\n");
		/*Parsing Read or Write */
		while ((this_char = strsep((char **)&ptr, ",")) != NULL)
		{
			if (!*this_char)
				continue;

			if ((value = strchr(this_char, '=')) != NULL)
				*value++ = 0;

			if (!value || !*value)
			{ /*Read */
				if (sscanf(this_char, "%d", &(rfId)) == 1)
				{
					if (rfId <= pAdapter->chipCap.MaxNumOfRfId)
					{
						{
							/* according to Andy, Gary, David require. */
							/* the command rf shall read rf register directly for dubug. */
							/* BBP_IO_READ8_BY_REG_ID(pAdapter, bbpId, &regBBP); */
							{
								RT30xxReadRFRegister(pAdapter, rfId, &regRF);
								sprintf(msg+strlen(msg), "R%02d[0x%02x]:%02X  ", rfId, rfId, regRF);
							}
						}
					}
					else
					{
						/* Invalid parametes, so default printk all RF */
						bIsPrintAllRF = TRUE;
						break;
					}
				}
				else
				{
					/* Invalid parametes, so default printk all RF */
					bIsPrintAllRF = TRUE;
					break;
				}
			}
			else
			{ /* Write */
				if ((sscanf(this_char, "%d", &(rfId)) == 1) && (sscanf(value, "%lx", &(rfValue)) == 1))
				{
					if (rfId <= pAdapter->chipCap.MaxNumOfRfId)
					{
						{
							/* according to Andy, Gary, David require. */
							/* the command RF shall read/write RF register directly for dubug. */
							/*BBP_IO_READ8_BY_REG_ID(pAdapter, bbpId, &regBBP); */
							/*BBP_IO_WRITE8_BY_REG_ID(pAdapter, (UCHAR)bbpId,(UCHAR) bbpValue); */
							{
								RT30xxReadRFRegister(pAdapter, rfId, &regRF);
								RT30xxWriteRFRegister(pAdapter, (UCHAR)rfId,(UCHAR) rfValue);
								/* Read it back for showing */
								RT30xxReadRFRegister(pAdapter, rfId, &regRF);
								sprintf(msg+strlen(msg), "R%02d[0x%02X]:%02X\n", rfId, rfId, regRF);
							}
						}
					}
					else
					{	/* Invalid parametes, so default printk all RF */
						bIsPrintAllRF = TRUE;
						break;
					}
				}
				else
				{	/* Invalid parametes, so default printk all RF */
					bIsPrintAllRF = TRUE;
					break;
				}
			}
		}
	}
	else
		bIsPrintAllRF = TRUE;

	if (bIsPrintAllRF)
	{
		memset(msg, 0x00, 2048);
		sprintf(msg, "\n");
		for (rfId = 0; rfId <= maxRFIdx; rfId++)
		{
			{
				/* according to Andy, Gary, David require. */
				/* the command RF shall read/write RF register directly for dubug. */
				{
					RT30xxReadRFRegister(pAdapter, rfId, &regRF);
					sprintf(msg+strlen(msg), "R%02d[0x%02X]:%02X    ", rfId, rfId*2, regRF);
					if (rfId%5 == 4)
						sprintf(msg+strlen(msg), "\n");
				}
			}
		}
		/* Copy the information into the user buffer */

#ifdef LINUX
		wrq->u.data.length = strlen(msg);
		if (copy_to_user(wrq->u.data.pointer, msg, wrq->u.data.length))
		{
			DBGPRINT(RT_DEBUG_TRACE, ("%s: copy_to_user() fail\n", __FUNCTION__));
		}
#endif /* LINUX */
	}
	else
	{
#ifdef LINUX
		/* Copy the information into the user buffer */
		wrq->u.data.length = strlen(msg);
		if (copy_to_user(wrq->u.data.pointer, msg, wrq->u.data.length))
		{
			DBGPRINT(RT_DEBUG_TRACE, ("%s: copy_to_user() fail\n", __FUNCTION__));
		}
#endif /* LINUX */
	}

	if (!bFromUI)
	{
		DBGPRINT(RT_DEBUG_ERROR, ("Dump RF msg[%d]=\n", (uint32_t)strlen(msg)));
		DBGPRINT(RT_DEBUG_OFF, ("%s\n", msg));
	}

/*	kfree(mpool); */
	kfree(mpool);
	if (!bFromUI)
		DBGPRINT(RT_DEBUG_TRACE, ("<==RTMPIoctlRF\n\n"));

}
#endif /* RTMP_RF_RW_SUPPORT */
#endif /*#ifdef DBG */

//#define ENHANCED_STAT_DISPLAY	// Display PER and PLR statistics


/*
    ==========================================================================
    Description:
        Read statistics counter
Arguments:
    pAdapter                    Pointer to our adapter
    wrq                         Pointer to the ioctl argument

    Return Value:
        None

    Note:
        Usage:
               1.) iwpriv ra0 stat 0     	==> Read statistics counter
    ==========================================================================
*/
VOID RTMPIoctlStatistics(struct rtmp_adapter *pAd, RTMP_IOCTL_INPUT_STRUCT *wrq)
{
	INT Status;
	char *msg;
	ULONG txCount = 0;
	uint32_t rxCount = 0;
#ifdef ENHANCED_STAT_DISPLAY
	ULONG per, plr;
	INT i;
#endif
#ifdef RTMP_EFUSE_SUPPORT
	UINT efusefreenum=0;
#endif /* RTMP_EFUSE_SUPPORT */

#ifdef BB_SOC
	ULONG txPackets=0, rxPackets=0, txBytes=0, rxBytes=0;
	UCHAR index=0;
#endif

	RTMP_CHIP_CAP *pChipCap = &pAd->chipCap;

/*	msg = (char *)kmalloc(sizeof(CHAR)*(2048), MEM_ALLOC_FLAG); */
	msg = kmalloc(sizeof(CHAR)*(2048), GFP_ATOMIC);
	if (msg == NULL) {
		return;
	}


    memset(msg, 0x00, 1600);
    sprintf(msg, "\n");

	{
		txCount = pAd->WlanCounters.TransmittedFragmentCount.u.LowPart;
		rxCount = pAd->WlanCounters.ReceivedFragmentCount.QuadPart;
	}

	sprintf(msg+strlen(msg), "Current temperature = %d�J\n", pChipCap->current_temp);
    sprintf(msg+strlen(msg), "Tx success                      = %ld\n", txCount);
#ifdef ENHANCED_STAT_DISPLAY
	per = txCount==0? 0: 1000*(pAd->WlanCounters.RetryCount.u.LowPart+pAd->WlanCounters.FailedCount.u.LowPart)/(pAd->WlanCounters.RetryCount.u.LowPart+pAd->WlanCounters.FailedCount.u.LowPart+txCount);
    sprintf(msg+strlen(msg), "Tx retry count                  = %ld, PER=%ld.%1ld%%\n",
									(ULONG)pAd->WlanCounters.RetryCount.u.LowPart,
									per/10, per % 10);
	plr = txCount==0? 0: 10000*pAd->WlanCounters.FailedCount.u.LowPart/(pAd->WlanCounters.FailedCount.u.LowPart+txCount);
    sprintf(msg+strlen(msg), "Tx fail to Rcv ACK after retry  = %ld, PLR=%ld.%02ld%%\n",
									(ULONG)pAd->WlanCounters.FailedCount.u.LowPart, plr/100, plr%100);
    sprintf(msg+strlen(msg), "Rx success                      = %ld\n", (ULONG)rxCount);
	per = pAd->WlanCounters.ReceivedFragmentCount.u.LowPart==0? 0: 1000*(pAd->WlanCounters.FCSErrorCount.u.LowPart)/(pAd->WlanCounters.FCSErrorCount.u.LowPart+pAd->WlanCounters.ReceivedFragmentCount.u.LowPart);
	sprintf(msg+strlen(msg), "Rx with CRC                     = %ld, PER=%ld.%1ld%%\n",
									(ULONG)pAd->WlanCounters.FCSErrorCount.u.LowPart, per/10, per % 10);
	sprintf(msg+strlen(msg), "Rx with PhyErr                  = %ld\n",
									(ULONG)pAd->RalinkCounters.PhyErrCnt);
	sprintf(msg+strlen(msg), "Rx with PlcpErr                 = %ld\n",
									(ULONG)pAd->RalinkCounters.PlcpErrCnt);
	sprintf(msg+strlen(msg), "Rx drop due to out of resource  = %ld\n", (ULONG)pAd->Counters8023.RxNoBuffer);
	sprintf(msg+strlen(msg), "Rx duplicate frame              = %ld\n", (ULONG)pAd->WlanCounters.FrameDuplicateCount.u.LowPart);

	sprintf(msg+strlen(msg), "False CCA                       = %ld\n", (ULONG)pAd->RalinkCounters.FalseCCACnt);
#else
    sprintf(msg+strlen(msg), "Tx retry count                  = %ld\n", (ULONG)pAd->WlanCounters.RetryCount.u.LowPart);
    sprintf(msg+strlen(msg), "Tx fail to Rcv ACK after retry  = %ld\n", (ULONG)pAd->WlanCounters.FailedCount.u.LowPart);
    sprintf(msg+strlen(msg), "RTS Success Rcv CTS             = %ld\n", (ULONG)pAd->WlanCounters.RTSSuccessCount.u.LowPart);
    sprintf(msg+strlen(msg), "RTS Fail Rcv CTS                = %ld\n", (ULONG)pAd->WlanCounters.RTSFailureCount.u.LowPart);

    sprintf(msg+strlen(msg), "Rx success                      = %ld\n", (ULONG)pAd->WlanCounters.ReceivedFragmentCount.QuadPart);
    sprintf(msg+strlen(msg), "Rx with CRC                     = %ld\n", (ULONG)pAd->WlanCounters.FCSErrorCount.u.LowPart);
    sprintf(msg+strlen(msg), "Rx drop due to out of resource  = %ld\n", (ULONG)pAd->Counters8023.RxNoBuffer);
    sprintf(msg+strlen(msg), "Rx duplicate frame              = %ld\n", (ULONG)pAd->WlanCounters.FrameDuplicateCount.u.LowPart);

    sprintf(msg+strlen(msg), "False CCA (one second)          = %ld\n", (ULONG)pAd->RalinkCounters.OneSecFalseCCACnt);
#endif /* ENHANCED_STAT_DISPLAY */

	{
#ifdef ENHANCED_STAT_DISPLAY
	sprintf(msg+strlen(msg), "RSSI                            = %ld %ld %ld\n",
    			(LONG)(pAd->ApCfg.RssiSample.LastRssi0 - pAd->BbpRssiToDbmDelta),
    			(LONG)(pAd->ApCfg.RssiSample.LastRssi1 - pAd->BbpRssiToDbmDelta),
    			(LONG)(pAd->ApCfg.RssiSample.LastRssi2 - pAd->BbpRssiToDbmDelta));

    	/* Display Last Rx Rate and BF SNR of first Associated entry in MAC table */
    	if (pAd->MacTab.Size > 0)
    	{
    		static char *phyMode[5] = {"CCK", "OFDM", "MM", "GF", "VHT"};
#ifdef RT65xx
			static char *bw[3] = {"20M", "40M", "80M"};
			static char *fec_coding[2] = {"bcc", "ldpc"};
#endif /* RT65xx */

    		for (i=1; i<MAX_LEN_OF_MAC_TABLE; i++)
			{
    			PMAC_TABLE_ENTRY pEntry = &(pAd->MacTab.Content[i]);
    			if (IS_ENTRY_CLIENT(pEntry) && pEntry->Sst==SST_ASSOC)
				{
					//sprintf(msg+strlen(msg), "sta mac: %02x:%02x:%02x:%02x:%02x:%02x\n", pEntry->wdev->if_addr[0], pEntry->wdev->if_addr[1],  pEntry->wdev->if_addr[2],  pEntry->wdev->if_addr[3],  pEntry->wdev->if_addr[4],  pEntry->wdev->if_addr[5]);
					uint32_t lastRxRate = pEntry->LastRxRate;
					uint32_t lastTxRate = pEntry->LastTxRate;
#ifdef RT65xx
					if (IS_RT65XX(pAd)) {
						ULONG TxTotalCnt, TxSuccess, TxRetransmit, TxFailCount, TxErrorRatio = 0;
						TX_STA_CNT1_STRUC StaTx1;
						TX_STA_CNT0_STRUC TxStaCnt0;

						/*  Update statistic counter */
						NicGetTxRawCounters(pAd, &TxStaCnt0, &StaTx1);

						TxRetransmit = StaTx1.field.TxRetransmit;
						TxSuccess = StaTx1.field.TxSuccess;
						TxFailCount = TxStaCnt0.field.TxFailCount;
						TxTotalCnt = TxRetransmit + TxSuccess + TxFailCount;

						if (TxTotalCnt)
							TxErrorRatio = ((TxRetransmit + TxFailCount) * 100) / TxTotalCnt;

						if (((lastTxRate >> 13) & 0x7) == 0x04) {
							sprintf(msg+strlen(msg), "Last TX Rate                    = MCS%d, %dSS, %s, %s, %cGI, %s%s\n",
								lastTxRate & 0x0F,
								(((lastTxRate >> 4) & 0x3) + 1),
								fec_coding[((lastTxRate >> 6) & 0x1)],
								bw[((lastTxRate >> 7) & 0x3)],
								((lastTxRate >> 9) & 0x1)? 'S': 'L',
								phyMode[(lastTxRate >> 13) & 0x7],
								((lastTxRate >> 10) & 0x3)? ", STBC": " ");

							sprintf(msg+strlen(msg), "Last TX PER = %lu\n", TxErrorRatio);
						} else {
							sprintf(msg+strlen(msg), "Last TX Rate                    = MCS%d, %s, %s, %cGI, %s%s\n",
								lastTxRate & 0x3F,
								fec_coding[((lastTxRate >> 6) & 0x1)],
								bw[((lastTxRate >> 7) & 0x3)],
								((lastTxRate >> 9) & 0x1)? 'S': 'L',
								phyMode[(lastTxRate >> 13) & 0x7],
								((lastTxRate >> 10) & 0x3)? ", STBC": " ");
						}

						if (((lastRxRate >> 13) & 0x7) == 0x04) {
							sprintf(msg+strlen(msg), "Last RX Rate                    = MCS%d, %dSS, %s, %s, %cGI, %s%s\n",
								lastRxRate & 0x0F,
								(((lastRxRate >> 4) & 0x3) + 1),
								fec_coding[((lastRxRate >> 6) & 0x1)],
								bw[((lastRxRate >> 7) & 0x3)],
								((lastRxRate >> 9) & 0x1)? 'S': 'L',
								phyMode[(lastRxRate >> 13) & 0x7],
								((lastRxRate >> 10) & 0x3)? ", STBC": " ");
						} else {
							sprintf(msg+strlen(msg), "Last RX Rate                    = MCS%d, %s, %s, %cGI, %s%s\n",
								lastRxRate & 0x3F,
								fec_coding[((lastRxRate >> 6) & 0x1)],
								bw[((lastRxRate >> 7) & 0x3)],
								((lastRxRate >> 9) & 0x1)? 'S': 'L',
								phyMode[(lastRxRate >> 13) & 0x7],
								((lastRxRate >> 10) & 0x3)? ", STBC": " ");
						}
					}
					else
#endif /* RT65xx */
					{
						sprintf(msg+strlen(msg), "Last TX Rate                    = MCS%d, %2dM, %cGI, %s%s\n",
							lastTxRate & 0x3F,  ((lastTxRate>>7) & 0x3)? 40: 20,
							((lastTxRate>>9) & 0x1)? 'S': 'L',
							phyMode[(lastTxRate>>13) & 0x3],
							((lastTxRate>>10) & 0x1)? ", STBC": " ");
						sprintf(msg+strlen(msg), "Last RX Rate                    = MCS%d, %2dM, %cGI, %s%s\n",
							lastRxRate & 0x3F,  ((lastRxRate>>7) & 0x3)? 40: 20,
							((lastRxRate>>9) & 0x1)? 'S': 'L',
							phyMode[(lastRxRate>>13) & 0x3],
							((lastRxRate>>10) & 0x1)? ", STBC": " ");
					}

					break;
				}
			}
    	}
#else
    	sprintf(msg+strlen(msg), "RSSI-A                          = %ld\n", (LONG)(pAd->ApCfg.RssiSample.LastRssi0 - pAd->BbpRssiToDbmDelta));
		sprintf(msg+strlen(msg), "RSSI-B (if available)           = %ld\n", (LONG)(pAd->ApCfg.RssiSample.LastRssi1 - pAd->BbpRssiToDbmDelta));
		sprintf(msg+strlen(msg), "RSSI-C (if available)           = %ld\n\n", (LONG)(pAd->ApCfg.RssiSample.LastRssi2 - pAd->BbpRssiToDbmDelta));
#endif /* ENHANCED_STAT_DISPLAY */
	}


#if /*TCSUPPORT_COMPILE*/ defined(TCSUPPORT_SCHEDULE)
	if(pAd->Flags & fRTMP_ADAPTER_RADIO_OFF)
		sprintf(msg+strlen(msg), "Enable Wireless LAN		= %s\n", "0");
	else
		sprintf(msg+strlen(msg), "Enable Wireless LAN		= %s\n", "1");
	sprintf(msg+strlen(msg), "\n");
#endif /*TCSUPPORT_COMPILE*/

/*
 * Let "iwpriv ra0 stat" can print out Tx/Rx Packet and Byte count.
 * Therefore, we can parse them out in cfg_manager. --Trey */
#ifdef BB_SOC
	for (index = 0; index < pAd->ApCfg.BssidNum; index++){
		rxPackets += (ULONG)pAd->ApCfg.MBSSID[index].RxCount;
		txPackets += (ULONG)pAd->ApCfg.MBSSID[index].TxCount;
		rxBytes += (ULONG)pAd->ApCfg.MBSSID[index].ReceivedByteCount;
		txBytes += (ULONG)pAd->ApCfg.MBSSID[index].TransmittedByteCount;
	}
	sprintf(msg+strlen(msg), "Packets Received       = %lu\n", rxPackets);
	sprintf(msg+strlen(msg), "Packets Sent           = %lu\n", txPackets);
	sprintf(msg+strlen(msg), "Bytes Received         = %lu\n", rxBytes);
	sprintf(msg+strlen(msg), "Bytes Sent             = %lu\n", txBytes);
	sprintf(msg+strlen(msg), "\n");
#endif

    /* Copy the information into the user buffer */
    wrq->u.data.length = strlen(msg);
    Status = copy_to_user(wrq->u.data.pointer, msg, wrq->u.data.length);

	kfree(msg);
/*	kfree(msg); */

#if defined(TXBF_SUPPORT) && defined(ENHANCED_STAT_DISPLAY)
#ifdef DBG_CTRL_SUPPORT
	/* Debug code to display BF statistics */
	if (pAd->CommonCfg.DebugFlags & DBF_SHOW_BF_STATS)
	{
		for (i=0; i<MAX_LEN_OF_MAC_TABLE; i++) {
			PMAC_TABLE_ENTRY pEntry = &(pAd->MacTab.Content[i]);
			COUNTER_TXBF *pCnt;
			ULONG totalNBF, totalEBF, totalIBF, totalTx, totalRetry, totalSuccess;

			if (!IS_ENTRY_CLIENT(pEntry) || pEntry->Sst!=SST_ASSOC)
				continue;

			pCnt = &pEntry->TxBFCounters;

			totalNBF = pCnt->TxSuccessCount + pCnt->TxFailCount;
			totalEBF = pCnt->ETxSuccessCount + pCnt->ETxFailCount;
			totalIBF = pCnt->ITxSuccessCount + pCnt->ITxFailCount;

			totalTx = totalNBF + totalEBF + totalIBF;
			totalRetry = pCnt->TxRetryCount + pCnt->ETxRetryCount + pCnt->ITxRetryCount;
			totalSuccess = pCnt->TxSuccessCount + pCnt->ETxSuccessCount + pCnt->ITxSuccessCount;

			DBGPRINT(RT_DEBUG_OFF, ("MacTable[%d]     Success    Retry/PER    Fail/PLR\n", i) );
			if (totalTx==0) {
				DBGPRINT(RT_DEBUG_OFF, ("   Total = 0\n") );
				continue;
			}

			if (totalNBF!=0) {
				DBGPRINT(RT_DEBUG_OFF, ("   NonBF (%3lu%%): %7lu  %7lu (%2lu%%) %5lu (%1lu%%)\n",
					100*totalNBF/totalTx, pCnt->TxSuccessCount,
					pCnt->TxRetryCount, 100*pCnt->TxRetryCount/(pCnt->TxSuccessCount+pCnt->TxRetryCount),
					pCnt->TxFailCount, 100*pCnt->TxFailCount/totalNBF) );
			}

			if (totalEBF!=0) {
				DBGPRINT(RT_DEBUG_OFF, ("   ETxBF (%3lu%%): %7lu  %7lu (%2lu%%) %5lu (%1lu%%)\n",
					 100*totalEBF/totalTx, pCnt->ETxSuccessCount,
					pCnt->ETxRetryCount, 100*pCnt->ETxRetryCount/(pCnt->ETxSuccessCount+pCnt->ETxRetryCount),
					pCnt->ETxFailCount, 100*pCnt->ETxFailCount/totalEBF) );
			}

			if (totalIBF!=0) {
				DBGPRINT(RT_DEBUG_OFF, ("   ITxBF (%3lu%%): %7lu  %7lu (%2lu%%) %5lu (%1lu%%)\n",
					100*totalIBF/totalTx, pCnt->ITxSuccessCount,
					pCnt->ITxRetryCount, 100*pCnt->ITxRetryCount/(pCnt->ITxSuccessCount+pCnt->ITxRetryCount),
					pCnt->ITxFailCount, 100*pCnt->ITxFailCount/totalIBF) );
			}

			DBGPRINT(RT_DEBUG_OFF, ("   Total         %7lu  %7lu (%2lu%%) %5lu (%1lu%%)\n",
				totalSuccess, totalRetry, 100*totalRetry/(totalSuccess + totalRetry),
				pCnt->TxFailCount+pCnt->ETxFailCount+pCnt->ITxFailCount,
				100*(pCnt->TxFailCount+pCnt->ETxFailCount+pCnt->ITxFailCount)/totalTx) );
		}
	}
#endif /* DBG_CTRL_SUPPORT */
#endif /* defined(TXBF_SUPPORT) && defined(ENHANCED_STAT_DISPLAY) */

    DBGPRINT(RT_DEBUG_TRACE, ("<==RTMPIoctlStatistics\n"));
}


/*
    ==========================================================================
    Description:
        Get Block ACK Table
	Arguments:
	    pAdapter                    Pointer to our adapter
	    wrq                         Pointer to the ioctl argument

    Return Value:
        None

    Note:
        Usage:
        		1.) iwpriv ra0 get_ba_table
        		3.) UI needs to prepare at least 4096bytes to get the results
    ==========================================================================
*/
VOID RTMPIoctlQueryBaTable(
	IN	struct rtmp_adapter *pAd,
	IN	RTMP_IOCTL_INPUT_STRUCT	*wrq)
{
	/*char *msg; */
	UCHAR	TotalEntry, i, j, index;
	QUERYBA_TABLE		*BAT;

	BAT = vmalloc(sizeof(QUERYBA_TABLE));

	if (BAT == NULL)
		return;

	RTMPZeroMemory(BAT, sizeof(QUERYBA_TABLE));

	TotalEntry = pAd->MacTab.Size;
	index = 0;
	for (i=0; ((i < MAX_LEN_OF_MAC_TABLE) && (TotalEntry > 0)); i++)
	{
		PMAC_TABLE_ENTRY pEntry = &pAd->MacTab.Content[i];

		if (IS_ENTRY_CLIENT(pEntry) && (pEntry->Sst == SST_ASSOC) && (pEntry->TXBAbitmap))
		{
			memmove(BAT->BAOriEntry[index].MACAddr, pEntry->Addr, 6);
			for (j=0;j<8;j++)
			{
				if (pEntry->BAOriWcidArray[j] != 0)
					BAT->BAOriEntry[index].BufSize[j] = pAd->BATable.BAOriEntry[pEntry->BAOriWcidArray[j]].BAWinSize;
				else
					BAT->BAOriEntry[index].BufSize[j] = 0;
			}

			TotalEntry--;
			index++;
			BAT->OriNum++;
		}
	}

	TotalEntry = pAd->MacTab.Size;
	index = 0;
	for (i=0; ((i < MAX_LEN_OF_MAC_TABLE) && (TotalEntry > 0)); i++)
	{
		PMAC_TABLE_ENTRY pEntry = &pAd->MacTab.Content[i];

		if (IS_ENTRY_CLIENT(pEntry) && (pEntry->Sst == SST_ASSOC) && (pEntry->RXBAbitmap))
		{
			memmove(BAT->BARecEntry[index].MACAddr, pEntry->Addr, 6);
			BAT->BARecEntry[index].BaBitmap = (UCHAR)pEntry->RXBAbitmap;
			for (j = 0; j < 8; j++)
			{
				if (pEntry->BARecWcidArray[j] != 0)
					BAT->BARecEntry[index].BufSize[j] = pAd->BATable.BARecEntry[pEntry->BARecWcidArray[j]].BAWinSize;
				else
					BAT->BARecEntry[index].BufSize[j] = 0;
			}

			TotalEntry--;
			index++;
			BAT->RecNum++;
		}
	}

	wrq->u.data.length = sizeof(QUERYBA_TABLE);

	if (copy_to_user(wrq->u.data.pointer, BAT, wrq->u.data.length))
	{
		DBGPRINT(RT_DEBUG_TRACE, ("%s: copy_to_user() fail\n", __FUNCTION__));
	}

	vfree(BAT);

}


#ifdef APCLI_SUPPORT
INT Set_ApCli_Enable_Proc(
	IN  struct rtmp_adapter *pAd,
	IN  char *arg)
{
	UINT Enable;
	struct os_cookie *pObj;
	UCHAR ifIndex;

	pObj = pAd->OS_Cookie;
	if (pObj->ioctl_if_type != INT_APCLI)
		return FALSE;

	ifIndex = pObj->ioctl_if;

	Enable = simple_strtol(arg, 0, 16);

	pAd->ApCfg.ApCliTab[ifIndex].Enable = (Enable > 0) ? TRUE : FALSE;

	DBGPRINT(RT_DEBUG_TRACE, ("I/F(apcli%d) Set_ApCli_Enable_Proc::(enable = %d)\n", ifIndex, pAd->ApCfg.ApCliTab[ifIndex].Enable));
#ifdef APCLI_CONNECTION_TRIAL
	if (pAd->ApCfg.ApCliTab[ifIndex].TrialCh == 0)
#endif /* APCLI_CONNECTION_TRIAL */
	ApCliIfDown(pAd);

	return TRUE;
}


INT Set_ApCli_Ssid_Proc(struct rtmp_adapter *pAd, char *arg)
{
	struct os_cookie *pObj;
	UCHAR ifIndex;
	BOOLEAN apcliEn;
	INT success = FALSE;
	/*UCHAR keyMaterial[40]; */
	UCHAR PskKey[100];
	APCLI_STRUCT *apcli_entry;
	struct rtmp_wifi_dev *wdev;

	pObj = pAd->OS_Cookie;
	if (pObj->ioctl_if_type != INT_APCLI)
		return FALSE;

	ifIndex = pObj->ioctl_if;

	if(strlen(arg) <= MAX_LEN_OF_SSID)
	{
		apcli_entry = &pAd->ApCfg.ApCliTab[ifIndex];
		wdev = &apcli_entry->wdev;

		/* bring apcli interface down first */
		apcliEn = apcli_entry->Enable;
#ifdef APCLI_CONNECTION_TRIAL
		if (pAd->ApCfg.ApCliTab[ifIndex].TrialCh == 0)
		{
#endif /* APCLI_CONNECTION_TRIAL */
		if(apcliEn == TRUE )
		{
			apcli_entry->Enable = FALSE;
			ApCliIfDown(pAd);
		}
#ifdef APCLI_CONNECTION_TRIAL
		}
#endif /* APCLI_CONNECTION_TRIAL */

		memset(apcli_entry->CfgSsid, MAX_LEN_OF_SSID);
		memmove(apcli_entry->CfgSsid, arg, strlen(arg));
		apcli_entry->CfgSsidLen = (UCHAR)strlen(arg);
		success = TRUE;

		/* Upadte PMK and restart WPAPSK state machine for ApCli link */
		if (((wdev->AuthMode == Ndis802_11AuthModeWPAPSK) ||
			(wdev->AuthMode == Ndis802_11AuthModeWPA2PSK)) &&
			apcli_entry->PSKLen > 0)
		{
			memset(PskKey, 100);
			memmove(PskKey, apcli_entry->PSK, apcli_entry->PSKLen);

			RT_CfgSetWPAPSKKey(pAd, (char *)PskKey,
									apcli_entry->PSKLen,
									(u8 *)apcli_entry->CfgSsid,
									apcli_entry->CfgSsidLen,
									apcli_entry->PMK);
		}

		DBGPRINT(RT_DEBUG_TRACE, ("I/F(apcli%d) Set_ApCli_Ssid_Proc::(Len=%d,Ssid=%s)\n",
				ifIndex, apcli_entry->CfgSsidLen, apcli_entry->CfgSsid));

		apcli_entry->Enable = apcliEn;
	}
	else
		success = FALSE;

	return success;
}


INT Set_ApCli_Bssid_Proc(
	IN  struct rtmp_adapter *pAd,
	IN  char *arg)
{
	INT i;
	char *value;
	UCHAR ifIndex;
	BOOLEAN apcliEn;
	struct os_cookie *pObj;

	pObj = pAd->OS_Cookie;
	if (pObj->ioctl_if_type != INT_APCLI)
		return FALSE;

	ifIndex = pObj->ioctl_if;

	apcliEn = pAd->ApCfg.ApCliTab[ifIndex].Enable;

	/* bring apcli interface down first */
	if(apcliEn == TRUE )
	{
		pAd->ApCfg.ApCliTab[ifIndex].Enable = FALSE;
#ifdef APCLI_CONNECTION_TRIAL
		if (pAd->ApCfg.ApCliTab[ifIndex].TrialCh == 0)
#endif /* APCLI_CONNECTION_TRIAL */
		ApCliIfDown(pAd);
	}

	memset(pAd->ApCfg.ApCliTab[ifIndex].CfgApCliBssid, MAC_ADDR_LEN);

	if(strlen(arg) == 17)  /* Mac address acceptable format 01:02:03:04:05:06 length 17 */
	{
		for (i=0, value = rstrtok(arg,":"); value; value = rstrtok(NULL,":"), i++)
		{
			if((strlen(value) != 2) || (!isxdigit(*value)) || (!isxdigit(*(value+1))) )
				return FALSE;  /* Invalid */

			AtoH(value, &pAd->ApCfg.ApCliTab[ifIndex].CfgApCliBssid[i], 1);
		}

		if(i != 6)
			return FALSE;  /* Invalid */
	}

	DBGPRINT(RT_DEBUG_TRACE, ("Set_ApCli_Bssid_Proc (%2X:%2X:%2X:%2X:%2X:%2X)\n",
		pAd->ApCfg.ApCliTab[ifIndex].CfgApCliBssid[0],
		pAd->ApCfg.ApCliTab[ifIndex].CfgApCliBssid[1],
		pAd->ApCfg.ApCliTab[ifIndex].CfgApCliBssid[2],
		pAd->ApCfg.ApCliTab[ifIndex].CfgApCliBssid[3],
		pAd->ApCfg.ApCliTab[ifIndex].CfgApCliBssid[4],
		pAd->ApCfg.ApCliTab[ifIndex].CfgApCliBssid[5]));

	pAd->ApCfg.ApCliTab[ifIndex].Enable = apcliEn;

	return TRUE;
}


/*
    ==========================================================================
    Description:
        Set ApCli-IF Authentication mode
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_ApCli_AuthMode_Proc(struct rtmp_adapter *pAd, char *arg)
{
	ULONG i;
	struct os_cookie *	pObj = pAd->OS_Cookie;
	UCHAR ifIndex;
	struct rtmp_wifi_dev *wdev;

	if (pObj->ioctl_if_type != INT_APCLI)
		return FALSE;

	ifIndex = pObj->ioctl_if;
	wdev = &pAd->ApCfg.ApCliTab[ifIndex].wdev;

	if (rtstrcasecmp(arg, "WEPAUTO") == TRUE)
		wdev->AuthMode = Ndis802_11AuthModeAutoSwitch;
	else if (rtstrcasecmp(arg, "SHARED") == TRUE)
		wdev->AuthMode = Ndis802_11AuthModeShared;
	else if (rtstrcasecmp(arg, "WPAPSK") == TRUE)
		wdev->AuthMode = Ndis802_11AuthModeWPAPSK;
	else if (rtstrcasecmp(arg, "WPA2PSK") == TRUE)
		wdev->AuthMode = Ndis802_11AuthModeWPA2PSK;
	else if (rtstrcasecmp(arg, "WPAPSKWPA2PSK") == TRUE)
	{
		wdev->AuthMode = Ndis802_11AuthModeWPA1PSKWPA2PSK;
		wdev->bWpaAutoMode = TRUE;
	}
#ifdef APCLI_WPA_SUPPLICANT_SUPPORT
   	else if (rtstrcasecmp(arg, "WPA") == TRUE)
       	wdev->AuthMode = Ndis802_11AuthModeWPA;
    	else if (rtstrcasecmp(arg, "WPA2") == TRUE)
        	wdev->AuthMode = Ndis802_11AuthModeWPA2;
#endif /*APCLI_WPA_SUPPLICANT_SUPPORT */

	else
		wdev->AuthMode = Ndis802_11AuthModeOpen;

	for (i=0; i<MAX_LEN_OF_MAC_TABLE; i++)
	{
		if (IS_ENTRY_APCLI(&pAd->MacTab.Content[i]))
		{
			pAd->MacTab.Content[i].PortSecured  = WPA_802_1X_PORT_NOT_SECURED;
		}
	}

	RTMPMakeRSNIE(pAd, wdev->AuthMode, wdev->WepStatus, (ifIndex + MIN_NET_DEVICE_FOR_APCLI));

	wdev->DefaultKeyId  = 0;

	if(wdev->AuthMode >= Ndis802_11AuthModeWPA)
		wdev->DefaultKeyId = 1;

	DBGPRINT(RT_DEBUG_TRACE, ("IF(apcli%d) Set_ApCli_AuthMode_Proc::(AuthMode=%d)\n", ifIndex, wdev->AuthMode));
	return TRUE;
}


/*
    ==========================================================================
    Description:
        Set ApCli-IF Encryption Type
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_ApCli_EncrypType_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	struct os_cookie *	pObj = pAd->OS_Cookie;
	UCHAR 		ifIndex;
	PAPCLI_STRUCT   pApCliEntry = NULL;
	struct rtmp_wifi_dev *wdev;


	if (pObj->ioctl_if_type != INT_APCLI)
		return FALSE;

	ifIndex = pObj->ioctl_if;

	pApCliEntry = &pAd->ApCfg.ApCliTab[ifIndex];
	wdev = &pApCliEntry->wdev;

	wdev->WepStatus = Ndis802_11WEPDisabled;
	if (rtstrcasecmp(arg, "WEP") == TRUE)
    {
		if (wdev->AuthMode < Ndis802_11AuthModeWPA)
			wdev->WepStatus = Ndis802_11WEPEnabled;
	}
	else if (rtstrcasecmp(arg, "TKIP") == TRUE)
	{
		if (wdev->AuthMode >= Ndis802_11AuthModeWPA)
			wdev->WepStatus = Ndis802_11Encryption2Enabled;
    }
	else if ((rtstrcasecmp(arg, "AES") == TRUE) || (rtstrcasecmp(arg, "TKIPAES") == TRUE))
	{
		if (wdev->AuthMode >= Ndis802_11AuthModeWPA)
			wdev->WepStatus = Ndis802_11Encryption3Enabled;
	}
	else
	{
		wdev->WepStatus = Ndis802_11WEPDisabled;
	}

	pApCliEntry->PairCipher = wdev->WepStatus;
	pApCliEntry->GroupCipher = wdev->WepStatus;
	pApCliEntry->bMixCipher = FALSE;

	if (wdev->WepStatus >= Ndis802_11Encryption2Enabled)
		wdev->DefaultKeyId = 1;

	RTMPMakeRSNIE(pAd, wdev->AuthMode, wdev->WepStatus, (ifIndex + MIN_NET_DEVICE_FOR_APCLI));
	DBGPRINT(RT_DEBUG_TRACE, ("IF(apcli%d) Set_ApCli_EncrypType_Proc::(EncrypType=%d)\n", ifIndex, wdev->WepStatus));

	return TRUE;
}



/*
    ==========================================================================
    Description:
        Set Default Key ID
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_ApCli_DefaultKeyID_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	ULONG 			KeyIdx;
	struct os_cookie *		pObj = pAd->OS_Cookie;
	struct rtmp_wifi_dev *wdev;


	if (pObj->ioctl_if_type != INT_APCLI)
		return FALSE;

	wdev = &pAd->ApCfg.ApCliTab[pObj->ioctl_if].wdev;

	KeyIdx = simple_strtol(arg, 0, 10);
	if((KeyIdx >= 1 ) && (KeyIdx <= 4))
		wdev->DefaultKeyId = (UCHAR) (KeyIdx - 1 );
	else
		return FALSE;  /* Invalid argument */

	DBGPRINT(RT_DEBUG_TRACE, ("IF(apcli%d) Set_DefaultKeyID_Proc::(DefaultKeyID(0~3)=%d)\n", pObj->ioctl_if, wdev->DefaultKeyId));

	return TRUE;
}

/*
    ==========================================================================
    Description:
        Set WPA PSK key for ApCli link

    Arguments:
        pAdapter            Pointer to our adapter
        arg                 WPA pre-shared key string

    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_ApCli_WPAPSK_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	UCHAR ifIndex;
	struct os_cookie *pObj;
	PAPCLI_STRUCT   pApCliEntry = NULL;
	INT retval;

	pObj = pAd->OS_Cookie;
	if (pObj->ioctl_if_type != INT_APCLI)
		return FALSE;

	ifIndex = pObj->ioctl_if;
	pApCliEntry = &pAd->ApCfg.ApCliTab[ifIndex];

	DBGPRINT(RT_DEBUG_TRACE, ("Set_ApCli_WPAPSK_Proc::(WPAPSK=%s)\n", arg));

	retval = RT_CfgSetWPAPSKKey(pAd, arg, strlen(arg), (u8 *)pApCliEntry->CfgSsid, pApCliEntry->CfgSsidLen, pApCliEntry->PMK);
	if (retval == FALSE)
		return FALSE;

	memmove(pApCliEntry->PSK, arg, strlen(arg));
	pApCliEntry->PSKLen = strlen(arg);

	return TRUE;
}


/*
    ==========================================================================
    Description:
        Set WEP KEY1 for ApCli-IF
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_ApCli_Key1_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	struct os_cookie *		pObj = pAd->OS_Cookie;
	PAPCLI_STRUCT	pApCliEntry = NULL;
	UCHAR			ifIndex;
	INT				retVal;

	if (pObj->ioctl_if_type != INT_APCLI)
		return FALSE;

	ifIndex = pObj->ioctl_if;
	pApCliEntry = &pAd->ApCfg.ApCliTab[ifIndex];

	retVal = RT_CfgSetWepKey(pAd, arg, &pApCliEntry->SharedKey[0], 0);
	if(retVal == TRUE)
		DBGPRINT(RT_DEBUG_TRACE, ("IF(apcli%d) Set_ApCli_Key1_Proc::(Key1=%s) success!\n", ifIndex, arg));

	return retVal;

}


/*
    ==========================================================================
    Description:
        Set WEP KEY2 for ApCli-IF
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_ApCli_Key2_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	struct os_cookie *		pObj;
	PAPCLI_STRUCT	pApCliEntry = NULL;
	UCHAR			ifIndex;
	INT				retVal;

	pObj = pAd->OS_Cookie;
	if (pObj->ioctl_if_type != INT_APCLI)
		return FALSE;

	ifIndex = pObj->ioctl_if;
	pApCliEntry = &pAd->ApCfg.ApCliTab[ifIndex];

	retVal = RT_CfgSetWepKey(pAd, arg, &pApCliEntry->SharedKey[1], 1);
	if(retVal == TRUE)
		DBGPRINT(RT_DEBUG_TRACE, ("IF(apcli%d) Set_ApCli_Key2_Proc::(Key2=%s) success!\n", ifIndex, arg));

	return retVal;
}


/*
    ==========================================================================
    Description:
        Set WEP KEY3 for ApCli-IF
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_ApCli_Key3_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	struct os_cookie *		pObj;
	PAPCLI_STRUCT	pApCliEntry = NULL;
	UCHAR			ifIndex;
	INT				retVal;

	pObj = pAd->OS_Cookie;
	if (pObj->ioctl_if_type != INT_APCLI)
		return FALSE;

	ifIndex = pObj->ioctl_if;
	pApCliEntry = &pAd->ApCfg.ApCliTab[ifIndex];

	retVal = RT_CfgSetWepKey(pAd, arg, &pApCliEntry->SharedKey[2], 2);
	if(retVal == TRUE)
		DBGPRINT(RT_DEBUG_TRACE, ("IF(apcli%d) Set_ApCli_Key3_Proc::(Key3=%s) success!\n", ifIndex, arg));

	return retVal;
}


/*
    ==========================================================================
    Description:
        Set WEP KEY4 for ApCli-IF
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_ApCli_Key4_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	struct os_cookie *		pObj;
	PAPCLI_STRUCT	pApCliEntry = NULL;
	UCHAR			ifIndex;
	INT				retVal;

	pObj = pAd->OS_Cookie;
	if (pObj->ioctl_if_type != INT_APCLI)
		return FALSE;

	ifIndex = pObj->ioctl_if;
	pApCliEntry = &pAd->ApCfg.ApCliTab[ifIndex];

	retVal = RT_CfgSetWepKey(pAd, arg, &pApCliEntry->SharedKey[3], 3);
	if(retVal == TRUE)
		DBGPRINT(RT_DEBUG_TRACE, ("IF(apcli%d) Set_ApCli_Key4_Proc::(Key4=%s) success!\n", ifIndex, arg));

	return retVal;
}

INT Set_ApCli_TxMode_Proc(
	IN  struct rtmp_adapter *pAd,
	IN  char *arg)
{
	struct os_cookie *pObj = pAd->OS_Cookie;
	struct rtmp_wifi_dev *wdev;


	if (pObj->ioctl_if_type != INT_APCLI)
		return FALSE;

	wdev = &pAd->ApCfg.ApCliTab[pObj->ioctl_if].wdev;

	wdev->DesiredTransmitSetting.field.FixedTxMode = RT_CfgSetFixedTxPhyMode(arg);
	DBGPRINT(RT_DEBUG_TRACE, ("I/F(apcli%d) Set_ApCli_TxMode_Proc = %d\n",
				pObj->ioctl_if, wdev->DesiredTransmitSetting.field.FixedTxMode));

	return TRUE;
}

INT Set_ApCli_TxMcs_Proc(
	IN  struct rtmp_adapter *pAd,
	IN  char *arg)
{
	struct os_cookie *pObj = pAd->OS_Cookie;
	struct rtmp_wifi_dev *wdev;


	if (pObj->ioctl_if_type != INT_APCLI)
		return FALSE;

	wdev = &pAd->ApCfg.ApCliTab[pObj->ioctl_if].wdev;

	wdev->DesiredTransmitSetting.field.MCS =
			RT_CfgSetTxMCSProc(arg, &wdev->bAutoTxRateSwitch);

	if (wdev->DesiredTransmitSetting.field.MCS == MCS_AUTO)
	{
		DBGPRINT(RT_DEBUG_TRACE, ("I/F(apcli%d) Set_ApCli_TxMcs_Proc = AUTO\n", pObj->ioctl_if));
	}
	else
	{
		DBGPRINT(RT_DEBUG_TRACE, ("I/F(apcli%d) Set_ApCli_TxMcs_Proc = %d\n",
					pObj->ioctl_if, wdev->DesiredTransmitSetting.field.MCS));
	}

	return TRUE;
}

#ifdef APCLI_CONNECTION_TRIAL
INT Set_ApCli_Trial_Ch_Proc(
	IN  struct rtmp_adapter *pAd,
	IN  char *arg)
{
	struct os_cookie *		pObj;
	UCHAR 			ifIndex;
	PAPCLI_STRUCT	pApCliEntry = NULL;

	pObj = pAd->OS_Cookie;
	if (pObj->ioctl_if_type != INT_APCLI)
		return FALSE;

	ifIndex = pObj->ioctl_if;
	pApCliEntry = &pAd->ApCfg.ApCliTab[ifIndex];

	pApCliEntry->TrialCh = simple_strtol(arg, 0, 10);

	if (pApCliEntry->TrialCh)
	{
		DBGPRINT(RT_DEBUG_TRACE, ("I/F(apcli%d) pApCliEntry->TrialCh = %d\n", ifIndex, pApCliEntry->TrialCh));
	}
	else
	{
		DBGPRINT(RT_DEBUG_TRACE, ("I/F(apcli%d) pApCliEntry->TrialCh = %d\n", ifIndex, pApCliEntry->TrialCh));
	}

	return TRUE;
}
#endif /* APCLI_CONNECTION_TRIAL */

#ifdef APCLI_WPA_SUPPLICANT_SUPPORT
INT Set_ApCli_Wpa_Support(
    IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	struct os_cookie *		pObj;
	UCHAR 			ifIndex;
	PAPCLI_STRUCT	pApCliEntry = NULL;

	pObj = pAd->OS_Cookie;
	if (pObj->ioctl_if_type != INT_APCLI)
		return FALSE;

	ifIndex = pObj->ioctl_if;
	pApCliEntry = &pAd->ApCfg.ApCliTab[ifIndex];

    if ( simple_strtol(arg, 0, 10) == 0)
        pApCliEntry->WpaSupplicantUP = WPA_SUPPLICANT_DISABLE;
    else if ( simple_strtol(arg, 0, 10) == 1)
        pApCliEntry->WpaSupplicantUP = WPA_SUPPLICANT_ENABLE;
    else if ( simple_strtol(arg, 0, 10) == 2)
        pApCliEntry->WpaSupplicantUP = WPA_SUPPLICANT_ENABLE_WITH_WEB_UI;
    else
        pApCliEntry->WpaSupplicantUP = WPA_SUPPLICANT_DISABLE;

    DBGPRINT(RT_DEBUG_TRACE, ("Set_ApCli_Wpa_Support::(WpaSupplicantUP=%d)\n", pApCliEntry->WpaSupplicantUP));

    return TRUE;
}


INT	Set_ApCli_IEEE8021X_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
    	ULONG ieee8021x;
	struct os_cookie *		pObj;
	UCHAR 			ifIndex;
	PAPCLI_STRUCT	pApCliEntry = NULL;

	pObj = pAd->OS_Cookie;
	if (pObj->ioctl_if_type != INT_APCLI)
		return FALSE;

	ifIndex = pObj->ioctl_if;
	pApCliEntry = &pAd->ApCfg.ApCliTab[ifIndex];

	ieee8021x = simple_strtol(arg, 0, 10);

	if (ieee8021x == 1)
        pApCliEntry->wdev.IEEE8021X = TRUE;
	else if (ieee8021x == 0)
		pApCliEntry->wdev.IEEE8021X = FALSE;
	else
		return FALSE;

	DBGPRINT(RT_DEBUG_TRACE, ("IF(ra%d) Set_ApCli_IEEE8021X_Proc::(IEEE8021X=%d)\n", pObj->ioctl_if, pApCliEntry->wdev.IEEE8021X));

	return TRUE;
}
#endif /* APCLI_WPA_SUPPLICANT_SUPPORT */


#ifdef APCLI_AUTO_CONNECT_SUPPORT
/*
    ==========================================================================
    Description:
        Trigger Apcli Auto connect to find the missed AP.
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT Set_ApCli_AutoConnect_Proc(
	IN struct rtmp_adapter *pAd,
	IN char *arg)
{
	struct os_cookie * 		pObj= pAd->OS_Cookie;
	UCHAR				ifIndex;
	PAP_ADMIN_CONFIG	pApCfg;
	long scan_mode = simple_strtol(arg, 0, 10);

	if (pObj->ioctl_if_type != INT_APCLI)
		return FALSE;
	pApCfg = &pAd->ApCfg;
	ifIndex = pObj->ioctl_if;

	if (pApCfg->ApCliAutoConnectRunning == FALSE)
	{
		Set_ApCli_Enable_Proc(pAd, "0");
		pApCfg->ApCliAutoConnectRunning = TRUE;
	}
	else
	{
		DBGPRINT(RT_DEBUG_TRACE, ("Set_ApCli_AutoConnect_Proc() is still running\n"));
		return TRUE;
	}
	DBGPRINT(RT_DEBUG_TRACE, ("I/F(apcli%d) Set_ApCli_AutoConnect_Proc::(Len=%d,Ssid=%s)\n",
			ifIndex, pApCfg->ApCliTab[ifIndex].CfgSsidLen, pApCfg->ApCliTab[ifIndex].CfgSsid));

#ifdef AP_PARTIAL_SCAN_SUPPORT
#define AUTO_SCAN_MODE_FULL    1
#define AUTO_SCAN_MODE_PARTIAL 2

	if (scan_mode == AUTO_SCAN_MODE_PARTIAL)
	{
		pAd->ApCfg.bPartialScanning = TRUE;
	}
	else
#endif /* AP_PARTIAL_SCAN_SUPPORT */
	{
		/*      AUTO_SCAN_MODE_FULL
		use site survey function to trigger auto connecting (when pAd->ApCfg.ApAutoConnectRunning == TRUE)
		*/
		Set_SiteSurvey_Proc(pAd, "");//pApCfg->ApCliTab[ifIndex].CfgSsid);
	}

	return TRUE;
}
#endif  /* APCLI_AUTO_CONNECT_SUPPORT */



#ifdef APCLI_CERT_SUPPORT
INT Set_ApCli_Cert_Enable_Proc(
	IN  struct rtmp_adapter *pAd,
	IN  char *arg)
{
	UINT Enable;
	struct os_cookie *pObj;
	UCHAR ifIndex;

	pObj = pAd->OS_Cookie;
	if (pObj->ioctl_if_type != INT_APCLI)
		return FALSE;

	ifIndex = pObj->ioctl_if;

	Enable = simple_strtol(arg, 0, 16);

	pAd->bApCliCertTest = (Enable > 0) ? TRUE : FALSE;

	DBGPRINT(RT_DEBUG_TRACE, ("I/F(apcli%d) Set_ApCli_Cert_Enable_Proc::(enable = %d)\n", ifIndex, pAd->bApCliCertTest));

	return TRUE;
}

INT Set_ApCli_WMM_Enable_Proc(
	IN  struct rtmp_adapter *pAd,
	IN  char *arg)
{
	UINT Enable;
	struct os_cookie *pObj;
	UCHAR ifIndex;
	PAPCLI_STRUCT pApCliEntry = NULL;
	struct rtmp_wifi_dev *wdev;

	pObj = pAd->OS_Cookie;
	if (pObj->ioctl_if_type != INT_APCLI)
		return FALSE;

	ifIndex = pObj->ioctl_if;

	Enable = simple_strtol(arg, 0, 16);
	pApCliEntry = &pAd->ApCfg.ApCliTab[ifIndex];
	pApCliEntry->wdev.bWmmCapable = (Enable > 0) ? TRUE : FALSE;

	DBGPRINT(RT_DEBUG_TRACE, ("I/F(apcli%d) Set_ApCli_WMM_Enable_Proc::(enable = %d)\n", ifIndex, pApCliEntry->wdev.bWmmCapable));

	return TRUE;
}
#endif /* APCLI_CERT_SUPPORT */
#endif /* APCLI_SUPPORT */

INT	Set_DisConnectSta_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	UCHAR					macAddr[MAC_ADDR_LEN];
	char *				value;
	INT						i;
	MAC_TABLE_ENTRY *pEntry = NULL;

	if(strlen(arg) != 17)  /*Mac address acceptable format 01:02:03:04:05:06 length 17 */
		return FALSE;

	for (i=0, value = rstrtok(arg,":"); value; value = rstrtok(NULL,":"))
	{
		if((strlen(value) != 2) || (!isxdigit(*value)) || (!isxdigit(*(value+1))) )
			return FALSE;  /*Invalid */

		AtoH(value, (UCHAR *)&macAddr[i++], 1);
	}

	pEntry = MacTableLookup(pAd, macAddr);
	if (pEntry)
	{
		MlmeDeAuthAction(pAd, pEntry, REASON_DISASSOC_STA_LEAVING, FALSE);
/*		MacTableDeleteEntry(pAd, pEntry->wcid, Addr); */
	}

	return TRUE;
}

INT Set_DisConnectAllSta_Proc(
        IN struct rtmp_adapter *pAd,
	IN char *arg)
{
#ifdef DOT11W_PMF_SUPPORT
        CHAR value = simple_strtol(arg, 0, 10);

	if (value == 2)
        {
		struct os_cookie *pObj = pAd->OS_Cookie;
		INT i;

		DBGPRINT(RT_DEBUG_WARN, ("[PMF]%s:: apidx=%d\n", __FUNCTION__, pObj->ioctl_if));
		APMlmeKickOutAllSta(pAd, pObj->ioctl_if, REASON_DEAUTH_STA_LEAVING);
		for (i=1; i<MAX_LEN_OF_MAC_TABLE; i++)
		{
			MAC_TABLE_ENTRY *pEntry = &pAd->MacTab.Content[i];
			if (IS_ENTRY_CLIENT(pEntry)) {
				DBGPRINT(RT_DEBUG_ERROR, ("[PMF]%s: MacTableDeleteEntry %x:%x:%x:%x:%x:%x\n",
						__FUNCTION__, PRINT_MAC(pEntry->Addr)));
				MacTableDeleteEntry(pAd, pEntry->wcid, pEntry->Addr);
			}
		}
        } else
#endif /* DOT11W_PMF_SUPPORT */
	{
		MacTableReset(pAd);
	}

	return TRUE;
}


#ifdef DOT1X_SUPPORT
/*
    ==========================================================================
    Description:
        Set IEEE8021X.
        This parameter is 1 when 802.1x-wep turn on, otherwise 0
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_IEEE8021X_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	ULONG ieee8021x;
	struct os_cookie *pObj = pAd->OS_Cookie;
	struct rtmp_wifi_dev *wdev;

	ieee8021x = simple_strtol(arg, 0, 10);

	wdev = &pAd->ApCfg.MBSSID[pObj->ioctl_if].wdev;
	if (ieee8021x == 1)
		wdev->IEEE8021X = TRUE;
	else if (ieee8021x == 0)
		wdev->IEEE8021X = FALSE;
	else
		return FALSE;  /*Invalid argument */

	DBGPRINT(RT_DEBUG_TRACE, ("IF(ra%d) Set_IEEE8021X_Proc::(IEEE8021X=%d)\n", pObj->ioctl_if, wdev->IEEE8021X));

	return TRUE;
}

/*
    ==========================================================================
    Description:
        Set pre-authentication enable or disable when WPA/WPA2 turn on
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	Set_PreAuth_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
    ULONG PreAuth;
	struct os_cookie *pObj = pAd->OS_Cookie;

	PreAuth = simple_strtol(arg, 0, 10);

	if (PreAuth == 1)
		pAd->ApCfg.MBSSID[pObj->ioctl_if].PreAuth = TRUE;
	else if (PreAuth == 0)
		pAd->ApCfg.MBSSID[pObj->ioctl_if].PreAuth = FALSE;
	else
		return FALSE;  /*Invalid argument */

	DBGPRINT(RT_DEBUG_TRACE, ("IF(ra%d) Set_PreAuth_Proc::(PreAuth=%d)\n", pObj->ioctl_if, pAd->ApCfg.MBSSID[pObj->ioctl_if].PreAuth));

	return TRUE;
}

INT	Set_OwnIPAddr_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	uint32_t 	ip_addr;

	if (rtinet_aton(arg, &ip_addr))
 	{
        pAd->ApCfg.own_ip_addr = ip_addr;
		DBGPRINT(RT_DEBUG_TRACE, ("own_ip_addr=%s(%x)\n", arg, pAd->ApCfg.own_ip_addr));
	}
	return TRUE;
}

INT	Set_EAPIfName_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	INT			i;
	char *	macptr;

	for (i=0, macptr = rstrtok(arg,";"); (macptr && i < MAX_MBSSID_NUM(pAd)); macptr = rstrtok(NULL,";"), i++)
	{
		if (strlen(macptr) > 0)
		{
			pAd->ApCfg.EAPifname_len[i] = strlen(macptr);
			memmove(pAd->ApCfg.EAPifname[i], macptr, strlen(macptr));
			DBGPRINT(RT_DEBUG_TRACE, ("NO.%d EAPifname=%s, len=%d\n", i,
														pAd->ApCfg.EAPifname[i],
														pAd->ApCfg.EAPifname_len[i]));
		}
	}
	return TRUE;
}

INT	Set_PreAuthIfName_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	INT			i;
	char *	macptr;

	for (i=0, macptr = rstrtok(arg,";"); (macptr && i < MAX_MBSSID_NUM(pAd)); macptr = rstrtok(NULL,";"), i++)
	{
		if (strlen(macptr) > 0)
		{
			pAd->ApCfg.PreAuthifname_len[i] = strlen(macptr);
			memmove(pAd->ApCfg.PreAuthifname[i], macptr, strlen(macptr));
			DBGPRINT(RT_DEBUG_TRACE, ("NO.%d PreAuthifname=%s, len=%d\n", i,
														pAd->ApCfg.PreAuthifname[i],
														pAd->ApCfg.PreAuthifname_len[i]));
		}
	}
	return TRUE;

}

INT	Set_RADIUS_Server_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	struct os_cookie * pObj = pAd->OS_Cookie;
	UCHAR	    apidx = pObj->ioctl_if;
	char *	macptr;
	INT			count;
	uint32_t 	ip_addr;
	INT			srv_cnt = 0;

	for (count = 0, macptr = rstrtok(arg,";"); (macptr && count < MAX_RADIUS_SRV_NUM); macptr = rstrtok(NULL,";"), count++)
	{
		if (rtinet_aton(macptr, &ip_addr))
		{
			PRADIUS_SRV_INFO pSrvInfo = &pAd->ApCfg.MBSSID[apidx].radius_srv_info[srv_cnt];

			pSrvInfo->radius_ip = ip_addr;
			srv_cnt++;
			DBGPRINT(RT_DEBUG_TRACE, ("IF(ra%d), radius_ip(seq-%d)=%s(%x)\n",
										apidx, srv_cnt, macptr,
										pSrvInfo->radius_ip));
		}
	}

	if (srv_cnt > 0)
		pAd->ApCfg.MBSSID[apidx].radius_srv_num = srv_cnt;

	return TRUE;
}

INT	Set_RADIUS_Port_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	struct os_cookie * pObj = pAd->OS_Cookie;
	UCHAR	    apidx = pObj->ioctl_if;
	char *	macptr;
	INT			count;
	INT			srv_cnt = 0;

	for (count = 0, macptr = rstrtok(arg,";"); (macptr && count < MAX_RADIUS_SRV_NUM); macptr = rstrtok(NULL,";"), count++)
	{
		if (srv_cnt < pAd->ApCfg.MBSSID[apidx].radius_srv_num)
		{
			PRADIUS_SRV_INFO pSrvInfo = &pAd->ApCfg.MBSSID[apidx].radius_srv_info[srv_cnt];

        	pSrvInfo->radius_port = (uint32_t) simple_strtol(macptr, 0, 10);
			srv_cnt ++;
			DBGPRINT(RT_DEBUG_TRACE, ("IF(ra%d), radius_port(seq-%d)=%d\n",
									  apidx, srv_cnt, pSrvInfo->radius_port));
		}
	}

	return TRUE;
}

INT	Set_RADIUS_Key_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	struct os_cookie * pObj = pAd->OS_Cookie;
	UCHAR	    apidx = pObj->ioctl_if;
	char *	macptr;
	INT			count;
	INT			srv_cnt = 0;

	for (count = 0, macptr = rstrtok(arg,";"); (macptr && count < MAX_RADIUS_SRV_NUM); macptr = rstrtok(NULL,";"), count++)
	{
		if (strlen(macptr) > 0 && srv_cnt < pAd->ApCfg.MBSSID[apidx].radius_srv_num)
		{
			PRADIUS_SRV_INFO pSrvInfo = &pAd->ApCfg.MBSSID[apidx].radius_srv_info[srv_cnt];

			pSrvInfo->radius_key_len = strlen(macptr);
			memmove(pSrvInfo->radius_key, macptr, pSrvInfo->radius_key_len);
			srv_cnt ++;
			DBGPRINT(RT_DEBUG_TRACE, ("IF(ra%d), radius_key(seq-%d)=%s, len=%d\n",
										apidx, srv_cnt,
										pSrvInfo->radius_key,
										pSrvInfo->radius_key_len));
		}
	}
	return TRUE;
}
#endif /* DOT1X_SUPPORT */

#ifdef UAPSD_SUPPORT
INT Set_UAPSD_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	struct os_cookie *pObj = pAd->OS_Cookie;
	UCHAR IdMbss = pObj->ioctl_if;

	if (simple_strtol(arg, 0, 10) != 0)
		pAd->ApCfg.MBSSID[IdMbss].UapsdInfo.bAPSDCapable = TRUE;
	else
		pAd->ApCfg.MBSSID[IdMbss].UapsdInfo.bAPSDCapable = FALSE;

	return TRUE;
} /* End of Set_UAPSD_Proc */
#endif /* UAPSD_SUPPORT */

INT Set_OBSSScanParam_Proc(
	IN struct rtmp_adapter *	pAd,
	IN char *		arg)
{
	INT ObssScanValue;
	UINT Idx;
	char *thisChar;

	Idx = 0;
	while ((thisChar = strsep((char **)&arg, "-")) != NULL)
	{
		ObssScanValue = (INT) simple_strtol(thisChar, 0, 10);
		switch (Idx)
		{
			case 0:
				if (ObssScanValue < 5 || ObssScanValue > 1000)
				{
					DBGPRINT(RT_DEBUG_ERROR, ("Invalid OBSSScanParam for Dot11OBssScanPassiveDwell(%d), should in range 5~1000\n", ObssScanValue));
				}
				else
				{
					pAd->CommonCfg.Dot11OBssScanPassiveDwell = ObssScanValue;	/* Unit : TU. 5~1000 */
					DBGPRINT(RT_DEBUG_TRACE, ("OBSSScanParam for Dot11OBssScanPassiveDwell=%d\n", ObssScanValue));
				}
				break;
			case 1:
				if (ObssScanValue < 10 || ObssScanValue > 1000)
				{
					DBGPRINT(RT_DEBUG_ERROR, ("Invalid OBSSScanParam for Dot11OBssScanActiveDwell(%d), should in range 10~1000\n", ObssScanValue));
				}
				else
				{
					pAd->CommonCfg.Dot11OBssScanActiveDwell = ObssScanValue;	/* Unit : TU. 10~1000 */
					DBGPRINT(RT_DEBUG_TRACE, ("OBSSScanParam for Dot11OBssScanActiveDwell=%d\n", ObssScanValue));
				}
				break;
			case 2:
				pAd->CommonCfg.Dot11BssWidthTriggerScanInt = ObssScanValue;	/* Unit : Second */
				DBGPRINT(RT_DEBUG_TRACE, ("OBSSScanParam for Dot11BssWidthTriggerScanInt=%d\n", ObssScanValue));
				break;
			case 3:
				if (ObssScanValue < 200 || ObssScanValue > 10000)
				{
					DBGPRINT(RT_DEBUG_ERROR, ("Invalid OBSSScanParam for Dot11OBssScanPassiveTotalPerChannel(%d), should in range 200~10000\n", ObssScanValue));
				}
				else
				{
					pAd->CommonCfg.Dot11OBssScanPassiveTotalPerChannel = ObssScanValue;	/* Unit : TU. 200~10000 */
					DBGPRINT(RT_DEBUG_TRACE, ("OBSSScanParam for Dot11OBssScanPassiveTotalPerChannel=%d\n", ObssScanValue));
				}
				break;
			case 4:
				if (ObssScanValue < 20 || ObssScanValue > 10000)
				{
					DBGPRINT(RT_DEBUG_ERROR, ("Invalid OBSSScanParam for Dot11OBssScanActiveTotalPerChannel(%d), should in range 20~10000\n", ObssScanValue));
				}
				else
				{
					pAd->CommonCfg.Dot11OBssScanActiveTotalPerChannel = ObssScanValue;	/* Unit : TU. 20~10000 */
					DBGPRINT(RT_DEBUG_TRACE, ("OBSSScanParam for Dot11OBssScanActiveTotalPerChannel=%d\n", ObssScanValue));
				}
				break;
			case 5:
				pAd->CommonCfg.Dot11BssWidthChanTranDelayFactor = ObssScanValue;
				DBGPRINT(RT_DEBUG_TRACE, ("OBSSScanParam for Dot11BssWidthChanTranDelayFactor=%d\n", ObssScanValue));
				break;
			case 6:
				pAd->CommonCfg.Dot11OBssScanActivityThre = ObssScanValue;	/* Unit : percentage */
				DBGPRINT(RT_DEBUG_TRACE, ("OBSSScanParam for Dot11BssWidthChanTranDelayFactor=%d\n", ObssScanValue));
				break;
		}
		Idx++;
	}

	if (Idx != 7)
	{
		DBGPRINT(RT_DEBUG_ERROR, ("Wrong OBSSScanParamtetrs format in ioctl cmd!!!!! Use default value\n"));

		pAd->CommonCfg.Dot11OBssScanPassiveDwell = dot11OBSSScanPassiveDwell;	/* Unit : TU. 5~1000 */
		pAd->CommonCfg.Dot11OBssScanActiveDwell = dot11OBSSScanActiveDwell;	/* Unit : TU. 10~1000 */
		pAd->CommonCfg.Dot11BssWidthTriggerScanInt = dot11BSSWidthTriggerScanInterval;	/* Unit : Second */
		pAd->CommonCfg.Dot11OBssScanPassiveTotalPerChannel = dot11OBSSScanPassiveTotalPerChannel;	/* Unit : TU. 200~10000 */
		pAd->CommonCfg.Dot11OBssScanActiveTotalPerChannel = dot11OBSSScanActiveTotalPerChannel;	/* Unit : TU. 20~10000 */
		pAd->CommonCfg.Dot11BssWidthChanTranDelayFactor = dot11BSSWidthChannelTransactionDelayFactor;
		pAd->CommonCfg.Dot11OBssScanActivityThre = dot11BSSScanActivityThreshold;	/* Unit : percentage */
	}
	pAd->CommonCfg.Dot11BssWidthChanTranDelay = (pAd->CommonCfg.Dot11BssWidthTriggerScanInt * pAd->CommonCfg.Dot11BssWidthChanTranDelayFactor);
	DBGPRINT(RT_DEBUG_TRACE, ("OBSSScanParam for Dot11BssWidthChanTranDelay=%ld\n", pAd->CommonCfg.Dot11BssWidthChanTranDelay));

	return TRUE;
}


INT	Set_AP2040ReScan_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *arg)
{
	APOverlappingBSSScan(pAd);

	/* apply setting */
	SetCommonHT(pAd);
	AsicBBPAdjust(pAd);
	AsicSwitchChannel(pAd, pAd->CommonCfg.CentralChannel, FALSE);
	AsicLockChannel(pAd, pAd->CommonCfg.CentralChannel);

	DBGPRINT(RT_DEBUG_TRACE, ("Set_AP2040ReScan_Proc() Trigger AP ReScan !!!\n"));

	return TRUE;
}

INT Set_EntryLifeCheck_Proc(
	IN struct rtmp_adapter *	pAd,
	IN char *		arg)
{
	ULONG LifeCheckCnt = (ULONG) simple_strtol(arg, 0, 10);

	if (LifeCheckCnt <= 65535)
		pAd->ApCfg.EntryLifeCheck = LifeCheckCnt;
	else
		printk("LifeCheckCnt must in range of 0 to 65535\n");

	printk("EntryLifeCheck Cnt = %ld.\n", pAd->ApCfg.EntryLifeCheck);
	return TRUE;
}

/*
    ==========================================================================
    Description:
        Set Authentication mode
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
INT	ApCfg_Set_AuthMode_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	INT				apidx,
	IN	char *		arg)
{
	struct rtmp_wifi_dev *wdev = &pAd->ApCfg.MBSSID[apidx].wdev;

	if ((strcmp(arg, "WEPAUTO") == 0) || (strcmp(arg, "wepauto") == 0))
		wdev->AuthMode = Ndis802_11AuthModeAutoSwitch;
	else if ((strcmp(arg, "OPEN") == 0) || (strcmp(arg, "open") == 0))
		wdev->AuthMode = Ndis802_11AuthModeOpen;
	else if ((strcmp(arg, "SHARED") == 0) || (strcmp(arg, "shared") == 0))
		wdev->AuthMode = Ndis802_11AuthModeShared;
	else if ((strcmp(arg, "WPAPSK") == 0) || (strcmp(arg, "wpapsk") == 0))
		wdev->AuthMode = Ndis802_11AuthModeWPAPSK;
	else if ((strcmp(arg, "WPA2PSK") == 0) || (strcmp(arg, "wpa2psk") == 0))
		wdev->AuthMode = Ndis802_11AuthModeWPA2PSK;
	else if ((strcmp(arg, "WPAPSKWPA2PSK") == 0) || (strcmp(arg, "wpapskwpa2psk") == 0))
		wdev->AuthMode = Ndis802_11AuthModeWPA1PSKWPA2PSK;
#ifdef DOT1X_SUPPORT
	else if ((strcmp(arg, "WPA") == 0) || (strcmp(arg, "wpa") == 0))
		wdev->AuthMode = Ndis802_11AuthModeWPA;
	else if ((strcmp(arg, "WPA2") == 0) || (strcmp(arg, "wpa2") == 0))
		wdev->AuthMode = Ndis802_11AuthModeWPA2;
	else if ((strcmp(arg, "WPA1WPA2") == 0) || (strcmp(arg, "wpa1wpa2") == 0))
		wdev->AuthMode = Ndis802_11AuthModeWPA1WPA2;
#endif /* DOT1X_SUPPORT */
	else
		wdev->AuthMode = Ndis802_11AuthModeOpen;

	DBGPRINT(RT_DEBUG_TRACE, ("IF(ra%d)::AuthMode=%d\n", apidx, wdev->AuthMode));

	return TRUE;
}

INT	ApCfg_Set_MaxStaNum_Proc(
	IN struct rtmp_adapter *	pAd,
	IN INT				apidx,
	IN char *			arg)
{
	pAd->ApCfg.MBSSID[apidx].MaxStaNum = (UCHAR)simple_strtol(arg, 0, 10);

	DBGPRINT(RT_DEBUG_TRACE, ("IF(ra%d) %s::(MaxStaNum=%d)\n",
					apidx, __FUNCTION__, pAd->ApCfg.MBSSID[apidx].MaxStaNum));
	return TRUE;
}

INT	ApCfg_Set_IdleTimeout_Proc(
	IN struct rtmp_adapter *	pAd,
	IN char *			arg)
{
	LONG idle_time;

	idle_time = simple_strtol(arg, 0, 10);

	if (idle_time < MAC_TABLE_MIN_AGEOUT_TIME)
		pAd->ApCfg.StaIdleTimeout = MAC_TABLE_MIN_AGEOUT_TIME;
	else
		pAd->ApCfg.StaIdleTimeout = idle_time;

	DBGPRINT(RT_DEBUG_TRACE, ("%s : IdleTimeout=%d\n", __FUNCTION__, pAd->ApCfg.StaIdleTimeout));

	return TRUE;
}






INT	Set_MemDebug_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
#ifdef VENDOR_FEATURE2_SUPPORT
	printk("Number of Packet Allocated = %lu\n", OS_NumOfPktAlloc);
	printk("Number of Packet Freed = %lu\n", OS_NumOfPktFree);
	printk("Offset of Packet Allocated/Freed = %lu\n", OS_NumOfPktAlloc - OS_NumOfPktFree);
#endif /* VENDOR_FEATURE2_SUPPORT */
	return TRUE;
}


#ifdef APCLI_SUPPORT
#ifdef APCLI_WPA_SUPPLICANT_SUPPORT
VOID RTMPApCliAddKey(
	IN	struct rtmp_adapter *    pAd,
	IN 	INT				apidx,
	IN	PNDIS_APCLI_802_11_KEY    pKey)
{
	ULONG				KeyIdx;
	MAC_TABLE_ENTRY  	*pEntry;
	INT 	ifIndex,BssIdx;
	PAPCLI_STRUCT pApCliEntry;
	MAC_TABLE_ENTRY				*pMacEntry=(MAC_TABLE_ENTRY *)NULL;

    DBGPRINT(RT_DEBUG_TRACE, ("RTMPApCliAddKey ------>\n"));

	ifIndex=apidx;
	pApCliEntry = &pAd->ApCfg.ApCliTab[ifIndex];
	pMacEntry = &pAd->MacTab.Content[pApCliEntry->MacTabWCID];
	BssIdx = pAd->ApCfg.BssidNum + MAX_MESH_NUM + ifIndex;

	if (pApCliEntry->AuthMode >= Ndis802_11AuthModeWPA)
	{
		if (pKey->KeyIndex & 0x80000000)
		{
			    if (pApCliEntry->AuthMode == Ndis802_11AuthModeWPANone)
	            		{
		                memset(pApCliEntry->PMK, 32);
		                memmove(pApCliEntry->PMK, pKey->KeyMaterial, pKey->KeyLength);
	                		goto end;
	            		}
			    /* Update PTK */
			    memset(&pMacEntry->PairwiseKey, sizeof(CIPHER_KEY));
	            		pMacEntry->PairwiseKey.KeyLen = LEN_TK;
	            		memmove(pMacEntry->PairwiseKey.Key, pKey->KeyMaterial, LEN_TK);

		            if (pApCliEntry->PairCipher == Ndis802_11Encryption2Enabled)
		            {
		                memmove(pMacEntry->PairwiseKey.RxMic, pKey->KeyMaterial + LEN_TK, LEN_TKIP_MIC);
		                memmove(pMacEntry->PairwiseKey.TxMic, pKey->KeyMaterial + LEN_TK + LEN_TKIP_MIC, LEN_TKIP_MIC);
		            }
		            else

		            {
		            	memmove(pMacEntry->PairwiseKey.TxMic, pKey->KeyMaterial + LEN_TK, LEN_TKIP_MIC);
		                memmove(pMacEntry->PairwiseKey.RxMic, pKey->KeyMaterial + LEN_TK + LEN_TKIP_MIC, LEN_TKIP_MIC);
		            }

            /* Decide its ChiperAlg */
		        	if (pApCliEntry->PairCipher == Ndis802_11Encryption2Enabled)
		        		pMacEntry->PairwiseKey.CipherAlg = CIPHER_TKIP;
		        	else if (pApCliEntry->PairCipher == Ndis802_11Encryption3Enabled)
		        		pMacEntry->PairwiseKey.CipherAlg = CIPHER_AES;
		        	else
		        		pMacEntry->PairwiseKey.CipherAlg = CIPHER_NONE;

		    AsicAddPairwiseKeyEntry(
		        pAd,
		        (UCHAR)pMacEntry->Aid,
		        &pMacEntry->PairwiseKey);

			RTMPSetWcidSecurityInfo(pAd,
									BssIdx,
									0,
									pMacEntry->PairwiseKey.CipherAlg,
									(UCHAR)pMacEntry->Aid,
									PAIRWISEKEYTABLE);

	            if (pMacEntry->AuthMode >= Ndis802_11AuthModeWPA)
	            {
	                /* set 802.1x port control */
	                pMacEntry->PortSecured = WPA_802_1X_PORT_SECURED;
			  pMacEntry->PrivacyFilter = Ndis802_11PrivFilterAcceptAll;
	            }
		}
        else
        {
            /* Update GTK  */
            pApCliEntry->DefaultKeyId = (pKey->KeyIndex & 0xFF);
            memset(&pApCliEntry->SharedKey[pApCliEntry->DefaultKeyId], sizeof(CIPHER_KEY));
            pApCliEntry->SharedKey[pApCliEntry->DefaultKeyId].KeyLen = LEN_TK;
            memmove(pApCliEntry->SharedKey[pApCliEntry->DefaultKeyId].Key, pKey->KeyMaterial, LEN_TK);

            if (pApCliEntry->GroupCipher == Ndis802_11Encryption2Enabled)
            {
                memmove(pApCliEntry->SharedKey[pApCliEntry->DefaultKeyId].RxMic, pKey->KeyMaterial + LEN_TK, LEN_TKIP_MIC);
                memmove(pApCliEntry->SharedKey[pApCliEntry->DefaultKeyId].TxMic, pKey->KeyMaterial + LEN_TK + LEN_TKIP_MIC, LEN_TKIP_MIC);
            }
            else

            {
            	memmove(pApCliEntry->SharedKey[pApCliEntry->DefaultKeyId].TxMic, pKey->KeyMaterial + LEN_TK, LEN_TKIP_MIC);
                memmove(pApCliEntry->SharedKey[pApCliEntry->DefaultKeyId].RxMic, pKey->KeyMaterial + LEN_TK + LEN_TKIP_MIC, LEN_TKIP_MIC);
            }

            /* Update Shared Key CipherAlg */
    		pApCliEntry->SharedKey[pApCliEntry->DefaultKeyId].CipherAlg = CIPHER_NONE;
    		if (pApCliEntry->GroupCipher == Ndis802_11Encryption2Enabled)
    			pApCliEntry->SharedKey[pApCliEntry->DefaultKeyId].CipherAlg = CIPHER_TKIP;
    		else if (pApCliEntry->GroupCipher == Ndis802_11Encryption3Enabled)
    			pApCliEntry->SharedKey[pApCliEntry->DefaultKeyId].CipherAlg = CIPHER_AES;

            /* Update group key information to ASIC Shared Key Table */
        	AsicAddSharedKeyEntry(pAd,
        						  BssIdx,
        						  pApCliEntry->DefaultKeyId,
        						  &pApCliEntry->SharedKey[pApCliEntry->DefaultKeyId]);



        	/* Update ASIC WCID attribute table and IVEIV table */
        	RTMPAddWcidAttributeEntry(pAd,
        							  BssIdx,
        							  pApCliEntry->DefaultKeyId,
        							  pApCliEntry->SharedKey[pApCliEntry->DefaultKeyId].CipherAlg,
        							  NULL);


            /* set 802.1x port control */
             if (pMacEntry->AuthMode >= Ndis802_11AuthModeWPA)
            {
                /* set 802.1x port control */
                pMacEntry->PortSecured = WPA_802_1X_PORT_SECURED;
		  pMacEntry->PrivacyFilter = Ndis802_11PrivFilterAcceptAll;
            }
        }
	}
	else	/* dynamic WEP from wpa_supplicant */
	{
		UCHAR	CipherAlg;
    	u8 *Key;

		if(pKey->KeyLength == 32)
			goto end;

		KeyIdx = pKey->KeyIndex & 0x0fffffff;

		if (KeyIdx < 4)
		{
			/* it is a default shared key, for Pairwise key setting */
			if (pKey->KeyIndex & 0x80000000)
			{
				pEntry = MacTableLookup(pAd, pKey->BSSID);

				if (pEntry && IS_ENTRY_APCLI(pEntry))
				{
					DBGPRINT(RT_DEBUG_TRACE, ("RTMPAddKey: Set Pair-wise Key\n"));

					/* set key material and key length */
 					pEntry->PairwiseKey.KeyLen = (UCHAR )pKey->KeyLength;
					memmove(pEntry->PairwiseKey.Key, &pKey->KeyMaterial, pKey->KeyLength);

					/* set Cipher type */
					if (pKey->KeyLength == 5)
						pEntry->PairwiseKey.CipherAlg = CIPHER_WEP64;
					else
						pEntry->PairwiseKey.CipherAlg = CIPHER_WEP128;

					/* Add Pair-wise key to Asic */
					AsicAddPairwiseKeyEntry(
						pAd,
						(UCHAR)pEntry->wcid,
                				&pEntry->PairwiseKey);

					/* update WCID attribute table and IVEIV table for this entry */
					RTMPSetWcidSecurityInfo(pAd,
											BssIdx,
											KeyIdx,
											pEntry->PairwiseKey.CipherAlg,
											pEntry->wcid,
											PAIRWISEKEYTABLE);
				}
			}
			else
            		{
				/* Default key for tx (shared key) */
				pApCliEntry->DefaultKeyId = (UCHAR) KeyIdx;

				/*/ set key material and key length */
				pApCliEntry->SharedKey[KeyIdx].KeyLen = (UCHAR) pKey->KeyLength;
				memmove(pApCliEntry->SharedKey[KeyIdx].Key, &pKey->KeyMaterial, pKey->KeyLength);

				/* Set Ciper type */
				if (pKey->KeyLength == 5)
					pApCliEntry->SharedKey[KeyIdx].CipherAlg = CIPHER_WEP64;
				else
					pApCliEntry->SharedKey[KeyIdx].CipherAlg = CIPHER_WEP128;

	    			CipherAlg = pApCliEntry->SharedKey[KeyIdx].CipherAlg;
	    			Key = pApCliEntry->SharedKey[KeyIdx].Key;

					/* Set Group key material to Asic */
	    			AsicAddSharedKeyEntry(pAd, BssIdx, KeyIdx, &pApCliEntry->SharedKey[KeyIdx]);

				/* STA doesn't need to set WCID attribute for group key */

				/* Update WCID attribute table and IVEIV table for this group key table */
				RTMPAddWcidAttributeEntry(pAd, BssIdx, KeyIdx, CipherAlg, NULL);

			}
		}
	}
end:

    DBGPRINT(RT_DEBUG_INFO, ("<------ RTMPApCliAddKey\n"));

	return;
}
#endif/*APCLI_WPA_SUPPLICANT_SUPPORT*/
#endif/*APCLI_SUPPORT*/

#ifdef CONFIG_AP_SUPPORT
/*
========================================================================
Routine Description:
	Set power save life time.

Arguments:
	pAd					- WLAN control block pointer
	Arg					- Input arguments

Return Value:
	None

Note:
========================================================================
*/
INT	Set_PowerSaveLifeTime_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	pAd->MacTab.MsduLifeTime = simple_strtol(arg, 0, 10);
	DBGPRINT(RT_DEBUG_TRACE, ("Set new life time = %d\n", pAd->MacTab.MsduLifeTime));
	return TRUE;
}
#endif /* CONFIG_AP_SUPPORT */


#ifdef MBSS_SUPPORT
/*
========================================================================
Routine Description:
	Show MBSS information.

Arguments:
	pAd					- WLAN control block pointer
	Arg					- Input arguments

Return Value:
	None

Note:
========================================================================
*/
INT	Show_MbssInfo_Display_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *		arg)
{
	uint32_t IdBss;
	UCHAR PhyMode;
	CHAR *mod_str = NULL;

	DBGPRINT(RT_DEBUG_ERROR, ("\n\tBSS Idx\t\tPhy Mode\n"));

	for(IdBss=0; IdBss<=pAd->ApCfg.BssidNum; IdBss++)
	{
		if (IdBss == 0)
		{
			PhyMode = pAd->CommonCfg.PhyMode;
			DBGPRINT(RT_DEBUG_ERROR, ("\tMAX\t\t"));
		}
		else
		{
			PhyMode = pAd->ApCfg.MBSSID[IdBss-1].wdev.PhyMode;
			DBGPRINT(RT_DEBUG_ERROR, ("\t%d\t\t", IdBss-1));
		} /* End of if */

		switch(PhyMode)
		{
			case (WMODE_B | WMODE_G):
				mod_str = "BG Mixed";
				break;

			case (WMODE_B):
				mod_str = "B Only";
				break;

			case (WMODE_A):
				mod_str = "A Only";
				break;

			case (WMODE_A | WMODE_B | WMODE_G):
				mod_str = "ABG Mixed ==> BG Mixed";
				break;

			case (WMODE_G):
				mod_str = "G Only";
				break;

			case (WMODE_A | WMODE_B | WMODE_G | WMODE_AN | WMODE_GN):
				mod_str = "ABGN Mixed ==> BGN Mixed";
				break;

			case (WMODE_GN):
				mod_str = "2.4G N Only";
				break;

			case (WMODE_G | WMODE_GN):
				mod_str = "GN Mixed";
				break;

			case (WMODE_A | WMODE_AN):
				mod_str = "AN Mixed";
				break;

			case (WMODE_B | WMODE_G | WMODE_GN):
				mod_str = "BGN Mixed";
				break;

			case (WMODE_A | WMODE_G | WMODE_GN | WMODE_AN):
				mod_str = "AGN Mixed";
				break;

			case (WMODE_AN):
				mod_str = "5G N Only";
				break;
		}
	}

	if (mod_str)
		DBGPRINT(RT_DEBUG_ERROR, ("%s\n", mod_str));
	DBGPRINT(RT_DEBUG_ERROR, ("\n"));

	return TRUE;
} /* End of Show_MbssInfo_Display_Proc */
#endif /* MBSS_SUPPORT */


#ifdef HOSTAPD_SUPPORT
VOID RtmpHostapdSecuritySet(
	IN	struct rtmp_adapter 		*pAd,
	IN	RTMP_IOCTL_INPUT_STRUCT	*wrqin)
{
	if(wrqin->u.data.length > 20 && MAX_LEN_OF_RSNIE > wrqin->u.data.length && wrqin->u.data.pointer)
	{
		UCHAR RSNIE_Len[2];
		UCHAR RSNIe[2];
		int offset_next_ie=0;

		DBGPRINT(RT_DEBUG_TRACE,("ioctl SIOCSIWGENIE pAd->IoctlIF=%d\n",apidx));

		RSNIe[0]=*(UINT8 *)wrqin->u.data.pointer;
		if(IE_WPA != RSNIe[0] && IE_RSN != RSNIe[0] )
		{
			DBGPRINT(RT_DEBUG_TRACE,("IE %02x != 0x30/0xdd\n",RSNIe[0]));
			Status = -EINVAL;
			break;
		}
		RSNIE_Len[0]=*((UINT8 *)wrqin->u.data.pointer + 1);
		if(wrqin->u.data.length != RSNIE_Len[0]+2)
		{
			DBGPRINT(RT_DEBUG_TRACE,("IE use WPA1 WPA2\n"));
			memset(pAd->ApCfg.MBSSID[apidx].RSN_IE[1], MAX_LEN_OF_RSNIE);
			RSNIe[1]=*(UINT8 *)wrqin->u.data.pointer;
			RSNIE_Len[1]=*((UINT8 *)wrqin->u.data.pointer + 1);
			DBGPRINT(RT_DEBUG_TRACE,( "IE1 %02x %02x\n",RSNIe[1],RSNIE_Len[1]));
			pAd->ApCfg.MBSSID[apidx].RSNIE_Len[1] = RSNIE_Len[1];
			memmove(pAd->ApCfg.MBSSID[apidx].RSN_IE[1], (UCHAR *)(wrqin->u.data.pointer)+2, RSNIE_Len[1]);
			offset_next_ie=RSNIE_Len[1]+2;
		}
		else
			DBGPRINT(RT_DEBUG_TRACE,("IE use only %02x\n",RSNIe[0]));

		memset(pAd->ApCfg.MBSSID[apidx].RSN_IE[0], MAX_LEN_OF_RSNIE);
		RSNIe[0]=*(((UINT8 *)wrqin->u.data.pointer)+offset_next_ie);
		RSNIE_Len[0]=*(((UINT8 *)wrqin->u.data.pointer) + offset_next_ie + 1);
		if(IE_WPA != RSNIe[0] && IE_RSN != RSNIe[0] )
		{
			Status = -EINVAL;
			break;
		}
		pAd->ApCfg.MBSSID[apidx].RSNIE_Len[0] = RSNIE_Len[0];
		memmove(pAd->ApCfg.MBSSID[apidx].RSN_IE[0], ((UCHAR *)(wrqin->u.data.pointer))+2+offset_next_ie, RSNIE_Len[0]);
		APMakeAllBssBeacon(pAd);
		APUpdateAllBeaconFrame(pAd);
	}
}
#endif /* HOSTAPD_SUPPORT */


/*
========================================================================
Routine Description:
	Driver Ioctl for AP.

Arguments:
	pAdSrc			- WLAN control block pointer
	wrq				- the IOCTL parameters
	cmd				- the command ID
	subcmd			- the sub-command ID
	pData			- the IOCTL private data pointer
	Data			- the IOCTL private data

Return Value:
	NDIS_STATUS_SUCCESS	- IOCTL OK
	Otherwise			- IOCTL fail

Note:
========================================================================
*/
INT RTMP_AP_IoctlHandle(
	IN	struct rtmp_adapter				*pAd,
	IN	RTMP_IOCTL_INPUT_STRUCT	*wrq,
	IN	INT						cmd,
	IN	USHORT					subcmd,
	IN	VOID					*pData,
	IN	ULONG					Data)
{
	struct os_cookie *pObj = pAd->OS_Cookie;
	INT Status = NDIS_STATUS_SUCCESS;


	switch(cmd)
	{
		case CMD_RTPRIV_IOCTL_GET_MAC_TABLE:
			RTMPIoctlGetMacTable(pAd,wrq);
		    break;

#if defined (AP_SCAN_SUPPORT) || defined (CONFIG_STA_SUPPORT)
		case CMD_RTPRIV_IOCTL_GSITESURVEY:
			RTMPIoctlGetSiteSurvey(pAd,wrq);
			break;
#endif /* AP_SCAN_SUPPORT */

		case CMD_RTPRIV_IOCTL_STATISTICS:
			RTMPIoctlStatistics(pAd, wrq);
			break;

		case CMD_RTPRIV_IOCTL_QUERY_BATABLE:
		    RTMPIoctlQueryBaTable(pAd, wrq);
		    break;

#ifdef DBG
#ifdef RTMP_RF_RW_SUPPORT
		case CMD_RTPRIV_IOCTL_RF:
			RTMPAPIoctlRF(pAd, wrq);
			break;
#endif /* RTMP_RF_RW_SUPPORT */
#endif /* defined(DBG) || defined(BB_SOC) */

		case CMD_RTPRIV_IOCTL_GET_MAC_TABLE_STRUCT:
			RTMPIoctlGetMacTableStaInfo(pAd, wrq);
			break;

		case CMD_RTPRIV_IOCTL_AP_SIOCGIFHWADDR:
			if (pObj->ioctl_if < MAX_MBSSID_NUM(pAd))
				memcpy((char *) wrq->u.name, (char *) pAd->ApCfg.MBSSID[pObj->ioctl_if].wdev.bssid, 6);
			break;

		case CMD_RTPRIV_IOCTL_AP_SIOCGIWESSID:
		{
			RT_CMD_AP_IOCTL_SSID *pSSID = (RT_CMD_AP_IOCTL_SSID *)pData;

#ifdef APCLI_SUPPORT
			if (pSSID->priv_flags == INT_APCLI)
			{
				if (pAd->ApCfg.ApCliTab[pObj->ioctl_if].Valid == TRUE)
				{
					pSSID->length = pAd->ApCfg.ApCliTab[pObj->ioctl_if].SsidLen;
					pSSID->pSsidStr = (char *)&pAd->ApCfg.ApCliTab[pObj->ioctl_if].Ssid;
				}
				else {
					pSSID->length = 0;
					pSSID->pSsidStr = NULL;
				}
			}
			else
#endif /* APCLI_SUPPORT */
			{
				pSSID->length = pAd->ApCfg.MBSSID[pSSID->apidx].SsidLen;
				pSSID->pSsidStr = (char *)pAd->ApCfg.MBSSID[pSSID->apidx].Ssid;
			}
		}
			break;

#ifdef MBSS_SUPPORT
		case CMD_RTPRIV_IOCTL_MBSS_BEACON_UPDATE:
			APMakeAllBssBeacon(pAd);
			APUpdateAllBeaconFrame(pAd);
			break;

		case CMD_RTPRIV_IOCTL_MBSS_OPEN:
			if (MBSS_Open(pData) != 0)
				return NDIS_STATUS_FAILURE;
			break;

		case CMD_RTPRIV_IOCTL_MBSS_CLOSE:
			MBSS_Close(pData);
			break;

		case CMD_RTPRIV_IOCTL_MBSS_INIT:
			MBSS_Init(pAd, pData);
			break;

		case CMD_RTPRIV_IOCTL_MBSS_REMOVE:
			MBSS_Remove(pAd);
			break;
#endif /* MBSS_SUPPORT */

		case CMD_RTPRIV_IOCTL_WSC_INIT:
		{
#ifdef APCLI_SUPPORT
#endif /* APCLI_SUPPORT */
		}
			break;

#ifdef APCLI_SUPPORT
		case CMD_RTPRIV_IOCTL_APC_UP:
			ApCliIfUp(pAd);
			break;

		case CMD_RTPRIV_IOCTL_APC_DISCONNECT:
			MlmeEnqueue(pAd, APCLI_CTRL_STATE_MACHINE, APCLI_CTRL_DISCONNECT_REQ, 0, NULL, Data);
			RTMP_MLME_HANDLER(pAd);
			break;

		case CMD_RTPRIV_IOCTL_APC_INIT:
			APCli_Init(pAd, pData);
			break;

		case CMD_RTPRIV_IOCTL_APC_OPEN:
			if (ApCli_Open(pAd, pData) != TRUE)
				return NDIS_STATUS_FAILURE;
			break;

		case CMD_RTPRIV_IOCTL_APC_CLOSE:
			if (ApCli_Close(pAd, pData) != TRUE)
				return NDIS_STATUS_FAILURE;
			break;

		case CMD_RTPRIV_IOCTL_APC_REMOVE:
			ApCli_Remove(pAd);
			break;
#endif /* APCLI_SUPPORT */

		case CMD_RTPRIV_IOCTL_MAIN_OPEN:
			pAd->ApCfg.MBSSID[MAIN_MBSSID].bBcnSntReq = TRUE;
			break;

		case CMD_RTPRIV_IOCTL_PREPARE:
		{
			RT_CMD_AP_IOCTL_CONFIG *pConfig = (RT_CMD_AP_IOCTL_CONFIG *)pData;
			pConfig->Status = RTMP_AP_IoctlPrepare(pAd, pData);
			if (pConfig->Status != 0)
				return NDIS_STATUS_FAILURE;
		}
			break;

		case CMD_RTPRIV_IOCTL_AP_SIOCGIWAP:
		{
			UCHAR *pBssidDest = (UCHAR *)pData;
			PCHAR pBssidStr;

#ifdef APCLI_SUPPORT
			if (Data == INT_APCLI)
			{
				if (pAd->ApCfg.ApCliTab[pObj->ioctl_if].Valid == TRUE)
					pBssidStr = (PCHAR)&APCLI_ROOT_BSSID_GET(pAd, pAd->ApCfg.ApCliTab[pObj->ioctl_if].MacTabWCID);
				else
					pBssidStr = NULL;
			}
			else
#endif /* APCLI_SUPPORT */
			{
				pBssidStr = (PCHAR) &pAd->ApCfg.MBSSID[pObj->ioctl_if].wdev.bssid[0];
			}

			if (pBssidStr != NULL)
			{
				memcpy(pBssidDest, pBssidStr, ETH_ALEN);
				DBGPRINT(RT_DEBUG_TRACE, ("IOCTL::SIOCGIWAP(=%02x:%02x:%02x:%02x:%02x:%02x)\n",
						PRINT_MAC(pBssidStr)));
			}
			else
			{
				memset(pBssidDest, 0, ETH_ALEN);
			}
		}
			break;

		case CMD_RTPRIV_IOCTL_AP_SIOCGIWRATEQ:
		/* handle for SIOCGIWRATEQ */
		{
			RT_CMD_IOCTL_RATE *pRate = (RT_CMD_IOCTL_RATE *)pData;
			HTTRANSMIT_SETTING HtPhyMode;

#ifdef APCLI_SUPPORT
			if (pRate->priv_flags == INT_APCLI)
				HtPhyMode = pAd->ApCfg.ApCliTab[pObj->ioctl_if].wdev.HTPhyMode;
			else
#endif /* APCLI_SUPPORT */
			{
				HtPhyMode = pAd->ApCfg.MBSSID[pObj->ioctl_if].wdev.HTPhyMode;

#ifdef MBSS_SUPPORT
				/* reset phy mode for MBSS */
				MBSS_PHY_MODE_RESET(pObj->ioctl_if, HtPhyMode);
#endif /* MBSS_SUPPORT */
			}

			RtmpDrvRateGet(pAd, HtPhyMode.field.MODE, HtPhyMode.field.ShortGI,
							HtPhyMode.field.BW, HtPhyMode.field.MCS,
							pAd->Antenna.field.TxPath,
							(uint32_t *)&pRate->BitRate);
		}
			break;

#ifdef HOSTAPD_SUPPORT
		case CMD_RTPRIV_IOCTL_AP_SIOCGIWRATEQ:
			RtmpHostapdSecuritySet(pAd, wrq);
			break;
#endif /* HOSTAPD_SUPPORT */


		default:
			Status = RTMP_COM_IoctlHandle(pAd, wrq, cmd, subcmd, pData, Data);
			break;
	}

	return Status;
}



#ifdef DYNAMIC_VGA_SUPPORT
INT Set_AP_DyncVgaEnable_Proc(
	IN	struct rtmp_adapter *pAd,
	IN	char *	arg)
{
	UINT Enable;
	uint32_t bbp_val;

	Enable = simple_strtol(arg, 0, 10);

	pAd->CommonCfg.lna_vga_ctl.bDyncVgaEnable = (Enable > 0) ? TRUE : FALSE;

	if (pAd->CommonCfg.lna_vga_ctl.bDyncVgaEnable == FALSE)
	{
#ifdef MT76x2
		if (IS_MT76x2(pAd)) {
			RTMP_BBP_IO_READ32(pAd, AGC1_R8, &bbp_val);
			bbp_val = (bbp_val & 0xffff80ff) | (pAd->CommonCfg.lna_vga_ctl.agc_vga_init_0 << 8);
			RTMP_BBP_IO_WRITE32(pAd, AGC1_R8, bbp_val);

			if (pAd->CommonCfg.RxStream >= 2) {
				RTMP_BBP_IO_READ32(pAd, AGC1_R9, &bbp_val);
				bbp_val = (bbp_val & 0xffff80ff) | (pAd->CommonCfg.lna_vga_ctl.agc_vga_init_1 << 8);
				RTMP_BBP_IO_WRITE32(pAd, AGC1_R9, bbp_val);
			}
		}
#endif /* MT76x2 */

	}
	else {
	}

	DBGPRINT(RT_DEBUG_TRACE, ("Set_DyncVgaEnable_Proc::(enable = %d)\n", pAd->CommonCfg.lna_vga_ctl.bDyncVgaEnable));

	return TRUE;
}

INT set_dynamic_lna_trigger_timer_proc(
	IN struct rtmp_adapter *pAd,
	IN char *		arg)
{
	int32_t val = simple_strtol(arg, 0, 10);

	pAd->chipCap.dynamic_lna_trigger_timer = (val <= 0) ? 1 : val;

	DBGPRINT(RT_DEBUG_OFF, ("%s::(lna trigger timer = %d)\n",
		__FUNCTION__, pAd->chipCap.dynamic_lna_trigger_timer));

	return TRUE;
}

INT set_false_cca_hi_th(struct rtmp_adapter *pAd, char *arg)
{
	int32_t val = simple_strtol(arg, 0, 10);

	pAd->CommonCfg.lna_vga_ctl.nFalseCCATh = (val <= 0) ? 800 : val;


	DBGPRINT(RT_DEBUG_OFF, ("%s::(false cca high threshould = %d)\n",
		__FUNCTION__, pAd->CommonCfg.lna_vga_ctl.nFalseCCATh));

	return TRUE;
}

INT set_false_cca_low_th(struct rtmp_adapter *pAd, char *arg)
{
	int32_t val = simple_strtol(arg, 0, 10);

	pAd->CommonCfg.lna_vga_ctl.nLowFalseCCATh = (val <= 0) ? 10 : val;

	DBGPRINT(RT_DEBUG_OFF, ("%s::(false cca low threshould = %d)\n",
		__FUNCTION__, pAd->CommonCfg.lna_vga_ctl.nLowFalseCCATh));

	return TRUE;
}
#endif /* DYNAMIC_VGA_SUPPORT */

#ifdef THERMAL_PROTECT_SUPPORT
INT set_thermal_protection_criteria_proc(
	IN struct rtmp_adapter *pAd,
	IN char *arg)
{
	int32_t criteria = simple_strtol(arg, 0, 10);

	pAd->thermal_pro_criteria = (criteria <= 0) ? 80 : criteria;

	DBGPRINT(RT_DEBUG_ERROR, ("%s::criteria=%d\n", __FUNCTION__, pAd->thermal_pro_criteria));
	return TRUE;
}
#endif /* THERMAL_PROTECT_SUPPORT */

#ifdef ED_MONITOR
INT edcca_tx_stop_start(struct rtmp_adapter *pAd, BOOLEAN stop)
{
	uint32_t macCfg  = 0, macCfg_2 = 0, macStatus = 0;
	uint32_t MTxCycle = 0;
	ULONG stTime = 0, mt_time = 0, mr_time = 0;

	/* Disable MAC Tx and wait MAC Tx/Rx status in idle state or direcyl enable tx */
	NdisGetSystemUpTime(&stTime);
	RTMP_IO_READ32(pAd, MAC_SYS_CTRL, &macCfg);


	if (stop == TRUE) {
		macCfg &= (~0x04);
	} else {
		macCfg |= 0x04;
	}
	RTMP_IO_WRITE32(pAd, MAC_SYS_CTRL, macCfg);


	if (stop == TRUE) {
		for (MTxCycle = 0; MTxCycle < 10000; MTxCycle++)
		{
			RTMP_IO_READ32(pAd, MAC_STATUS_CFG, &macStatus);
			if (macStatus & 0x1)
				RtmpusecDelay(50);
			else
				break;
		}

		NdisGetSystemUpTime(&mt_time);
		mt_time -= stTime;

		if (MTxCycle == 10000)
			DBGPRINT(RT_DEBUG_OFF, ("%s(cnt=%d,time=0x%lx):stop MTx,macStatus=0x%x!\n",
				__FUNCTION__, MTxCycle, mt_time, macStatus));
	}

	DBGPRINT(RT_DEBUG_OFF, ("%s():%s tx\n",
		__FUNCTION__, ((stop == TRUE) ? "stop" : "start")));

	return TRUE;
}

INT ed_status_read(struct rtmp_adapter *pAd)
{
	uint32_t period_us = pAd->ed_chk_period * 1000;
	ULONG irqflag;
	BOOLEAN stop_edcca = FALSE;
	BOOLEAN stop_tx = FALSE;
	INT percent;
	RX_STA_CNT1_STRUC RxStaCnt1;
	uint32_t ch_idle_stat=0, ch_busy_stat=0, ed_2nd_stat=0, ed_stat=0;

	RTMP_IO_READ32(pAd, CH_IDLE_STA, &ch_idle_stat);
	RTMP_IO_READ32(pAd, 0x1140, &ed_stat);
	RTMP_IO_READ32(pAd, RX_STA_CNT1, &RxStaCnt1.word);

	RTMP_IRQ_LOCK(&pAd->irq_lock, irqflag);

	pAd->ch_idle_stat[pAd->ed_stat_lidx] = ch_idle_stat;
	pAd->ch_busy_stat[pAd->ed_stat_lidx] = ch_busy_stat;
	pAd->ed_2nd_stat[pAd->ed_stat_lidx] = ed_2nd_stat;
	pAd->ed_stat[pAd->ed_stat_lidx] = ed_stat;
	pAd->false_cca_stat[pAd->ed_stat_lidx] += RxStaCnt1.field.FalseCca;
	pAd->RalinkCounters.OneSecFalseCCACnt += RxStaCnt1.field.FalseCca;

	NdisGetSystemUpTime(&pAd->chk_time[pAd->ed_stat_lidx]);

	if ((pAd->ed_threshold > 0) && (period_us > 0) && (pAd->ed_block_tx_threshold > 0)) {
		percent = (pAd->ed_stat[pAd->ed_stat_lidx] * 100 ) / period_us;
		if (percent > 100)
			percent = 100;

		/* sync with Shiang's ppt's Algorithm. (20131217) */
		if (percent > pAd->ed_threshold) {
			pAd->ed_trigger_cnt++;
			pAd->ed_silent_cnt = 0;
		} else {
			pAd->ed_trigger_cnt = 0;
			pAd->ed_silent_cnt++;

			/* one point to disable edcca, we expect this is normal env not test env. */
			if (pAd->false_cca_stat[pAd->ed_stat_lidx] > pAd->false_cca_threshold) {
				pAd->ed_false_cca_cnt ++;

				if (pAd->ed_false_cca_cnt > pAd->ed_block_tx_threshold) {
					stop_edcca = TRUE;

					DBGPRINT(RT_DEBUG_ERROR, ("@@@ %s: pAd->false_cca_stat[%u]=%u,  pAd->false_cca_threshold=%u !!\n",
						__FUNCTION__, pAd->ed_stat_lidx, pAd->false_cca_stat[pAd->ed_stat_lidx],  pAd->false_cca_threshold));
				}
			} else
				pAd->ed_false_cca_cnt = 0;
		}
	}
	pAd->ed_trigger_stat[pAd->ed_stat_lidx] = pAd->ed_trigger_cnt;
	pAd->ed_silent_stat[pAd->ed_stat_lidx] = pAd->ed_silent_cnt;

	INC_RING_INDEX(pAd->ed_stat_lidx, ED_STAT_CNT);
	pAd->false_cca_stat[pAd->ed_stat_lidx] = 0;

	if (pAd->ed_stat_sidx == pAd->ed_stat_lidx) {
		INC_RING_INDEX(pAd->ed_stat_sidx, ED_STAT_CNT);
	}

	RTMP_IRQ_UNLOCK(&pAd->irq_lock, irqflag);

	if (stop_edcca) /* disable edcca!*/
	{
		if (pAd->ed_chk) {
			DBGPRINT(RT_DEBUG_ERROR, ("@@@ %s: go to ed_monitor_exit()!!\n", __FUNCTION__));
			ed_monitor_exit(pAd);
		}
	}
	else
	{
		if (pAd->ed_trigger_cnt > pAd->ed_block_tx_threshold) {
			if (pAd->ed_tx_stoped == FALSE) {
				edcca_tx_stop_start(pAd, TRUE);
				pAd->ed_tx_stoped = TRUE;
			}
		}

		if (pAd->ed_silent_cnt > pAd->ed_block_tx_threshold) {
			if (pAd->ed_tx_stoped == TRUE) {
				edcca_tx_stop_start(pAd, FALSE);
				pAd->ed_tx_stoped = FALSE;
			}
		}
	}

	return TRUE;
}

/* this function will be called in multi entry */
INT ed_monitor_exit(struct rtmp_adapter *pAd)
{
	ULONG irqflag;
	BOOLEAN old_ed_tx_stoped, old_ed_chk;

	RTMP_IRQ_LOCK(&pAd->irq_lock, irqflag);
	DBGPRINT(RT_DEBUG_OFF, ("@@@ %s : ===>\n", __FUNCTION__));

	memset(&pAd->ed_stat[0], sizeof(pAd->ed_stat));
	memset(&pAd->ch_idle_stat[0], sizeof(pAd->ch_idle_stat));
	memset(&pAd->ch_busy_stat[0], sizeof(pAd->ch_busy_stat));
	memset(&pAd->chk_time[0], sizeof(pAd->chk_time));
	memset(&pAd->ed_trigger_stat[0], sizeof(pAd->ed_trigger_stat));
	memset(&pAd->ed_silent_stat[0], sizeof(pAd->ed_silent_stat));
	memset(&pAd->false_cca_stat[0], sizeof(pAd->false_cca_stat));

	pAd->ed_stat_lidx = pAd->ed_stat_sidx = 0;
	pAd->ed_trigger_cnt = 0;
	pAd->ed_silent_cnt = 0;
	/* ignore fisrt time's incorrect false cca */
	pAd->ed_false_cca_cnt = 0;

	old_ed_tx_stoped = pAd->ed_tx_stoped;
	old_ed_chk = pAd->ed_chk;

	pAd->ed_tx_stoped = FALSE;
	/* also clear top level flags */
	pAd->ed_chk = FALSE;

	DBGPRINT(RT_DEBUG_OFF, ("@@@ %s : <===\n", __FUNCTION__));
	RTMP_IRQ_UNLOCK(&pAd->irq_lock, irqflag);

	if (old_ed_tx_stoped)
		edcca_tx_stop_start(pAd, FALSE);

	if (old_ed_chk)
		RTMP_CHIP_ASIC_SET_EDCCA(pAd, FALSE);

	return TRUE;
}

/* open & muanl cmd will call */
INT ed_monitor_init(struct rtmp_adapter *pAd)
{
	ULONG irqflag;

	RTMP_IRQ_LOCK(&pAd->irq_lock, irqflag);
	DBGPRINT(RT_DEBUG_OFF, ("@@@ %s : ===>\n", __FUNCTION__));

	memset(&pAd->ed_stat[0], sizeof(pAd->ed_stat));
	memset(&pAd->ch_idle_stat[0], sizeof(pAd->ch_idle_stat));
	memset(&pAd->ch_busy_stat[0], sizeof(pAd->ch_busy_stat));
	memset(&pAd->chk_time[0], sizeof(pAd->chk_time));
	memset(&pAd->ed_trigger_stat[0], sizeof(pAd->ed_trigger_stat));
	memset(&pAd->ed_silent_stat[0], sizeof(pAd->ed_silent_stat));
	memset(&pAd->false_cca_stat[0], sizeof(pAd->false_cca_stat));

	pAd->ed_stat_lidx = pAd->ed_stat_sidx = 0;
	pAd->ed_trigger_cnt = 0;
	pAd->ed_silent_cnt = 0;
	/* ignore first time's incorrect false cca */
	pAd->ed_false_cca_cnt = 0;
	pAd->ed_tx_stoped = FALSE;
	/* also set top level flags */
	pAd->ed_chk = TRUE;

	DBGPRINT(RT_DEBUG_OFF, ("@@@ %s : <===\n", __FUNCTION__));
	RTMP_IRQ_UNLOCK(&pAd->irq_lock, irqflag);

	RTMP_CHIP_ASIC_SET_EDCCA(pAd, TRUE);
}

INT set_ed_block_tx_thresh(struct rtmp_adapter *pAd, char *arg)
{
	UINT block_tx_threshold = simple_strtol(arg, 0, 10);

	pAd->ed_block_tx_threshold = block_tx_threshold;
	DBGPRINT(RT_DEBUG_OFF, ("%s()::ed_block_tx_threshold=%d\n",
		__FUNCTION__, pAd->ed_block_tx_threshold));

	return TRUE;
}

INT set_ed_threshold(struct rtmp_adapter *pAd, char *arg)
{
	ULONG percent = simple_strtol(arg, 0, 10);

	if (percent > 100)
		pAd->ed_threshold = (percent % 100);
	else
		pAd->ed_threshold = percent;

	DBGPRINT(RT_DEBUG_OFF, ("%s()::ed_threshold=%d\n",
		__FUNCTION__, pAd->ed_threshold));

	return TRUE;
}

INT set_ed_false_cca_threshold(struct rtmp_adapter *pAd, char *arg)
{
	ULONG false_cca_threshold = simple_strtol(arg, 0, 10);

	pAd->false_cca_threshold = false_cca_threshold > 0 ? false_cca_threshold : 0;

	DBGPRINT(RT_DEBUG_OFF, ("%s()::false_cca_threshold=%d\n",
		__FUNCTION__, pAd->false_cca_threshold));

	return TRUE;
}

/* let run-time turn on/off */
INT set_ed_chk_proc(struct rtmp_adapter *pAd, char *arg)
{
	UINT ed_chk = simple_strtol(arg, 0, 10);

	DBGPRINT(RT_DEBUG_OFF, ("%s()::ed_chk=%d\n",
		__FUNCTION__, ed_chk));

	if (ed_chk != 0)
		ed_monitor_init(pAd);
	else
		ed_monitor_exit(pAd);

	return TRUE;
}

#ifdef CONFIG_AP_SUPPORT
INT set_ed_sta_count_proc(struct rtmp_adapter *pAd, char *arg)
{
	UINT ed_sta_th = simple_strtol(arg, 0, 10);

	DBGPRINT(RT_DEBUG_OFF, ("%s()::ed_sta_th=%d\n",
		__FUNCTION__, ed_sta_th));

	pAd->ed_sta_threshold = ed_sta_th;

	return TRUE;
}

INT set_ed_ap_count_proc(struct rtmp_adapter *pAd, char *arg)
{
	UINT ed_ap_th = simple_strtol(arg, 0, 10);

	DBGPRINT(RT_DEBUG_OFF, ("%s()::ed_ap_th=%d\n",
		__FUNCTION__, ed_ap_th));

	pAd->ed_ap_threshold = ed_ap_th;

	return TRUE;
}
#endif /* CONFIG_AP_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
INT set_ed_ap_scaned_count_proc(struct rtmp_adapter *pAd, char *arg)
{
	UINT ed_ap_scaned = simple_strtol(arg, 0, 10);

	DBGPRINT(RT_DEBUG_OFF, ("%s()::ed_ap_scaned=%d\n",
		__FUNCTION__, ed_ap_scaned));

	pAd->ed_ap_scaned = ed_ap_scaned;

	return TRUE;
}

INT set_ed_current_ch_ap_proc(struct rtmp_adapter *pAd, char *arg)
{
	UINT ed_current_ch_aps = simple_strtol(arg, 0, 10);

	DBGPRINT(RT_DEBUG_OFF, ("%s()::ed_current_ch_aps=%d\n",
		__FUNCTION__, ed_current_ch_aps));

	pAd->ed_current_ch_aps = ed_current_ch_aps;

	return TRUE;
}

INT set_ed_current_rssi_threhold_proc(struct rtmp_adapter *pAd, char *arg)
{
	INT ed_rssi_threshold = simple_strtol(arg, 0, 10);

	DBGPRINT(RT_DEBUG_OFF, ("%s()::ed_rssi_threshold=%d\n",
		__FUNCTION__, ed_rssi_threshold));

	pAd->ed_rssi_threshold = ed_rssi_threshold;

	return TRUE;
}
#endif /* CONFIG_STA_SUPPORT */

INT show_ed_stat_proc(struct rtmp_adapter *pAd, char *arg)
{
	unsigned long irqflags;
	uint32_t ed_stat[ED_STAT_CNT], ed_2nd_stat[ED_STAT_CNT], false_cca_stat[ED_STAT_CNT];
	uint32_t silent_stat[ED_STAT_CNT], trigger_stat[ED_STAT_CNT];
	uint32_t busy_stat[ED_STAT_CNT], idle_stat[ED_STAT_CNT];
	ULONG chk_time[ED_STAT_CNT];
	INT period_us = 0;
	UCHAR start = 0, end = 0, idx = 0;

	RTMP_IRQ_LOCK(&pAd->irq_lock, irqflags);
	start = pAd->ed_stat_sidx;
	end = pAd->ed_stat_lidx;
	memmove(&ed_stat[0], &pAd->ed_stat[0], sizeof(ed_stat));
	memmove(&ed_2nd_stat[0], &pAd->ed_2nd_stat[0], sizeof(ed_2nd_stat));
	memmove(&busy_stat[0], &pAd->ch_busy_stat[0], sizeof(busy_stat));
	memmove(&idle_stat[0], &pAd->ch_idle_stat[0], sizeof(idle_stat));
	memmove(&chk_time[0], &pAd->chk_time[0], sizeof(chk_time));
	memmove(&trigger_stat[0], &pAd->ed_trigger_stat[0], sizeof(trigger_stat));
	memmove(&silent_stat[0], &pAd->ed_silent_stat[0], sizeof(silent_stat));
	memmove(&false_cca_stat[0], &pAd->false_cca_stat[0], sizeof(false_cca_stat));
	RTMP_IRQ_UNLOCK(&pAd->irq_lock, irqflags);

#ifdef CONFIG_AP_SUPPORT
	DBGPRINT(RT_DEBUG_OFF, ("Dump ChannelBusy Counts, ed_chk=%u, ed_sta_threshold=%u, ed_ap_threshold=%u, false_cca_threshold=%u, ChkPeriod=%dms, ED_Threshold=%d%%, HitCntForBlockTx=%d\n",
		pAd->ed_chk, pAd->ed_sta_threshold, pAd->ed_ap_threshold, pAd->false_cca_threshold,
		pAd->ed_chk_period, pAd->ed_threshold, pAd->ed_block_tx_threshold));
#endif /* CONFIG_AP_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
	DBGPRINT(RT_DEBUG_OFF, ("Dump ChannelBusy Counts, ed_chk=%u, ed_ap_scaned=%u, ed_current_ch_aps=%u, ed_rssi_threshold=%d, false_cca_threshold=%u, ChkPeriod=%dms, ED_Threshold=%d%%, HitCntForBlockTx=%d\n",
		pAd->ed_chk, pAd->ed_ap_scaned, pAd->ed_current_ch_aps, pAd->ed_rssi_threshold, pAd->false_cca_threshold,
		pAd->ed_chk_period, pAd->ed_threshold, pAd->ed_block_tx_threshold));
#endif /* CONFIG_STA_SUPPORT */

	period_us = pAd->ed_chk_period * 1000;
	DBGPRINT(RT_DEBUG_OFF, ("TimeSlot:"));
	idx = start;
	do {
		DBGPRINT(RT_DEBUG_OFF, ("%ld  ", chk_time[idx]));
		INC_RING_INDEX(idx, ED_STAT_CNT);
	} while (idx != end);
	DBGPRINT(RT_DEBUG_OFF, ("\n"));

	DBGPRINT(RT_DEBUG_OFF, ("Dump ED_STAT\n"));
	DBGPRINT(RT_DEBUG_OFF, ("RawCnt:"));
	idx = start;
	do {
		DBGPRINT(RT_DEBUG_OFF, ("%d  ", ed_stat[idx]));
		INC_RING_INDEX(idx, ED_STAT_CNT);
	} while (idx != end);
	DBGPRINT(RT_DEBUG_OFF, ("\n"));

	DBGPRINT(RT_DEBUG_OFF, ("Percent:"));
	idx = start;
	do {
		DBGPRINT(RT_DEBUG_OFF, ("\t%d", (ed_stat[idx] * 100) / period_us));
		INC_RING_INDEX(idx, ED_STAT_CNT);
	} while (idx != end);
	DBGPRINT(RT_DEBUG_OFF, ("\n"));

	DBGPRINT(RT_DEBUG_OFF, ("FalseCCA:"));
	idx = start;
	do {
		DBGPRINT(RT_DEBUG_OFF, ("\t%d", false_cca_stat[idx]));
		INC_RING_INDEX(idx, ED_STAT_CNT);
	} while (idx != end);
	DBGPRINT(RT_DEBUG_OFF, ("\n"));

	DBGPRINT(RT_DEBUG_OFF, ("TriggerCnt:"));
	idx = start;
	do {
		DBGPRINT(RT_DEBUG_OFF, ("\t%d", trigger_stat[idx]));
		INC_RING_INDEX(idx, ED_STAT_CNT);
	} while (idx != end);

	DBGPRINT(RT_DEBUG_OFF, ("SilentCnt:"));
	idx = start;
	do {
		DBGPRINT(RT_DEBUG_OFF, ("\t%d", silent_stat[idx]));
		INC_RING_INDEX(idx, ED_STAT_CNT);
	} while (idx != end);
	DBGPRINT(RT_DEBUG_OFF, ("\n==========================\n"));


	DBGPRINT(RT_DEBUG_OFF, ("Dump ED_2nd_STAT\n"));
	DBGPRINT(RT_DEBUG_OFF, ("RawCnt:"));
	idx = start;
	do {
		DBGPRINT(RT_DEBUG_OFF, ("%d  ", ed_2nd_stat[idx]));
		INC_RING_INDEX(idx, ED_STAT_CNT);
	} while (idx != end);
	DBGPRINT(RT_DEBUG_OFF, ("\n"));

	DBGPRINT(RT_DEBUG_OFF, ("Percent:"));
	idx = start;
	do {
		DBGPRINT(RT_DEBUG_OFF, ("\t%d", (ed_2nd_stat[idx] * 100) / period_us));
		INC_RING_INDEX(idx, ED_STAT_CNT);
	} while (idx != end);
	DBGPRINT(RT_DEBUG_OFF, ("\n"));
	DBGPRINT(RT_DEBUG_OFF, ("\n==========================\n"));


	DBGPRINT(RT_DEBUG_OFF, ("Dump CH_IDLE_STAT\n"));
	DBGPRINT(RT_DEBUG_OFF, ("RawCnt:"));
	idx = start;
	do {
		DBGPRINT(RT_DEBUG_OFF, ("%d  ", idle_stat[idx]));
		INC_RING_INDEX(idx, ED_STAT_CNT);
	} while (idx != end);
	DBGPRINT(RT_DEBUG_OFF, ("\n"));

	DBGPRINT(RT_DEBUG_OFF, ("Percent:"));
	idx = start;
	do {
		DBGPRINT(RT_DEBUG_OFF, ("\t%d", (idle_stat[idx] *100)/ period_us));
		INC_RING_INDEX(idx, ED_STAT_CNT);
	} while (idx != end);
	DBGPRINT(RT_DEBUG_OFF, ("\n"));
	DBGPRINT(RT_DEBUG_OFF, ("\n==========================\n"));

	DBGPRINT(RT_DEBUG_OFF, ("Dump CH_BUSY_STAT\n"));
	DBGPRINT(RT_DEBUG_OFF, ("RawCnt:"));
	idx = start;
	do {
		DBGPRINT(RT_DEBUG_OFF, ("%d  ", busy_stat[idx]));
		INC_RING_INDEX(idx, ED_STAT_CNT);
	} while (idx != end);
	DBGPRINT(RT_DEBUG_OFF, ("\n"));

	DBGPRINT(RT_DEBUG_OFF, ("Percent:"));
	idx = start;
	do {
		DBGPRINT(RT_DEBUG_OFF, ("\t%d", (busy_stat[idx] *100 )/ period_us));
		INC_RING_INDEX(idx, ED_STAT_CNT);
	} while (idx != end);
	DBGPRINT(RT_DEBUG_OFF, ("\n"));
	DBGPRINT(RT_DEBUG_OFF, ("\n==========================\n"));

	return TRUE;
}
#endif /* ED_MONITOR */



static INT Set_AP_VENDOR_SPECIFIC_IE(
	IN struct rtmp_adapter *pAd,
	IN UINT8 OUIType,
	IN char *IE,
	IN uint32_t IELen)
{
	struct os_cookie *pObj = pAd->OS_Cookie;
	UCHAR apidx = pObj->ioctl_if;


	switch (OUIType) {
		default:
			DBGPRINT(RT_DEBUG_ERROR, ("%s: Unknown OUIType = %d\n", __FUNCTION__, OUIType));
		break;

	}

	return TRUE;
}


INT Set_AP_IE(
	IN struct rtmp_adapter *pAd,
	IN char *IE,
	IN uint32_t IELen)
{
	UINT8 EID;
	UINT8 OUIType;

	EID = *IE;

	switch (EID)
	{

		case IE_VENDOR_SPECIFIC:
			OUIType = *(IE + 5);
			Set_AP_VENDOR_SPECIFIC_IE(pAd, OUIType, IE, IELen);
			break;
		default:
			DBGPRINT(RT_DEBUG_ERROR, ("%s: Unknown IE(EID = %d)\n", __FUNCTION__, EID));
			break;
	}

	return TRUE;
}

