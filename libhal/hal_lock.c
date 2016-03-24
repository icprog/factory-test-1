#include <fcntl.h>

enum
{	
	MUTEX_I2C = 0,	
	MUTEX_CPLD,	
	MUTEX_MAX
};

#define CMD_LOCK           0x10405206
#define CMD_UNLOCK         0x10405207
static int fd_mutex = 0;
int halLockInit(void)
{
	if( (fd_mutex = open("/dev/ext_mutex",O_RDWR )) < 0)     
	{     
		printf("open ext_mutex failed \n");
		return   -1;     
	} 
	return fd_mutex;
}

static int halLock(int lock_type)
{
	if((ioctl(fd_mutex, CMD_LOCK, &lock_type)) !=0)
	{
		printf("i2c lock failed!!\n") ;
		return -1;
	}
	return 0;
}
static int halUnLock(int lock_type)
{
	if((ioctl(fd_mutex, CMD_UNLOCK, &lock_type)) !=0)
	{
		printf("i2c unlock failed!!\n") ;
		return -1;
	}
	return 0;
}
void halLockClose(void)
{
	close(fd_mutex);
}

int halI2CLock(void)
{
	return halLock(MUTEX_I2C);
}

int halI2CUnLock(void)
{
	return halUnLock(MUTEX_I2C);
}

int halCPLDLock(void)
{
	return halLock(MUTEX_CPLD);
}

int halCPLDUnLock(void)
{
	return halUnLock(MUTEX_CPLD);
}

