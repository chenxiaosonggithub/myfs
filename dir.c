// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2024
 * ChenXiaoSong (chenxiaosong@chenxiaosong.com)
 *
 *  from
 *
 *  fs/ext2/dir.c
 *
 *  Copyright (C) 1992, 1993, 1994, 1995
 *  Remy Card (card@masi.ibp.fr)
 *  Laboratoire MASI - Institut Blaise Pascal
 *  Universite Pierre et Marie Curie (Paris VI)
 */

#include "myfs.h"

#define	DBG_FACILITY	MYFS_DEBUG_DIR


static int myfs_dir_open(struct inode *inode, struct file *file)
{
	myfs_debug(DBG_FACILITY, "\n");
	return 0;
}

static int myfs_dir_release(struct inode *inode, struct file *file)
{
	myfs_debug(DBG_FACILITY, "\n");
	return 0;
}

static int
myfs_readdir(struct file *file, struct dir_context *ctx)
{
	// TODO
	myfs_debug(DBG_FACILITY, "\n");
	return 0;
}

const struct file_operations myfs_dir_operations = {
	.open		= myfs_dir_open,
	.release	= myfs_dir_release,
	.read		= generic_read_dir,
	.iterate_shared	= myfs_readdir,
};
