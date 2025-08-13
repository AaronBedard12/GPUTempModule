#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aaron Bedard");
MODULE_DESCRIPTION("A simple kernel module");
MODULE_VERSION("0.1");

static int __init main(void)
{
    printk(KERN_INFO "The process is \"%s\" (pid %i)\n", current->comm, current->pid);
    return 0;
}

static void __exit exit(void)
{
    printk(KERN_INFO "Goodbye World \n");
}

module_init(main);
module_exit(exit);
