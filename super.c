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

static int myfs_fill_super(struct super_block *sb, void *data, int silent)
{
	int ret = 0;

	return ret;
}

static void myfs_kill_sb(struct super_block *sb)
{
	kill_block_super(sb);
}

static struct dentry *myfs_mount(struct file_system_type *fs_type,
	int flags, const char *dev_name, void *data)
{
	return mount_bdev(fs_type, flags, dev_name, data, myfs_fill_super);
}

static struct file_system_type myfs_fs_type = {
	.owner			= THIS_MODULE,
	.name			= "myfs",
	.mount			= myfs_mount,
	.kill_sb		= myfs_kill_sb,
	.fs_flags		= FS_REQUIRES_DEV,
};
MODULE_ALIAS_FS("myfs");

static int __init init_myfs(void)
{
	int err = 0;

	printk("%s:%d\n", __func__, __LINE__);
	err = register_filesystem(&myfs_fs_type);
	if (err)
		goto out;
out:
	return err;
}

static void __exit exit_myfs(void)
{
	printk("%s:%d\n", __func__, __LINE__);
	unregister_filesystem(&myfs_fs_type);
}

MODULE_AUTHOR("ChenXiaoSong");
MODULE_DESCRIPTION("My Filesystem");
MODULE_LICENSE("GPL");
module_init(init_myfs)
module_exit(exit_myfs)
