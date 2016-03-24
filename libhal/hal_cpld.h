#define CPLD_VERSION_REG 0x00
#define CPLD_RESET_REG 0x01
#define CPLD_LED1_REG 0x02
#define CPLD_LED2_REG 0x03
#define CPLD_WD_SETTING_REG 0x04
#define CPLD_WD_CLEAR_REG 0x05
#define CPLD_FAN_CTRL_REG 0x06
#define CPLD_FAN1_SPEED_REG 0x07
#define CPLD_FAN2_SPEED_REG 0x08
#define CPLD_FAN3_SPEED_REG 0x09
#define CPLD_BUS_SWITCH_REG 0x0A
#define CPLD_SUBCARD_ON_REG 0x0B
#define CPLD_SFP_CTRL_REG 0x0C
#define CPLD_INT_STATE1_REG 0x0D
#define CPLD_INT_MASK1_REG 0x0E
#define CPLD_INT_STATE2_REG 0x0F
#define CPLD_INT_MASK2_REG 0x10
#define CPLD_IMP_GPIO_DATA_REG 0x11
#define CPLD_IMP_GPIO_DIR_REG 0x12
#define CPLD_FXS_OLT_GPIO_DATA_REG 0x13
#define CPLD_FXS_OLT_GPIO_DIR_REG 0x14

#define CPLD_IMP_RESET_BIT         0x0
#define CPLD_VOIP_OLT_RESET_BIT    0x1
#define CPLD_FXO_E1_RESET_BIT      0x2
#define CPLD_DSP_RESET_BIT         0x3
#define CPLD_LAN_PHY_RESET_BIT     0x4
#define CPLD_SWITCH_RESET_BIT      0x5
#define CPLD_WAN_RESET_BIT         0x6
#define CPLD_SYS_RESET_BIT         0x7

int hal_cpld_read(int slot, unsigned char *data, int offset, int len);
int hal_cpld_write(int slot, unsigned char *data, int offset, int len);


