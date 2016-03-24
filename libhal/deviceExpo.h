/************************************************************************/
/*    ��˹����Ƽ���չ���޹�˾          ��Ȩ����						*/
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
/*   �����ļ�����deviceExpo.h					                        */
/*   Filename  ��deviceExpo.h					                        */
/*   ����      ���ߺ�ΰ							                        */
/*   Author    ��gaohongwei						                        */
/*   ����      ��12/07/2008						                        */
/*   Date      ��12/07/2008						                        */
/*   �汾      ��1.0							                        */
/*   Version   ��1.0                                                    */
/*   ʵ��Ŀ��  ���豸������Ϣ��������                                   */
/*   Purpose   ��                                                       */
/************************************************************************/
/*�޸ļ�¼*/
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


/*�豸�����ض���*/
/*
�豸���ȫ������ Ӳ�����Ƿ�֧�ֵ�
*/
typedef struct
{
    uchar_t isTemperMonSupp;        /*�忨�¶ȼ��֧�� T/F*/
    uchar_t isCardPowerMonSupp;     /*�忨��ѹ��� T/F*/
    uchar_t isFanMonSupp;           /*���ȼ��֧�� T/F*/
    uchar_t isPwCardMonSupp;        /*��Դ�̵�ѹ���֧�� T/F*/
    
    uchar_t isPwModuleMonSupp;      /*��Դģ����֧�� T/F*/
    uchar_t isPwCardIntSupp;        /*��Դ���ж���Ϣ��ȡ֧�� T/F*/
    uchar_t isPWRMCardSupp;         /*�Ƿ�֧�����ܵ�Դ�� T/F*/
    uchar_t isFanSpeedSetSupp;      /*�Ƿ�֧�ַ�����������*/
    
    uchar_t serviceSlotNumSupp;     /*֧�ּ���ҵ��忨��λ*/    
    uchar_t fanNumSupp;             /*֧�ּ�������*/
    uchar_t powerNumSupp;           /*֧�ּ�����Դ��*/
    uchar_t powerModNumSupp;        /*֧�ּ�����Դģ��*/
    
    uchar_t subFanNumSupp;          /*һ�������ϼ������� Ŀǰһ���豸Ψһ*/
    uchar_t isPowerOffSupp;         /*�豸���Ƿ��а忨֧���µ�����*/
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
    /*0����*/
    /* �豸/����Ӳ������ */
    /* �豸���� */
	DEV_PARA_DEVICE_TYPE = 1,       /* �豸���ͱ��� */
	DEV_PARA_DEVICE_IS_SHELF,       /*����ʽΪtrue����ʽΪfalse*/
	DEV_PARA_CF_SUPPORT,            /*cf��֧��*/
	DEV_PARA_DOUBLEIMAGE_SUPPORT,   /*˫����֧��*/
	DEV_PARA_DEVICE_TYPE_NAME,      /* �豸�������� */
	DEV_PARA_PRODUCT_VERSION,      /*��Ʒ�汾*/
	DEV_PARA_SLOT_ID_MIN,/*������С��λID*/
	DEV_PARA_SLOT_ID_MAX,/*��������λID*/
	DEV_PARA_SERVICE_SLOT_ID_MIN,   /* �豸��С��λID��������+�ӿ��̲�λ��������Դ�̡������� */
	DEV_PARA_SERVICE_SLOT_ID_MAX,   /* �豸����λID */
	DEV_PARA_SMC_PRIMARY_SLOT_ID,   /* �������ء���˫���ػ����£������ӵ�����ʱ�������ش��ڹ���״̬ */
	DEV_PARA_SMC_SECONDARY_SLOT_ID, /* �������ء��Խ�����һ�����ص��豸��ȡֵӦ < 0 */
	DEV_PARA_BACKPLANE_BANDWIDTH,   /* ������� */
    DEV_SLOT_PROVISIONABLE_BITMAP,  /*�ɴ�����������*/
    DEV_SLOT_BITMAP,
    
    DEV_PARA_ENVIRON_SLOT_MIN,      /*֧�ֻ�����ص���С��λID*/
    DEV_PARA_ENVIRON_SLOT_MAX,      /*֧�ֻ�����ص�����λID*/
    DEV_PARA_ENVIRON_PORT_NUM,      /*ÿ����λ֧�ֻ�����صĶ˿���*/
    DEV_PARA_ENVIRON_PORT_MIN,      /*ÿ����λ֧�ֻ�����صĶ˿���СID*/
    DEV_PARA_QTAG_SIZE,             /*802.1Q tag���ȣ��ֽ���*/
    /*ϵͳʱ��*/
    DEV_PARA_TZ_OFFSET_DIRCTION,   /*ʱ��ƫ�Ʒ�����Ϊ0������Ϊ1*/
    DEV_PARA_TZ_OFFSET_HOUR,       /*ʱ��ƫ�Ƶ�Сʱ��              */

    /*ϵͳ���*/
    DEV_PARA_MEMORY_SIZE,           /*���ذ��ڴ��С*/    
    DEV_PARA_MEMORY_MAX_THRESHOLD_SIZE, /*�ڴ�澯��ֵ�����ֵ*/

    /*�豸���ģ�����*/
    DEV_PARA_POWER_MIN_SLOT_ID,
    DEV_PARA_POWER_MAX_SLOT_ID,
    DEV_PARA_POWER_MODULE_MIN_ID,
    DEV_PARA_POWER_MODULE_MAX_ID,
    
    DEV_PARA_FAN_MIN_SLOT_ID,
    DEV_PARA_FAN_MAX_SLOT_ID,
    DEV_PARA_FAN_SPEED_GEAR_LOW,
    DEV_PARA_FAN_SPEED_GEAR_HIGH,

    /* �豸/����������� */
	DEV_PARA_SOFTWARE_NAME_FULL,    /* ���ȫ���� */
	DEV_PARA_SOFTWARE_NAME_SHORT,   /* �����ơ� */
	DEV_PARA_VENDOR_NAME_FULL,      /* ����ȫ�ơ� */
	DEV_PARA_VENDOR_NAME_SHORT,     /* ���̼��  */
	DEV_PARA_VENDOR_ID,             /* ����ID��RAISECOM����IDΪ0x52430000  */
	DEV_PARA_USER_NAME_DEFAULT,     /* ȱʡ�û���������CLI��SNMP�ȡ� */
	DEV_PARA_USER_PASSWORD_DEFAULT, /* ȱʡ�û����롣����CLI��SNMP�ȡ� */

    /* �忨������ */
	DEV_PARA_SYS_RAM_SIZE,
	DEV_PARA_SYS_FLASH_SIZE,
    DEV_PARA_ROAP_ROOT_APP_ID,

    /*�˿ڼ�����*/
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
    DEV_PARA_MAX_PORT_PER_AG,  /*ÿ���ۺ���֧�ֵ����˿���Ŀ*/
    DEV_PARA_SW_NUM,
    DEV_PARA_SW_MIN_ID,
    DEV_PARA_SW_MAX_ID,
    DEV_PARA_OB_NUM,
    DEV_PARA_LO_NUM,
    DEV_PARA_VPORT_NUM,
    
    /*MAC��ַ�����*/
    DEV_PARA_MAX_MAC,
    DEV_PARA_MIN_SYSTEM_MTU,
    DEV_PARA_MAX_SYSTEM_MTU,
    
    /*ACL����*/
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

    /*QoS����*/
    DEV_PARA_QOS_QUEUE_MIN_ID,
    DEV_PARA_QOS_QUEUE_MAX_ID,
    DEV_PARA_QOS_QUEUE_NUM,
    DEV_PARA_QOS_METER_MIN_ID,
    DEV_PARA_QOS_METER_MAX_ID,

    /*Filter����*/
    DEV_PARA_FILTER_MIN_ID,
    DEV_PARA_FILTER_MAX_ID,

    /*QinQ����*/
    DEV_PARA_QINQ_MIN_ACL_ID,
    DEV_PARA_QINQ_MAX_ACL_ID,
    DEV_PARA_QINQ_MIN_IPV6_ACL_ID,
    DEV_PARA_QINQ_MAX_IPV6_ACL_ID,
    DEV_PARA_QINQ_MIN_ACL_RULE_ID,
    DEV_PARA_QINQ_MAX_ACL_RULE_ID,
    
    /*��ӿڲ���*/
    DEV_PARA_QINQ_MAX_VP_SUPPORT,

    /*�籩���Ʋ���*/
    DEV_PARA_MIN_STORM_CONTROL_BPS,
    DEV_PARA_MAX_STORM_CONTROL_BPS,

    /*�˿����ٲ���*/
    DEV_PARA_MIN_RATE_LIMIT_RATE,
    DEV_PARA_MAX_RATE_LIMIT_RATE,

    /*������*/
    DEV_PARA_MAX_STG_NUM,

    /*�������*/
    DEV_PARA_MAX_ISOLATE_GROUP_NUM,
    DEV_PARA_MAX_VLAN_ISOLATE_GROUP_NUM,
    DEV_PARA_MAX_TOTAL_ISOLATE_GROUP_NUM,

    /*����ҵ����*/
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
    /* �������������ӿ� */
	DEV_DRV_GET_SHELF_HARDWARE_VERSION = 1,
	DEV_DRV_GET_SHELF_SERIAL_NUM,
	DEV_DRV_SET_SYSTEM_MAC_ADDR,
	DEV_DRV_GET_SYSTEM_MAC_ADDR,

    /* ������������ӿ� */
	DEV_DRV_GET_SELF_SLOT_ID, /*0����*/
	DEV_DRV_IS_CARD_WORKING,    /* ��ѯ�����Ƿ��ڹ���״̬����ʽ�̶�ΪTRUE */
	DEV_DRV_IS_SLOT_WORKING,    /* ��ѯ�忨�Ƿ��ڹ���״̬ */
    DEV_DRV_CARD_GO_STANDBY,
	DEV_DRV_ENABLE_CU_HDLC,
	DEV_DRV_ENABLE_CU_ETH,
	DEV_DRV_GET_SOFTWARE_INFO,      /* ����汾�� */
	DEV_DRV_GET_FIRMWARE_INFO,      /* �̼��汾�� */
	DEV_DRV_FORMAT,


	DEV_DRV_GET_BASEBOOT_INFO,      /* ����BOOT�汾�� */
	DEV_DRV_GET_EXTBOOT_INFO,       /* ��չBOOT�汾�� */
	DEV_DRV_GET_SYSTEMHEAD_INFO,
	DEV_DRV_GET_ACTIVE_SOFTWARE_IMAGE_ID,  /* ��ǰ���е�ϵͳ���ӳ�� */
	DEV_DRV_GET_ACTIVE_EXTBOOT_IMAGE_ID,   /* ��ǰ���е���չBOOTӳ�� */
    DEV_DRV_GET_COMMIT_SOFTWARE_IMAGE_ID,  /* ��ǰ�ύ��ϵͳ���ӳ�� */
	DEV_DRV_GET_COMMIT_EXTBOOT_IMAGE_ID,   /* ��ǰ�ύ����չBOOTӳ�� */
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
    /* ����ָ����λ����������ӿ� */
	DEV_DRV_CARD_IS_ONSITE,     /* ��ѯָ�������Ƿ���λ������̶�ΪTRUE */
    DEV_DRV_IS_PEER_NMS_ONLINE,
	DEV_DRV_CARD_GET_MANUFACTURE,       /* ��ȡ�忨��Ʒ��Ϣ�����޵������ģ��ʹ�á� */
	DEV_DRV_CARD_SET_MANUFACTURE,       /* ���ð忨��Ʒ��Ϣ�����޵������ģ��ʹ�á� */
	DEV_DRV_CARD_GET_TYPE,              /* ��ȡָ����λ�ĵ������͡����޵������ģ��ʹ�á�����ģ��Ӧʹ�õ������ģ���ṩ�Ľӿ� */
	DEV_DRV_CARD_GET_NAME,
	DEV_DRV_CARD_GET_HARDWARE_VERSION,  /* ��ȡ�忨Ӳ���汾��Ϣ�����޵������ģ��ʹ�á� */
	DEV_DRV_CARD_GET_SERIAL_NUM,        /* ��ȡ�忨���к���Ϣ�����޵������ģ��ʹ�á� */
	DEV_DRV_CARD_INSTALL,
	DEV_DRV_CARD_UNINSTALL,
	DEV_DRV_CARD_GET_CPLD_VERSION,      /* ��ȡ�忨CPLD�汾��Ϣ�� */
	DEV_DRV_CARD_RESET,
    DEV_DRV_CARD_INIT,
  	DEV_DRV_CARD_SET_POWER_SWITCH,
	DEV_DRV_CARD_GET_POWER_SWITCH,

    /* ����CUͨ�ŵ������ӿ� */
	DEV_DRV_GET_CU_COM_TYPE,    /* ��ѯָ������������֮��Ĺ���ͨ������ */
	DEV_DRV_GET_CU_INT,         /* ��ѯָ�������Ƿ�������ͨ������ */
	DEV_DRV_MAKE_CU_INT,
	DEV_DRV_CLEAR_CU_INT,
	DEV_DRV_PREPARE_CU_FRAME_RECEPTION,
	DEV_DRV_SEND_CU_FRAME_HDLC,
	DEV_DRV_SEND_CU_FRAME_UART,
	
    /* �豸��������ӿ� */
    
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

    /* ��������ذ�������ӿ� */
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

/* �������ͨ��Э������ */
typedef enum
{
	E_CU_COM_HDLC = 1,
	E_CU_COM_UART,
	E_CU_COM_ETH,
	E_CU_COM_LOCAL,/* ����ֱ�ܣ������ͨ��Э�� */
	E_CU_COM_UNKNOWN
} cuComType_t;



/*
�忨�¶����в��� �ײ��ȡ
*/
typedef struct
{
    int temper;/*��ǰ�¶� ��λ C*/
}card_temper_drv_t;

/*
�忨��ѹ���в���
*/

/*��ѹ��ö��*/
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
    ulong_t voltTypeNum;       /*��ص����*/
    int ulVolType[16];     /*��ص����� ��������,��mib�������1*/
    int ulVoltage[16];     /*��ص�ֵ*/
    
}card_volt_drv_t;

/*
��������������ȡ(��̬����)
*/
typedef struct
{    
    ulong_t maxSpeed; /*���ת��*/    
    ulong_t minSpeed; /*��Сת��*/
    
    uchar_t subFanNum; /*���ȸ���*/
    uchar_t maxGear;   /*���λ*/
    uchar_t minGear;   /*��С��λ*/
    uchar_t gearAtlowTemper; /*����¶�ʱȡ�ĵ�λ*/
    
    uchar_t minTemper; /*����¶���ֵ*/
    uchar_t maxTemper; /*����¶���ֵ*/    
    uchar_t speedCtrlParam1; /*���ٲ���1*/
    uchar_t speedCtrlParam2; /*���ٲ���2*/
    
    uchar_t fanAlarmPrecent; /*������쳣�ٷֱ�*/
    uchar_t padding[3];
    
} fanDescDrv_t;


/*
�������в�����ȡ
*/
typedef struct
{    
    ulong_t subFanNum; /*���ȸ���*/
    ulong_t isOnSite; /*T/F*/
    ulong_t curGear;  /*��ǰ��λ,Ŀǰ��������һ��*/
    ulong_t speed[8]; /* �������ȷ���ת�� Ŀǰ��Ϊ8�� */
    
} fanDrv_t;

/*
��Դ���Դģ�������ȡ
*/

/*��Դ���������������ö��*/
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
    POWET_VOLT_TYPE ulVoltType; /*��ѹ����*/
    ulong_t voltValue;  /*��ѹֵ*/

    uchar_t isValueGet;/*�ܷ��ȡ����ѹֵ, ��ֵ������voltValue��1:֧�ֻ�ȡ,0��֧��*/    
  	uchar_t isAC; /*�Ƿ�Ϊ������. 1������0ֱ��*/
    uchar_t isOutput;/*���뻹����� 1��� 0����*/
    uchar_t isNormal;/*�Ƿ����� 1 normal 0 abnormal*/   
    
} voltTypeDrvInfo_t;

typedef struct
{
    ulong_t voltTypeNum;     /*��ѹ���͸���*/
    voltTypeDrvInfo_t voltTypeInfo[8];
} powerCardDrv_t;

typedef powerCardDrv_t powerModuleDrv_t;

/* �汾���� */
#define CARD_VERSION_IMAGE_1   1
#define CARD_VERSION_IMAGE_2   2

typedef struct
{
    Byte bCommitted;        /*�Ƿ����ύ*/
    Byte bActive;           /*�Ƿ�Ϊ��ǰ���а汾*/
    Byte  bVersion[64];     /*����汾,��󳤶�64�ֽڡ�*/
    DWord dwSize;           /*�����С */
    DWord dwUpdateTime;     /*�������ʱ��*/
    Byte bValid;            /*�Ƿ�Ϸ�*/
    Byte bReserve[3];       /*Ԥ��*/
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
	portType_unknown = 0,    	            /*δ֪�˿�����*/
	portType_gigabitethernet_copper,		/*ǧ�׵�*/
	portType_gigabitethernet_fiber,			/*ǧ�׹�*/
	portType_gigabitethernet_combo,			/*ǧ��combo*/
	portType_gigabitethernet_epon,          /*ǧ��epon*/
	portType_gigabitethernet_gpon,          /*ǧ��gpon*/
	portType_tengigabitethernet_copper,		/*���׵�*/
	portType_tengigabitethernet_fiber, 		/*���׹�*/
	portType_tengigabitethernet_epon,       /*����epon*/
	portType_number			                /*�˿�������*/
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

