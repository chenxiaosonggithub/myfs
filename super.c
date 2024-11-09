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

#include "myfs.h"
#include <linux/statfs.h>

#define	DBG_FACILITY	MYFS_DEBUG_SUPER

static int myfs_statfs (struct dentry * dentry, struct kstatfs * buf)
{
	buf->f_type = MYFS_SUPER_MAGIC;
	buf->f_bsize = 4096;
	buf->f_blocks = 5;
	buf->f_bfree = 5;
	buf->f_bavail = 5;
	buf->f_files = 5;
	buf->f_ffree = 5;
	buf->f_namelen = MYFS_NAME_LEN;
	buf->f_fsid = (__kernel_fsid_t){.val = {(u32)55, (u32)55}};
	return 0;
}

static const struct super_operations myfs_sops = {
	.statfs		= myfs_statfs,
};

static int myfs_fill_super(struct super_block *sb, void *data, int silent)
{
	int ret = 0;
	struct inode *root;

	sb->s_op = &myfs_sops;

	root = myfs_iget(sb, MYFS_ROOT_INO);
	if (IS_ERR(root)) {
		ret = PTR_ERR(root);
		goto err;
	}

	sb->s_root = d_make_root(root);
	if (!sb->s_root) {
		pr_err("%s:%d, error: get root inode failed", __func__, __LINE__);
		ret = -ENOMEM;
		goto err;
	}
err:
	return ret;
}

static void myfs_kill_sb(struct super_block *sb)
{
	kill_block_super(sb);
}

static struct dentry *myfs_mount(struct file_system_type *fs_type,
	int flags, const char *dev_name, void *data)
{
	myfs_debug(DBG_FACILITY, "\n");
	return mount_bdev(fs_type, flags, dev_name, data, myfs_fill_super);
}

struct file_system_type myfs_fs_type = {
	.owner			= THIS_MODULE,
	.name			= "myfs",
	.mount			= myfs_mount,
	.kill_sb		= myfs_kill_sb,
	.fs_flags		= FS_REQUIRES_DEV,
};

