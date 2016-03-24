#include <hardware_test.h>

#define TEST_MAX_NUM 1

static board_test *boards[TEST_MAX_NUM];

unsigned int test_result = 0;

board_test * get_bdtest_by_name(char *name)
{
	int i = 0;
	for(i = 0; i < TEST_MAX_NUM; i++)
	{
		if(!strcmp(boards[i]->name, name))
			return boards[i];
	}
	return NULL;
}
int factory_test(board_test *bdtest, int test_index)
{
	int i = 0;
	bdtest->test_index = test_index;
	if(ALL_TEST == test_index)
		for (i = 0; i < ALL_TEST; i++) {
			if ((*bdtest->test_fnc_ptr[i])(bdtest) != 0) {
				printf("failed test!\n");
			}
		}
	else
	{
		if (bdtest->test_fnc_ptr[test_index])
			if((*bdtest->test_fnc_ptr[test_index])(bdtest) != 0) {
				printf("failed test!\n");
			}
	}
	return 0;
}

int register_hwtest(board_test *bdtest, int board_index)
{
	boards[board_index] = bdtest;
	return 0;
}

