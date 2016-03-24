#include <i2cdev_core.h>

struct i2c_card_info_s *i2c_cards[MAXSLOT];

int register_i2c_cardinfo(struct i2c_card_info_s *cardinfo)
{
	if(!cardinfo)
		return -1;
	i2c_cards[cardinfo->slotid] = cardinfo;
	return 0;
}
struct i2c_dev_info_s *get_devinfo_by_devtype(SLOT_T slot, int dev_type)
{
	struct i2c_card_info_s *cardinfo;
	struct i2c_dev_info_s *devinfo;
	cardinfo = i2c_cards[slot];
	devinfo = cardinfo->dev_array[dev_type];
	return devinfo;
}
int i2cdev_read(SLOT_T slot, int dev_type, void *data, int offset, int size)
{
	struct i2c_dev_info_s *devinfo = NULL;
	devinfo = get_devinfo_by_devtype(slot, dev_type);
	return devinfo->read(devinfo, data, offset, size);
}
int i2cdev_write(SLOT_T slot, int dev_type, void *data, int offset, int size)
{
	struct i2c_dev_info_s *devinfo = NULL;
	devinfo = get_devinfo_by_devtype(slot, dev_type);
	return devinfo->write(devinfo, data, offset, size);
}
/* Bus addresses of the memory banks */
#define CMD_MUTEX_LOCK           0x10405206
#define CMD_MUTEX_UNLOCK         0x10405207

int pca9548_channel_switch(channel_chip_t *chip, int fd, unsigned char channel);

channel_chip_t msg3100_channel_route[] = {
	{
		.name = "9548",//芯片名称
		.dev_addr = 0x70, //芯片的i2c地址
		.channel_switch = pca9548_channel_switch, //通道切换的回调函数
	},
	{
		.name = NULL,
		.dev_addr = 0,
		.channel_switch = NULL,
	},
};


i2c_card_info_t *i2c_card_info = msg3100_i2c_card_info;



int pca95xx_channel_switch(channel_chip_t *chip, int fd, unsigned char channel)
{
	int ret=ERROR;

	if (ioctl(fd, I2C_SLAVE, (unsigned char)chip->dev_addr) < 0) 
	{
		printf("i2c set pac95xx dev (slave addr = %x) fail!\n", chip->dev_addr);
		ret = ERROR;
		goto out;
	}
	if (write(fd, &channel,1) != 1)
	{
		printf("i2c write pca95xx channel (%x) fail!\n", channel);
		ret = ERROR;
		goto out;
	}

out:
	return ret;
   
}

int pca9548_channel_switch(channel_chip_t *chip, int fd, unsigned char channel)
{
    pca95xx_channel_switch(chip, fd, 1<<channel);
}

int pca9544_channel_switch(channel_chip_t *chip, int fd, unsigned char channel)
{
    pca95xx_channel_switch(chip, fd, 0x4 | channel);
}

/*int pca9544_channel_off(int fd, unsigned char dev)
{
    pca95xx_channel_switch(fd, dev, 0);
}*/

int i2c_channel_switch(i2c_dev_info_t *i2c_dev, int fd)
{
	int ret;
	cascade_channel_t cascade = CASCADE_0;
	if(!i2c_dev->channel_route)
		return OK;
	while(i2c_dev->channel_route[cascade].channel_switch)
	{
		ret = i2c_dev->channel_route[cascade].channel_switch(&i2c_dev->channel_route[cascade], fd, i2c_dev->cascade_channel[cascade]);
		if(ret < 0)
			return ret;
		cascade++;
	}
	return OK;
}

/*e2prom read */
int i2c_eeprom_read(struct i2c_dev_info_s *dev, void *data, int offset, int size)
{
	int fd = 0, len, ret;
	char *buf = (char*)data;
	printf("%s:%d slotid = %d\n", __func__, __LINE__, slot);
	halI2CLock();
	fd = hal_i2c_init(dev->i2c_controler);
	if(fd < 0)
	{
		ret = ERROR;
		goto out;
	}
	i2c_channel_switch(dev, fd);
	while(size)
	{
		if(size > EEPROM_PAGE_WRITE_SIZE)
			len = EEPROM_PAGE_WRITE_SIZE;
		else
			len = size;
		ret = hal_i2c_read(fd, i2c_dev->dev_addr[offset >> 8], offset&0xff, buf, len);
		if(ret < 0)
			goto out;
		buf += len;
		offset += len;
		size -= len;
	}
out:
	if(fd > 0)
		hal_i2c_close(fd);
	halI2CUnLock();
	return ret;
}

/*e2prom write */
int i2c_eeprom_write(struct i2c_dev_info_s *dev, void *data, int offset, int size)
{
	int fd = 0, len, ret;
	char *buf = (char*)data;
	halI2CLock();
	fd = hal_i2c_init(i2c_dev->i2c_controler);
	if(fd < 0)
	{
		ret = ERROR;
		goto out;
	}
	i2c_channel_switch(dev, fd);
	while(size)
	{
		if(size > EEPROM_PAGE_WRITE_SIZE)
			len = EEPROM_PAGE_WRITE_SIZE;
		else
			len = size;
		ret = hal_i2c_write(fd, i2c_dev->dev_addr[offset >> 8], offset&0xff, buf, len);
		if(ret < 0)
			goto out;
		buf += len;
		offset += len;
		size -= len;
		usleep(10*1000);
	}
out:
	if(fd > 0)
		hal_i2c_close(fd);
	halI2CUnLock();
	return ret;
}

/*common read */
int i2c_common_read(struct i2c_dev_info_s *dev, void *data, int offset, int size)
{
	int fd = 0, ret;
	char *buf = (char*)data;
	halI2CLock();
	fd = hal_i2c_init(i2c_dev->i2c_controler);
	if(fd < 0)
	{
		ret = ERROR;
		goto out;
	}
	i2c_channel_switch(dev, fd);

	ret = hal_i2c_read(fd, i2c_dev->dev_addr[0], offset, buf, size);
	if(ret < 0)
		goto out;

out:
	if(fd > 0)
		hal_i2c_close(fd);
	halI2CUnLock();
	return ret;
}

/*common write */
int i2c_common_write(struct i2c_dev_info_s *dev, void *data, int offset, int size)
{
	int fd = 0, write_len, ret;
	halI2CLock();
	fd = hal_i2c_init(i2c_dev->i2c_controler);
	if(fd < 0)
	{
		ret = ERROR;
		goto out;
	}
	i2c_channel_switch(dev, fd);

	ret = hal_i2c_write(fd, i2c_dev->dev_addr[0], offset, buf, size);
	if(ret < 0)
		goto out;
out:
	if(fd > 0)
		i2c_close(fd);
	halI2CUnLock();
	return ret;
}

