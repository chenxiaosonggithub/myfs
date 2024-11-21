// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright (C) 2024
 * ChenXiaoSong (chenxiaosong@chenxiaosong.com)
 */

#include <linux/module.h>
#include <linux/device/class.h>
#include "myfs.h"

#define	DBG_FACILITY	MYFS_DEBUG_MAIN

static int __init init_myfs(void)
{
	int ret = 0;

	ret = class_register(&myfs_ctrl_class);
	if (ret) {
		pr_err("Unable to register myfs-ctrl class\n");
		return ret;
	}

	ret = register_filesystem(&myfs_fs_type);
	if (ret)
		goto out;
	myfs_debug(DBG_FACILITY, "success\n");
	return 0;
out:
	class_unregister(&myfs_ctrl_class);
	return ret;
}

static void __exit exit_myfs(void)
{
	myfs_debug(DBG_FACILITY, "\n");
	class_unregister(&myfs_ctrl_class);
	unregister_filesystem(&myfs_fs_type);
}

MODULE_AUTHOR("ChenXiaoSong");
MODULE_DESCRIPTION("My Filesystem");
MODULE_LICENSE("GPL");
module_init(init_myfs)
module_exit(exit_myfs)
