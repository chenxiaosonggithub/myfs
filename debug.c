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

#include <linux/device/class.h>
#include "myfs.h"

int myfs_debug_types = MYFS_DEBUG_ALL; // 开发时候调试用

static const char * const debug_type_strings[] = {"main", "super", "inode", "file", "dir"};

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

struct class myfs_ctrl_class = {
	.name		= "myfs-ctrl",
	.class_groups	= myfs_ctrl_class_groups,
};
