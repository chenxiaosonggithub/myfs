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

 // TODO: 用于暂时调试，后续删除
static void myfs_set_debug_inode(struct inode *inode)
{
	switch (inode->i_ino) {
	case MYFS_ROOT_INO: // 2
	case 3:
	case 4:
		inode->i_mode = S_IFDIR | 0777;
		break;
	case 5:
	case 6:
		inode->i_mode = S_IFREG | 0777;
		break;
	}
}

struct inode *myfs_iget(struct super_block *sb, unsigned long ino)
{
	struct inode *inode;

	myfs_debug(DBG_FACILITY, "\n");
	inode = iget_locked(sb, ino);
	if (!inode)
		return ERR_PTR(-ENOMEM);
	myfs_set_debug_inode(inode);
	if (!(inode->i_state & I_NEW))
		return inode;

	if (S_ISREG(inode->i_mode)) {
		inode->i_fop = &myfs_file_operations;
	} else if (S_ISDIR(inode->i_mode)) {
		inode->i_fop = &myfs_dir_operations;
	}

	unlock_new_inode(inode);
	return inode;
}

