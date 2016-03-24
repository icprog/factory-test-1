#include "hal_api.h"

STRU_DEV_MON_CAPABILITY_DRV msg3100_mon_capability = {
    .isTemperMonSupp = 1,        /*�忨�¶ȼ��֧�� T/F*/
    .isCardPowerMonSupp = 1,     /*�忨��ѹ��� T/F*/
    .isFanMonSupp = 1,           /*���ȼ��֧�� T/F*/
    .isPwCardMonSupp = 1,        /*��Դ�̵�ѹ���֧�� T/F*/

    .isPwModuleMonSupp = 1,      /*��Դģ����֧�� T/F*/
    .isPwCardIntSupp = 1,        /*��Դ���ж���Ϣ��ȡ֧�� T/F*/
    .isPWRMCardSupp = 1,         /*�Ƿ�֧�����ܵ�Դ�� T/F*/
    .isFanSpeedSetSupp = 1,      /*�Ƿ�֧�ַ�����������*/
    
    .serviceSlotNumSupp = 1,     /*֧�ּ���ҵ��忨��λ*/    
    .fanNumSupp = 1,             /*֧�ּ�������*/
    .powerNumSupp = 1,           /*֧�ּ�����Դ��*/
    .powerModNumSupp = 1,        /*֧�ּ�����Դģ��*/
    
    .subFanNumSupp = 1,          /*һ�������ϼ������� Ŀǰһ���豸Ψһ*/
    .isPowerOffSupp = 1,         /*�豸���Ƿ��а忨֧���µ�����*/

};

fanDrv_t msg3100_fan = {
    .subFanNum = 1, /*���ȸ���*/
    .isOnSite = 1, /*T/F*/
    .curGear = 1,  /*��ǰ��λ,Ŀǰ��������һ��*/
    .speed = 
    {
    	[0] = 1,
		[1] = 1,
    }, /* �������ȷ���ת�� Ŀǰ��Ϊ8�� */
};

fanDescDrv_t msg3100_fan_desc = {
    .maxSpeed = 1, /*���ת��*/    
    .minSpeed = 1, /*��Сת��*/
    
    .subFanNum = 1, /*���ȸ���*/
    .maxGear = 1,   /*���λ*/
    .minGear = 1,   /*��С��λ*/
    .gearAtlowTemper = 1, /*����¶�ʱȡ�ĵ�λ*/
    
    .minTemper = 1, /*����¶���ֵ*/
    .maxTemper = 1, /*����¶���ֵ*/    
    .speedCtrlParam1 = 1, /*���ٲ���1*/
    .speedCtrlParam2 = 1, /*���ٲ���2*/
    
    .fanAlarmPrecent = 1, /*������쳣�ٷֱ�*/

};

powerCardDrv_t msg3100_powercard = {
	.voltTypeNum = 1,     /*��ѹ���͸���*/
    .voltTypeInfo = {
    [0] = {
		.ulVoltType = 1, /*��ѹ����*/
		.voltValue = 1,	/*��ѹֵ*/
		
		.isValueGet = 1,/*�ܷ��ȡ����ѹֵ, ��ֵ������voltValue��1:֧�ֻ�ȡ,0��֧��*/	
		.isAC = 1, /*�Ƿ�Ϊ������. 1������0ֱ��*/
		.isOutput = 1,/*���뻹����� 1��� 0����*/
		.isNormal = 1,/*�Ƿ����� 1 normal 0 abnormal*/	
		},
    },
};

	

