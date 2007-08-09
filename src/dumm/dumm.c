/*
 * Copyright (C) 2007 Martin Willi
 * Hochschule fuer Technik Rapperswil
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

#define _GNU_SOURCE

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>

#include <debug.h>

#include "dumm.h"

#define PERME (S_IRWXU | S_IRWXG)
#define GUEST_DIR "guests"
#define SCENARIO_DIR "scenarios"
#define SCENARIO_DIFF_DIR "diff"

/**
 * instances of dumm, used to deliver signals
 */
static linked_list_t *instances = NULL;

typedef struct private_dumm_t private_dumm_t;

struct private_dumm_t {
	/** public dumm interface */
	dumm_t public;
	/** working dir */
	char *dir;
	/** directory of guests */
	char *guest_dir;
	/** directory of scenarios */
	char *scenario_dir;
	/** directory of loaded scenario */
	char *scenario;
	/** list of managed guests */
	linked_list_t *guests;
	/** list of managed bridges */
	linked_list_t *bridges;
	/** do not catch signals if we are destroying */
	bool destroying;
};

/**
 * Implementation of dumm_t.create_guest.
 */
static guest_t* create_guest(private_dumm_t *this, char *name, char *kernel, 
							 char *master, int mem)
{
	guest_t *guest;
	
	guest = guest_create(this->guest_dir, name, kernel, master, mem);
	if (guest)
	{
		this->guests->insert_last(this->guests, guest);
	}
	return guest;
}

/**
 * Implementation of dumm_t.create_guest_iterator.
 */
static iterator_t* create_guest_iterator(private_dumm_t *this)
{
	return this->guests->create_iterator(this->guests, TRUE);
}

/**
 * Implementation of dumm_t.create_bridge.
 */
static bridge_t* create_bridge(private_dumm_t *this, char *name)
{
	bridge_t *bridge;
	
	bridge = bridge_create(name);
	if (bridge)
	{
		this->bridges->insert_last(this->bridges, bridge);
	}
	return bridge;
}

/**
 * Implementation of dumm_t.create_bridge_iterator.
 */
static iterator_t* create_bridge_iterator(private_dumm_t *this)
{
	return this->bridges->create_iterator(this->bridges, TRUE);
}

/**
 * disable the currently enabled scenario 
 */
static void clear_scenario(private_dumm_t *this)
{
	iterator_t *iterator;
	guest_t *guest;

	free(this->scenario);
	this->scenario = NULL;

	iterator = this->guests->create_iterator(this->guests, TRUE);
	while (iterator->iterate(iterator, (void**)&guest))
	{
		guest->set_scenario(guest, NULL);
	}
	iterator->destroy(iterator);
}

/**
 * Implementation of dumm_t.load_scenario.
 */
static bool load_scenario(private_dumm_t *this, char *name)
{
	iterator_t *iterator;
	guest_t *guest;
	char dir[PATH_MAX];
	size_t len;
	
	if (name == NULL)
	{
		clear_scenario(this);
		return TRUE;
	}

	free(this->scenario);
	asprintf(&this->scenario, "%s/%s", this->scenario_dir, name);
	mkdir(this->scenario_dir, PERME);
	
	len = snprintf(dir, sizeof(dir), "%s/%s", this->scenario, SCENARIO_DIFF_DIR);
	if (len < 0 || len >= sizeof(dir))
	{
		clear_scenario(this);
		return FALSE;
	}
	
	if (access(this->scenario, F_OK) != 0)
	{	/* does not exist, create scenario */
		if (mkdir(this->scenario, PERME) != 0)
		{
			DBG1("creating scenario directory '%s' failed: %m", this->scenario);
			clear_scenario(this);
			return FALSE;
		}
		if (mkdir(dir, PERME) != 0)
		{
			DBG1("creating scenario overlay directory '%s' failed: %m", dir);
			clear_scenario(this);
			return FALSE;
		}
	}
	iterator = this->guests->create_iterator(this->guests, TRUE);
	while (iterator->iterate(iterator, (void**)&guest))
	{
		if (!guest->set_scenario(guest, dir))
		{
			iterator->destroy(iterator);
			clear_scenario(this);
			return FALSE;
		}
	}
	iterator->destroy(iterator);
	return TRUE;
}

/**
 * Implementation of dumm_t.save_scenario.
 */
static bool save_scenario(private_dumm_t *this)
{
	DBG1("scenario loading unimplemented.");
	return FALSE;
}

/**
 * signal handler 
 */
void signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	if (sig == SIGCHLD)
	{
		switch (info->si_code)
		{
			case CLD_EXITED:
			case CLD_KILLED:
			case CLD_DUMPED:
			{
				private_dumm_t *this;
				guest_t *guest;
				iterator_t *iterator, *guests;
				
				iterator = instances->create_iterator(instances, TRUE);
				while (iterator->iterate(iterator, (void**)&this))
				{
					if (this->destroying)
					{
						continue;
					}
					guests = this->guests->create_iterator(this->guests, TRUE);
					while (guests->iterate(guests, (void**)&guest))
					{
						if (guest->get_pid(guest) == info->si_pid)
						{
							guest->sigchild(guest);
							break;
						}
					}
					guests->destroy(guests);
				}
				iterator->destroy(iterator);
				break;
			}
			default:
				break;
		}

	}
	/* SIGHUP is currently just ignored */
}

/**
 * add a dumm instance
 */
static void add_instance(private_dumm_t *this)
{
	if (instances == NULL)
	{
		struct sigaction action;
		
		instances = linked_list_create();
		
		memset(&action, 0, sizeof(action));
		action.sa_sigaction = signal_handler;
		action.sa_flags = SA_SIGINFO;
		
		if (sigaction(SIGCHLD, &action, NULL) != 0 ||
			sigaction(SIGHUP, &action, NULL) != 0)
		{
			DBG1("installing signal handler failed!");
		}
	}
	instances->insert_last(instances, this);
}

/**
 * remove a dumm instance
 */
static void remove_instance(private_dumm_t *this)
{
	iterator_t *iterator;
	private_dumm_t *current;
	
	iterator = instances->create_iterator(instances, TRUE);
	while (iterator->iterate(iterator, (void**)&current))
	{
		if (current == this)
		{
			iterator->remove(iterator);
			break;
		}
	}
	iterator->destroy(iterator);
	if (instances->get_count(instances) == 0)
	{
		instances->destroy(instances);
		instances = NULL;
	}
}

/**
 * Implementation of dumm_t.destroy
 */
static void destroy(private_dumm_t *this)
{
	iterator_t *iterator;
	guest_t *guest;

	this->bridges->destroy_offset(this->bridges, offsetof(bridge_t, destroy));
	
	iterator = this->guests->create_iterator(this->guests, TRUE);
	while (iterator->iterate(iterator, (void**)&guest))
	{
		guest->stop(guest);
	}
	iterator->destroy(iterator);
	
	this->destroying = TRUE;
	this->guests->destroy_offset(this->guests, offsetof(guest_t, destroy));
	free(this->guest_dir);
	free(this->scenario_dir);
	free(this->scenario);
	free(this->dir);
	remove_instance(this);
	free(this);
}

/**
 * load all guests in our working dir
 */
static void load_guests(private_dumm_t *this)
{
	DIR *dir;
	struct dirent *ent;
	guest_t *guest;
	
	dir = opendir(this->guest_dir);
	if (dir == NULL)
	{
		return;
	}
	
	while ((ent = readdir(dir)))
	{
		if (streq(ent->d_name, ".") ||  streq(ent->d_name, ".."))
		{
			continue;
		}
		guest = guest_load(this->guest_dir, ent->d_name);
		if (guest)
		{
			DBG1("loaded guest '%s'", ent->d_name);
			this->guests->insert_last(this->guests, guest);
		}
		else
		{
			DBG1("loading guest in directory '%s' failed, skipped", ent->d_name);
		}
	}
	closedir(dir);
}

/**
 * create a dumm instance
 */
dumm_t *dumm_create(char *dir)
{
	char cwd[PATH_MAX];
	private_dumm_t *this = malloc_thing(private_dumm_t);
	
	this->public.create_guest = (guest_t*(*)(dumm_t*,char*,char*,char*,int))create_guest;
	this->public.create_guest_iterator = (iterator_t*(*)(dumm_t*))create_guest_iterator;
	this->public.create_bridge = (bridge_t*(*)(dumm_t*, char *name))create_bridge;
	this->public.create_bridge_iterator = (iterator_t*(*)(dumm_t*))create_bridge_iterator;
	this->public.load_scenario = (bool(*)(dumm_t*, char *name))load_scenario;
	this->public.save_scenario = (bool(*)(dumm_t*))save_scenario;
	this->public.destroy = (void(*)(dumm_t*))destroy;
	
	this->destroying = FALSE;
	if (*dir == '/' || getcwd(cwd, sizeof(cwd)) == 0)
	{
		this->dir = strdup(dir);
	}
	else
	{
		asprintf(&this->dir, "%s/%s", cwd, dir);
	}
	this->scenario = NULL;
	asprintf(&this->guest_dir, "%s/%s", this->dir, GUEST_DIR);
	asprintf(&this->scenario_dir, "%s/%s", this->dir, SCENARIO_DIR);
	this->guests = linked_list_create();
	this->bridges = linked_list_create();
	
	add_instance(this);
	
	if (mkdir(this->guest_dir, PERME) < 0 && errno != EEXIST)
	{
		DBG1("creating guest directory '%s' failed: %m", this->guest_dir);
		destroy(this);
		return NULL;
	}
	
	load_guests(this);
	return &this->public;
}

