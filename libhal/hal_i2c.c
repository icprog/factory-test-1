#include <sys/param.h>
#include <sys/file.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>

#include "hal_api.h"
#include "hal_i2c.h"

int hal_i2c_read(int fd, unsigned char slave_addr, unsigned char offset_addr, unsigned char  *read_data , int num)
{
    int i = 0;
	int ret=OK;
    if(num < 1)
    {
    	  return 0;
    }
	
    if (ioctl(fd, I2C_SLAVE, slave_addr) < 0) 
    {
        printf("i2c read:set slave addr error!\r\n");
		ret = ERROR;
		goto out;
    }
    if (write(fd,&offset_addr,1) != 1)
    {
    printf("%s:%d offset_addr = 0x%x\n", __func__, __LINE__, offset_addr);
        printf("i2c write offset addr error!\r\n");
		ret = ERROR;
		goto out;
    }
    //usleep(10*1000);                        
    if (read(fd,read_data,num) != num) 
    {
        printf("i2c read data error!\r\n");
		ret = ERROR;
		goto out;
    }
	
out:
    return ret;
}


int hal_i2c_write(int fd, unsigned char slave_addr, unsigned char  offset_addr, unsigned char *write_data, int num)
{
     unsigned char *buf, *p;
	 int ret = OK;
	 
	buf = (unsigned char*)malloc(num+1);
	 if(!buf)
	 	return ERROR;
	 buf[0] = offset_addr;
	 p = &buf[1];
     memcpy((char*)p,(char*)write_data,num);
	
     if (ioctl(fd, I2C_SLAVE, slave_addr) < 0) 
     {
         printf("i2c write:set slave addr error!\r\n");
		ret = ERROR;
		goto out;
     }
   
     if (write(fd,buf,num+1) < 0)
     {
         printf("i2c write data error!\r\n");
		ret = ERROR;
		goto out;
     } 

out:
	free(buf);
    return ret;
}

int hal_i2c_init(int i2c_controler)
{ 
	char devname[16];
	int i2cdevfd = 0;
	sprintf(devname, "/dev/i2c-%d", i2c_controler);
    /* Open the host adapter */
    if ((i2cdevfd = open(devname, O_RDWR)) < 0) 
    {
      printf("i2c_init: open i2c device error!\r\n");
      return   ERROR;
    }   
    if (ioctl(i2cdevfd,I2C_TENBIT,0)< 0) 
    {
         printf("i2c_init: ioctl I2C_TENBIT error!\r\n");
      return   ERROR;
    }

    return  i2cdevfd;        
}

int hal_i2c_close(int fd)
{
     if( close(fd)== -1 )     
    {     
       printf("close i2c device failed \n");     
       return   ERROR;     
    }
	 
    return  OK;   
}

