#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>

#include <hal_api.h>

#define SYSFS_GPIO_PATH "/sys/class/gpio"
#define SYSFS_GPIO_EXPORT_PATH "/sys/class/gpio/export"
#define SYSFS_GPIO_UNEXPORT_PATH "/sys/class/gpio/unexport"

int hal_gpio_unexport(int gpionum)
{
	int gpiofd, ret = OK;
	if ((gpiofd = open(SYSFS_GPIO_UNEXPORT_PATH, O_RDWR)) < 0) 
	{
		printf("%s:open gpio uxexport error!\n", __func__);
		return  ERROR;
	}   
	
	if (write(gpiofd, &gpionum, sizeof(int)) < 0) 
	{
		printf("%s:unexport gpio error!\n", __func__);
		ret = ERROR;
		goto out;
	}

	out:
	close(gpiofd);
	return ret;

}


int hal_gpio_export(int gpionum)
{
	int gpiofd, ret = OK;
	if ((gpiofd = open(SYSFS_GPIO_EXPORT_PATH, O_RDWR)) < 0) 
	{
		printf("%s:open gpio export error!\n", __func__);
		return  ERROR;
	}   
	
	if (write(gpiofd, &gpionum, sizeof(int)) < 0) 
	{
		printf("%s:export gpio error!\n", __func__);
		ret = ERROR;
		goto out;
	}

	out:
	close(gpiofd);
	return ret;
}

int hal_gpio_set_direction_out(int gpionum)
{
	char path[64];
	int gpiofd, ret = OK;

	sprintf(path, "%s/gpio%d/direction", SYSFS_GPIO_PATH, gpionum);
	if ((gpiofd = open(path, O_RDWR)) < 0) 
	{
		printf("%s:open gpio direction error!\n", __func__);
		return  ERROR;
	}   
	
	if (write(gpiofd, "out", 4) < 0)
	{
		printf("%s:set gpio direction error!\n", __func__);
		ret = ERROR;
		goto out;
	}

	out:
	close(gpiofd);
	return ret;
}
int hal_gpio_set_direction_in(int gpionum)
{
	char path[64];
	int gpiofd, ret = OK;

	sprintf(path, "%s/gpio%d/direction", SYSFS_GPIO_PATH, gpionum);
	if ((gpiofd = open(path, O_RDWR)) < 0) 
	{
		printf("%s:open gpio direction error!\n", __func__);
		return  ERROR;
	}   
	
	if (write(gpiofd, "in", 3) < 0)
	{
		printf("%s:set gpio direction error!\n", __func__);
		ret = ERROR;
		goto out;
	}

	out:
	close(gpiofd);
	return ret;
}
int hal_gpio_set_value(int gpionum, int value)
{
	char path[64];
	int gpiofd, ret = OK;
	hal_gpio_set_direction_out(gpionum);

	sprintf(path, "%s/gpio%d/value", SYSFS_GPIO_PATH, gpionum);
	if ((gpiofd = open(path, O_RDWR)) < 0) 
	{
		printf("%s:open gpio value error!\n", __func__);
		return  ERROR;
	}   
	
	if (write(gpiofd, &value, sizeof(int)) < 0)
	{
		printf("%s:set gpio value error!\n", __func__);
		ret = ERROR;
		goto out;
	}

	out:
	close(gpiofd);
	return ret;
}
int hal_gpio_get_value(int gpionum, int *value)
{
	char path[64];
	int gpiofd, ret = OK;
	hal_gpio_set_direction_in(gpionum);

	sprintf(path, "%s/gpio%d/value", SYSFS_GPIO_PATH, gpionum);
	if ((gpiofd = open(path, O_RDWR)) < 0) 
	{
		printf("%s:open gpio value error!\n", __func__);
		return  ERROR;
	}   
	
	if (read(gpiofd, value, sizeof(int)) < 0)
	{
		printf("%s:get gpio value error!\n", __func__);
		ret = ERROR;
		goto out;
	}

	out:
	close(gpiofd);
	return ret;
}

int hal_gpio_init(int i2c_controler)
{ 
	char devname[16];
	int gpiofd = 0;
	sprintf(devname, "/dev/i2c-%d", i2c_controler);
    /* Open the host adapter */
    if ((gpiofd = open(devname, O_RDWR)) < 0) 
    {
      printf("i2c_init: open i2c device error!\r\n");
      return   ERROR;
    }   
    if (ioctl(gpiofd,I2C_TENBIT,0)< 0) 
    {
         printf("i2c_init: ioctl I2C_TENBIT error!\r\n");
      return   ERROR;
    }

    return  gpiofd;        
}

int hal_gpio_close(int fd)
{
     if( close(fd)== -1 )     
    {     
       printf("close i2c device failed \n");     
       return   ERROR;     
    }
	 
    return  OK;   
}

