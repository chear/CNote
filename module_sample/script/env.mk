#############################################################################
# Hisi toolchain used to compile kernel modules
##############################################################################

#######################################################
## [here] Toolchains
#######################################################
export ARCH                      = arm
export HI_MAKEFLAGS				 = --no-print-directory
export ROOT_DIR 			     := /home/chear/ssd/Hisilicon/HSANV200R011C01SPC036TB001
export BUILD_DIR				 := $(ROOT_DIR)/openwrt/build_dir/target-arm-openwrt-linux-uclibcgnueabi
export HI_TOOLCHAIN_PREFIX       = openwrt
export HI_TOOLCHAINS_DIR         = $(ROOT_DIR)/toolchain/arm-openwrt-linux-uclibcgnueabi
export HI_TOOLCHAINS             = arm-$(HI_TOOLCHAIN_PREFIX)-linux-uclibcgnueabi
export HI_TOOLCHAINS_BIN         = $(HI_TOOLCHAINS_DIR)/bin
export HI_TOOLCHAIN_INC_DIR      = $(HI_TOOLCHAINS_DIR)/include
export HI_GATEWAY_ROOT_DIR       = $(BUILD_DIR)/hi_gateway
export HI_TOOLS_DIR				 = $(ROOT_DIR)/Tools/hitools
export PATH:=$(HI_TOOLS_DIR):$(PATH)

# prefix
ifndef CROSS_COMPILE
export CROSS_COMPILE := $(HI_TOOLCHAINS_BIN)/$(HI_TOOLCHAINS)-
endif

#define compiler
export AR       = $(CROSS_COMPILE)ar
export AS       = $(CROSS_COMPILE)as
export LD       = $(CROSS_COMPILE)ld
export CC       = $(CROSS_COMPILE)gcc
export CXX      = $(CROSS_COMPILE)g++
export CPP      = $(CROSS_COMPILE)cpp
export NM       = $(CROSS_COMPILE)nm
export STRIP    = $(CROSS_COMPILE)strip
export SSTRIP   = $(CROSS_COMPILE)sstrip
export OBJCOPY  = $(CROSS_COMPILE)objcopy
export OBJDUMP  = $(CROSS_COMPILE)objdump
export RANLIB   = $(CROSS_COMPILE)ranlib


#######################################################
# [here] Kernel and UBoot include
#######################################################
export HI_KERNEL_VER_NUM    = 3.18.11
export HI_KERNEL_VER        = linux-$(HI_KERNEL_VER_NUM)
export HI_KERNEL_DIR		= $(BUILD_DIR)/linux-hsan_generic/$(HI_KERNEL_VER)
export HI_KERNEL_INC_DIR    = $(HI_KERNEL_DIR)/include


#######################################################
# [here] HSAN Include
#######################################################
export HI_BUILD_INC_COMM_DIR     = $(HI_BUILD_INC_DIR)/common


#######################################################
# [here] Compileraiton flags
#######################################################
export HI_CFLAGS  += -Wall -DHI_SDK_DEBUG -O2
export HI_LDFLAGS +=


