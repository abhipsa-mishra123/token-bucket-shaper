#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>

#define BUFFER_SIZE 256

static char driver_buffer[BUFFER_SIZE];
static size_t buffer_length = 0;

static ssize_t traffic_driver_write(
    struct file *file,
    const char __user *buffer,
    size_t length,
    loff_t *offset)
{
    size_t copy_length;

    copy_length = length;

    if (copy_length >= BUFFER_SIZE)
        copy_length = BUFFER_SIZE - 1;

    if (copy_from_user(driver_buffer, buffer, copy_length))
        return -EFAULT;

    driver_buffer[copy_length] = '\0';
    buffer_length = copy_length;

    printk(KERN_INFO "Traffic Policier Driver: data received\n");

    return copy_length;
}

static ssize_t traffic_driver_read(
    struct file *file,
    char __user *buffer,
    size_t length,
    loff_t *offset)
{
    size_t remaining;
    size_t copy_length;

    if (*offset >= buffer_length)
        return 0;

    remaining = buffer_length - *offset;
    copy_length = length;

    if (copy_length > remaining)
        copy_length = remaining;

    if (copy_to_user(buffer, driver_buffer + *offset, copy_length))
        return -EFAULT;

    *offset += copy_length;

    return copy_length;
}

static const struct file_operations traffic_driver_fops =
{
    .owner = THIS_MODULE,
    .read = traffic_driver_read,
    .write = traffic_driver_write
};

static struct miscdevice traffic_driver_device =
{
    .minor = MISC_DYNAMIC_MINOR,
    .name = "traffic_policier",
    .fops = &traffic_driver_fops,
    .mode = 0666
};

static int __init traffic_driver_init(void)
{
    int result;

    result = misc_register(&traffic_driver_device);

    if (result != 0)
    {
        printk(KERN_ERR "Traffic Policier Driver: registration failed\n");
        return result;
    }

    printk(KERN_INFO "Traffic Policier Driver: loaded successfully\n");

    return 0;
}

static void __exit traffic_driver_exit(void)
{
    misc_deregister(&traffic_driver_device);

    printk(KERN_INFO "Traffic Policier Driver: unloaded\n");
}

module_init(traffic_driver_init);
module_exit(traffic_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Capstone Project");
MODULE_DESCRIPTION("Linux character device driver for Token-Bucket Traffic Policier");
