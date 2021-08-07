/*
 * Copyright (C) 1997-2001 Id Software, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 * =======================================================================
 *
 * Header for the in-game menu.
 *
 * =======================================================================
 */ 

#ifndef CTF_MENU_H
#define CTF_MENU_H

enum
{
	PMENU_ALIGN_LEFT,
	PMENU_ALIGN_CENTER,
	PMENU_ALIGN_RIGHT,
};

enum
{
	PMENU_NORMAL = 0,
	PMENU_SCROLLING,
	PMENU_VOTE
};

typedef struct pmenuhnd_s
{
	struct pmenu_s *header; /* FS */
	struct pmenu_s *entries;
	int cur;
	int num;
	int numheader; /* FS */
	void *arg;
	int menutype;
} pmenuhnd_t;

typedef void (*SelectFunc_t)(edict_t *ent, pmenuhnd_t *hnd);

typedef struct pmenu_s
{
	char *text;
	int align;
	SelectFunc_t SelectFunc;
} pmenu_t;

pmenuhnd_t *PMenu_Open(edict_t *ent,
		pmenu_t *entries,
		pmenu_t *header,
		int cur,
		int num,
		int numheader,
		void *arg,
		int menutype);
void PMenu_Close(edict_t *ent);
void PMenu_UpdateEntry(pmenu_t *entry,
		const char *text,
		int align,
		SelectFunc_t SelectFunc);
void PMenu_Do_Update(edict_t *ent);
void PMenu_Update(edict_t *ent);
void PMenu_Next(edict_t *ent);
void PMenu_Prev(edict_t *ent);
void PMenu_Select(edict_t *ent);

void CoopOpenJoinMenu(edict_t *ent);

#endif

