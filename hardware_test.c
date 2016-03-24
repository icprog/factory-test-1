#include <linux/kernel.h>

#include <hardware_test.h>

hw_test *msg_hwtest;
test_fnc_t **test_fnc_ptr;



hw_test * get_hwtest_by_id(int board_id)
{
	return NULL;
}

hw_test * get_hwtest_by_name(char *name)
{
	return NULL;
}
int msg_hardware_test(int test_index)
{
	msg_hwtest->test_index = test_index;
	if(-1 == test_index)
		for (; *test_fnc_ptr; ++test_fnc_ptr) {
			if ((*test_fnc_ptr)(msg_hwtest) != 0) {
				printk("failed test!\n");
			}
		}
	else
	{
		if (test_fnc_ptr[test_index])
			if((test_fnc_ptr[test_index])(msg_hwtest) != 0) {
				printk("failed test!\n");
			}
	}
	return 0;
}
int register_test_func(test_fnc_t **test_sequence)
{
	test_fnc_ptr = test_sequence;
	return 0;
}

int register_hwtest(hw_test *hwtest)
{
	msg_hwtest = hwtest;
	return 0;
}

