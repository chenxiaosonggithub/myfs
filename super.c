// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2024
 * ChenXiaoSong (chenxiaosong@chenxiaosong.com)
 *
 *  from
 *
 *  linux/fs/ext2/super.c
 *
 *  Copyright (C) 1992, 1993, 1994, 1995
 *  Remy Card (card@masi.ibp.fr)
 *  Laboratoire MASI - Institut Blaise Pascal
 *  Universite Pierre et Marie Curie (Paris VI)
 */

#include <linux/module.h>
#include "myfs.h"

static int __init init_myfs(void)
{
	int err = 0;

	return err;
}

static void __exit exit_myfs(void)
{
}

MODULE_AUTHOR("ChenXiaoSong");
MODULE_DESCRIPTION("My Filesystem");
MODULE_LICENSE("GPL");
module_init(init_myfs)
module_exit(exit_myfs)
