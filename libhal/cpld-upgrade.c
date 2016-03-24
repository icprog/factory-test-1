
#include <stdio.h>
#include <fcntl.h>

extern int cpld_update(char *fileName,unsigned char ucCardType, unsigned char ucSlotId,unsigned long length);
extern void calibration(unsigned char a_ucCardType,unsigned char a_ucSlotId);
#define BUF_SIZE (256*1024)

void drvapi_usage(void)
{
    printf("usage:\n");
    printf(" cpld-upgrade slotx file cardtype\n");
}

int main(int argc, char **argv)
{
	int fd , size = 0, slot = 0, cardtype = 0;
	char buf[BUF_SIZE];
	
	if(argc != 4)
	{
		drvapi_usage();
		return 0;
	}
	fd = open(argv[2], O_RDONLY);
	size = read(fd, buf, BUF_SIZE);
	sscanf(argv[1], "slot%d", &slot);
	sscanf(argv[3], "%d", &cardtype);
	//calibration(cardtype, slot);
	cpld_update(buf, cardtype, slot, size);
	return 0;
}
