/*
 * ioctl() Example
 * This sample its based for driver/boardctrl/boardctrl.c for Mitrastar.
 */


/* Linux */
#include <linux/types.h>
#include <linux/input.h>
#include <linux/hidraw.h>

/* Unix */
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* C */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define BOARDCTRL_TEST 			 (0)
#define BOARDCTRL_BTN_TEST 		 (1)
#define BOARDCTRL_SET_LED		 (2)
#define BOARDCTRL_SYSLOG_FLAG	 (3)
#define BOARDCTRL_BP_GET	 	 (4)
#define BOARDCTRL_LED_BLINK      (5)
#define BOARDCTRL_SET_PHONE_PID  (6)
#define BOARDCTRL_SET_CUSTOMGUI	 (7)
#define BOARDCTRL_WDT_START		 (8)
#define BOARDCTRL_WDT_STOP		 (9)
#define BOARDCTRL_WDT_KICK		 (10)
#define BOARDCTRL_TEST_LED		(11)


const char *bus_str(int bus);

int main(int argc, char **argv) {
    int fd;
	int i, res, desc_size = 0;
	char buf[256];
	/*
    struct hidraw_report_descriptor rpt_desc;
	struct hidraw_devinfo info;
    */

    /* Open the Device with non-blocking reads. In real life,
	   don't use a hard coded path; use libudev instead. */
	fd = open("/dev/boardctrl", O_RDWR|O_NONBLOCK);
    if (fd < 0) {
		perror("Unable to open device");
		return 1;
	}

    /*
	memset(&rpt_desc, 0x0, sizeof(rpt_desc));
	memset(&info, 0x0, sizeof(info));
	memset(buf, 0x0, sizeof(buf));
    */

	/* Get Report Descriptor Size */
	res = ioctl(fd, BOARDCTRL_TEST, &desc_size);
	if (res < 0)
		perror("BOARDCTRL_TEST");
	else
		printf("Report Descriptor Size: %d\n", desc_size);

	close(fd);


    return 0;
}
