#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/rtc.h>
#include <sys/time.h>
#include <sys/ioctl.h>

int main()
{
	int fd;
	int wait_time = 2;
    int i;
	struct rtc_time diag_old_tm;
    struct rtc_time diag_cur_tm;	
	
	printf("\n--------------------RTC test---------------------\n");
	if ((fd = open("/dev/rtc0", O_RDONLY)) < 0) 
	{
		printf("%s:open /dev/rtc0 error!\n", __func__);
		return  TEST_FAIL;
	}

	ioctl(fd,RTC_RD_TIME,&diag_old_tm);
	
	printf("get curent date:%02d-%02d-%02d %02d:%02d:%02d\n",diag_old_tm.tm_year,diag_old_tm.tm_mon,diag_old_tm.tm_mday,diag_old_tm.tm_hour,diag_old_tm.tm_min,diag_old_tm.tm_sec);

	printf("wait 3 Sec");

	while (wait_time >=0)
	{
	/* delay 1000 * 1ms */
	for (i=0;i<1000; ++i)
	udelay (1000);
	printf("\b\b\b\b\b%d Sec", wait_time);
	--wait_time;
	}

	printf("\n");

	ioctl(fd,RTC_RD_TIME,&diag_cur_tm);

	printf("get curent date:%02d-%02d-%02d %02d:%02d:%02d\n",diag_cur_tm.tm_year,diag_cur_tm.tm_mon,diag_cur_tm.tm_mday,diag_cur_tm.tm_hour,diag_cur_tm.tm_min,diag_cur_tm.tm_sec);

	if(diag_old_tm.tm_sec > 56)
	{
		diag_old_tm.tm_sec -= 60;
		diag_old_tm.tm_min += 1;
	}

	if(diag_cur_tm.tm_year == diag_old_tm.tm_year  
	&& diag_cur_tm.tm_mon == diag_old_tm.tm_mon 
	&& diag_cur_tm.tm_mday == diag_old_tm.tm_mday    
	&& diag_cur_tm.tm_hour == diag_old_tm.tm_hour   
	&& diag_cur_tm.tm_min == diag_old_tm.tm_min
	&& diag_cur_tm.tm_sec == diag_old_tm.tm_sec + 0x03)
	{
		test_result &= ~RTC_TEST_FAIL;
		printf("RTC Test: OK!\n");
		return TEST_PASS; 
	}
	else
	{
		test_result |= RTC_TEST_FAIL;
		printf("RTC Test: ERROR!\n");
		return TEST_FAIL;
	}
	return TEST_PASS; 
}

