#include "hal_api.h"

STRU_DEV_MON_CAPABILITY_DRV msg3100_mon_capability = {
    .isTemperMonSupp = 1,        /*板卡温度监控支持 T/F*/
    .isCardPowerMonSupp = 1,     /*板卡电压监控 T/F*/
    .isFanMonSupp = 1,           /*风扇监控支持 T/F*/
    .isPwCardMonSupp = 1,        /*电源盘电压监控支持 T/F*/

    .isPwModuleMonSupp = 1,      /*电源模块监控支持 T/F*/
    .isPwCardIntSupp = 1,        /*电源盘中断信息获取支持 T/F*/
    .isPWRMCardSupp = 1,         /*是否支持智能电源盘 T/F*/
    .isFanSpeedSetSupp = 1,      /*是否支持风扇速率设置*/
    
    .serviceSlotNumSupp = 1,     /*支持几个业务板卡槽位*/    
    .fanNumSupp = 1,             /*支持几个风扇*/
    .powerNumSupp = 1,           /*支持几个电源板*/
    .powerModNumSupp = 1,        /*支持几个电源模块*/
    
    .subFanNumSupp = 1,          /*一个风扇上几个子扇 目前一种设备唯一*/
    .isPowerOffSupp = 1,         /*设备上是否有板卡支持下电设置*/

};

fanDrv_t msg3100_fan = {
    .subFanNum = 1, /*子扇个数*/
    .isOnSite = 1, /*T/F*/
    .curGear = 1,  /*当前档位,目前所有子扇一致*/
    .speed = 
    {
    	[0] = 1,
		[1] = 1,
    }, /* 各个子扇风扇转速 目前定为8个 */
};

fanDescDrv_t msg3100_fan_desc = {
    .maxSpeed = 1, /*最大转速*/    
    .minSpeed = 1, /*最小转速*/
    
    .subFanNum = 1, /*子扇个数*/
    .maxGear = 1,   /*最大档位*/
    .minGear = 1,   /*最小档位*/
    .gearAtlowTemper = 1, /*最低温度时取的档位*/
    
    .minTemper = 1, /*最低温度阈值*/
    .maxTemper = 1, /*最高温度阈值*/    
    .speedCtrlParam1 = 1, /*调速参数1*/
    .speedCtrlParam2 = 1, /*调速参数2*/
    
    .fanAlarmPrecent = 1, /*允许的异常百分比*/

};

powerCardDrv_t msg3100_powercard = {
	.voltTypeNum = 1,     /*电压类型个数*/
    .voltTypeInfo = {
    [0] = {
		.ulVoltType = 1, /*电压类型*/
		.voltValue = 1,	/*电压值*/
		
		.isValueGet = 1,/*能否获取到电压值, 有值放置在voltValue中1:支持获取,0不支持*/	
		.isAC = 1, /*是否为交流电. 1交流，0直流*/
		.isOutput = 1,/*输入还是输出 1输出 0输入*/
		.isNormal = 1,/*是否正常 1 normal 0 abnormal*/	
		},
    },
};

	

