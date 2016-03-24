#include <i2cdev_core.h>

i2c_card_info_t r210i_i2c_mc_card_info = {
		.name = "R210I-MC",
		.slotid = SLOT_SMC,	
		.dev_array = {
			[I2CDEV_EEPROM] = {
				.card_info = &r210i_i2c_mc_card_info,
				.i2c_controler = 0,
				.dev_addr = {[0]=0x54, [1]=0x55, [2]=0x56, [3]=0x57},
				.read = i2c_eeprom_read,
				.write = i2c_eeprom_write,
			},
			[I2CDEV_RTC] = {
				.card_info = &r210i_i2c_mc_card_info,
				.i2c_controler = 0,
				.dev_addr = {[0]=0x51},
				.read = i2c_common_read,
				.write = i2c_common_write,
			},
			[I2CDEV_TMP] = {
				.card_info = &r210i_i2c_mc_card_info,
				.i2c_controler = 0,
				.dev_addr = {[0]=0x48},
				.read = i2c_common_read,
				.write = i2c_common_write,
			},
			[I2CDEV_WAN0_SFP] = {
				.card_info = &r210i_i2c_mc_card_info,
				.i2c_controler = 3,
				.dev_addr = {[0]=0x50},
				.read = i2c_common_read,
				.write = i2c_common_write,
			},
			[I2CDEV_WAN1_SFP] = {
				.card_info = &r210i_i2c_mc_card_info,
				.i2c_controler = 1,
				.dev_addr = {[0]=0x50},
				.read = i2c_common_read,
				.write = i2c_common_write,
			},
			[I2CDEV_MCU] = {
				.card_info = &r210i_i2c_mc_card_info,
				.i2c_controler = 1,
				.dev_addr = {[0]=0x50},
				.read = i2c_common_read,
				.write = i2c_common_write,
			},
		}
};
i2c_card_info_t r210i_i2c_sc_card_info = {
		.name = "R210I-SC",
		.slotid = SLOT_SUB,
		.card_type = CT_SC,
		.dev_array = {
			[I2CDEV_EEPROM] = {
				.card_info = &r210i_i2c_sc_card_info,
				.i2c_controler = 3,
				.dev_addr = {[0]=0x54, [1]=0x55, [2]=0x56, [3]=0x57},
				.read = i2c_eeprom_read,
				.write = i2c_eeprom_write,
			},
	}
}

int i2c_card_init()
{
	register_i2c_cardinfo(&r210i_i2c_mc_card_info);
	register_i2c_cardinfo(&r210i_i2c_sc_card_info);
	return 0;
}

