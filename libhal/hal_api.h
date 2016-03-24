#include "deviceExpo.h"
#include "hal_cpld.h"

#define OK 0
#define ERROR -1

#define MAINCARDSLOT 1


#define HAL_PRODUCT_NAME_LEN 32
#define HAL_PRODUCT_VERSION_LEN 8
#define HAL_SERIAL_NO_LEN 64
#define HAL_VENDOR_LEN 32
#define HAL_MAC_LEN 6
#define HAL_PCB_VERSION_LEN 8

int bspGetClockRtc(CAL_CLOCK* rtc_time);
int bspSetClockRtc(CAL_CLOCK* rtc_time);
int bspWatchDogEnable(unsigned long ulEnable);
int bspWatchDogResetTimeSet(unsigned long ulTime);
int bspSnmpPortLinkStatusGet(int *link);
int bspSnmpPortSpeedGet(int *model);
int bspGetDevMonCapability(STRU_DEV_MON_CAPABILITY_DRV *pCapability);
int bspGetBackPlaneSlotId();
int bspGetSoftwareVersionInfo(int nImageId, STRU_VERSION_INFO *pstVersion);
int bspGetBasebootVersionInfo(int nImageId, STRU_VERSION_INFO *pstVersion);
int bspGetDevCpuMacAddr(char *cMacAddr, int iLen);
int bspGetSelfSlotId();
int bspSysLedNormalEnable();
int bspGetCardManufactureInfo(int iSlotNum, EepromCardParams *pEepromParams);
int bspSetCardManufactureInfo(int iSlotNum, EepromCardParams *pEepromParams);
int bspSlotOnline(int iSlotNum);
int bspGetCardSerialNumber(int iSlotNum, char *pcSerialNumber, int len);
int bspGetCardHardwareVersion(int iSlotNum, char *pcHwVersion, int len);
int bspGetCardCpldVersion(int iSlotNum, char *pcCpldVersion, int len);
int bspResetCard(int iSlotNum);
int bspSetCardPowerSwitch(int iSlotNum, BOOL bTag, ulong_t ulCardType);
int bspCardTemperatureGet(int iSlotNum, card_temper_drv_t *pTemper, ulong_t ulCardType);
int bspGetPowerInfo(int iSlotNum, powerCardDrv_t *pPwrCardInfo);
int bspGetFanInfo(int iSlotNum, fanDrv_t *pFanRunningInfo);
int bspGetFanDesc(int iSlotNum, fanDescDrv_t *pFanDescInfo);
int bspGetPowerCardInfo(int iSlotNum, powerCardDrv_t *pPwrCardInfo);
int bspSetFanSpeedGear(ulong_t ulGear);

