#include <factory_test.h>
#include <hal_led.h>

int led_test(board_test *bdtest)
{
	int ledx = 0, loop_time = 0;
	printf("\n--------------------LED test---------------------\n");
    for(;loop_time < 16;loop_time++)
    {
        if(loop_time %2 == 0)
        {
        	for(ledx = 0; ledx < LED_MAX_NUM; ledx++)
    		{
    			if(bdtest->leds[ledx].activate == 0)
            		continue;
				hal_led_off(&bdtest->leds[ledx]);
        	}
			msleep(300);
        }
		else
		{
			for(ledx = 0; ledx < LED_MAX_NUM; ledx++)
    		{
    			if(bdtest->leds[ledx].activate == 0)
            		continue;
				hal_led_on(&bdtest->leds[ledx]);
        	}
			msleep(300);
		}
    }
	return TEST_PASS;
}
