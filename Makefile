# SPDX-License-Identifier: GPL-2.0-or-later
#
# Makefile for the my-filesystem.
#

obj-m += myfs.o
myfs-y := main.o super.o inode.o

KDIR	:= /root/code/linux/x86_64-build/
PWD	:= $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

