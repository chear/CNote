# 1) to make s1_write2chardev.ko
obj-$(SAMPLE_WRITE_TO_CDEV) += s1_write2chardev.o

# 2) to make s2_boardctrl_ioctl
# List of programs to build
hostprogs-y := s2_boardctrl_ioctl

# Tell kbuild to always build the programs
always := $(hostprogs-y)
HOSTCFLAGS_s2_boardctrl_ioctl += -I$(objtree)/usr/include
