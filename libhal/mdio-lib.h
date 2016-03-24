
#define CMD_MDIO_READ  0x80000000
#define CMD_MDIO_WRITE 0x80000001

struct mdio_read_s
{
    unsigned int phyAddr;
    unsigned int regAddr;
    unsigned short *pdata;
};

struct mdio_write_s
{
    unsigned int phyAddr;
    unsigned int regAddr;
    unsigned short data;
};
