/************************************************************************/
/*    瑞斯康达科技发展有限公司          版权所有						*/
/************************************************************************/
/*   @@BEGAIN_INTERNAL_LEGAL@@			 			                    */
/*									                                    */
/*                   Copyright(C) Description                           */
/* Raisecom  Science & Technology Development Co.,Ltd. Beijing, China   */
/* Unpublished work-rights reserved under the China Copyright Act.	    */
/* Use,duplication, or disclosure by the government is subject to	    */
/* restrictions set forth in the raisecom commercial license agreement. */
/*									                                    */
/*   @@END_INTERNAL_LEGAL@@						                        */
/************************************************************************/
/*   程序文件名：deviceExpo.h					                        */
/*   Filename  ：deviceExpo.h					                        */
/*   作者      ：高洪伟							                        */
/*   Author    ：gaohongwei						                        */
/*   日期      ：12/07/2008						                        */
/*   Date      ：12/07/2008						                        */
/*   版本      ：1.0							                        */
/*   Version   ：1.0                                                    */
/*   实现目的  ：设备描述信息函数声明                                   */
/*   Purpose   ：                                                       */
/************************************************************************/
/*修改记录*/
/*

01, 20080712, gaohongwei, First version
*/

#ifndef __DEVICE_EXPO_H
#define __DEVICE_EXPO_H

//#include "deviceIfLib.h"

typedef char			char_t;
typedef	short		    short_t;
typedef	int	            int_t;
typedef	long			long_t;
typedef unsigned char	uchar_t;
typedef	unsigned short	ushort_t;
typedef unsigned int	uint_t;
typedef unsigned long	ulong_t;

typedef unsigned char	Byte;
typedef int	            BOOL;
typedef	unsigned short	Word;
typedef	int	DWord;


/*设备监控相关定义*/
/*
设备监控全局描述 硬件上是否支持等
*/
typedef struct
{
    uchar_t isTemperMonSupp;        /*板卡温度监控支持 T/F*/
    uchar_t isCardPowerMonSupp;     /*板卡电压监控 T/F*/
    uchar_t isFanMonSupp;           /*风扇监控支持 T/F*/
    uchar_t isPwCardMonSupp;        /*电源盘电压监控支持 T/F*/
    
    uchar_t isPwModuleMonSupp;      /*电源模块监控支持 T/F*/
    uchar_t isPwCardIntSupp;        /*电源盘中断信息获取支持 T/F*/
    uchar_t isPWRMCardSupp;         /*是否支持智能电源盘 T/F*/
    uchar_t isFanSpeedSetSupp;      /*是否支持风扇速率设置*/
    
    uchar_t serviceSlotNumSupp;     /*支持几个业务板卡槽位*/    
    uchar_t fanNumSupp;             /*支持几个风扇*/
    uchar_t powerNumSupp;           /*支持几个电源板*/
    uchar_t powerModNumSupp;        /*支持几个电源模块*/
    
    uchar_t subFanNumSupp;          /*一个风扇上几个子扇 目前一种设备唯一*/
    uchar_t isPowerOffSupp;         /*设备上是否有板卡支持下电设置*/
    uchar_t pandding[2];
    
}STRU_DEV_MON_CAPABILITY_DRV;

#define drvGetDeviceType()          devGetDeviceParameter(DEV_PARA_DEVICE_TYPE)
#define drvGetDeviceShelf()          devGetDeviceParameter(DEV_PARA_DEVICE_IS_SHELF)
#define drvGetDeviceName()          ((const char*) devGetDeviceParameter(DEV_PARA_DEVICE_TYPE_NAME))
#define drvGetPrimaryNmsSlotId()    devGetDeviceParameter(DEV_PARA_SMC_PRIMARY_SLOT_ID)
#define drvGetSecondaryNmsSlotId()  devGetDeviceParameter(DEV_PARA_SMC_SECONDARY_SLOT_ID)
#define drvGetSoftwareNameFull()    ((const char*) devGetDeviceParameter(DEV_PARA_SOFTWARE_NAME_FULL))
#define drvGetSoftwareNameShort()   ((const char*) devGetDeviceParameter(DEV_PARA_SOFTWARE_NAME_SHORT))
#define drvGetVendorNameFull()      ((const char*) devGetDeviceParameter(DEV_PARA_VENDOR_NAME_FULL))
#define drvGetVendorNameShort()     ((const char*) devGetDeviceParameter(DEV_PARA_VENDOR_NAME_SHORT))
#define drvGetDefaultUserName()     ((const char*) devGetDeviceParameter(DEV_PARA_USER_NAME_DEFAULT))
#define drvGetDefaultUserPassword() ((const char*) devGetDeviceParameter(DEV_PARA_USER_PASSWORD_DEFAULT))
#define drvGetRoapRootAppId()       (devGetDeviceParameter(DEV_PARA_ROAP_ROOT_APP_ID))
#define drvGetSlotNum()             devGetDeviceParameter(DEV_PARA_SERVICE_SLOT_ID_MAX)

enum
{
    /*0保留*/
    /* 设备/机框级硬件特征 */
    /* 设备类型 */
	DEV_PARA_DEVICE_TYPE = 1,       /* 设备类型编码 */
	DEV_PARA_DEVICE_IS_SHELF,       /*机架式为true，盒式为false*/
	DEV_PARA_CF_SUPPORT,            /*cf卡支持*/
	DEV_PARA_DOUBLEIMAGE_SUPPORT,   /*双镜像支持*/
	DEV_PARA_DEVICE_TYPE_NAME,      /* 设备类型名称 */
	DEV_PARA_PRODUCT_VERSION,      /*产品版本*/
	DEV_PARA_SLOT_ID_MIN,/*机框最小槽位ID*/
	DEV_PARA_SLOT_ID_MAX,/*机框最大槽位ID*/
	DEV_PARA_SERVICE_SLOT_ID_MIN,   /* 设备最小槽位ID。主控盘+接口盘槽位，不含电源盘、风扇盘 */
	DEV_PARA_SERVICE_SLOT_ID_MAX,   /* 设备最大槽位ID */
	DEV_PARA_SMC_PRIMARY_SLOT_ID,   /* 主用主控。在双主控环境下，整机加电启动时主用主控处于工作状态 */
	DEV_PARA_SMC_SECONDARY_SLOT_ID, /* 备用主控。对仅包含一块主控的设备，取值应 < 0 */
	DEV_PARA_BACKPLANE_BANDWIDTH,   /* 背板带宽 */
    DEV_SLOT_PROVISIONABLE_BITMAP,  /*可创建操作比特*/
    DEV_SLOT_BITMAP,
    
    DEV_PARA_ENVIRON_SLOT_MIN,      /*支持环境监控的最小槽位ID*/
    DEV_PARA_ENVIRON_SLOT_MAX,      /*支持环境监控的最大槽位ID*/
    DEV_PARA_ENVIRON_PORT_NUM,      /*每个槽位支持环境监控的端口数*/
    DEV_PARA_ENVIRON_PORT_MIN,      /*每个槽位支持环境监控的端口最小ID*/
    DEV_PARA_QTAG_SIZE,             /*802.1Q tag长度，字节数*/
    /*系统时钟*/
    DEV_PARA_TZ_OFFSET_DIRCTION,   /*时区偏移方向，向东为0，向西为1*/
    DEV_PARA_TZ_OFFSET_HOUR,       /*时区偏移的小时数              */

    /*系统监控*/
    DEV_PARA_MEMORY_SIZE,           /*主控板内存大小*/    
    DEV_PARA_MEMORY_MAX_THRESHOLD_SIZE, /*内存告警阈值的最大值*/

    /*设备监控模块参数*/
    DEV_PARA_POWER_MIN_SLOT_ID,
    DEV_PARA_POWER_MAX_SLOT_ID,
    DEV_PARA_POWER_MODULE_MIN_ID,
    DEV_PARA_POWER_MODULE_MAX_ID,
    
    DEV_PARA_FAN_MIN_SLOT_ID,
    DEV_PARA_FAN_MAX_SLOT_ID,
    DEV_PARA_FAN_SPEED_GEAR_LOW,
    DEV_PARA_FAN_SPEED_GEAR_HIGH,

    /* 设备/机框级软件参数 */
	DEV_PARA_SOFTWARE_NAME_FULL,    /* 软件全名。 */
	DEV_PARA_SOFTWARE_NAME_SHORT,   /* 软件简称。 */
	DEV_PARA_VENDOR_NAME_FULL,      /* 厂商全称。 */
	DEV_PARA_VENDOR_NAME_SHORT,     /* 厂商简称  */
	DEV_PARA_VENDOR_ID,             /* 厂商ID。RAISECOM厂商ID为0x52430000  */
	DEV_PARA_USER_NAME_DEFAULT,     /* 缺省用户名。用于CLI、SNMP等。 */
	DEV_PARA_USER_PASSWORD_DEFAULT, /* 缺省用户密码。用于CLI、SNMP等。 */

    /* 板卡级参数 */
	DEV_PARA_SYS_RAM_SIZE,
	DEV_PARA_SYS_FLASH_SIZE,
    DEV_PARA_ROAP_ROOT_APP_ID,

    /*端口级参数*/
    DEV_PARA_OUTBAND_IF_NAME,
    DEV_PARA_OUTBAND_IF_ID_MIN,
    DEV_PARA_CPUIF_NUM,
    DEV_PARA_INBIND_HW_IF_NAME,
    DEV_PARA_MNG_HW_IF_NAME,
    DEV_PARA_PORT_MIN_MAC_NUM,
    DEV_PARA_PORT_MAX_MAC_NUM,
    DEV_PARA_PORT_NUM,
    DEV_PARA_MIN_GIGA_ID,
    DEV_PARA_MAX_GIGA_ID,
    DEV_PARA_AG_NUM,
    DEV_PARA_AG_MIN_ID,
    DEV_PARA_AG_MAX_ID,
    DEV_PARA_MAX_PORT_PER_AG,  /*每个聚合组支持的最大端口数目*/
    DEV_PARA_SW_NUM,
    DEV_PARA_SW_MIN_ID,
    DEV_PARA_SW_MAX_ID,
    DEV_PARA_OB_NUM,
    DEV_PARA_LO_NUM,
    DEV_PARA_VPORT_NUM,
    
    /*MAC地址表管理*/
    DEV_PARA_MAX_MAC,
    DEV_PARA_MIN_SYSTEM_MTU,
    DEV_PARA_MAX_SYSTEM_MTU,
    
    /*ACL参数*/
    DEV_PARA_ACL_MIN_L2_ACL_ID,
    DEV_PARA_ACL_MAX_L2_ACL_ID,
    DEV_PARA_ACL_MIN_IPV4_ACL_ID,
    DEV_PARA_ACL_MAX_IPV4_ACL_ID,
    DEV_PARA_ACL_MIN_IPV6_ACL_ID,
    DEV_PARA_ACL_MAX_IPV6_ACL_ID,
    DEV_PARA_ACL_MIN_HYBRID_ACL_ID,
    DEV_PARA_ACL_MAX_HYBRID_ACL_ID,
    DEV_PARA_ACL_MIN_IPV6_HYBRID_ACL_ID,
    DEV_PARA_ACL_MAX_IPV6_HYBRID_ACL_ID,
    DEV_PARA_ACL_MIN_USER_ACL_ID,
    DEV_PARA_ACL_MAX_USER_ACL_ID,
    DEV_PARA_ACL_MIN_ID,
    DEV_PARA_ACL_MAX_ID,
    DEV_PARA_ACL_MIN_RULE_ID,
    DEV_PARA_ACL_MAX_RULE_ID,
    DEV_PARA_USER_ACL_PROF_MIN_FIELD_ID,
    DEV_PARA_USER_ACL_PROF_MAX_FIELD_ID,

    /*QoS参数*/
    DEV_PARA_QOS_QUEUE_MIN_ID,
    DEV_PARA_QOS_QUEUE_MAX_ID,
    DEV_PARA_QOS_QUEUE_NUM,
    DEV_PARA_QOS_METER_MIN_ID,
    DEV_PARA_QOS_METER_MAX_ID,

    /*Filter参数*/
    DEV_PARA_FILTER_MIN_ID,
    DEV_PARA_FILTER_MAX_ID,

    /*QinQ参数*/
    DEV_PARA_QINQ_MIN_ACL_ID,
    DEV_PARA_QINQ_MAX_ACL_ID,
    DEV_PARA_QINQ_MIN_IPV6_ACL_ID,
    DEV_PARA_QINQ_MAX_IPV6_ACL_ID,
    DEV_PARA_QINQ_MIN_ACL_RULE_ID,
    DEV_PARA_QINQ_MAX_ACL_RULE_ID,
    
    /*虚接口参数*/
    DEV_PARA_QINQ_MAX_VP_SUPPORT,

    /*风暴抑制参数*/
    DEV_PARA_MIN_STORM_CONTROL_BPS,
    DEV_PARA_MAX_STORM_CONTROL_BPS,

    /*端口限速参数*/
    DEV_PARA_MIN_RATE_LIMIT_RATE,
    DEV_PARA_MAX_RATE_LIMIT_RATE,

    /*生成树*/
    DEV_PARA_MAX_STG_NUM,

    /*二层隔离*/
    DEV_PARA_MAX_ISOLATE_GROUP_NUM,
    DEV_PARA_MAX_VLAN_ISOLATE_GROUP_NUM,
    DEV_PARA_MAX_TOTAL_ISOLATE_GROUP_NUM,

    /*三层业务功能*/
    DEV_RM_IPV4_MAX_HW_HOST_NUM,
    DEV_RM_IPV4_MAX_HW_SUBNET_NUM,
    DEV_RM_IPV4_MAX_HW_ECMP_NUM,
    DEV_RM_IPV4_MAX_HW_ECMP_NH_NUM,
    DEV_RM_IPV4_MAX_ROUTE_NUM,
    DEV_SROUTE_IPV4_SMAXROUTENUM,
    DEV_RIP_IPV4_MAX_ROUTE_NUM,
    DEV_MAX_KEYCHAIN_NUM,
    DEV_LOOPBACK_VLAN,

	/*This must be last*/
	DEV_PARA_ID_LAST
};

enum
{
    /* 管理机框的驱动接口 */
	DEV_DRV_GET_SHELF_HARDWARE_VERSION = 1,
	DEV_DRV_GET_SHELF_SERIAL_NUM,
	DEV_DRV_SET_SYSTEM_MAC_ADDR,
	DEV_DRV_GET_SYSTEM_MAC_ADDR,

    /* 管理本板的驱动接口 */
	DEV_DRV_GET_SELF_SLOT_ID, /*0保留*/
	DEV_DRV_IS_CARD_WORKING,    /* 查询本盘是否处于工作状态。盒式固定为TRUE */
	DEV_DRV_IS_SLOT_WORKING,    /* 查询板卡是否处于工作状态 */
    DEV_DRV_CARD_GO_STANDBY,
	DEV_DRV_ENABLE_CU_HDLC,
	DEV_DRV_ENABLE_CU_ETH,
	DEV_DRV_GET_SOFTWARE_INFO,      /* 软件版本。 */
	DEV_DRV_GET_FIRMWARE_INFO,      /* 固件版本。 */
	DEV_DRV_FORMAT,


	DEV_DRV_GET_BASEBOOT_INFO,      /* 基本BOOT版本。 */
	DEV_DRV_GET_EXTBOOT_INFO,       /* 扩展BOOT版本。 */
	DEV_DRV_GET_SYSTEMHEAD_INFO,
	DEV_DRV_GET_ACTIVE_SOFTWARE_IMAGE_ID,  /* 当前运行的系统软件映像 */
	DEV_DRV_GET_ACTIVE_EXTBOOT_IMAGE_ID,   /* 当前运行的扩展BOOT映像 */
    DEV_DRV_GET_COMMIT_SOFTWARE_IMAGE_ID,  /* 当前提交的系统软件映像 */
	DEV_DRV_GET_COMMIT_EXTBOOT_IMAGE_ID,   /* 当前提交的扩展BOOT映像 */
	DEV_DRV_SET_COMMIT_SOFTWARE_IMAGE_ID,
    DEV_DRV_SET_COMMIT_EXTBOOT_IMAGE_ID,
    DEV_DRV_CPLD_WRITE,
    DEV_DRV_BASEBOOT_WRITE,
    DEV_DRV_MAINBOOT_READ,
    DEV_DRV_MAINBOOT_WRITE,
    DEV_DRV_MAINBOOT_BAK_READ,
    DEV_DRV_MAINBOOT_BAK_WRITE,
    DEV_DRV_GET_SOFTPACKAGE_ENABLE,
    DEV_DRV_GET_SOFTPACKAGE_NAME,
    DEV_DRV_SET_SOFTPACKAGE_ENABLE,
    DEV_DRV_SET_SOFTPACKAGE_NAME,
    DEV_DRV_RTC_INIT,
    DEV_DRV_RTC_GET_TIME,
    DEV_DRV_RTC_SET_TIME,
    DEV_DRV_GET_OUTBIND_LINKSTATE,
    DEV_DRV_GET_OUTBIND_DUPSPEED,
    /* 管理指定槽位单板的驱动接口 */
	DEV_DRV_CARD_IS_ONSITE,     /* 查询指定单板是否在位。本板固定为TRUE */
    DEV_DRV_IS_PEER_NMS_ONLINE,
	DEV_DRV_CARD_GET_MANUFACTURE,       /* 获取板卡产品信息。仅限单板管理模块使用。 */
	DEV_DRV_CARD_SET_MANUFACTURE,       /* 设置板卡产品信息。仅限单板管理模块使用。 */
	DEV_DRV_CARD_GET_TYPE,              /* 获取指定槽位的单板类型。仅限单板管理模块使用。其它模块应使用单板管理模块提供的接口 */
	DEV_DRV_CARD_GET_NAME,
	DEV_DRV_CARD_GET_HARDWARE_VERSION,  /* 获取板卡硬件版本信息。仅限单板管理模块使用。 */
	DEV_DRV_CARD_GET_SERIAL_NUM,        /* 获取板卡序列号信息。仅限单板管理模块使用。 */
	DEV_DRV_CARD_INSTALL,
	DEV_DRV_CARD_UNINSTALL,
	DEV_DRV_CARD_GET_CPLD_VERSION,      /* 获取板卡CPLD版本信息。 */
	DEV_DRV_CARD_RESET,
    DEV_DRV_CARD_INIT,
  	DEV_DRV_CARD_SET_POWER_SWITCH,
	DEV_DRV_CARD_GET_POWER_SWITCH,

    /* 管理CU通信的驱动接口 */
	DEV_DRV_GET_CU_COM_TYPE,    /* 查询指定单板与主控之间的管理通信类型 */
	DEV_DRV_GET_CU_INT,         /* 查询指定单板是否有上行通信请求 */
	DEV_DRV_MAKE_CU_INT,
	DEV_DRV_CLEAR_CU_INT,
	DEV_DRV_PREPARE_CU_FRAME_RECEPTION,
	DEV_DRV_SEND_CU_FRAME_HDLC,
	DEV_DRV_SEND_CU_FRAME_UART,
	
    /* 设备监控驱动接口 */
    
    DEV_DRV_DEV_MON_CAPABILITY,    
	DEV_DRV_CARD_GET_TEMPERATURE,
  	DEV_DRV_CARD_GET_POWER_INFO,
    
	DEV_DRV_FAN_GET_INFO,
	DEV_DRV_FAN_GET_DESC,
	DEV_DRV_FAN_SET_ALARM_LED_STATUS,
    DEV_DRV_FAN_SET_SPEED_GEAR,	
    DEV_DRV_FAN_GET_EEPROM_FEATURE,
    DEV_DRV_FAN_GET_MANUFACTURE,
    DEV_DRV_FAN_SET_MANUFACTURE,

    DEV_DRV_GET_POWER_INFO,
	DEV_DRV_GET_POWER_INT_INFO,
	DEV_DRV_GET_POWERMODULE_INFO,
	DEV_DRV_GET_CF_CARD_INFO,
	DEV_DRT_GET_BACKPLANE_BANDWIDTH,

    /* 管理环境监控板的驱动接口 */
	DEV_DRV_ENVIRON_SET_ALARM_LED,
	DEV_DRV_ENVIRON_SET_MON_ENABLE,
	DEV_DRV_ENVIRON_GET_PORT_STATUS,

    DEV_DRV_GET_PORT_TYPE,
    DEV_DRV_GET_BACKPLANE_INFO,
    DEV_DRV_GET_PORT_ENABLE_HOOK,
    DEV_DRV_GET_PORT_TRANSFER_ONLINE,
    DEV_DRV_WATCHDOG_ENABLE,
    DEV_DRV_WATCHDOG_RESET_TIME_SET,    
	/*This must be last*/
	DEV_DRV_ID_LAST
};

/* 单板管理通信协议类型 */
typedef enum
{
	E_CU_COM_HDLC = 1,
	E_CU_COM_UART,
	E_CU_COM_ETH,
	E_CU_COM_LOCAL,/* 主控直管，无软件通信协议 */
	E_CU_COM_UNKNOWN
} cuComType_t;



/*
板卡温度运行参数 底层获取
*/
typedef struct
{
    int temper;/*当前温度 单位 C*/
}card_temper_drv_t;

/*
板卡电压运行参数
*/

/*电压点枚举*/
typedef enum
{
    E_POWER_INVALID = -1,
    E_POWER_750MV = 0,  /*1*/
    E_POWER_900MV,      /*2*/
    E_POWER_1000MV ,    /*3*/

	E_POWER_1200MV,     /*4*/



	E_POWER_1500MV,     /*5*/

    E_POWER_1800MV,     /*6*/
	E_POWER_2500MV,     /*7*/

	E_POWER_3300MV,     /*8*/
	E_POWER_4800MV,     /*9*/
	E_POWER_5000MV,     /*10*/
	E_POWER_5200MV,     /*11*/
	E_POWER_12000MV,    /*12*/
    E_POWER_1070MV,     /*13*//*dj add impa vol*/
	E_POWER_1350MV,     /*14*//*dj add impa vol*/
	E_POWER_1780MV,     /*15*//*dj add impa vol*/
    E_POWER_1100MV,     
    E_POWER_2000MV,
    E_POWER_1350TO1500MV,
    E_POWER_500TO1300MV,
    E_POWER_500TO1300_1MV,
    E_POWER_1000_1MV,

	E_POWER_VCCP1,      /*unknown*/
	E_POWER_VCCP2 ,      /*null*/

    E_POWER_1250MV,     /*15*/
    E_POWER_2900MV,    /*16*/
    E_POWER_MAX_TYPE = E_POWER_2900MV,
    
} cardPowerType_t;

typedef struct
{
    ulong_t voltTypeNum;       /*监控点个数*/
    int ulVolType[16];     /*监控点类型 驱动类型,与mib类型相差1*/
    int ulVoltage[16];     /*监控点值*/
    
}card_volt_drv_t;

/*
风扇描述参数获取(静态属性)
*/
typedef struct
{    
    ulong_t maxSpeed; /*最大转速*/    
    ulong_t minSpeed; /*最小转速*/
    
    uchar_t subFanNum; /*子扇个数*/
    uchar_t maxGear;   /*最大档位*/
    uchar_t minGear;   /*最小档位*/
    uchar_t gearAtlowTemper; /*最低温度时取的档位*/
    
    uchar_t minTemper; /*最低温度阈值*/
    uchar_t maxTemper; /*最高温度阈值*/    
    uchar_t speedCtrlParam1; /*调速参数1*/
    uchar_t speedCtrlParam2; /*调速参数2*/
    
    uchar_t fanAlarmPrecent; /*允许的异常百分比*/
    uchar_t padding[3];
    
} fanDescDrv_t;


/*
风扇运行参数获取
*/
typedef struct
{    
    ulong_t subFanNum; /*子扇个数*/
    ulong_t isOnSite; /*T/F*/
    ulong_t curGear;  /*当前档位,目前所有子扇一致*/
    ulong_t speed[8]; /* 各个子扇风扇转速 目前定为8个 */
    
} fanDrv_t;

/*
电源板电源模块参数获取
*/

/*电源输入输出所有类型枚举*/
typedef enum
{
    E_POWER_VOLT_INVALID = -1,
    E_POWER_VOLT_3V = 0,
    E_POWER_VOLT_5V,
    E_POWER_VOLT_12V,
	E_POWER_VOLT_24V,
	E_POWER_VOLT_48V,
	E_POWER_VOLT_110V,
	E_POWER_VOLT_220V,
	E_POWER_VOLT_UNKNOWN,
	E_POWER_VOLT_TYPE_MAX=E_POWER_VOLT_UNKNOWN,
} POWET_VOLT_TYPE;

typedef struct
{
    POWET_VOLT_TYPE ulVoltType; /*电压类型*/
    ulong_t voltValue;  /*电压值*/

    uchar_t isValueGet;/*能否获取到电压值, 有值放置在voltValue中1:支持获取,0不支持*/    
  	uchar_t isAC; /*是否为交流电. 1交流，0直流*/
    uchar_t isOutput;/*输入还是输出 1输出 0输入*/
    uchar_t isNormal;/*是否正常 1 normal 0 abnormal*/   
    
} voltTypeDrvInfo_t;

typedef struct
{
    ulong_t voltTypeNum;     /*电压类型个数*/
    voltTypeDrvInfo_t voltTypeInfo[8];
} powerCardDrv_t;

typedef powerCardDrv_t powerModuleDrv_t;

/* 版本管理 */
#define CARD_VERSION_IMAGE_1   1
#define CARD_VERSION_IMAGE_2   2

typedef struct
{
    Byte bCommitted;        /*是否已提交*/
    Byte bActive;           /*是否为当前运行版本*/
    Byte  bVersion[64];     /*软件版本,最大长度64字节。*/
    DWord dwSize;           /*软件大小 */
    DWord dwUpdateTime;     /*软件升级时间*/
    Byte bValid;            /*是否合法*/
    Byte bReserve[3];       /*预留*/
}STRU_VERSION_INFO;

/* EEPROM Driver  */
#define EEPROM_LEN           1024

#define EEPROM_FRAME_START   0x95

#define EEPROM_PRODUCT_NAME_ID     0x01
#define EEPROM_PRODUCT_VERSION_ID  0x02
#define EEPROM_SERIAL_NO_ID        0x03
#define EEPROM_VENDOR_ID           0x04
#define EEPROM_MAC_ID              0x05

#define EEPROM_PRODUCT_NAME_LEN    32
#define EEPROM_PRODUCT_VERSION_LEN 8
#define EEPROM_SERIAL_NO_LEN       32
#define EEPROM_VENDOR_LEN          32
#define EEPROM_MAC_LEN             6
#define EEPROM_PCB_VERSION_LEN    8


typedef struct
{
    char eepromProductName[EEPROM_PRODUCT_NAME_LEN+1];
    char eepromProductVersion[EEPROM_PRODUCT_VERSION_LEN+1];
    char eepromSerialNo[EEPROM_SERIAL_NO_LEN+1];
    char eepromVendor[EEPROM_VENDOR_LEN+1];
    char eepromMac[EEPROM_MAC_LEN+1];
	char eepromPbcVersion[EEPROM_PCB_VERSION_LEN+1];  
    char eepromBoardName[EEPROM_PRODUCT_NAME_LEN+1];
}EepromCardParams;

#define FAN_MAX_SPEED_LEN           4
#define FAN_MIN_SPEED_LEN           4 
#define FAN_LOW_GEAR_TEMP_LEN       4
#define FAN_LOW_TEMP_LEN            4
#define FAN_HIGH_TEMP_LEN           4
#define FAN_PARAM_ONE_LEN           4
#define FAN_PARAM_TWO_LEN           4
#define FAN_PARAM_MAX_LEN           4 
#define FAN_THRESHOLD_PERCENT_LEN   4

typedef struct
{
    EepromCardParams eepromParams;
    char fanMaxSpeed[FAN_MAX_SPEED_LEN+1];           
    char fanMinSpeed[FAN_MIN_SPEED_LEN+1];        
    char fanLowGearTemp[FAN_LOW_GEAR_TEMP_LEN+1];       
    char fanLowTemp[FAN_LOW_TEMP_LEN+1];           
    char fanHighTemp[FAN_HIGH_TEMP_LEN+1];          
    char fanParamOne[FAN_PARAM_ONE_LEN+1];         
    char fanParamTwo[FAN_PARAM_TWO_LEN+1];          
    char fanParamMax[FAN_PARAM_MAX_LEN+1];
    char fanThresholdPercent[FAN_THRESHOLD_PERCENT_LEN+1]; 
}EepromFanParams;

typedef struct temp_vol_S
{
   unsigned int temp1_vol;
   unsigned int temp2_vol;
   unsigned int temp3_vol;
} temp_vol;

typedef enum
{
    MSG3600_BACKPLANE_3U=1,
    MSG3600_BACKPLANE_6U
}BACKPLANE_TYPE;

typedef enum{
	portType_unknown = 0,    	            /*未知端口类型*/
	portType_gigabitethernet_copper,		/*千兆电*/
	portType_gigabitethernet_fiber,			/*千兆光*/
	portType_gigabitethernet_combo,			/*千兆combo*/
	portType_gigabitethernet_epon,          /*千兆epon*/
	portType_gigabitethernet_gpon,          /*千兆gpon*/
	portType_tengigabitethernet_copper,		/*万兆电*/
	portType_tengigabitethernet_fiber, 		/*万兆光*/
	portType_tengigabitethernet_epon,       /*万兆epon*/
	portType_number			                /*端口类型数*/
} portType_t;

typedef struct calendar
{
    int tm_sec; 
    int tm_min; 
    int tm_hour; 
    int tm_mday; 
    int tm_mon; 
    int tm_year; 
    int tm_wday; 
    int tm_yday; 
    int tm_isdst; 
} CAL_CLOCK;

#endif /*__DEVICE_EXPO_H*/

