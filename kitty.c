#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/string.h>
#include <linux/uaccess.h>
static ssize_t device_read(struct file *filp,char *buff,size_t length,loff_t *offset){
	const char *s_ptr;
	int error_code=0;
	ssize_t len=0;
	s_ptr="Meow!!! =^..^=\n";
	len=min( (unsigned long)(strlen(s_ptr)-*offset),(unsigned long)(length));
	if(len<=0){
		return 0;
		}
		
	error_code=copy_to_user(buff, s_ptr+*offset,len);
	printk("The file was read! len:%d\n",len);
	printk("Error code: %d\n",error_code);
	
	*offset+=len;
	return len;
	}
static struct file_operations fops={
	.read=device_read,
	};
static int major;
static int __init start(void){
	printk(KERN_ALERT "Kitty Module Loaded\n");
	major=register_chrdev(0,"kitty",&fops);
	if(major<0){
		printk(KERN_ALERT "Kitty char-dev module loaded!\n");
		return major;
		}
	printk("New char-dev 'kitty' created with major %d and minor %d\n",major,0);
	return 0;
	}
static void __exit end(void){
	unregister_chrdev(major,"kitty");
	printk(KERN_ALERT "Kitty unloaded\n");
	}
module_init(start);
module_exit(end);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Edith F");
MODULE_DESCRIPTION("This is a char-dev of a kitty\n");
