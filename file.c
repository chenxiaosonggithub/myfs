// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2024
 * ChenXiaoSong (chenxiaosong@chenxiaosong.com)
 *
 *  from
 *
 *  linux/fs/ext2/file.c
 *
 *  Copyright (C) 1992, 1993, 1994, 1995
 *  Remy Card (card@masi.ibp.fr)
 *  Laboratoire MASI - Institut Blaise Pascal
 *  Universite Pierre et Marie Curie (Paris VI)
 */

#include "myfs.h"

#define	DBG_FACILITY	MYFS_DEBUG_FILE

static int myfs_file_open(struct inode *inode, struct file *filp)
{
	myfs_debug(DBG_FACILITY, "\n");
	return generic_file_open(inode, filp);
}

static int myfs_release_file(struct inode * inode, struct file * filp)
{
	myfs_debug(DBG_FACILITY, "\n");
	return 0;
}

const struct file_operations myfs_file_operations = {
	.open		= myfs_file_open,
	.release	= myfs_release_file,
};
