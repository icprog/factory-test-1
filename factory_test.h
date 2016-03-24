#ifndef _HARDWARE_TEST_H
#define _HARDWARE_TEST_H
#include <hal_led.h>

#define TEST_PASS                	(0x00)
#define TEST_FAIL                	(0x01)

enum {
	LED_TEST = 0,
	WDT_TEST,
	RTC_TEST,
	EEPROM_TEST,
	SFP_TEST,
	PCI_TEST,
	SWITCH_TEST,
	USB_TEST,
	ETH_TEST,
	WIFI_TEST,
	SSD_TEST,
	BT_TEST,
	GPS_TEST,
	LTE_TEST,
	ALL_TEST
}

#define LED_TEST_FAIL 0x00000001
#define WDT_TEST_FAIL 0x00000002
#define RTC_TEST_FAIL 0x00000004
#define EEPROM_TEST_FAIL 0x00000008
#define SFP_TEST_FAIL 0x00000010
#define PCI_TEST_FAIL 0x00000020
#define SWITCH_TEST_FAIL 0x00000040
#define USB_TEST_FAIL 0x00000080
#define ETH_TEST_FAIL 0x00000100
#define WIFI_TEST_FAIL 0x00000200
#define SSD_TEST_FAIL 0x00000400
#define BT_TEST_FAIL 0x00000800
#define GPS_TEST_FAIL 0x00001000
#define LTE_TEST_FAIL 0x00002000

struct pci_info
{
	int vendor_id;
	int device_id;
};

typedef int (test_fnc_t) (board_test *hwtest);

typedef struct test
{
	const char *name;
	int board_id;
	int pci_dev_num;
	int led_num;
	int test_index;
	
	struct pci_info *pci;
	struct led_s *leds;
	
	test_fnc_t *test_fnc_ptr[ALL_TEST];
	
} board_test;

extern unsigned int test_result;
int register_test_func(board_test *hwtest, test_fnc_t **test_sequence);
int register_hwtest(board_test *hwtest);

#endif

