/*
 * Soft:        Keepalived is a failover program for the LVS project
 *              <www.linuxvirtualserver.org>. It monitor & manipulate
 *              a loadbalanced server pool using multi-layer checks.
 *
 * Part:        Dynamic data structure definition.
 *
 * Author:      Alexandre Cassen, <acassen@linux-vs.org>
 *
 *              This program is distributed in the hope that it will be useful,
 *              but WITHOUT ANY WARRANTY; without even the implied warranty of
 *              MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *              See the GNU General Public License for more details.
 *
 *              This program is free software; you can redistribute it and/or
 *              modify it under the terms of the GNU General Public License
 *              as published by the Free Software Foundation; either version
 *              2 of the License, or (at your option) any later version.
 *
 * Copyright (C) 2001-2017 Alexandre Cassen, <acassen@gmail.com>
 */

#ifndef _VRRP_DATA_H
#define _VRRP_DATA_H

/* system includes */
#include <sys/types.h>
#include <stdio.h>
#include <stdbool.h>

/* local includes */
#include "list_head.h"
#include "vector.h"
#include "vrrp_static_track.h"


/* Configuration data root */
typedef struct _vrrp_data {
	list_head_t		static_track_groups;	/* static_track_group_t */
	list_head_t		static_addresses;	/* ip_address_t */
	list_head_t		static_routes;		/* ip_route_t */
	list_head_t		static_rules;		/* ip_rule_t */
	list_head_t		vrrp_sync_group;	/* vrrp_sgroup_t */
	list_head_t		vrrp;			/* vrrp_t */
	list_head_t		vrrp_socket_pool;	/* sock_t */
	list_head_t		vrrp_script;		/* vrrp_script_t */
	list_head_t		vrrp_track_files;	/* tracked_file_t */
#ifdef _WITH_TRACK_PROCESS_
	list_head_t		vrrp_track_processes;	/* vrrp_tracked_process_t */
	size_t			vrrp_max_process_name_len;
	bool			vrrp_use_process_cmdline;
	bool			vrrp_use_process_comm;
#endif
#ifdef _WITH_BFD_
	list_head_t		vrrp_track_bfds;	/* vrrp_tracked_bfd_t */
#endif
	unsigned		num_smtp_alert;		/* No of smtp_alerts configured */
} vrrp_data_t;

/* Global Vars exported */
extern vrrp_data_t *vrrp_data;
extern vrrp_data_t *old_vrrp_data;
extern void *vrrp_buffer;
extern size_t vrrp_buffer_len;

/* prototypes */
extern static_track_group_t *alloc_static_track_group(const char *);
extern void alloc_saddress(const vector_t *);
extern void alloc_sroute(const vector_t *);
extern void alloc_srule(const vector_t *);
extern vrrp_sgroup_t *alloc_vrrp_sync_group(const char *);
extern vrrp_t *alloc_vrrp(const char *);
extern void alloc_vrrp_unicast_peer(const vector_t *);
extern void alloc_vrrp_track_if(const vector_t *);
extern vrrp_script_t *alloc_vrrp_script(const char *);
extern void free_vscript(vrrp_script_t *);
extern void alloc_vrrp_track_script(const vector_t *);
extern void alloc_vrrp_track_file(const vector_t *);
#ifdef _WITH_TRACK_PROCESS_
extern vrrp_tracked_process_t *alloc_vrrp_process(const char *);
extern void free_vprocess(vrrp_tracked_process_t *);
extern void alloc_vrrp_track_process(const vector_t *);
#endif
#ifdef _WITH_BFD_
extern void free_vrrp_tracked_bfd(vrrp_tracked_bfd_t *);
extern void alloc_vrrp_track_bfd(const vector_t *);
#endif
extern void alloc_vrrp_group_track_if(const vector_t *);
extern void alloc_vrrp_group_track_script(const vector_t *);
extern void alloc_vrrp_group_track_file(const vector_t *);
#ifdef _WITH_TRACK_PROCESS_
extern void alloc_vrrp_group_track_process(const vector_t *);
#endif
#ifdef _WITH_BFD_
extern void alloc_vrrp_group_track_bfd(const vector_t *);
#endif
extern void alloc_vrrp_vip(const vector_t *);
extern void alloc_vrrp_evip(const vector_t *);
extern void alloc_vrrp_vroute(const vector_t *);
extern void alloc_vrrp_vrule(const vector_t *);
extern void alloc_vrrp_buffer(size_t);
extern void free_vrrp_buffer(void);
extern vrrp_data_t *alloc_vrrp_data(void);
extern void free_vrrp_data(vrrp_data_t **);
extern void free_sync_group(vrrp_sgroup_t *);
extern void free_sock_list(list_head_t *);
extern void dump_sock_list(FILE *, const list_head_t *);
extern void dump_tracking_vrrp(FILE *, const void *);
extern void dump_tracking_vrrp_list(FILE *, const list_head_t *);
extern void dump_data_vrrp(FILE *);

#endif
