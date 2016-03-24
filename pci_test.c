#include <factory_test.h>

char *strstr(const char *s1, const char *s2)
{
	size_t l1, l2;

	l2 = strlen(s2);
	if (!l2)
		return (char *)s1;
	l1 = strlen(s1);
	while (l1 >= l2) {
		l1--;
		if (!memcmp(s1, s2, l2))
			return (char *)s1;
		s1++;
	}
	return NULL;
}

int pci_test(board_test *bdtest)
{
	int fd, len, cnt, i, num;
	char tmp[16];
	char *line = NULL;
	char *pos = NULL;
	system("lspci > /tmp/pci_info.txt");
	if ((fd = open("/tmp/pci_info.txt", O_RDWR)) < 0) 
	{
		printf("%s:open /tmp/pci_info.txt error!\n", __func__);
		return  TEST_FAIL;
	}
	
	while(-1 != (cnt = getline(&line, &len, fd)))	
	{
		for(i = 0; bdtest->pci[i].device_id != -1; i++)
		{
			sprintf(tmp, "%.4x:%.4x", bdtest->pci[i].vendor_id, bdtest->pci[i].device_id);
			if((pos = strstr(line,tmp)) != NULL)
			{
				num++;
			}
		} 
	} 

	if(num == bdtest->pci_dev_num)
	{
		test_result &= ~PCI_TEST_FAIL;
		printf("PCI Test: OK!\n");
		return TEST_PASS;
	}
	test_result |= PCI_TEST_FAIL;
	printk("PCI Test: ERROR!\n");
	return  TEST_FAIL;
}

