#include <stdio.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "mdio-lib.h"

static int fdmdio = -1;

int drv_mdio_open(void)
{
    fdmdio = open("/dev/mdio", O_RDWR);
    if(fdmdio == -1)
    {
        printf("drv_mdio_open: open mdio failed\n");
        return -1;
    }
    
    return 0;
}

int drv_mdio_close(void)
{
    if(fdmdio != -1)
        close(fdmdio);

    return 0;
}

int drv_mdio_read(unsigned int phyAddr, unsigned int regAddr, unsigned short *val)
{
    struct mdio_read_s mdio_read_info;

    if (fdmdio < 0)
    {
        printf("please call drv_mdio_open() first!!! %s, %d\n", __FILE__, __LINE__);
        return -1;
    }

    mdio_read_info.phyAddr = phyAddr;
    mdio_read_info.regAddr = regAddr;
    mdio_read_info.pdata   = val;

    if(ioctl(fdmdio, CMD_MDIO_READ, &mdio_read_info))
    {
        printf("drv_mdio_read: ioctl error\n");
        return -1;
    }

    return 0;
}

int drv_mdio_write(unsigned int phyAddr, unsigned int regAddr, unsigned short val)
{
    struct mdio_write_s mdio_write_info;
    
    if (fdmdio < 0)
    {
        printf("please call drv_mdio_open() first!!! %s, %d\n", __FILE__, __LINE__);
        return -1;
    }

    mdio_write_info.phyAddr = phyAddr;
    mdio_write_info.regAddr = regAddr;
    mdio_write_info.data    = val;

    if(ioctl(fdmdio, CMD_MDIO_WRITE, &mdio_write_info))
    {
        printf("drv_mdio_write: ioctl error\n");
        return -1;
    }

    return 0;
}

