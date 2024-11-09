// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2024
 * ChenXiaoSong (chenxiaosong@chenxiaosong.com)
 *
 *  from
 *
 *  fs/ext2/inode.c
 *
 *  Copyright (C) 1992, 1993, 1994, 1995
 *  Remy Card (card@masi.ibp.fr)
 *  Laboratoire MASI - Institut Blaise Pascal
 *  Universite Pierre et Marie Curie (Paris VI)
 */

#include "myfs.h"

#define	DBG_FACILITY	MYFS_DEBUG_INODE

struct inode *myfs_iget(struct super_block *sb, unsigned long ino)
{
	struct inode *inode;

	myfs_debug(DBG_FACILITY, "\n");
	inode = iget_locked(sb, ino);
	if (!inode)
		return ERR_PTR(-ENOMEM);
	if (!(inode->i_state & I_NEW))
		return inode;

	unlock_new_inode(inode);
	return inode;
}

