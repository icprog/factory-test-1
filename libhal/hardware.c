/*********************************************************************************
* Lattice Semiconductor Corp. Copyright 2000-2008
* 
* This is the hardware.c of ispVME V12.1 for JTAG programmable devices.
* All the functions requiring customization are organized into this file for 
* the convinience of porting. 
*********************************************************************************/
/*********************************************************************************
* Revision History:
* 
* 09/11/07 NN Type cast mismatch variables
* 09/24/07 NN Added calibration function.
*             Calibration will help to determine the system clock frequency
*             and the count value for one micro-second delay of the target 
*             specific hardware.
*             Modified the ispVMDelay function
*             Removed Delay Percent support
*             Moved the sclock() function from ivm_core.c to hardware.c
*********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "hal_i2c.h"
#define VME_DEBUG
/********************************************************************************
* Declaration of global variables 
*
*********************************************************************************/

unsigned char  g_siIspPins        = 0x00;   /*Keeper of JTAG pin state*/

unsigned short g_usCpu_Frequency  = 3800;   /*Enter your CPU frequency here, unit in MHz.*/



/*********************************************************************************
* This is the definition of the bit locations of each respective
* signal in the global variable g_siIspPins.
*
* NOTE: Users must add their own implementation here to define
*       the bit location of the signal to target their hardware.
*       The example below is for the Lattice download cable on
*       on the parallel port.
*
*********************************************************************************/
/* define the pin bit accroding to pca9555  pin*/
const unsigned char g_ucPinTDI          = 0x08;    /* Bit address of TDI */
const unsigned char g_ucPinTCK          = 0x02;    /* Bit address of TCK */
const unsigned char g_ucPinTMS          = 0x04;    /* Bit address of TMS */
const unsigned char g_ucPinENABLE       = 0x00;    /* Bit address of ENABLE ,not support*/
const unsigned char g_ucPinTRST         = 0x00;    /* Bit address of TRST,not support*/
const unsigned char g_ucPinTDO          = 0x01;    /* Bit address of TDO*/
#define ARCH_NR_GPIOS 256
#define T1040_GPIO(pin) ((ARCH_NR_GPIOS - 32) - (pin & (~0x1f)) + (pin & 0x1f))
#define GPIO_TDO T1040_GPIO(112)// 144
#define GPIO_TCK T1040_GPIO(113)// 145
#define GPIO_TMS T1040_GPIO(114)// 146
#define GPIO_TDI T1040_GPIO(115)// 147
#define GPIO_SYSFS_EXPORT_PATH "/sys/class/gpio/export"
#define GPIO_SYSFS_UNEXPORT_PATH "/sys/class/gpio/unexport"

/***************************************************************
*
* Functions declared in hardware.c module.
*
***************************************************************/
int writePort( unsigned char a_ucPins, unsigned char a_ucValue ,unsigned char a_ucCardType,unsigned char a_ucSlotId);
int readPort(unsigned char a_ucCardType,unsigned char a_ucSlotId);
void sclock(unsigned char a_ucCardType,unsigned char a_ucSlotId);
void ispVMDelay( unsigned short a_usTimeDelay );
void calibration(unsigned char a_ucCardType,unsigned char a_ucSlotId);

extern unsigned long g_usFileBufferSize;
extern unsigned char * g_pucFileBuffer;
extern unsigned long g_usChecksum;

static void export_gpio(int gpio)
{
	int fd;
	char buf[4];
	fd = open(GPIO_SYSFS_EXPORT_PATH, O_WRONLY);
	if(fd < 0) {
		printf("open failed!\n");
		return ;
	}
	sprintf(buf, "%d", gpio);
	write(fd, buf, sizeof(buf));
	close(fd);
}
static void unexport_gpio(int gpio)
{
	int fd ;
	char buf[4];
	fd = open(GPIO_SYSFS_UNEXPORT_PATH, O_WRONLY);
	if(fd < 0) {
		printf("open failed!\n");
		return ;
	}
	sprintf(buf, "%d", gpio);
	write(fd, buf, sizeof(buf));
	close(fd);
}
static void set_gpio_direction(int gpio,int is_input)
{
	int fd;
	char path[64];
	sprintf(path, "/sys/class/gpio/gpio%d/direction", gpio);
	fd = open(path, O_WRONLY);
	if(fd < 0) {
		printf("open failed!\n");
		return ;
	}
	if(is_input)
		write(fd, "in", 2);
	else
		write(fd, "out", 3);
	close(fd);
}
static void set_gpio_value(int gpio, int data)
{
	int fd;
	char path[64];
	char buf[4];
	sprintf(path, "/sys/class/gpio/gpio%d/value", gpio);
	//printf("%s: path is %s\n", __func__, path);
	fd = open(path, O_WRONLY);
	if(fd < 0) {
		printf("open failed!\n");
		return ;
	}
	sprintf(buf, "%d", data);
	write(fd, buf, sizeof(buf));
	close(fd);

}
static int get_gpio_value(int gpio)
{
	int fd;
	int data = 0;
	char path[64];
	char buf[4]={0};
	sprintf(path, "/sys/class/gpio/gpio%d/value", gpio);
	//printf("%s: path is %s\n", __func__, path);
	fd = open(path,O_RDONLY);
	if(fd < 0) {
		printf("open failed!\n");
		return ;
	}
	read(fd, buf, 1);
	sscanf(&buf[0], "%d", &data);
	close(fd);
	return data;
}
static void cpld_update_gpio_init()
{
	export_gpio(GPIO_TDO);
	export_gpio(GPIO_TCK);
	export_gpio(GPIO_TMS);
	export_gpio(GPIO_TDI);
	set_gpio_direction(GPIO_TDO, 1);
	set_gpio_direction(GPIO_TCK, 0);
	set_gpio_direction(GPIO_TMS, 0);
	set_gpio_direction(GPIO_TDI, 0);
}
static void cpld_update_gpio_exit()
{
	set_gpio_direction(GPIO_TDO, 1);
	set_gpio_direction(GPIO_TCK, 1);
	set_gpio_direction(GPIO_TMS, 1);
	set_gpio_direction(GPIO_TDI, 1);
	unexport_gpio(GPIO_TDO);
	unexport_gpio(GPIO_TCK);
	unexport_gpio(GPIO_TMS);
	unexport_gpio(GPIO_TDI);
}

/*********************************************************************************
*
* cpld_update
*
* The API to application layer .
*
**********************************************************************************/
int cpld_update(char *fileName,unsigned char ucCardType, unsigned char ucSlotId,unsigned long length)
{
   int ret = 0;
   
   if(fileName==NULL)
   {
     printf("use null pointer \r\n");
     return -1;
   }

    g_usFileBufferSize  = length;
    g_pucFileBuffer     = fileName;
	if((ucCardType==1)||(ucCardType==2))
   {
		unsigned char reg = 0xf1; 
		if(halPCA9555Write(ucSlotId, PCA9555_CONF_PORT1, &reg, 1))
		{
			printf("%s:%d: halPCA9555Write error!\n\n", __func__, __LINE__);
			return -1;
		}
	} 
	else if(ucCardType==0)
	{
		cpld_update_gpio_init();
	}
    //taskDelay(1);
    ret = ispVM(fileName,ucCardType,ucSlotId);
    
    #ifdef VME_DEBUG
    char szCommandLineArg[ 300 ] = { 0 };
  
    if ( ret < 0 ) {
  		error_handler( ret, szCommandLineArg );
  		vme_out_string( "Failed due to ");
  		vme_out_string ( szCommandLineArg );
  		vme_out_string ("\n\n");
  		vme_out_string( "+=======+\n" );
  		vme_out_string( "| FAIL! |\n" );
  		vme_out_string( "+=======+\n\n" );
  	} 
  	else {
  		vme_out_string( "+=======+\n" );
  		vme_out_string( "| PASS! |\n" );
  		vme_out_string( "+=======+\n\n" );
          
  	}
    #endif
    
    g_pucFileBuffer     = NULL;
    g_usFileBufferSize  = 0 ;
	if(ucCardType==0)
	{
		cpld_update_gpio_exit();
	}

    return ret ;

}

/********************************************************************************
* writePort
* To apply the specified value to the pins indicated. This routine will
* be modified for specific systems.                     
*  Parameters:
*   - a_ucPins, which is actually a set of bit flags (defined above)
*     that correspond to the bits of the data port. Each of the I/O port
*     bits that drives an isp programming pin is assigned a flag 
*     (through a #define) corresponding to the signal it drives. To 
*     change the value of more than one pin at once, the flags are added 
*     together, much like file access flags are.
*
*     The bit flags are only set if the pin is to be changed. Bits that 
*     do not have their flags set do not have their levels changed. The 
*     state of the port is always manintained in the static global 
*     variable g_siIspPins, so that each pin can be addressed individually 
*     without disturbing the others.
*
*   - a_ucValue, which is either HIGH (0x01 ) or LOW (0x00 ). Only these two
*     values are valid. Any non-zero number sets the pin(s) high.
*
*********************************************************************************/

int writePort( unsigned char a_ucPins, unsigned char a_ucValue ,unsigned char a_ucCardType,unsigned char a_ucSlotId)
{
    unsigned char ucSlotId  = a_ucSlotId ;
    unsigned char ucCardType = a_ucCardType;
    unsigned char value=0;
   
   if((ucCardType==1)||(ucCardType==2))
   {
      if(halPCA9555Read(a_ucSlotId, PCA9555_OUT_PORT1, &value, 1))
       {
          printf("\r\n%s :%d pca9555_byte_read \r\n",__FUNCTION__,__LINE__);
          goto exit;
       }
       if(a_ucPins==g_ucPinTDI)
       {
            if(a_ucValue)
            value |= 0x08;
           else
            value &=~0x08;
       }
       else if (a_ucPins==g_ucPinTCK)
       {
            if(a_ucValue)
            value |= 0x02;
            else
            value &=~0x02;

       }
       else
       {
            if(a_ucValue)
            value |= 0x04;
            else
            value &=~0x04;
       }      
       if(halPCA9555Write(a_ucSlotId, PCA9555_OUT_PORT1, &value, 1))
       {
          printf("\r\n%s:%d PCA9544_write error \r\n",__FUNCTION__,__LINE__);
          goto exit;
       }
       
   }
   else if(ucCardType==0)
   {
       if(a_ucPins==g_ucPinTDI)
       {
         if(a_ucValue)
            set_gpio_value(GPIO_TDI,1);
         else
            set_gpio_value(GPIO_TDI,0);
       }
       else if(a_ucPins==g_ucPinTCK)
       {
          if(a_ucValue)
            set_gpio_value(GPIO_TCK,1);
          else
            set_gpio_value(GPIO_TCK,0);
          
       }
       else
       { 
         if(a_ucValue)
           set_gpio_value(GPIO_TMS,1);
         else
           set_gpio_value(GPIO_TMS,0);
       }
                 
   }
   exit:

  return 0;
}

/*********************************************************************************
*
* readPort
*
* Returns the value of the TDO from the device.
*
**********************************************************************************/
int readPort(unsigned char a_ucCardType,unsigned char a_ucSlotId)
{
	unsigned char ucRet = 0;
    unsigned char ucSlotId =a_ucSlotId;
    unsigned char ucCardType =a_ucCardType;
    unsigned char value ;
    
    if(ucCardType==1)/*smca,xp2a,xp4a*/
    {
       if(halPCA9555Read(a_ucSlotId, PCA9555_IN_PORT1, &value, 1))
       {
           printf("\r\n%s:%d pca9555_byte_read error \r\n",__FUNCTION__,__LINE__);
           goto exit;
       }
       if(value& 0x01)
       { 
          ucRet = 0x01;
       }
       else
       {
          ucRet = 0x00;        
       }
   }
   else if(ucCardType==0)
   {
      ucRet = get_gpio_value(GPIO_TDO);
	  //printf("%s: ucRet=0x%x\n", __func__, ucRet);
   }
   
#if 0
   else if(ucCardType==2)/*ep16*/
   {
       if(pca9555_byte_read(1,PCA9555_ADDR, PCA9555_INPUT_PORT_1, &value)!=OK)
       {
           printf("\r\n%s:%d pca9555_byte_read error \r\n",__FUNCTION__,__LINE__);
           goto exit;
       }
       if(value& 0x10)
       { 
          ucRet = 0x01;
       }
       else
       {
          ucRet = 0x00;
          
       }
   }
   #endif
   exit:
   return ( ucRet );
} 

/*********************************************************************************
* sclock
*
* Apply a pulse to TCK.
*
* This function is located here so that users can modify to slow down TCK if
* it is too fast (> 25MHZ). Users can change the IdleTime assignment from 0 to 
* 1, 2... to effectively slowing down TCK by half, quarter...
*
*********************************************************************************/
void sclock(unsigned char a_ucCardType,unsigned char a_ucSlotId)
{	
	unsigned short IdleTime    = 0; /*change to > 0 if need to slow down TCK*/
	unsigned short usIdleIndex = 0;
    unsigned char ucCardType = a_ucCardType;
    unsigned char ucSlotId = a_ucSlotId;
    
	IdleTime++;
	for ( usIdleIndex = 0; usIdleIndex < IdleTime; usIdleIndex++ ) {
		writePort( g_ucPinTCK, 0x01,ucCardType,ucSlotId);
	}
	for ( usIdleIndex = 0; usIdleIndex < IdleTime; usIdleIndex++ ) { 
		writePort( g_ucPinTCK, 0x00,ucCardType,ucSlotId);
	}
}
/********************************************************************************
*
* ispVMDelay
*
*
* Users must implement a delay to observe a_usTimeDelay, where
* bit 15 of the a_usTimeDelay defines the unit.
*      1 = milliseconds
*      0 = microseconds
* Example:
*      a_usTimeDelay = 0x0001 = 1 microsecond delay.
*      a_usTimeDelay = 0x8001 = 1 millisecond delay.
*
* This subroutine is called upon to provide a delay from 1 millisecond to a few 
* hundreds milliseconds each time. 
* It is understood that due to a_usTimeDelay is defined as unsigned short, a 16 bits
* integer, this function is restricted to produce a delay to 64000 micro-seconds 
* or 32000 milli-second maximum. The VME file will never pass on to this function
* a delay time > those maximum number. If it needs more than those maximum, the VME
* file will launch the delay function several times to realize a larger delay time
* cummulatively.
* It is perfectly alright to provide a longer delay than required. It is not 
* acceptable if the delay is shorter.
*
* Delay function example--using the machine clock signal of the native CPU------
* When porting ispVME to a native CPU environment, the speed of CPU or 
* the system clock that drives the CPU is usually known. 
* The speed or the time it takes for the native CPU to execute one for loop 
* then can be calculated as follows:
*       The for loop usually is compiled into the ASSEMBLY code as shown below:
*       LOOP: DEC RA;
*             JNZ LOOP;
*       If each line of assembly code needs 4 machine cycles to execute, 
*       the total number of machine cycles to execute the loop is 2 x 4 = 8.
*       Usually system clock = machine clock (the internal CPU clock). 
*       Note: Some CPU has a clock multiplier to double the system clock for 
              the machine clock.
*
*       Let the machine clock frequency of the CPU be F, or 1 machine cycle = 1/F.
*       The time it takes to execute one for loop = (1/F ) x 8.
*       Or one micro-second = F(MHz)/8;
*
* Example: The CPU internal clock is set to 100Mhz, then one micro-second = 100/8 = 12
*
* The C code shown below can be used to create the milli-second accuracy. 
* Users only need to enter the speed of the cpu.
*
**********************************************************************************/
void ispVMDelay( unsigned short a_usTimeDelay )
{
#if 1
	unsigned short loop_index     = 0;
	unsigned short ms_index       = 0;
	unsigned short us_index       = 0;
	if ( a_usTimeDelay & 0x8000 ) /*Test for unit*/
	{
		a_usTimeDelay &= ~0x8000; /*unit in milliseconds*/
	}
	else { /*unit in microseconds*/
		a_usTimeDelay = (unsigned short) (a_usTimeDelay/1000); /*convert to milliseconds*/
		if ( a_usTimeDelay <= 0 ) {
			 a_usTimeDelay = 1; /*delay is 1 millisecond minimum*/
		}
	}
	/*Users can replace the following section of code by their own*/
	for( ms_index = 0; ms_index < a_usTimeDelay; ms_index++)
	{
		/*Loop 1000 times to produce the milliseconds delay*/
		for (us_index = 0; us_index < 1000; us_index++)
		{ /*each loop should delay for 1 microsecond or more.*/
			loop_index = 0;
			do {
				/*The NOP fakes the optimizer out so that it doesn't toss out the loop code entirely*/
                __asm__ __volatile__ ("NOP");
			}while (loop_index++ < ((g_usCpu_Frequency/8)+(+ ((g_usCpu_Frequency % 8) ? 1 : 0))));/*use do loop to force at least one loop*/
		}
	}
#endif
}

/*********************************************************************************
*
* calibration
*
* It is important to confirm if the delay function is indeed providing 
* the accuracy required. Also one other important parameter needed 
* checking is the clock frequency. 
* Calibration will help to determine the system clock frequency 
* and the loop_per_micro value for one micro-second delay of the target 
* specific hardware.
*              
**********************************************************************************/
void calibration(unsigned char a_ucCardType,unsigned char a_ucSlotId)
{
    unsigned char ucCardType=a_ucCardType;
    unsigned char ucSlotId =a_ucSlotId;
	if(ucCardType==0)
	{
		cpld_update_gpio_init();
	}
	/*Apply 2 pulses to TCK.*/
	writePort( g_ucPinTCK, 0x00,ucCardType,ucSlotId);
	writePort( g_ucPinTCK, 0x01,ucCardType,ucSlotId);
	writePort( g_ucPinTCK, 0x00,ucCardType,ucSlotId);
	writePort( g_ucPinTCK, 0x01,ucCardType,ucSlotId);
	writePort( g_ucPinTCK, 0x00,ucCardType,ucSlotId);

	/*Delay for 1 millisecond. Pass on 1000 or 0x8001 both = 1ms delay.*/
	ispVMDelay(1000);

	/*Apply 2 pulses to TCK*/
	writePort( g_ucPinTCK, 0x01,ucCardType,ucSlotId);
	writePort( g_ucPinTCK, 0x00,ucCardType,ucSlotId);
	writePort( g_ucPinTCK, 0x01,ucCardType,ucSlotId);
	writePort( g_ucPinTCK, 0x00,ucCardType,ucSlotId);
	if(ucCardType==0)
	{
		cpld_update_gpio_exit();
	}
}

