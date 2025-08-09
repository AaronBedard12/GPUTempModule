#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("You");
MODULE_DESCRIPTION("Simple GPU temperature reader using hwmon sysfs");

static char *path = "/sys/class/hwmon/hwmon0/temp1_input";
module_param(path, charp, 0444);
MODULE_PARM_DESC(path, "Path to GPU temperature sensor sysfs file");

static int __init gpu_temp_reader_init(void)
{
    struct file *f;
    char *buf;
    loff_t pos = 0;
    ssize_t read_size;
    int temp_millic = 0;
    int ret;

    buf = kzalloc(32, GFP_KERNEL);
    if (!buf)
        return -ENOMEM;

    f = filp_open(path, O_RDONLY, 0);
    if (IS_ERR(f)) {
        printk(KERN_ERR "Failed to open %s\n", path);
        kfree(buf);
        return PTR_ERR(f);
    }

    read_size = kernel_read(f, buf, 31, &pos);
    if (read_size > 0) {
        buf[read_size] = '\0';
        ret = kstrtoint(strstrip(buf), 10, &temp_millic);
        if (ret == 0)
            printk(KERN_INFO "GPU Temperature: %d.%d°C\n",
                   temp_millic / 1000, temp_millic % 1000);
        else
            printk(KERN_ERR "Failed to parse temperature: %s\n", buf);
    } else {
        printk(KERN_ERR "Failed to read temperature\n");
    }

    filp_close(f, NULL);
    kfree(buf);

    return 0;
}

static voi

