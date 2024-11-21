/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2024
 * ChenXiaoSong (chenxiaosong@chenxiaosong.com)
 *
 *  from
 *
 *  fs/ext2/ext2.h
 *
 *  Copyright (C) 1992, 1993, 1994, 1995
 *  Remy Card (card@masi.ibp.fr)
 *  Laboratoire MASI - Institut Blaise Pascal
 *  Universite Pierre et Marie Curie (Paris VI)
 */
#ifndef __NFS_NETNS_H__
#define __NFS_NETNS_H__

#include <linux/fs.h>

#define MYFS_SUPER_MAGIC	0x555555

#define MYFS_NAME_LEN 255

/*
 * Special inode numbers
 */
#define	MYFS_BAD_INO		 1	/* Bad blocks inode */
#define	MYFS_ROOT_INO		 2	/* Root inode */

extern int myfs_debug_types;

#define MYFS_DEBUG_MAIN		BIT(0)
#define MYFS_DEBUG_SUPER	BIT(1)
#define MYFS_DEBUG_INODE	BIT(2)
#define MYFS_DEBUG_FILE		BIT(3)
#define MYFS_DEBUG_DIR		BIT(4)
#define MYFS_DEBUG_ALL		(MYFS_DEBUG_MAIN | MYFS_DEBUG_SUPER | \
				 MYFS_DEBUG_INODE | MYFS_DEBUG_FILE | \
				 MYFS_DEBUG_DIR)

#define myfs_debug(type, fmt, ...)				\
	do {							\
		if (myfs_debug_types & type)	\
			pr_info("[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__);		\
	} while (0)


extern struct file_system_type myfs_fs_type;
extern const struct file_operations myfs_file_operations;
extern const struct file_operations myfs_dir_operations;
extern struct class myfs_ctrl_class;

extern struct inode *myfs_iget(struct super_block *sb, unsigned long ino);

#endif
