#ifndef _DRV_I2C_H_
#define _DRV_I2C_H_

#define I2C_SLAVE	    0x0703	                /* Use this slave address */
#define I2C_TENBIT	  0x0704	
#define I2C_NOSTOP	  0x0711	
int hal_i2c_read(int fd, unsigned char slave_addr, unsigned char offset_addr, unsigned char  *read_data , int num);
int hal_i2c_write(int fd, unsigned char slave_addr, unsigned char  offset_addr, unsigned char *write_data, int num);
int hal_i2c_init(int i2c_controler);
int hal_i2c_close(int fd);

#endif

