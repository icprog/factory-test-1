/*definition of led*/
#define LED_WIFI_NUM               0          //wifi led
#define LED_USB2_NUM               1          //usb port 2 led
#define LED_USB1_NUM               2          //usb port 1 led
#define LED_3G_NUM                 3          // 3g module/data card status led
#define LED_MGNT_NUM               4
#define LED_SYS_NUM                5          //system led
#define LED_VPN_NUM                6
#define LED_STU_NUM                7
#define LED_LPB_NUM                8
#define LED_SHDSL1_STU_NUM             9
#define LED_SHDSL2_STU_NUM             10
#define LED_SERIAL_MODE_NUM        11         //serial mode led
#define LED_3G_SIGNAL0_NUM         12         // 3g signal strength led0
#define LED_3G_SIGNAL1_NUM         13         // 3g signal strength led1
#define LED_3G_SIGNAL2_NUM         14         // 3g signal strength led2
#define LED_WPS1_NUM               15
#define LED_WPS2_NUM               16
#define LED_PON_NUM               17        //gpon or epon
#define LED_LOS_NUM                18
#define LED_INTERNET_NUM           19
#define GPIO_PON_TX_ENABLE		   20
#define LED_P2P_RX_TX_NUM		   21
#define LED_SHDSL3_STU_NUM             22                       
#define LED_SHDSL4_STU_NUM             23
#define LED_SHDSL1_LINK_NUM             24
#define LED_SHDSL2_LINK_NUM             25
#define LED_SHDSL3_LINK_NUM             26
#define LED_SHDSL4_LINK_NUM             27
#define LED_WIFI2_NUM             28
#define LED_MAX_NUM                29

/*definition of led state*/
#define LED_OFF                      0x00000000
#define LED_RED_ON                   0x00000001
#define LED_GREEN_ON                 0x00000002
#define LED_RED_FAST_BLINK_ON        0x00000004
#define LED_RED_FAST_BLINK_OFF       0x00000008  
#define LED_GREEN_FAST_BLINK_ON      0x00000010
#define LED_GREEN_FAST_BLINK_OFF     0x00000020
#define LED_RED_SLOW_BLINK_ON        0x00000040
#define LED_RED_SLOW_BLINK_OFF       0x00000080
#define LED_GREEN_SLOW_BLINK_ON      0x00000100
#define LED_GREEN_SLOW_BLINK_OFF     0x00000200
#define LED_RED_FAST_FLASH           0x00000400
#define LED_GREEN_FAST_FLASH         0x00000800
#define LED_RED_SLOW_FLASH           0x00001000
#define LED_GREEN_SLOW_FLASH         0x00002000
#define LED_STATE_INVALID            0xFFFFFFFF

#define LED_WPS_START                 0x00004000
#define LED_WPS_END                   0x00008000
#define LED_WPS_SUCCESS               0x00010000
#define LED_WPS_ERROR                 0x00020000
#define LED_WPS_MUL_USERS             0x00040000


/*led state mask*/
#define LED_RED_MASK       (LED_RED_ON | LED_RED_FAST_BLINK_ON |\
	                    LED_RED_FAST_BLINK_OFF | LED_RED_SLOW_BLINK_ON | LED_RED_SLOW_BLINK_OFF |\
	                    LED_RED_FAST_FLASH | LED_RED_SLOW_FLASH) 
	                                   
#define LED_GREEN_MASK     (LED_GREEN_ON | LED_GREEN_FAST_BLINK_ON |\
	                    LED_GREEN_FAST_BLINK_OFF | LED_GREEN_SLOW_BLINK_ON | LED_GREEN_SLOW_BLINK_OFF |\
	                    LED_GREEN_FAST_FLASH | LED_GREEN_SLOW_FLASH) 	 
	                                   
#define LED_FAST_MASK      (LED_RED_FAST_BLINK_ON | LED_RED_FAST_BLINK_OFF | LED_RED_FAST_FLASH |\
	                    LED_GREEN_FAST_BLINK_ON | LED_GREEN_FAST_BLINK_OFF | LED_GREEN_FAST_FLASH)

#define LED_SLOW_MASK      (LED_RED_SLOW_BLINK_ON | LED_RED_SLOW_BLINK_OFF | LED_RED_SLOW_FLASH |\
	                    LED_GREEN_SLOW_BLINK_ON | LED_GREEN_SLOW_BLINK_OFF | LED_GREEN_SLOW_FLASH)

#define LED_BLINK_ON_MASK  (LED_RED_FAST_BLINK_ON | LED_RED_SLOW_BLINK_ON |\
	                    LED_GREEN_FAST_BLINK_ON | LED_GREEN_SLOW_BLINK_ON)

#define LED_BLINK_OFF_MASK (LED_RED_FAST_BLINK_OFF | LED_RED_SLOW_BLINK_OFF |\
	                    LED_GREEN_FAST_BLINK_OFF | LED_GREEN_SLOW_BLINK_OFF)

#define LED_FLASH_MASK     (LED_RED_FAST_FLASH | LED_RED_SLOW_FLASH | \
	                    LED_GREEN_FAST_FLASH | LED_GREEN_SLOW_FLASH)
	                                 
#define LED_STATE_INVALID_MASK  0xffffc000

/*definition for leds' flash and blink state*/
#define LED_BLINK_NUM                      6          //调用一次blink闪烁次数
#define LED_FLASH_ALWAYS               0xff     //flash状态，永远闪烁
#define LED_FAST_BLINK_PERIOD        1          //LED灯快速闪烁的周期
#define LED_SLOW_BLINK_PERIOD       10        //LED灯慢速闪烁的周期

#define MAX_REG_GROUP 16

/*led pin polarity*/
enum
{
    POLAR_REVERSE = 0, /*gpio output 0 to light on led*/
    POLAR_NORMAL,      /*gpio output 1 to light on led*/  
};

enum {
	LED_GPIO = 0,
	LED_CPLD,
	LED_GROUP_END,
};

enum {
	LED_RED = 0,
	LED_GREEN,
	LED_COLOR_END,
};


struct led_s {
    int index;
    int state;                       //led的状态
    int type;//led类型:GPIO or CPLD
    unsigned long jiffies;        //记录操作led时的jiffies
    unsigned char activate;    //标志该led灯是否有效,1有效，0无效
		
    /*members for led controlled by GPIO*/
    unsigned char polarity;    //POLAR_REVERSE为低电平灯亮，POLAR_NORMAL为高电平灯亮
    unsigned char red_pin;    //红色led对应的gpio引脚
    unsigned char grn_pin;    //绿色led对应的gpio引脚
    unsigned char pin;          //存储当前操作的gpio引脚
    unsigned char flash;       //led闪烁次数，LED_FLASH_AWAYS为永久闪烁，0为不闪烁

    /*members for led controlled by CPLD, currently for MSG2100 product*/
    unsigned char addr;       //led在CPLD中的地址
    unsigned char offset;     //led在CPLD寄存器中的偏移
    unsigned char mask;      //led在CPLD寄存器中的掩码值  
};

/* end LED */

