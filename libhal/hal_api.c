#include <sys/types.h>
#include <linux/net.h>
#include <ctrlnetlink.h>
#include <linux/sockios.h>
#include <asm-generic/stat.h>
#include <msg_plat.h>
#include <stdio.h>

#include "hal_api.h"
#include <linux/in.h>
#include <linux/in6.h>

#include "if.h"
#include "ios_syslib.h"

#ifndef min
#define min(a, b) ((a) > (b) ? (b) : (a))
#endif
#define CP_FILES_PATH       "/lib/libzebra.so"
#define CP_FILES            "libzebra.so"
#define PROC_PARTION        "/proc/partitions"
#define DEV_BUFLEN		(10)


extern STRU_DEV_MON_CAPABILITY_DRV msg3100_mon_capability; 
extern fanDrv_t msg3100_fan;
extern fanDescDrv_t msg3100_fan_desc;
extern powerCardDrv_t msg3100_powercard;

static struct ios_sysinfo systeminfo_hal;
struct thread_master *master;

static int sys_info_init(void)
{
    struct plat_ioctl_args io_args;
    int fd = -1, ret = 0;
	static int flag = 0;
	if(flag)
		return OK;
	
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return ERROR;

    memset(&io_args, 0, sizeof(struct plat_ioctl_args));
    strncpy(io_args.name, "msg_plat", 8);
    io_args.subcmd = PLT_BRD_GET; // plat_ioctl_cmds

    io_args.u.sysinfo = &systeminfo_hal;
    memset(&systeminfo_hal, 0, sizeof(struct ios_sysinfo));

    ret = ioctl(fd, SIOCGPLTDRV, &io_args);
    close (fd);
	flag = 1;
    if (ret < 0)
    {
        printf("%s:ioctl error.\n\r", __FUNCTION__);
        return ERROR;
    }

    return OK;
}

static unsigned short eeprom_info_checksum(unsigned short *buffer, int size)
{
	unsigned long cksum=0;

    /*to avoid the buffer is full of 0xFF; the pad can be set to zero to checksum again*/
    if((0xFFFF == *buffer) && (0xFFFF == *(buffer+1)))
        return 0xFFFF;

	while(size >1) {
		cksum+=*buffer++;
		size-=sizeof(unsigned short);
	}

	if(size)
		cksum+=*(unsigned char*)buffer;

	cksum=(cksum >> 16)+(cksum&0xffff);
	cksum+=(cksum >>16);

	return (unsigned short)(~cksum);
}

static int eeprom_info_cksum_up(id_eeprom_t *eeprom_info)
{
    unsigned short pad = 0;
    
    if(eeprom_info == NULL)
    {
        printf("msg_board_info can not null.\n");
        return -1;
    }

    eeprom_info->pad = 0;  
    
    pad = eeprom_info_checksum((unsigned short *)eeprom_info, sizeof(id_eeprom_t));
    eeprom_info->pad = pad;
        
    if(eeprom_info_checksum((unsigned short *)eeprom_info, sizeof(id_eeprom_t)))
    {
        printf("generate pad error.\n");
        return -1;
    }
    
    return 0;
}

int bspGetClockRtc(CAL_CLOCK* rtc_time)
{
	struct rtc_time *tm = (struct rtc_time*)rtc_time;
	struct plat_ioctl_args io_args;
	int fd = -1, ret = 0;

	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return ERROR;

	memset(&io_args, 0, sizeof(struct plat_ioctl_args));
	strncpy(io_args.name, "msg_plat", 8);
	io_args.subcmd = PLT_RTC_GET; // plat_ioctl_cmds
	io_args.u.rtc_tm = tm;
	ret = ioctl(fd, SIOCGPLTDRV, &io_args);
	close (fd);
	
	return OK;
}

int bspSetClockRtc(CAL_CLOCK* rtc_time)
{
	struct rtc_time *tm = (struct rtc_time*)rtc_time;
	struct plat_ioctl_args io_args;
	int fd = -1, ret = 0;

	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return ERROR;

	memset(&io_args, 0, sizeof(struct plat_ioctl_args));
	strncpy(io_args.name, "msg_plat", 8);
	io_args.subcmd = PLT_RTC_SET; // plat_ioctl_cmds
	io_args.u.rtc_tm = tm;
	ret = ioctl(fd, SIOCGPLTDRV, &io_args);
	close (fd);
	
	return OK;

}

int bspWatchDogEnable(unsigned long ulEnable)
{
	struct plat_ioctl_args io_args;
	int fd = -1, ret = 0;

	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return ERROR;

	memset(&io_args, 0, sizeof(struct plat_ioctl_args));
	strncpy(io_args.name, "msg_plat", 8);
	io_args.subcmd = PLT_WTD_SET; // plat_ioctl_cmds
	io_args.u.wtd_en = (unsigned char)ulEnable;
	ret = ioctl(fd, SIOCGPLTDRV, &io_args);
	close (fd);
	
	return OK;

}

int bspWatchDogResetTimeSet(unsigned long ulTime)
{
	struct plat_ioctl_args io_args;
	int fd = -1, ret = 0;

	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return ERROR;

	memset(&io_args, 0, sizeof(struct plat_ioctl_args));
	strncpy(io_args.name, "msg_plat", 8);
	io_args.subcmd = PLT_WTD_EXPIRES_SET; // plat_ioctl_cmds
	io_args.u.wtd_en = ulTime;
	ret = ioctl(fd, SIOCGPLTDRV, &io_args);
	close (fd);
	
	return OK;

}

int bspSnmpPortLinkStatusGet(int *link)
{
    #if 0
	struct interface_info info;
	memcpy(info.name, "eth1", 5);

	eth_if_setting_get(&info);
	*link = info.eth_setting.link_stat;
    #endif
	return OK;
}

int bspSnmpPortSpeedGet(int *model)
{
    #if 0
	struct interface_info info;

	memcpy(info.name, "eth1", 5);

	eth_if_setting_get(&info);
	*model = info.eth_setting.speed_stat;
    #endif
	return OK;
}

int bspGetDevMonCapability(STRU_DEV_MON_CAPABILITY_DRV *pCapability)
{
	memcpy(pCapability, &msg3100_mon_capability, sizeof(STRU_DEV_MON_CAPABILITY_DRV));
	return OK;
}

int bspGetBackPlaneSlotId()
{
    
}

char *get_monthnum_from_str(char *dst_str, char *src_str)
{
	switch(src_str[0])
	{
	case 'A':
		if (src_str[1] == 'p')
			strncpy(dst_str, "04", 2);
		else
			strncpy(dst_str, "08", 2);
		break;
	case 'D':
		strncpy(dst_str, "12", 2);
		break;
	case 'F':
		strncpy(dst_str, "02", 2);
		break;
	case 'J':
		if (src_str[1] == 'a')
			strncpy(dst_str, "01", 2);
		else if (src_str[2] == 'n')
			strncpy(dst_str, "06", 2);
		else
			strncpy(dst_str, "07", 2);
		break;
	case 'M':
		if (src_str[2] == 'y')
			strncpy(dst_str, "05", 2);
		else
			strncpy(dst_str, "03", 2);
		break;
	case 'N':
		strncpy(dst_str, "11", 2);
		break;
	case 'O':
		strncpy(dst_str, "10", 2);
		break;
	case 'S':
		strncpy(dst_str, "09", 2);
		break;
	}
	return dst_str;
}
/*change date from May 31 2007 or Jun  1 2007 to 20070531 or 20070601*/
char *change_compile_date_version(char *dst_str, char *src_str)
{
	strncpy(dst_str, src_str+7, 4);
	get_monthnum_from_str(dst_str+4, src_str);
	if (src_str[4] == ' ')
	{
		dst_str[6]='0';
		dst_str[7]=src_str[5];
	}
	else
		strncpy(dst_str+6, src_str+4, 2);
	return dst_str;
}
int ios_get_version(char *version_str, int version_len)
{
	char rciosversion[128];
	char tmp_version[64];
       char tmp_buf[64];

	snprintf(tmp_version, 32, "%s", IOS_VERSION_HEAD);

	memset(rciosversion, 0, 128);
	/*sprintf(rciosversion, "%s", tmp_version+6);*/
	sprintf(rciosversion, "%s", tmp_version); /*不去掉前面6个字符*/
    strncat(rciosversion, "_", 1);

	memset(tmp_buf, 0, 64);
	change_compile_date_version(tmp_buf, __DATE__);

    strncat(rciosversion, tmp_buf, 8);

	snprintf(version_str, version_len, "%s%s", rciosversion, VERSION_TYPE);

	return 0;
}
int bspGetSoftwareVersionInfo(int nImageId, STRU_VERSION_INFO *pstVersion)
{
	char version[512];
    if(nImageId == CARD_VERSION_IMAGE_1)
    {
    	ios_get_version(version, sizeof(version));
    	pstVersion->bCommitted = 1;
    	pstVersion->bActive = 1;
    	memcpy(pstVersion->bVersion, version, sizeof(pstVersion->bVersion));
    	pstVersion->dwSize = 1;
    	pstVersion->dwUpdateTime = 1;
    	pstVersion->bValid = 1;
    }
    else
    {
        strcpy((char*)pstVersion->bVersion,"--");
    }
	return OK;
}
int get_boot_verinfo(char *boot_verinfo)
{
#ifdef CONFIG_CPU_CAVIUM_OCTEON
	FILE *infile = fopen("/proc/octeon_info", "r");
	if(infile == NULL)
	{
		perror("Error opening /proc/octeon_info");
		exit(-1);
	}

	while(!feof(infile))
	{
		char buffer[80];
		if(fgets(buffer, sizeof(buffer), infile))
		{
			if(strncmp(buffer, "boot_version:",13) == 0)
			{
				strcpy(boot_verinfo, buffer+21);
				break;
			}
		}
	}
    
    if(boot_verinfo[0] == 0) {
        strcpy(boot_verinfo, "Boot Version <1.1.7\n");
    }
    
	return 0;
#endif

    struct plat_ioctl_args io_args;
    int fd = -1, ret = 0;

    if((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return -1;

    memset(&io_args, 0, sizeof(struct plat_ioctl_args));
    io_args.subcmd = PLT_BOOTVER_GET;

    ret = ioctl(fd, SIOCGPLTDRV, &io_args);
    close(fd);

    if(ret < 0)
    {
        return -1;
    }
    
    strcpy(boot_verinfo, io_args.u.boot_version);

    return 0;
}
int bspGetBasebootVersionInfo(int nImageId, STRU_VERSION_INFO *pstVersion)
{
	char version[512];
    #if 1
    if(0 ==	get_boot_verinfo(version))
    {
    	version[0] = '1';//ucs uboot major version is 1
    	pstVersion->bCommitted = 1;
    	pstVersion->bActive = 1;
    	memcpy(pstVersion->bVersion, version, sizeof(pstVersion->bVersion));
    	pstVersion->dwSize = 1;
    	pstVersion->dwUpdateTime = 1;
    	pstVersion->bValid = 1;
    }
    else
    {
        strcpy(pstVersion->bVersion,"--");
    }
    #endif
	return OK;

}

int bspGetDevCpuMacAddr(char *cMacAddr, int iLen)
{
	sys_info_init();
	memcpy(cMacAddr, systeminfo_hal.macbase, 6);
	return OK;
}

int bspGetSelfSlotId()
{
    return 1;
}
#if 0
int halSockIoctl(struct plat_ioctl_args *args)
{
	int fd = -1, ret = 0;

	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return -1;

	ret = ioctl(fd, SIOCSPLTDRV, args);

    close (fd);

    if (ret < 0)
    {
        vty_print_std("%s:ioctl error.\n\r", __FUNCTION__);
        return -1;
    }

    return 0;

}
void ioctl_args_init(struct plat_ioctl_args *args, int cmd, void *data)
{
	memset(args, 0, sizeof(struct plat_ioctl_args));
	args->subcmd = cmd;
	args->data = data;
}

int bspSysLedNormalEnable()
{
    struct plat_ioctl_args io_args;
    struct led_state_args led_state;

	led_state.led_index = LED_SYS_NUM;
	led_state.led_status = LED_GREEN_SLOW_FLASH;
	ioctl_args_init(&io_args, PLT_LED_STATE_SET, &led_state);
	halSockIoctl(&io_args);


    return 0;

}
#endif
int bspSysLedNormalEnable()
{	
	struct plat_ioctl_args io_args;
	struct led_state_args led_state;
	int fd = -1, ret = 0;

	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return ERROR;

	memset(&io_args, 0, sizeof(struct plat_ioctl_args));
	strncpy(io_args.name, "msg_plat", 8);
	io_args.subcmd = PLT_LED_STATE_SET; // plat_ioctl_cmds
	io_args.u.led_state.led_index = LED_SYS_NUM;
	io_args.u.led_state.led_status = LED_GREEN_SLOW_FLASH;
	ret = ioctl(fd, SIOCGPLTDRV, &io_args);
	close (fd);
	
	return OK;
}

int bspGetCardManufactureInfo(int iSlotNum, EepromCardParams *pEepromParams)
{
	id_eeprom_t hal_eeprom_map;

	if(halE2promRead(iSlotNum, 0, &hal_eeprom_map, sizeof(id_eeprom_t)) < 0)
		return ERROR;
	if(eeprom_info_checksum((unsigned short*)&hal_eeprom_map, sizeof(id_eeprom_t)))
		return ERROR;
	memcpy(pEepromParams->eepromProductName, hal_eeprom_map.prod_pn, min(sizeof(hal_eeprom_map.prod_pn), EEPROM_PRODUCT_NAME_LEN));
	memcpy(pEepromParams->eepromProductVersion, hal_eeprom_map.prod_rev, min(sizeof(hal_eeprom_map.prod_rev), EEPROM_PRODUCT_VERSION_LEN));
	memcpy(pEepromParams->eepromSerialNo, hal_eeprom_map.prod_sn, min(sizeof(hal_eeprom_map.prod_sn), EEPROM_SERIAL_NO_LEN));
	memcpy(pEepromParams->eepromVendor, hal_eeprom_map.vendor, min(sizeof(hal_eeprom_map.vendor), EEPROM_VENDOR_LEN));
	memcpy(pEepromParams->eepromMac, hal_eeprom_map.macbase, min(sizeof(hal_eeprom_map.macbase), EEPROM_MAC_LEN));
	memcpy(pEepromParams->eepromPbcVersion, hal_eeprom_map.pcb_rev, min(sizeof(hal_eeprom_map.pcb_rev), EEPROM_PCB_VERSION_LEN));
    memcpy(pEepromParams->eepromBoardName, hal_eeprom_map.brd_pn, min(sizeof(hal_eeprom_map.brd_pn), EEPROM_PRODUCT_NAME_LEN));

    return OK;
}

int bspSetCardManufactureInfo(int iSlotNum, EepromCardParams *pEepromParams)
{
	id_eeprom_t hal_eeprom_map;
	
	if(halE2promRead(iSlotNum, 0, &hal_eeprom_map, sizeof(id_eeprom_t)) < 0)
			return ERROR;
	memcpy(hal_eeprom_map.prod_pn, pEepromParams->eepromProductName, min(sizeof(hal_eeprom_map.prod_pn), EEPROM_PRODUCT_NAME_LEN+1));
	memcpy(hal_eeprom_map.prod_rev, pEepromParams->eepromProductVersion, min(sizeof(hal_eeprom_map.prod_rev), EEPROM_PRODUCT_VERSION_LEN+1));
	memcpy(hal_eeprom_map.prod_sn, pEepromParams->eepromSerialNo, min(sizeof(hal_eeprom_map.prod_sn), EEPROM_SERIAL_NO_LEN+1));
	memcpy(hal_eeprom_map.vendor, pEepromParams->eepromVendor, min(sizeof(hal_eeprom_map.vendor), EEPROM_VENDOR_LEN+1));
	memcpy(hal_eeprom_map.macbase, pEepromParams->eepromMac, min(sizeof(hal_eeprom_map.macbase), EEPROM_MAC_LEN+1));
	memcpy(hal_eeprom_map.pcb_rev, pEepromParams->eepromPbcVersion, min(sizeof(hal_eeprom_map.pcb_rev), EEPROM_PCB_VERSION_LEN+1));
    memcpy(hal_eeprom_map.brd_pn, pEepromParams->eepromBoardName, min(sizeof(hal_eeprom_map.brd_pn), EEPROM_PRODUCT_NAME_LEN+1));
	eeprom_info_cksum_up(&hal_eeprom_map);
	return halE2promWrite(iSlotNum, 0, &hal_eeprom_map, sizeof(id_eeprom_t));
}

int bspSlotOnline(int iSlotNum)
{
	unsigned char subcard_reg = 1;
	int maincard = MAINCARDSLOT;
	
	if(hal_cpld_read(maincard, &subcard_reg, CPLD_SUBCARD_ON_REG, sizeof(unsigned char)) < 0)
		return ERROR;
	return subcard_reg &= (0x1 << iSlotNum);

}

int bspGetCardSerialNumber(int iSlotNum, char *pcSerialNumber, int len)
{
	sys_info_init();
	memcpy(pcSerialNumber, systeminfo_hal.prod_sn, min(sizeof(systeminfo_hal.prod_sn), len));
	return OK;

}

int bspGetCardHardwareVersion(int iSlotNum, char *pcHwVersion, int len)
{
	sys_info_init();
	sprintf(pcHwVersion, "%c.%01X", ((ntohs(systeminfo_hal.pcb_rev) >> 8) & 0xff)-0xa+'A',((ntohs(systeminfo_hal.pcb_rev)) & 0x0f));
	return OK;
}

int bspGetCardCpldVersion(int iSlotNum, char *pcCpldVersion, int len)
{
	unsigned char version_reg = 1;
	int maincard = MAINCARDSLOT;

	if(hal_cpld_read(maincard, &version_reg, CPLD_VERSION_REG, sizeof(unsigned char)) < 0)
		return ERROR;
	/*memcpy(pcCpldVersion, &version_reg, min(sizeof(unsigned char), len));*/
    sprintf(pcCpldVersion,"%d.%d",(int)(version_reg&0xF0>>4),(int)(version_reg&0x0F));
	return OK;
}

int bspResetCard(int iSlotNum)
{
	unsigned char reset_reg = 1;
	int maincard = MAINCARDSLOT;
	
	if(hal_cpld_read(maincard, &reset_reg, CPLD_RESET_REG, sizeof(unsigned char)) < 0)
		return ERROR;
	reset_reg &= ~(0x1 << iSlotNum);
	if(hal_cpld_write(maincard, &reset_reg, CPLD_RESET_REG, sizeof(unsigned char)) < 0)
		return ERROR;
	reset_reg |= 0x1 << iSlotNum;
	if(hal_cpld_write(maincard, &reset_reg, CPLD_RESET_REG, sizeof(unsigned char)) < 0)
		return ERROR;
	return OK;
}

int bspSetCardPowerSwitch(int iSlotNum, BOOL bTag, ulong_t ulCardType)
{
    return OK;
}

static int tmp_high[8] = {1, 2, 4, 8, 16, 32, 64, 128};
static float tmp_low[3] = {0.125, 0.25, 0.5};

static float calculate_tmp(unsigned char high, unsigned char low)
{
	int i;
	float tmp = 0.0;
	for(i = 0; high != 0, i < 8; i++)
	{
		tmp += (high & 0x1) ? tmp_high[i]:0;
		high >>= 1;
	}
	low >>= 5;
	for(i = 0; low != 0, i < 3; i++)
	{
		tmp += (low & 0x1) ? tmp_low[i]:0;
		low >>= 1;
	}
	return (tmp - 64.0);
	
}

int bspCardTemperatureGet(int iSlotNum, card_temper_drv_t *pTemper, ulong_t ulCardType)
{
	float internal, external;
	temp_reg_t temp;
	struct plat_ioctl_args io_args;
	int fd = -1, ret = 0;

	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return -1;

	memset(&io_args, 0, sizeof(struct plat_ioctl_args));
	strncpy(io_args.name, "msg_plat", 8);
	io_args.subcmd = PLT_TMP_GET; // plat_ioctl_cmds
	io_args.u.temperature = &temp.allreg;
	ret = ioctl(fd, SIOCGPLTDRV, &io_args);
	close (fd);
	
	internal = calculate_tmp(temp.reg[TMP_INT_HIGH_INDEX], temp.reg[TMP_INT_LOW_INDEX]);
	external = calculate_tmp(temp.reg[TMP_EXT_HIGH_INDEX], temp.reg[TMP_EXT_LOW_INDEX]);

	pTemper->temper = (int)internal;

	return 0;

}

int bspGetPowerInfo(int iSlotNum, powerCardDrv_t *pPwrCardInfo)
{
	memcpy(pPwrCardInfo, &msg3100_powercard, sizeof(powerCardDrv_t));
	return OK;
}

int bspGetFanInfo(int iSlotNum, fanDrv_t *pFanRunningInfo)
{
	memcpy(pFanRunningInfo, &msg3100_fan, sizeof(fanDrv_t));
	return OK;

}

int bspGetFanDesc(int iSlotNum, fanDescDrv_t *pFanDescInfo)
{
	memcpy(pFanDescInfo, &msg3100_fan_desc, sizeof(fanDescDrv_t));
	return OK;

}

int bspGetPowerCardInfo(int iSlotNum, powerCardDrv_t *pPwrCardInfo)
{
	memcpy(pPwrCardInfo, &msg3100_powercard, sizeof(powerCardDrv_t));
	return OK;

}

int bspSetFanSpeedGear(ulong_t ulGear)
{
	unsigned char fan_ctrl_reg = (unsigned char)ulGear;
	int maincard = MAINCARDSLOT;

	if(hal_cpld_write(maincard, &fan_ctrl_reg, CPLD_FAN_CTRL_REG, sizeof(unsigned char)) < 0)
		return ERROR;

}
static unsigned long get_file_size(const char *filename)
{
    struct stat buf;
    if(stat(filename, &buf)<0) 
     { 
         return 0; 
     } 
    return (unsigned long)buf.st_size; 
}

int bspFactoryTestUSB(void)
{
    int  ret_lib=0, ret_usb=0, num=0;
    int	 failed = 0;
	int len = 0, cnt = 0;
    FILE *fp = fopen(PROC_PARTION,"r");
    char usb_dev[DEV_BUFLEN];
    char usb_path[DEV_BUFLEN];
	char tmp[128];
    char *line = NULL;
    char *pos_dev = NULL;
	char ch;
    
    memset(usb_dev,0,DEV_BUFLEN);
    memset(usb_path,0,DEV_BUFLEN);
    memset(tmp,0,128);
	
    if(fp == NULL)
    {
       printf("USB MOUNT FAIL!\n");
       return ERROR;
    }
    ret_lib = get_file_size(CP_FILES_PATH);
	while(-1 != (cnt = getline(&line, &len, fp)))	
    {
    	for(ch = 'a'; ch <= 'z'; ch++)
    	{
    		sprintf(tmp, "sd%c", ch);
			pos_dev = strstr(line,tmp);  
    		if(pos_dev != NULL && ((pos_dev[3] >= '0') && (pos_dev[3] <= '9')))
        	{
	            memcpy(usb_dev,pos_dev,4);
		        sprintf(usb_path, "/mnt/%s", usb_dev);
				sprintf(tmp, "cp "CP_FILES_PATH" %s", usb_path);
		        system(tmp);
				sprintf(tmp, "%s/"CP_FILES, usb_path);
		        ret_usb= get_file_size(tmp);
				sprintf(tmp, "rm -f %s/"CP_FILES, usb_path);
		        system(tmp);
		        
		        if(ret_lib == ret_usb) 
		        {
		            printf("USB%d OK (file size=%u)!\n", num, ret_usb);
		        } 
		        else
		        {
		            failed = 1;
		            printf("USB%d FAILED (file size=%u)!\n", num, ret_usb);
		        }
				num++;
				break;
        	}
    	}        
    }
	
	if(line)
		free(line);
    fclose(fp);
	
	if(num == 0 || failed == 1)
		return ERROR;

    return OK;
	
}

int __attribute__ ((constructor)) halDevInit(void)
{   
	int ret = 0;

	halLockInit();

	return ret;
}

int __attribute__ ((destructor)) halDevExit(void)
{
	halLockClose();
}

