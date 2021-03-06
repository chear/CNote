/*
 * NOTE:
 */


#include <linux/init.h>           // Macros used to mark up functions e.g. __init __exit
#include <linux/module.h>         // Core header for loading LKMs into the kernel
#include <linux/device.h>         // Header to support the kernel Driver Model
#include <linux/kernel.h>         // Contains types, macros, functions for the kernel
#include <linux/fs.h>             // Header for the Linux file system support
#include <linux/uaccess.h>          // Required for the copy to user function
#include <linux/input.h>
#include <linux/mm.h>
#include <linux/slab.h>

#define TELNET_TTY "/dev/ttyp0"
#define DEVICE_NAME "chear_dev"     // create device file for /dev/char_dev
#define CLASS_NAME "chear"

static int    majorNumber;                  ///< Stores the device number -- determined automatically
static char   message[256] = {0};           ///< Memory for the string that is passed from userspace
static short  size_of_message;              ///< Used to remember the size of the string stored
static int    numberOpens = 0;              ///< Counts the number of times the device is opened
static struct class*  ebbcharClass  = NULL; ///< The device-driver class struct pointer
static struct device* ebbcharDevice = NULL; ///< The device-driver device struct pointer


// The prototype functions for the character driver -- must come before the struct definition
static int     dev_open(struct inode *, struct file *);
static int     dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);

/* @brief Devices are represented as file structure in the kernel. The file_operations structure from
 *  /linux/fs.h lists the callback functions that you wish to associated with your file operations
 *  using a C99 syntax structure. char devices usually implement open, read, write and release calls
 */
static struct file_operations fops =
{
    .open = dev_open,
    .read = dev_read,
    .write = dev_write,
    .release = dev_release,
};



/* @brief The device open function that is called each time the device is opened
 *  This will only increment the numberOpens counter in this case.
 *  @param inodep A pointer to an inode object (defined in linux/fs.h)
 *  @param filep A pointer to a file object (defined in linux/fs.h)
 */
static int dev_open(struct inode *inodep, struct file *filep){
    numberOpens++;
    printk(KERN_INFO "EBBChar: Device has been opened %d time(s)\n");
}


/* @brief This function is called whenever device is being read from user space i.e. data is
 *  being sent from the device to the user. In this case is uses the copy_to_user() function to
 *  send the buffer string to the user and captures any errors.
 *  @param filep A pointer to a file object (defined in linux/fs.h)
 *  @param buffer The pointer to the buffer to which this function writes the data
 *  @param len The length of the b
 *  @param offset The offset if required
 */
static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset){
    int error_count = 0;
    //copy_to_user has the format ( * to, *from, size ) and returns 0 on success  
    error_count = copy_to_user(buffer, message, size_of_message);

    if (error_count==0){            // if true then have success
        printk(KERN_INFO "EBBChar: Sent %d characters to the user\n", size_of_message);
        return (size_of_message=0); // clear the position to the start and return 0
    }
    else {
        printk(KERN_INFO "EBBChar: Failed to send %d characters to the user\n", error_count);
        return -EFAULT;             // Failed -- return a bad address message (i.e. -14)
    }
}

/* @brief This function is called whenever the device is being written to from user space i.e.
 *  data is sent to the device from the user. The data is copied to the message[] array in this
 *  LKM using the sprintf() function along with the length of the string.
 *  @param filep A pointer to a file object
 *  @param buffer The buffer to that contains the string to write to the device
 *  @param len The length of the array of data that is being passed in the const char buffer
 *  @param offset The offset if required
 */
static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset){
    sprintf(message, "%s(%zu letters)", buffer, len);  // appending received string with its length
    size_of_message = strlen(message);                 // store the length of the stored message
    printk(KERN_INFO "EBBChar: Received %zu characters from the user\n", len);
    return len;
}

/* @brief The device release function that is called whenever the device is closed/released by
 *  the userspace program
 *  @param inodep A pointer to an inode object (defined in linux/fs.h)
 *  @param filep A pointer to a file object (defined in linux/fs.h)
 */
static int dev_release(struct inode *inodep, struct file *filep){
    printk(KERN_INFO "EBBChar: Device successfully closed\n");
    return 0;
}


/*
 * handle to send msg to /dev/ttyp0 ,for telnet login users.
 */
void handle_print(void){
    filewrite(TELNET_TTY, "kernel write test\n");
}


void fileread(const char * filename){
//    struct file*    filp;  // 
//    struct inode*   inode; // inodefile
//    mm_segment_t    fs;
//
//    /* :
//     * typedefstruct{
//     *  unsignedlongseg;
//     *  }mm_segment_t;
//     */
//
//    off_t fsize;
//    char*   buf;
//    unsigned long magic;
//    printk(KERN_DEBUG "start....\n"); 
//    filp = filp_open(filename,O_RDONLY,0);            //  
//    inode = filp->f_dentry->d_inode;  // 
//    magic = inode->i_sb->s_magic;  // 
//    printk(KERN_DEBUG "<1>file system magic:%li \n",magic); 
//    printk(KERN_DEBUG "<1>super blocksize:%li \n",inode->i_sb->s_blocksize); 
//    printk(KERN_DEBUG "<1>inode %li \n",inode->i_ino); 
//    fsize=inode->i_size; 
//    printk(KERN_DEBUG "<1>file size:%i \n",(int)fsize); 
//    //buf = (char *) kmalloc(fsize+1,GFP_ATOMIC); // 
//    buf = kmalloc(fsize+1,GFP_ATOMIC); 
//
//    fs = get_fs();
//    set_fs(KERNEL_DS);
//    filp->f_op->read(filp,buf,fsize,&(filp->f_pos));
//    set_fs(fs);
//    buf[fsize] = '\0';
//    printk(KERN_DEBUG "<1>The File Content is:\n");
//    printk(KERN_DEBUG "<1>%s",buf);
//    filp_close(filp,NULL);
}

void filewrite (char* filename, char* data){
    struct file *filp;
    mm_segment_t fs;
    filp = filp_open(filename, O_RDWR|O_APPEND, 0644);
    if(IS_ERR(filp)){
        printk(KERN_ERR "open error \n");
        return;
    }
    fs = get_fs();
    set_fs(KERNEL_DS);
    filp->f_op->write(filp , data, strlen(data) , &filp->f_pos);
    set_fs(fs);
    filp_close(filp,NULL);
}

void formatMsg(char* msg){
    unsigned int len = strlen(msg) , i =0;
    len += 10;
    char* border = (char *)kmalloc(len + 1 , GFP_KERNEL);
    char* output = (char *)kmalloc(len + 1, GFP_KERNEL);
    snprintf(output, len + 1, "|    %s    |\n", msg);
    printk(KERN_DEBUG "%s" , output);
    for (i=0;i<len;i++)
        border[i] ='-';
    border[len] = '\n';
    filewrite(TELNET_TTY , border);
    filewrite(TELNET_TTY , output);
    filewrite(TELNET_TTY , border);
}

static int __init sample_init(void)
{
	int ret ,fd;
	printk(KERN_INFO "module initializing !! \n");

    // Try to dynamically allocate a major number for the device -- more difficult but worth it
    majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
    if (majorNumber<0){
        printk(KERN_ALERT "EBBChar failed to register a major number\n");
        return majorNumber;
    }
    printk(KERN_INFO "EBBChar: registered correctly with major number %d\n", majorNumber);

    // Register the device class
    ebbcharClass = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(ebbcharClass)){                // Check for error and clean up if there is
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to register device class\n");
        return PTR_ERR(ebbcharClass);         // Correct way to return an error on a pointer
    }
    printk(KERN_INFO "EBBChar: device class registered correctly\n");

    // Register the device driver
    ebbcharDevice = device_create(ebbcharClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
    if (IS_ERR(ebbcharDevice)){               // Clean up if there is an error
        class_destroy(ebbcharClass);          // Repeated code but the alternative is goto statements
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to create the device\n");
        return PTR_ERR(ebbcharDevice);
    }
    printk(KERN_INFO "EBBChar: device class created correctly !!! \n"); // Made it! device was initialized

    formatMsg("kernel");
//    filewrite(TELNET_TTY, "kernel write test\n");
    
    return 0;
}


static void __exit sample_exit(void){
    device_destroy(ebbcharClass, MKDEV(majorNumber, 0));     // remove the device
    class_unregister(ebbcharClass);                          // unregister the device class
    class_destroy(ebbcharClass);                             // remove the device class
    unregister_chrdev(majorNumber, DEVICE_NAME);             // unregister the major number
    printk(KERN_INFO "EBBChar: Goodbye from the LKM!\n");
    printk(KERN_INFO "module exit !!\n");

}

module_init(sample_init)
module_exit(sample_exit)
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chear Huang <chear.huang@mistrastar.com>");

