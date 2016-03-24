#include <sys/types.h>
#include <linux/net.h>
#include <ctrlnetlink.h>
#include <linux/sockios.h>

#include <msg_plat.h>


int hal_cpld_read(int slot, unsigned char *data, int offset, int len)
{
	struct plat_ioctl_args io_args;
    struct i2c_args_s i2c_args;
    int fd = -1, ret = 0;

    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return -1;

    memset(&io_args, 0, sizeof(struct plat_ioctl_args));

    io_args.subcmd = PLT_CPLD_READ; // plat_ioctl_cmds
    io_args.u.i2c_args.offset = offset;
    io_args.u.i2c_args.len = len;
    io_args.u.i2c_args.data = data;

    ret = ioctl(fd, SIOCSPLTDRV, &io_args);

    close (fd);

    if (ret < 0)
    {
        printf("%s:ioctl error.\n\r", __FUNCTION__);
        return -1;
    }

    return 0;
}
int hal_cpld_write(int slot, unsigned char *data, int offset, int len)
{
	struct plat_ioctl_args io_args;
    struct i2c_args_s i2c_args;
    int fd = -1, ret = 0;

    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return -1;

    memset(&io_args, 0, sizeof(struct plat_ioctl_args));

    io_args.subcmd = PLT_CPLD_WRITE; // plat_ioctl_cmds
    io_args.u.i2c_args.offset = offset;
    io_args.u.i2c_args.len = len;
    io_args.u.i2c_args.data = data;

    ret = ioctl(fd, SIOCSPLTDRV, &io_args);

    close (fd);

    if (ret < 0)
    {
        printf("%s:ioctl error.\n\r", __FUNCTION__);
        return -1;
    }

    return 0;
}

