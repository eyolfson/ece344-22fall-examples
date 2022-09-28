#include <linux/module.h>
#include <linux/kernel.h>

MODULE_AUTHOR("Jon Eyolfson");
MODULE_DESCRIPTION("Prints messages in the kernel");
MODULE_LICENSE("GPL");

static int __init hello_init(void)
{
    printk(KERN_INFO "hello_init\n");
    return 0;
}
  
static void __exit hello_exit(void)
{
    printk(KERN_INFO "hello_exit\n");
}
  
module_init(hello_init);
module_exit(hello_exit);
