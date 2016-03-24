/* arm-marvell-linux-uclibcgnueabi-gcc -o mdio mdio-test.c ../libhal.so*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void mdio_usage(void)
{
    printf("usage:\n");
    printf(" mdio read phyAddr regAddr\n");
    printf(" mdio write phyAddr regAddr val\n");
    printf(" mdio show slot slotid mode\n");
    printf(" mdio dump reg addr\n");
    printf(" mdio config switch reg\n");
    printf(" mdio phy read slot phyaddr\n");
    printf(" mdio phy write slot phyaddr value\n");
    printf(" mdio mac addr show\n");
}

void main(int argc, char **argv)
{
    unsigned int phyAddr;
    unsigned int regAddr;
    unsigned short val = 0xFFFF;

    if((argc != 4) && (argc != 5) && (argc != 6))
    {
        mdio_usage();
        return;
    }

    if(drv_mdio_open())
        return;

    ++argv;
    if((*argv)[0] == 'r')
    {
        phyAddr = strtoul(*(++argv), NULL, 16);
        regAddr = strtoul(*(++argv), NULL, 16);
        
        if(drv_mdio_read(phyAddr, regAddr, &val))
            return;
        
        printf("mdio read 0x%x 0x%x = 0x%x\n", phyAddr, regAddr, val);
    }
    else if((*argv)[0] == 'w')
    {
        phyAddr = strtoul(*(++argv), NULL, 16);
        regAddr = strtoul(*(++argv), NULL, 16);
        val     = strtoul(*(++argv), NULL, 16);

        if(drv_mdio_write(phyAddr, regAddr, val))
            return;

        printf("mdio write 0x%x 0x%x 0x%x\n", phyAddr, regAddr, val);
    }
    else if((*argv)[0] == 'd')
    {
        dump_ip1826_registers();
    }
    else if ((*argv)[0] == 's')
    {
        regAddr = strtoul(*(argv+2), NULL, 10);
        val = strtoul(*(argv+3), NULL, 10);
        show_port_stats(regAddr, val);
    }
    else if ((*argv)[0] == 'c')
    {
        config_ip1826d();
    }
    else if ((*argv)[0] == 'p')
    {
        ++argv;
        if((*argv)[0] == 'r')
        {
            phyAddr = strtoul(*(++argv), NULL, 10);
            regAddr = strtoul(*(++argv), NULL, 16);
            ip1826d_phy_read(phyAddr, regAddr);
        }
        else
        {
            phyAddr = strtoul(*(++argv), NULL, 10);
            regAddr = strtoul(*(++argv), NULL, 16);  
            val     = strtoul(*(++argv), NULL, 16);
            ip1826d_phy_write(phyAddr, regAddr, val);
        }
    }
    else if ((*argv)[0] == 'm')
    {
        ip1826d_show_mac();
    }

    
    drv_mdio_close();
}

void get_ip1826_addr(unsigned long ulReg, unsigned long *pulPhyAddr, unsigned long *pulRegAddr)
{
    *pulPhyAddr = (ulReg >> 5);
    *pulRegAddr = (ulReg & 0x1F);
}

void dump_ip1826_registers(void)
{
    int i=0;
    unsigned long ulPhyAddr = 0;
    unsigned long ulRegAddr = 0;
    unsigned short ulVal = 0xFFFF;

    for(i=0; i<=0xFF; i++)
    {
        get_ip1826_addr(i, &ulPhyAddr, &ulRegAddr);
        if(drv_mdio_read(ulPhyAddr, ulRegAddr, &ulVal))
        {
            printf("read 0x%02x addr error\r\n", i);
            return;
        }

        printf("reg: 0x%02x, phy:0x%02x reg_:0x%02x val:0x%04x\r\n", i, ulPhyAddr, ulRegAddr, ulVal);         
    }
}

int get_ip1826port_counter(unsigned long ulPort, unsigned long *pulCounter1, unsigned long *pulCounter2)
{
    if ((ulPort > 26) || (ulPort < 0))
    {
        return -1;
    }

    if (ulPort <=23 && ulPort >=1)
    {
        *pulCounter1 = (ulPort -1)*2;
        *pulCounter2 = *pulCounter1+1;
    }
    else if(ulPort == 26)
    {
        *pulCounter1 = 48;
        *pulCounter2 = 49;
    }
    else if (ulPort == 24)
    {
        *pulCounter1 = 50;
        *pulCounter2 = 51;        
    }
    else if (ulPort == 25)
    {
        *pulCounter1 = 52;
        *pulCounter2 = 53;
    }
    else
    {
        return -1;
    }

    return 0;
}

int Write_register(unsigned long ulReg, unsigned short usValue)
{
    unsigned long ulPhyAddr = 0;
    unsigned long ulRegAddr = 0;
    
    get_ip1826_addr(ulReg, &ulPhyAddr, &ulRegAddr);
    if(drv_mdio_write(ulPhyAddr, ulRegAddr, usValue))
    {
        goto error_segment;
    }

    return 0;

    error_segment:
        printf("operate phy :0x%02x reg: 0x%02x error\r\n", ulPhyAddr, ulRegAddr);
        return -1;        
    
}

int Read_register(unsigned long ulReg, unsigned short *pusValue)
{
    unsigned long ulPhyAddr = 0;
    unsigned long ulRegAddr = 0;
    
    get_ip1826_addr(ulReg, &ulPhyAddr, &ulRegAddr);
    if(drv_mdio_read(ulPhyAddr, ulRegAddr, pusValue))
    {
        goto error_segment;
    }

    return 0;
    
    error_segment:
        printf("operate phy :0x%02x reg: 0x%02x error\r\n", ulPhyAddr, ulRegAddr);
        return -1;        
    
}


void show_ip1826_port_statistics(unsigned long ulPort, unsigned long ulMode)
{
    unsigned long ulPhyAddr = 0;
    unsigned long ulRegAddr = 0;
    unsigned short ulVal = 0xFFFF;
    unsigned long ulCount1 = 0;
    unsigned long ulCount2 = 0;    
    char aucCounter1[128] = {0};
    char aucCounter2[128] = {0};
    int res = 0;

    switch (ulMode)
    {
        case 1:/*reg 01(9) = 0, reg 0x3b/c (port bit) = 0*/
            res = Read_register(1, &ulVal);
            if (res == -1)
            {
                goto error_segment;
            }
            
            ulVal |= (0x1 << 10);
            ulVal &= ~(0x1 << 9);
            res = Write_register(1, ulVal);
            if (res == -1)
            {
                goto error_segment;
            }    
            
            if (ulPort <= 16 && ulPort >=1)
            {
                res = Read_register(0x3B, &ulVal);
                if (res == -1)
                {
                    goto error_segment;
                }   

                ulVal &= ~(1<<(ulPort-1)); 
                res = Write_register(0x3B, ulVal);
                if (res == -1)
                {
                    goto error_segment;
                }    
            }
            else
            {
                res = Read_register(0x3C, &ulVal);
                if (res == -1)
                {
                    goto error_segment;
                }   

                ulVal &= ~(1<<(ulPort-16)); 
                res = Write_register(0x3C, ulVal);
                if (res == -1)
                {
                    goto error_segment;
                }   
            }     

            sprintf(aucCounter1, "tx");
            sprintf(aucCounter2, "rx");
            break;

        case 2:/*reg 01(9) = 0, reg 0x3b/c (port bit) = 1*/
            res = Read_register(1, &ulVal);
            if (res == -1)
            {
                goto error_segment;
            }
            
            ulVal |= (0x1 << 10);
            ulVal &= ~(0x1 << 9);
            res = Write_register(1, ulVal);
            if (res == -1)
            {
                goto error_segment;
            }    
            
            if (ulPort <= 16 && ulPort >=1)
            {
                res = Read_register(0x3B, &ulVal);
                if (res == -1)
                {
                    goto error_segment;
                }   

                ulVal |= (1<<(ulPort-1)); 
                res = Write_register(0x3B, ulVal);
                if (res == -1)
                {
                    goto error_segment;
                }    
            }
            else
            {
                res = Read_register(0x3C, &ulVal);
                if (res == -1)
                {
                    goto error_segment;
                }   

                ulVal |= (1<<(ulPort-16)); 
                res = Write_register(0x3C, ulVal);
                if (res == -1)
                {
                    goto error_segment;
                }   
            }        
            sprintf(aucCounter1, "collision");
            sprintf(aucCounter2, "tx");
            break;

        case 3:/*reg 01(9) = 1, reg 0x3b/c (port bit) = 0*/
            res = Read_register(1, &ulVal);
            if (res == -1)
            {
                goto error_segment;
            }
            
            ulVal |= (0x1 << 10);
            ulVal |= (0x1 << 9);
            res = Write_register(1, ulVal);
            if (res == -1)
            {
                goto error_segment;
            }    
            
            if (ulPort <= 16 && ulPort >=1)
            {
                res = Read_register(0x3B, &ulVal);
                if (res == -1)
                {
                    goto error_segment;
                }   

                ulVal &= ~(1<<(ulPort-1)); 
                res = Write_register(0x3B, ulVal);
                if (res == -1)
                {
                    goto error_segment;
                }    
            }
            else
            {
                res = Read_register(0x3C, &ulVal);
                if (res == -1)
                {
                    goto error_segment;
                }   

                ulVal &= ~(1<<(ulPort-16)); 
                res = Write_register(0x3C, ulVal);
                if (res == -1)
                {
                    goto error_segment;
                }   
            }         
            sprintf(aucCounter1, "drop count(MAC)");
            sprintf(aucCounter2, "rx");            
            break;

        case 4:
            res = Read_register(1, &ulVal);
            if (res == -1)
            {
                goto error_segment;
            }
            
            ulVal |= (0x1 << 10);
            ulVal |= (0x1 << 9);
            res = Write_register(1, ulVal);
            if (res == -1)
            {
                goto error_segment;
            }    
            
            if (ulPort <= 16 && ulPort >=1)
            {
                res = Read_register(0x3B, &ulVal);
                if (res == -1)
                {
                    goto error_segment;
                }   

                ulVal |= (1<<(ulPort-1)); 
                res = Write_register(0x3B, ulVal);
                if (res == -1)
                {
                    goto error_segment;
                }    
            }
            else
            {
                res = Read_register(0x3C, &ulVal);
                if (res == -1)
                {
                    goto error_segment;
                }   

                ulVal |= (1<<(ulPort-16)); 
                res = Write_register(0x3C, ulVal);
                if (res == -1)
                {
                    goto error_segment;
                }   
            }         
            sprintf(aucCounter1, "Crc error");
            sprintf(aucCounter2, "rx");                
            break;

        default:
            printf("mode is 1-4\r\n");
            printf("mode 1: rx counter, tx counter\r\n"
                   "mode 2: tx count, collision counter r\n"
                   "mode 3: rx counter, drop pkt(MAC)"
                   "mode 4: rx counter, Crc error");
            
    }

    res = get_ip1826port_counter(ulPort, &ulCount1, &ulCount2);
    if (res < 0)
    {
        printf("get port %d counter error\r\n", ulPort);
        return;
    }

    ulVal = 0x0100 | ulCount1;
    res = Write_register(0x38, ulVal);
    if (res == -1)
    {
        goto error_segment;
    }  

    res = Read_register(0x3A, &ulVal);
    if (res == -1)
    {
        goto error_segment;
    }  
 
    printf("port %d %s: %d\r\n", ulPort, aucCounter1, ulVal);

    ulVal = 0x0100 | ulCount2;
    res = Write_register(0x38, ulVal);
    if (res == -1)
    {
        goto error_segment;
    }  
    
    res = Read_register(0x3A, &ulVal);
    if (res == -1)
    {
        goto error_segment;
    }  
 
    printf("port %d %s: %d\r\n", ulPort, aucCounter2, ulVal);        

    return;
    
error_segment:
        printf("operate phy :0x%02x reg: 0x%02x error\r\n", ulPhyAddr, ulRegAddr);
        return;
        
}

void show_port_stats(unsigned long ulSlot, unsigned long ulMode)
{
    if (ulSlot == 7)
    {
        show_ip1826_port_statistics(26, ulMode);
    }
    else if (ulSlot < 7)
    {
        show_ip1826_port_statistics(ulSlot, ulMode);
    }
    else
    {
        show_ip1826_port_statistics(ulSlot-1, ulMode);
    }
}

void config_ip1826d(void)
{
    unsigned long ulPhyAddr = 0;
    unsigned long ulRegAddr = 0;
    unsigned short ulVal = 0xFFFF;
    unsigned long i = 0;

    get_ip1826_addr(0x1, &ulPhyAddr, &ulRegAddr);
    if(drv_mdio_write(ulPhyAddr, ulRegAddr, 0x413))
    {
        goto error_segment;
    }
    
    get_ip1826_addr(0x2, &ulPhyAddr, &ulRegAddr);
    if(drv_mdio_write(ulPhyAddr, ulRegAddr, 0x9))
    {
        goto error_segment;
    }

    get_ip1826_addr(0x40, &ulPhyAddr, &ulRegAddr);
    if(drv_mdio_write(ulPhyAddr, ulRegAddr, 0x385c))
    {
        goto error_segment;
    }

    for (i = 0x53; i<=0x5A; i++)
    {
        get_ip1826_addr(i, &ulPhyAddr, &ulRegAddr);
        if(drv_mdio_write(ulPhyAddr, ulRegAddr, 0))
        {
            goto error_segment;
        }      
    }

    get_ip1826_addr(0x5B, &ulPhyAddr, &ulRegAddr);
    if(drv_mdio_write(ulPhyAddr, ulRegAddr, 0))/*0x6800*/
    {
        goto error_segment;
    }      

    for (i = 0x61; i<=0x7F; i++)
    {
        get_ip1826_addr(i, &ulPhyAddr, &ulRegAddr);
        if(drv_mdio_write(ulPhyAddr, ulRegAddr, 0xFFF))
        {
            goto error_segment;
        }      
    }

    get_ip1826_addr(0xC9, &ulPhyAddr, &ulRegAddr);/*´ò¿ª¶Ë¿Ú¸ôÀë*/
    if(drv_mdio_write(ulPhyAddr, ulRegAddr, 0xFFFF))
    {
        goto error_segment;
    }  

    get_ip1826_addr(0xCA, &ulPhyAddr, &ulRegAddr);
    if(drv_mdio_write(ulPhyAddr, ulRegAddr, 0x0800))
    {
        goto error_segment;
    }      

    for (i = 0xD4; i<=0xD5; i++)
    {
        get_ip1826_addr(i, &ulPhyAddr, &ulRegAddr);
        if(drv_mdio_write(ulPhyAddr, ulRegAddr, 0x0))
        {
            goto error_segment;
        }      
    }

    get_ip1826_addr(0xF2, &ulPhyAddr, &ulRegAddr);
    if(drv_mdio_write(ulPhyAddr, ulRegAddr, 0xC))
    {
        goto error_segment;
    }      

    get_ip1826_addr(0xFA, &ulPhyAddr, &ulRegAddr);
    if(drv_mdio_write(ulPhyAddr, ulRegAddr, 0x4122))
    {
        goto error_segment;
    }     

    get_ip1826_addr(0xF9, &ulPhyAddr, &ulRegAddr);
    if(drv_mdio_write(ulPhyAddr, ulRegAddr, 0x1EBA))
    {
        goto error_segment;
    } 

   
    printf("config ip1826D switch register OK!\r\n");
    return;
    
error_segment:
        printf("operate phy :0x%02x reg: 0x%02x error\r\n", ulPhyAddr, ulRegAddr);
        return;    
}

#define PHY_BUSY 0x2000

static int ip1826d_phy_is_free(unsigned long ulCount)
{
    unsigned short usVal = 0;
    
    while(ulCount--)
    {
        if(Read_register(0xDA, &usVal))
        {
            goto error_segment;
        }

        if (usVal & PHY_BUSY)
        {        
           return 0;
        }
        else
        {
            continue;
        }   
    }
    
error_segment:
        printf("operate phy 0xDA error, %s, %d\r\n", __FILE__, __LINE__);
        return -1; 
    
}

void ip1826d_phy_read(unsigned long ulSlot, unsigned long ulReg)
{
    unsigned long ulPhyAddr = 0;
    unsigned long ulRegAddr = 0;
    unsigned short ulVal = 0xFFFF;

    if (ulSlot < 10 && ulSlot >0)
    {
        if (ulSlot == 7)
        {
            printf("input slot error\r\n");
            return;            
        }
        else if (ulSlot < 7)
        {
            ulVal = 0x8 | (ulSlot -1);
            ulVal |= (ulReg << 5); 
        }
        else
        {
            ulVal = 0x8 | (ulSlot -2);
            ulVal |= (ulReg << 5); 
        }
    }
    else if(ulSlot >=10 && ulSlot <=13)
    {
          ulVal = 0x10 | (ulSlot -10);
          ulVal |= (ulReg << 5);         
    }
    else
    {   
        printf("input slot error\r\n");
        return;
    }

    ulVal = 0x8000 | ulVal;
    get_ip1826_addr(0xDA, &ulPhyAddr, &ulRegAddr);
    if(drv_mdio_write(ulPhyAddr, ulRegAddr, ulVal))
    {
        goto error_segment;
    }     

    if (ip1826d_phy_is_free(10) != 0)
    {
        return;
    }
    
    get_ip1826_addr(0xDB, &ulPhyAddr, &ulRegAddr);
    if(drv_mdio_read(ulPhyAddr, ulRegAddr, &ulVal))
    {
        goto error_segment;
    }   
    
    printf("read slot: %d, reg: 0x%02x val: 0x%02x\r\n", ulSlot, ulReg, ulVal);
    return;
    
error_segment:
        printf("operate phy :0x%02x reg: 0x%02x error\r\n", ulPhyAddr, ulRegAddr);
        return;    
    
}

void ip1826d_phy_write(unsigned long ulSlot, unsigned long ulReg, unsigned long ulValue)
{
    unsigned long ulPhyAddr = 0;
    unsigned long ulRegAddr = 0;
    unsigned short ulVal = 0xFFFF;

    if (ulSlot < 10 && ulSlot >0)
    {
        if (ulSlot == 7)
        {
            printf("input slot error\r\n");
            return;            
        }
        else if (ulSlot < 7)
        {
            ulVal = 0x8 | (ulSlot -1);
            ulVal |= (ulReg << 5); 
        }
        else
        {
            ulVal = 0x8 | (ulSlot -2);
            ulVal |= (ulReg << 5); 
        }
    }
    else if(ulSlot >=10 && ulSlot <=13)
    {
          ulVal = 0x10 | (ulSlot -10);
          ulVal |= (ulReg << 5);         
    }
    else
    {   
        printf("input slot error\r\n");
        return;
    }

    get_ip1826_addr(0xDB, &ulPhyAddr, &ulRegAddr);
    if(drv_mdio_write(ulPhyAddr, ulRegAddr, ulValue))
    {
        goto error_segment;
    }   

    ulVal = 0xC000 | ulVal;
    get_ip1826_addr(0xDA, &ulPhyAddr, &ulRegAddr);
    if(drv_mdio_write(ulPhyAddr, ulRegAddr, ulVal))
    {
        goto error_segment;
    }     

    if (ip1826d_phy_is_free(10) != 0)
    {
        return;
    }
    
    printf("write slot: %d, reg: 0x%02x val: 0x%02x\r\n", ulSlot, ulReg, ulValue);
    return;
    
error_segment:
        printf("operate phy :0x%02x reg: 0x%02x error\r\n", ulPhyAddr, ulRegAddr);
        return;        
}

void ip1826d_show_mac(void)
{
    int i=0;
    unsigned long ulPhyAddr = 0;
    unsigned long ulRegAddr = 0;
    unsigned short ulVal = 0;
    unsigned short ausMac[3] = {0};
    unsigned short ausZMac[3] = {0};
    unsigned char acMac[6] = {0};
    unsigned char acPort = 0;
    
    int res = 0;

    printf("mac addr table show:\r\n"); 
    for (i=0; i<4096; i++)
    {
        ulVal = i;
        ulVal = (1<<15) | (1<<14) | ulVal;
        res = Write_register(0xC5, ulVal);
        if(res == -1)
        {
            goto error_segment;
            return;
        }

        res = Read_register(0xC6, &ausMac[0]);
        if(res == -1)        
        {
            goto error_segment;
            return;
        }       

        res = Read_register(0xC7, &ausMac[1]);
        if(res == -1)        
        {
            goto error_segment;
            return;
        }  

        res = Read_register(0xC8, &ausMac[2]);
        if(res == -1)        
        {
            goto error_segment;
            return;
        } 
        
        if(memcmp(ausMac, ausZMac, sizeof(ausMac)) != 0)
        {
            acMac[5] = ((ausMac[2] & 0xF) << 5) | ((ausMac[1]>>12)<<1);
            acMac[4] = ((ausMac[1]>>4)& 0xFF);
            acMac[3] = ((ausMac[1]&0xF)<<4) | (ausMac[0]>>12);
            acMac[2] = ((ausMac[0]>>4)& 0xFF);
            acMac[1] = ((((ausMac[0])& 0xF))<<4) | ((i>>8)& 0xF);
            acMac[0] = (i&0xFF);
            acPort = (ausMac[2]>>4)&0x1F;
            if (acPort == 26)
            {
                acPort = 7;
            }
            else
            {
                acPort += 2;
            }
            printf("mac index: %d, mac addr: %02x:%02x:%02x:%02x:%02x:%02x slot:%d\r\n",
                i, acMac[5], acMac[4], acMac[3],acMac[2],acMac[1],acMac[0], acPort);
        }
    }

    return;    
error_segment:
        printf("operate phy :0x%02x reg: 0x%02x error\r\n", ulPhyAddr, ulRegAddr);
        return;        

}

