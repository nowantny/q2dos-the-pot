/*       D-Day: Normandy by Vipersoft
 ************************************
 *   $Source: /usr/local/cvsroot/dday/src/usa/usa_weapon.c,v $
 *   $Revision: 1.12 $
 *   $Date: 2002/07/23 07:26:15 $
 * 
 ***********************************

Copyright (C) 2002 Vipersoft

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include "usm_main.h"

/////////////////////////////////////////////////
// Colt .45
/////////////////////////////////////////////////

void USM_Weapon_Colt45 (edict_t *ent)
{
	static int	pause_frames[]	= {55};//{13, 32,42};
	static int	fire_frames[1];	//= {4,59,0};
	
	fire_frames[0]=(ent->client->aim)?75:4;

	ent->client->p_fract= &ent->client->mags[usm_index].pistol_fract;
	ent->client->p_rnd= &ent->client->mags[usm_index].pistol_rnd;

	ent->client->crosshair = false;

if ((ent->client->weaponstate == WEAPON_FIRING || ent->client->weaponstate == WEAPON_READY)
			&& !ent->client->heldfire && (ent->client->buttons & BUTTON_ATTACK)
			&& ent->client->ps.gunframe!=((ent->client->aim)?74:3)
			&& ent->client->ps.gunframe!=((ent->client->aim)?75:4)
			&& ent->client->ps.gunframe!=((ent->client->aim)?76:5)
			&& ent->client->ps.gunframe!=((ent->client->aim)?77:6)
			//gotta do it this way for both firing modes
)
		{
			if (ent->client->ps.gunframe<4)
//				firetype = abs(5-ent->client->ps.gunframe);  unknown function
			ent->client->ps.gunframe = 4;
			ent->client->weaponstate = WEAPON_READY;
			ent->client->latched_buttons |= BUTTON_ATTACK;
			ent->client->heldfire = true;
		}
		else
		{
			ent->client->buttons &= ~BUTTON_ATTACK;
			ent->client->latched_buttons &= ~BUTTON_ATTACK;
		}
//else
//		ent->client->heldfire = false;  // have to comment out or else semi-auto doesn't work

	Weapon_Generic (ent, 
		 3,  6, 47, 
		62, 65, 69,
		74, 77, 88, 
		
		pause_frames, fire_frames, Weapon_Pistol_Fire);
}


/////////////////////////////////////////////////
//M1 Garand
/////////////////////////////////////////////////

void USM_Weapon_m1 (edict_t *ent)
{
	static int	pause_frames[]	= {51};//{47, 80};
	static int	fire_frames[1];
	
	fire_frames[0] = (ent->client->aim)?76:4;

	// Wheaty: Uncomment next line to allow topping off
	//ent->client->p_fract = &ent->client->mags[usm_index].rifle_fract
	ent->client->p_rnd= &ent->client->mags[usm_index].rifle_rnd;

	ent->client->crosshair = false;

if ((ent->client->weaponstate == WEAPON_FIRING || ent->client->weaponstate == WEAPON_READY)
			&& !ent->client->heldfire && (ent->client->buttons & BUTTON_ATTACK)
			&& ent->client->ps.gunframe!=((ent->client->aim)?75:3)
			&& ent->client->ps.gunframe!=((ent->client->aim)?76:4)
			&& ent->client->ps.gunframe!=((ent->client->aim)?77:5)
			&& ent->client->ps.gunframe!=((ent->client->aim)?78:6)
			//gotta do it this way for both firing modes
)
		{
			if (ent->client->ps.gunframe<4)
//				firetype = abs(5-ent->client->ps.gunframe);  unknown function
			ent->client->ps.gunframe = 4;
			ent->client->weaponstate = WEAPON_READY;
		//	ent->client->latched_buttons |= BUTTON_ATTACK;
			ent->client->heldfire = true;
		}
		else
		{
			ent->client->buttons &= ~BUTTON_ATTACK;
			ent->client->latched_buttons &= ~BUTTON_ATTACK;
		}
//else
//		ent->client->heldfire = false;  // have to comment out or else semi-auto doesn't work

	Weapon_Generic (ent, 
		 3,  6, 47, 
		64, 67, 72, 
		75, 78, 89, 	
		pause_frames, fire_frames, Weapon_Rifle_Fire);

}


#define FRAME_LIDLE_FIRST		(FRAME_LFIRE_LAST+1)
#define FRAME_RELOAD_FIRST		(FRAME_LIDLE_LAST+1)
#define FRAME_RAISE_FIRST		(FRAME_DEACTIVATE_LAST+1)
#define FRAME_AIDLE_FIRST		(FRAME_AFIRE_LAST+1)

#define FRAME_pain304         	65
#define FRAME_pain301         	62
#define FRAME_crpain1         	169
#define FRAME_crpain4         	172
#define FRAME_crawlpain01		230
#define FRAME_crawlpain04		233
gitem_t	*FindItem (char *pickup_name);
void Shotgun_Reload (edict_t *ent, 
					 int FRAME_ACTIVATE_LAST,	int FRAME_LFIRE_LAST,	int FRAME_LIDLE_LAST, 
					 int FRAME_RELOAD_LAST,		int FRAME_LASTRD_LAST,	int FRAME_DEACTIVATE_LAST,
					 int FRAME_RAISE_LAST,		int FRAME_AFIRE_LAST,	int FRAME_AIDLE_LAST,
					 int *pause_frames,			int *fire_frames,		void (*fire)(edict_t *ent))
{
	static int zero = 0;

	int		ammo_index,	*ammo_amount;
	int		FRAME_IDLE_FIRST = (ent->client->aim)?FRAME_AIDLE_FIRST:FRAME_LIDLE_FIRST;

	if(ent->client->pers.weapon->ammo)
	{
		ammo_index = ent->client->ammo_index;
		ammo_amount=&ent->client->pers.inventory[ammo_index];
	}
	else
	{
		ammo_index = 0;
		ammo_amount=&zero;
	}

	ent->client->ps.fov=STANDARD_FOV;

	if (ent->client->ps.gunframe == FRAME_RELOAD_FIRST)
	{
		ent->client->anim_priority = ANIM_REVERSE;
		if (ent->stanceflags == STANCE_STAND)
		{
			ent->s.frame = FRAME_pain304+1;
			ent->client->anim_end = FRAME_pain301;
		}
		else if (ent->stanceflags == STANCE_DUCK)
		{
			ent->s.frame = FRAME_crpain4+1;
			ent->client->anim_end = FRAME_crpain1;
		}
		else if (ent->stanceflags == STANCE_CRAWL)
		{
			ent->s.frame = FRAME_crawlpain04+1;
			ent->client->anim_end = FRAME_crawlpain01;
		}
	}

	if (ent->client->aim) 
	{
		if(ent->client->ps.gunframe==FRAME_RAISE_FIRST)
			ent->client->aim=false;
		else if (ent->client->ps.gunframe > FRAME_RAISE_LAST || ent->client->ps.gunframe < FRAME_RAISE_FIRST)
			ent->client->ps.gunframe=FRAME_RAISE_LAST;
		else
			ent->client->ps.gunframe--;

		return;
	}

	if (ent->client->ps.gunframe ==63)
	{
		if (*ammo_amount)
		{
			ent->client->pers.inventory[ammo_index]--;
			ent->client->mags[ent->client->pers.weapon->mag_index].shotgun_rnd++;
		}
	}

	if (ent->client->ps.gunframe < FRAME_RELOAD_FIRST 
		|| ent->client->ps.gunframe > FRAME_RELOAD_LAST)
		ent->client->ps.gunframe = FRAME_RELOAD_FIRST;
	else if (ent->client->ps.gunframe == FRAME_RELOAD_LAST -2 
		&& ent->client->mags[ent->client->pers.weapon->mag_index].shotgun_rnd < 6 
		&& ent->client->pers.inventory[ammo_index]>0)
	{
		ent->client->ps.gunframe = 61;
	}
	else if(ent->client->ps.gunframe < FRAME_RELOAD_LAST-1)
	{ 
		ent->client->ps.gunframe++;
		if ((ent->client->pers.weapon->guninfo) && (ent->client->ps.gunframe == 0/*RELOAD SOUND FRAME*/))
			gi.sound(ent, CHAN_WEAPON, gi.soundindex(ent->client->pers.weapon->guninfo->ReloadSound1), 1, ATTN_NORM, 0);
	}
	else
	{
		ent->client->ps.gunframe = FRAME_IDLE_FIRST;
		ent->client->weaponstate = WEAPON_READY;
	}
}

void Weapon_Shotgun (edict_t * ent)
{
	static int	pause_frames[]	= {0};
	static int	fire_frames[1];

	fire_frames[0]=(ent->client->aim)?76:8;
	
	ent->client->p_fract = &ent->client->mags[usm_index].shotgun_fract;
	ent->client->p_rnd= &ent->client->mags[usm_index].shotgun_rnd;

	ent->client->crosshair = false;

	if (ent->client->ps.gunframe == 4)
		gi.sound(ent, CHAN_VOICE, gi.soundindex("usa/shotgun/load.wav"),1, ATTN_NORM, 0);
	else if (ent->client->ps.gunframe == 62)
		gi.sound(ent, CHAN_VOICE, gi.soundindex("usa/shotgun/reload.wav"),1, ATTN_NORM, 0);

	if (ent->client->weaponstate == WEAPON_RELOADING)
	{
		Shotgun_Reload(ent, 
			 7,  16, 55, 
			67, 67, 72,
			75, 84, 92, 
			pause_frames, fire_frames, Weapon_Shotgun_Fire);
	}
	else
	{
		Weapon_Generic (ent, 
			 7,  16, 55, 
			67, 67, 72,
			75, 84, 92, 
			pause_frames, fire_frames, Weapon_Shotgun_Fire);
	}
}



/////////////////////////////////////////////////
// Browining Automatic Rifle (BAR)
/////////////////////////////////////////////////

void USM_Weapon_BAR (edict_t *ent)
{
	static int	pause_frames[]	= {55};//{23, 45, 0};
	static int	fire_frames[2];

	fire_frames[0]=(ent->client->aim)?77:4;
	fire_frames[1]=(ent->client->aim)?78:5;

	ent->client->p_fract= &ent->client->mags[usm_index].lmg_fract;
	ent->client->p_rnd= &ent->client->mags[usm_index].lmg_rnd;

	ent->client->crosshair = false;

	Weapon_Generic (ent, 
		 3,  5, 44,
		69, 69, 73,
		76, 78, 89,
		
		pause_frames, fire_frames, Weapon_LMG_Fire);
}


/////////////////////////////////////////////////
// Browning Heavy Machingun (BHMG)
/////////////////////////////////////////////////

void USM_Weapon_30cal (edict_t *ent)
{
	static int	pause_frames[]	= {0};//{38, 61, 0};
	static int	fire_frames[2];

	fire_frames[0]=(ent->client->aim)?90:20;
	fire_frames[1]=(ent->client->aim)?91:21;
//	fire_frames[2]=(ent->client->aim)?91:0;

	ent->client->p_rnd= &ent->client->mags[usm_index].hmg_rnd;

	ent->client->crosshair = false;

	Weapon_Generic (ent, 
		19, 21,  61, 
		79, 82,  85,
		89, 91, 102, 
		
		pause_frames, fire_frames, Weapon_HMG_Fire);
}


/////////////////////////////////////////////////
// Bazooka
/////////////////////////////////////////////////

void USM_Weapon_Bazooka (edict_t *ent)
{
	static int	pause_frames[]	= {0};
	static int	fire_frames[1];

	fire_frames[0]=(ent->client->aim)?73:4;

	ent->client->p_rnd= &ent->client->mags[usm_index].antitank_rnd;

	ent->client->crosshair = false;

	Weapon_Generic (ent, 
		 3,  5, 45, 
		65, 65, 69, 
		72, 75, 86, 
		
		pause_frames, fire_frames, Weapon_Rocket_Fire);
}


/////////////////////////////////////////////////
// M1903 Springfield Sniper Rifle
/////////////////////////////////////////////////

void USM_Weapon_Sniper (edict_t *ent)
{
	static int	pause_frames[]	= {0};
	static int	fire_frames[4];

	fire_frames[0]=(ent->client->aim)?52:4;//fire here
	fire_frames[1]=(ent->client->aim)?60:0;//sniper bolt
	fire_frames[2]=(ent->client->aim)?75:0;//sniper start zoom
	fire_frames[3]=(ent->client->aim)?80:0;//sniper end zoom

	ent->client->p_fract= &ent->client->mags[usm_index].sniper_fract;
	ent->client->p_rnd= &ent->client->mags[usm_index].sniper_rnd;

	if (ent->client->ps.gunframe == 61)
		ent->client->ps.gunframe = 65;

	if (ent->client->ps.gunframe == 67)
		gi.sound(ent, CHAN_AUTO, gi.soundindex(ent->client->pers.weapon->guninfo->sniper_bolt_wav), 1, ATTN_NORM, 0);


	if (ent->client->aim) 
	{
		if ( (ent->client->ps.gunframe >= fire_frames[0] && ent->client->ps.gunframe <= fire_frames[1]) ||
			  ent->client->ps.gunframe >= fire_frames[3])
			ent->client->crosshair = true;
		else
			ent->client->crosshair = false;
	} 
	else
		ent->client->crosshair = false;

	if ((ent->client->weaponstate == WEAPON_FIRING || ent->client->weaponstate == WEAPON_READY)
			&& !ent->client->heldfire && (ent->client->buttons & BUTTON_ATTACK)
			&& ent->client->ps.gunframe!=((ent->client->aim)?51:3)
			&& ent->client->ps.gunframe!=((ent->client->aim)?52:4)
			&& ent->client->ps.gunframe!=((ent->client->aim)?53:5)
			&& ent->client->ps.gunframe!=((ent->client->aim)?54:6)
			&& ent->client->ps.gunframe!=((ent->client->aim)?55:7)
			&& ent->client->ps.gunframe!=((ent->client->aim)?56:8)
			&& ent->client->ps.gunframe!=((ent->client->aim)?57:9)
			&& ent->client->ps.gunframe!=((ent->client->aim)?58:10)
			&& ent->client->ps.gunframe!=((ent->client->aim)?59:11)
			&& ent->client->ps.gunframe!=((ent->client->aim)?60:12)
			&& ent->client->ps.gunframe!=((ent->client->aim)?61:13)
			&& ent->client->ps.gunframe!=((ent->client->aim)?62:14)
			&& ent->client->ps.gunframe!=((ent->client->aim)?63:15)
			&& ent->client->ps.gunframe!=((ent->client->aim)?64:16)
			&& ent->client->ps.gunframe!=((ent->client->aim)?65:17)
			&& ent->client->ps.gunframe!=((ent->client->aim)?66:18)
			&& ent->client->ps.gunframe!=((ent->client->aim)?67:19)
			&& ent->client->ps.gunframe!=((ent->client->aim)?68:20)
			&& ent->client->ps.gunframe!=((ent->client->aim)?69:21)
			&& ent->client->ps.gunframe!=((ent->client->aim)?70:22)
			&& ent->client->ps.gunframe!=((ent->client->aim)?71:23)
			&& ent->client->ps.gunframe!=((ent->client->aim)?72:24)
			&& ent->client->ps.gunframe!=((ent->client->aim)?73:25)
			&& ent->client->ps.gunframe!=((ent->client->aim)?74:26)
			&& ent->client->ps.gunframe!=((ent->client->aim)?75:3)
			&& ent->client->ps.gunframe!=((ent->client->aim)?76:4)
			&& ent->client->ps.gunframe!=((ent->client->aim)?77:5)
			&& ent->client->ps.gunframe!=((ent->client->aim)?78:6)
			&& ent->client->ps.gunframe!=((ent->client->aim)?79:7)
			&& ent->client->ps.gunframe!=((ent->client->aim)?80:8)
//			&& ent->client->ps.gunframe!=((ent->client->aim)?81:9)
//			&& ent->client->ps.gunframe!=((ent->client->aim)?82:10)
//			&& ent->client->ps.gunframe!=((ent->client->aim)?83:11)
//			&& ent->client->ps.gunframe!=((ent->client->aim)?84:12)
//			&& ent->client->ps.gunframe!=((ent->client->aim)?85:13)
//			&& ent->client->ps.gunframe!=((ent->client->aim)?86:14)
//			&& ent->client->ps.gunframe!=((ent->client->aim)?87:15)
//			&& ent->client->ps.gunframe!=((ent->client->aim)?88:16)
//			&& ent->client->ps.gunframe!=((ent->client->aim)?89:17)
//			&& ent->client->ps.gunframe!=((ent->client->aim)?90:18)

			//gotta do it this way for both firing modes
)
		{
			if (ent->client->ps.gunframe<4)
//				firetype = abs(5-ent->client->ps.gunframe);  unknown function
			ent->client->ps.gunframe = 4;
			ent->client->weaponstate = WEAPON_READY;
			ent->client->latched_buttons |= BUTTON_ATTACK;
			ent->client->heldfire = true;
		}
		else
		{
			ent->client->buttons &= ~BUTTON_ATTACK;
			ent->client->latched_buttons &= ~BUTTON_ATTACK;
		}
//else
//		ent->client->heldfire = false;  // have to comment out or else semi-auto doesn't work

	Weapon_Generic (ent, 
		 3, 26, 26, 
		43, 43, 48, 
		51, 80, 80, 
		
		pause_frames, fire_frames, Weapon_Sniper_Fire);
}


/////////////////////////////////////////////////
// Thompson
/////////////////////////////////////////////////

void USM_Weapon_Thompson (edict_t *ent)
{

	static int	pause_frames[]	= {55};
	static int	fire_frames[2];//try to put stutter back in

	fire_frames[0]=(ent->client->aim)?79:4;
	fire_frames[1]=(ent->client->aim)?80:5;

	ent->client->p_fract= &ent->client->mags[usm_index].submg_fract;
	ent->client->p_rnd= &ent->client->mags[usm_index].submg_rnd;

	ent->client->crosshair = false;

	Weapon_Generic (ent, 
		 3,  5, 45, 
		71, 71, 75,
		78, 80, 92, 
		
		pause_frames, fire_frames, Weapon_Submachinegun_Fire);
}
