// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright (C) 2024
 * ChenXiaoSong (chenxiaosong@chenxiaosong.com)
 *
 *  from
 *
 *  fs/smb/server/server.c
 *
 *  Copyright (C) 2016 Namjae Jeon <linkinjeon@kernel.org>
 *  Copyright (C) 2018 Samsung Electronics Co., Ltd.
 */

#include <linux/module.h>
#include "myfs.h"
#include <linux/sysfs.h>
#include <linux/device/class.h>

#define	DBG_FACILITY	MYFS_DEBUG_MAIN

int myfs_debug_types = MYFS_DEBUG_ALL; // 开发时候调试用

static const char * const debug_type_strings[] = {"main", "super", "inode"};

static ssize_t debug_show(const struct class *class,
	const struct class_attribute *attr, char *buf)
{
	ssize_t sz = 0;
	int i, pos = 0;

	for (i = 0; i < ARRAY_SIZE(debug_type_strings); i++) {
		if ((myfs_debug_types >> i) & 1) {
			pos = sysfs_emit_at(buf, sz, "[%s] ", debug_type_strings[i]);
		} else {
			pos = sysfs_emit_at(buf, sz, "%s ", debug_type_strings[i]);
		}
		sz += pos;
	}
	sz += sysfs_emit_at(buf, sz, "\n");
	return sz;
}

static ssize_t debug_store(const struct class *class, const struct class_attribute *attr,
			   const char *buf, size_t len)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(debug_type_strings); i++) {
		if (sysfs_streq(buf, "all")) {
			if (myfs_debug_types == MYFS_DEBUG_ALL)
				myfs_debug_types = 0;
			else
				myfs_debug_types = MYFS_DEBUG_ALL;
			break;
		}

		if (sysfs_streq(buf, debug_type_strings[i])) {
			if (myfs_debug_types & (1 << i))
				myfs_debug_types &= ~(1 << i);
			else
				myfs_debug_types |= (1 << i);
			break;
		}
	}

	return len;
}

static CLASS_ATTR_RW(debug);

static struct attribute *myfs_ctrl_class_attrs[] = {
	&class_attr_debug.attr,
	NULL,
};
ATTRIBUTE_GROUPS(myfs_ctrl_class);

static struct class myfs_ctrl_class = {
	.name		= "myfs-ctrl",
	.class_groups	= myfs_ctrl_class_groups,
};

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
