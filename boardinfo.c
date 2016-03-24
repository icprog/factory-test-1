#include <boardinfo.h>
#include <i2cdev_core.h>

board_info_t boardinfo;

int macstr_to_hex(char* mac_hex, const char*mac_str )
{
    int i;
    char tmp[3];

    for(i = 0; i < 6; i++)
    {
        tmp[0] = mac_str[(i * 3) + 0];
        tmp[1] = mac_str[(i * 3) + 1];
        tmp[2] = '\0';
        mac_hex[i] = (unsigned char) (simple_strtoul(tmp, NULL, 16));
		 
    }
	if((0x01 & mac_hex[0]) || !(mac_hex[0] | mac_hex[1] | mac_hex[2] | mac_hex[3] | mac_hex[4] | mac_hex[5]))
	{
		printf("\nmac_hex[0] = %02x,0x01 & mac_hex[0] = %02x\n",mac_hex[0],(0x01 & mac_hex[0]));
		printf("\nDon't input the multicast address and all zeros address,please input the unicast address again!\n");
		return -1;
	}
    return 0;
}

int set_boardid(void)
{
    char tmp_str[256];
    int i = 0;
    char get_char;
    unsigned short boardid;
    
    memset(tmp_str,0,sizeof(tmp_str));
    printf("Config BoardID:");
    while(1)
    {
        get_char =getc();
        if(get_char == '\r')
        {
            break;
        }
        else if(get_char == '\b' && i >0)
        {
            i--;
            tmp_str[i] ='\0';
            printf("\b \b");
        }
        else
        {
            putc(get_char);
            tmp_str[i++] =get_char;
        }
    }
    if(strlen(tmp_str) > 0)
    {
        boardid = (unsigned short)simple_strtoul(tmp_str, NULL, 16);
        boardinfo->brd_id = boardid;
    }
    return 0;    
}

int set_mac(void)
{
    char tmp_str[256];
    char macaddr[6];
    int i = 0;
    char get_char;

retry:    
    memset(tmp_str,0,sizeof(tmp_str));
    printf("\nConfig MAC ADDR(XX:XX:XX:XX:XX:XX):");
    while(1)
    {
        get_char =getc();
        if(get_char == '\r')
        {
            break;
        }
        else if(get_char == '\b' && i >0)
        {
            i--;
            tmp_str[i] ='\0';
            printf("\b \b");
        }
        else
        {
            putc(get_char);
            tmp_str[i++] =get_char;
        }
    }
    if(strlen(tmp_str) > 0)
    {
        if(macstr_to_hex(macaddr, tmp_str))
			goto retry;
        memncpy(boardinfo->macbase, macaddr, 6);
    }
    return 0;    
}

int set_sn(void)
{
    char tmp_str[256];
    int i = 0;
    char get_char;
    
    memset(tmp_str, 0, sizeof(tmp_str));
    i = 0;
    printf("\nConfig Serial Number:");
    while(1)
    {
        get_char =getc();
        if(get_char == '\r')
            break;
        else if(get_char == '\b' && i >0)
        {
            i--;
            tmp_str[i] ='\0';
            printf("\b \b");
        }
        else 
        {
            putc(get_char);
            tmp_str[i++] =get_char;
        }
    }
    
    if(strlen(tmp_str) > 0)
    {
    	memncpy(boardinfo->prod_sn, tmp_str, 64);
    }    
    return 0;    
}

int set_pn(void)
{
    char tmp_str[256];
    int i = 0;
    char get_char;

    memset(tmp_str,0,sizeof(tmp_str));
    printf("\nConfig PN:");
    while(1)
	{
	    get_char =getc();
		if(get_char == '\r')
			break;
		else if(get_char == '\b' && i >0)
		{
		    i--;
			tmp_str[i] ='\0';
			printf("\b \b");
		}
		else
		{
            putc(get_char);
            tmp_str[i++] =get_char;
		}
    }
    
	if(strlen(tmp_str) >0)
    {
    	memncpy(boardinfo->prod_pn, tmp_str, 32);
    }
    return 0;    
}

int set_brd_pn(void)
{
    char tmp_str[256];
    int i = 0;
    char get_char;

    memset(tmp_str,0,sizeof(tmp_str));
    printf("\nConfig Board PN:");
    while(1)
	{
	    get_char =getc();
		if(get_char == '\r')
			break;
		else if(get_char == '\b' && i >0)
		{
		    i--;
			tmp_str[i] ='\0';
			printf("\b \b");
		}
		else
		{
            putc(get_char);
            tmp_str[i++] =get_char;
		}
    }
    
	if(strlen(tmp_str) >0)
    {
    	memncpy(boardinfo->brd_pn, tmp_str, 32);
    }
    return 0;    
}

int set_bn(void)
{
    char tmp_str[256];
    int i = 0;
    char get_char;

    memset(tmp_str,0,sizeof(tmp_str));
    printf("\nConfig BN:");
    while(1)
	{
	    get_char =getc();
		if(get_char == '\r')
			break;
		else if(get_char == '\b' && i >0)
		{
		    i--;
			tmp_str[i] ='\0';
			printf("\b \b");
		}
		else
		{
            putc(get_char);
            tmp_str[i++] =get_char;
		}
    }
	if (strlen(tmp_str) >0)
    {
    	memncpy(boardinfo->prod_bn, tmp_str, 16);
    }
    return 0;     
}

int set_product_version(void)
{
    char tmp_str[32];
    unsigned short tmp_value;    
    int i = 0;
    char get_char;

    /* config Product version */
    memset(tmp_str,0,sizeof(tmp_str));
    printf("\nConfig Product version:");
    while(1)
    {
        get_char =getc();
        if(get_char == '\r')
            break;
        else if(get_char == '\b' && i >0)
        {
            i--;
            tmp_str[i] ='\0';
            printf("\b \b");
        }
        else
        {             
            putc(get_char);
            tmp_str[i++] =get_char;
            
            if(i > 4)
                break;   
        }
    }
    if (strlen(tmp_str) >0)
    {
    	memncpy(boardinfo->prod_rev, tmp_str, 8);
    }    
    return 0;    
}

int set_pcb_version(void)
{
    char tmp_str[32];
    unsigned short tmp_value;    
    int i = 0;
    char get_char;

    /* config pcb version */
    memset(tmp_str,0,sizeof(tmp_str));
    i = 0;
    printf("\nConfig pcb version:");
    while(1)
    {
        get_char =getc();
        if(get_char == '\r')
            break;
        else if(get_char == '\b' && i >0)
        {
            i--;
            tmp_str[i] ='\0';
            printf("\b \b");
        }
        else
        {             
            putc(get_char);
            tmp_str[i++] =get_char;
            
            if(i > 4)
                break;   
        }
    }
    if (strlen(tmp_str) >0)
    {
    	memncpy(boardinfo->pcb_rev, tmp_str, 8);
    }    
    return 0;    
}


int set_bom_version(void)
{
    char tmp_str[32];
    unsigned short tmp_value;    
    int i = 0;
    char get_char;

     /* config bom version */
    memset(tmp_str,0,sizeof(tmp_str));
    i = 0;
    printf("\nConfig bom version:");
    while(1)
    {
        get_char =getc();
        if(get_char == '\r')
            break;
        else if(get_char == '\b' && i >0)
        {
            i--;
            tmp_str[i] ='\0';
            printf("\b \b");
        }
        else
        {             
            putc(get_char);
            tmp_str[i++] =get_char;
            
            if(i > 4)
                break;   
        }
    }
    if (strlen(tmp_str) >0)
    {
    	memncpy(boardinfo->bom_rev, tmp_str, 8);
    }   
    return 0;    
}

unsigned short board_info_checksum(unsigned short *buffer, int size)
{
	unsigned long cksum=0;

    /*to avoid the buffer is full of 0xFF; the pad can be set to zero to checksum again*/
    if((0xFFFF == *buffer) && (0xFFFF == *(buffer+1)))
        return 0xFFFF;

	while(size >1) {
		cksum+=*buffer++;
		size-=sizeof(unsigned short);
	}

	if(size)
		cksum+=*(unsigned char*)buffer;

	cksum=(cksum >> 16)+(cksum&0xffff);
	cksum+=(cksum >>16);

	return (unsigned short)(~cksum);
}

int board_info_cksum_up(board_info_t *board_info_r)
{
    unsigned short pad = 0;
    
    if(board_info_r == NULL)
    {
        printf("boardinfo can not null.\n");
        return -1;
    }

    board_info_r->pad = 0;  
    
    pad = board_info_checksum((unsigned short *)board_info_r, sizeof(board_info_t));
    board_info_r->pad = pad;
    
    printf("pad:%2x\n", pad);
    printf("cksum:%x\n", board_info_checksum((unsigned short *)board_info_r, sizeof(board_info_t)));
    
    if(board_info_checksum((unsigned short *)board_info_r, sizeof(board_info_t)))
    {
        printf("generate pad error.\n");
        return -1;
    }
    
    return 0;
}

int save_boardinfo(void)
{
	if(board_info_cksum_up(&boardinfo))
		return -1;
	
	ret = i2cdev_write(SLOT_SMC, I2CDEV_EEPROM, &boardinfo, 0, sizeof(board_info_t));
	if(ret != sizeof(board_info_t))
	{
		printf("Save boardinfo failed!\n");
		return -1;
	}
	return 0;
}
int init_boardinfo(void)
{
	int ret;
	memset(&boardinfo, 0, sizeof(board_info_t));
	ret = i2cdev_read(SLOT_SMC, I2CDEV_EEPROM, &boardinfo, 0, sizeof(board_info_t));
	if(ret < 0)
	{
		printf("%s:Init boardinfo failed!\n", __func__);
		return -1;
	}
	if(board_info_checksum((unsigned short*)&boardinfo, sizeof(board_info_t)) == 0)
    {
		printf("%s:checksum ok!\n", __func__);
		return 0;
    }
	else
	{
		printf("%s:checksum failed!\n", __func__);
		return -1;
	}
	return 0;
}
