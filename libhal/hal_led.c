#include <hal_led.h>
#include <hal_gpio.h>

int hal_led_set_activate(struct led_s *led, int activate)
{
	led->activate= activate;
	return 0;
}

int hal_led_set_current_pin(struct led_s *led, int color)
{
	if(LED_RED == color)
		led->pin = led->red_pin;
	else(LED_GREEN== color)
		led->pin = led->grn_pin;
	return 0;
}
int hal_led_on(struct led_s *led)
{
	if(led->state & (LED_RED_ON | LED_GREEN_ON))
		return 0;
	
	if(LED_GPIO == led->type)
	{
		if(POLAR_NORMAL == led->polarity)
		{
			hal_gpio_export(led->pin);
			hal_gpio_set_value(led->pin,1);
		}
	}
	else if(LED_CPLD == led->type)
	{
		printf("%s: unsupport CPLD LED!\n", __func__);
		return ERROR;
	}
	else
	{
		printf("%s: unsupport LED type!\n", __func__);
		return ERROR;
	}
	return OK;
}
int hal_led_off(struct led_s *led)
{
	if(LED_OFF == led->state)
		return 0;
	
	if(LED_GPIO == led->type)
	{
		if(POLAR_NORMAL == led->polarity)
		{
			hal_gpio_export(led->pin);
			hal_gpio_set_value(led->pin,1);
		}
	}
	else if(LED_CPLD == led->type)
	{
		printf("%s: unsupport CPLD LED!\n", __func__);
		return ERROR;
	}
	else
	{
		printf("%s: unsupport LED type!\n", __func__);
		return ERROR;
	}
	return OK;

	return ;
}


