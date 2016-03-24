#define MSG3100_SLOT_MAX 4
#define I2CDELAY         5*1000                          // 5ms 

#define MAX_ADDR_ARRAY_NUM 4
#define EEPROM_PAGE_WRITE_SIZE 16

#define PCA9555_IN_PORT0 0x0
#define PCA9555_IN_PORT1 0x1
#define PCA9555_OUT_PORT0 0x2
#define PCA9555_OUT_PORT1 0x3
#define PCA9555_POL_PORT0 0x4
#define PCA9555_POL_PORT1 0x5
#define PCA9555_CONF_PORT0 0x6
#define PCA9555_CONF_PORT1 0x7

typedef enum{
    INVALID_SLOT = -1,
	SLOT_SMC = 0,
    SLOT1,
    SLOT2,
    SLOT3,
    SLOT4,
    SLOT5,
    SLOT6,
    SLOT7,
    SLOT8,
    SLOT9,
    SLOT10,
    SLOT11,
    SLOT12,
    SLOT13,
	SLOT_POWER1,
	SLOT_POWER2,
    SLOT_FAN,
    SLOT_BKPA,
	SLOT_SUB,

    MAXSLOT,
}SLOT_T;
typedef enum{
	CT_MC = 0,
	CT_SC,
	CT_MAX,
} card_type_t;

typedef enum{
	I2CDEV_EEPROM = 0,
	I2CDEV_RTC,
	I2CDEV_TMP,
	I2CDEV_POWERMON,
	I2CDEV_PCA9555,
	I2CDEV_WAN0_SFP,
	I2CDEV_WAN1_SFP,
	I2CDEV_LAN0_SFP,
	I2CDEV_MAX,
} i2c_dev_type_t;

typedef enum{
	CASCADE_0 = 0,
	CASCADE_1,
	MAX_CASCADE_CHANNEL_CHIP,
} cascade_channel_t;


/*描述一个i2c设备地址的数据结构*/
typedef union i2c_dev_addr_u {
	unsigned char addr_array[MAX_ADDR_ARRAY_NUM];//一个I2C设备可能存在多个地址，例如eeprom
	int addr;//一个i2c设备通常对应一个i2c地址
} i2c_dev_addr_t;

/*描述一个i2c通道选择芯片的数据结构*/
typedef struct channel_chip_s
{
	char *name;//芯片名称
	int dev_addr;//芯片的i2c地址
	int (*channel_switch)(struct channel_chip_s *chip, int fd, unsigned char channel);//通道切换的回调函数
} channel_chip_t;

struct i2c_card_info_s;
/*单个i2c设备数据结构*/
typedef struct i2c_dev_info_s {
	char *name;
	struct i2c_card_info_s *card_info;
	int i2c_controler;//该设备对应的i2c控制器编号
	int dev_addr[MAX_ADDR_ARRAY_NUM];//该设备的i2c地址
	int cascade_channel[MAX_CASCADE_CHANNEL_CHIP];//通道号数组
	channel_chip_t *channel_route;//主控板到该设备的通道路由
	int (*read) (struct i2c_dev_info_s *dev, void *data, int offset, int size);
	int (*write) (struct i2c_dev_info_s *dev, void *data, int offset, int size);
} i2c_dev_info_t;

/*描述每个板卡上所有I2C设备的数据结构*/
typedef struct i2c_card_info_s {
	char *name;
	int slotid;
	int card_type;
	i2c_dev_info_t dev_array[I2CDEV_MAX];//每个板卡上可以存在多个I2C设备
} i2c_card_info_t;

extern struct i2c_card_info_s *i2c_cards[MAXSLOT];

int i2cdev_read(SLOT_T slot, int dev_type, void *data, int offset, int size);
int i2cdev_write(SLOT_T slot, int dev_type, void *data, int offset, int size);

