//#include "g_local.h"
#include "m_player.h"
#include "bot.h"

void droptofloor (edict_t *ent);

edict_t *bot_team_flag1;
edict_t *bot_team_flag2;

void SetBotFlag1(edict_t *ent)	//�`�[��1�̊�
{
	bot_team_flag1 = ent;
}
void SetBotFlag2(edict_t *ent)  //�`�[��2�̊�
{
	bot_team_flag2 = ent;
}
edict_t *GetBotFlag1()	//�`�[��1�̊�
{
	return bot_team_flag1;
}
edict_t *GetBotFlag2()  //�`�[��2�̊�
{
	return bot_team_flag2;
}

qboolean ChkTFlg( void )
{
	if(bot_team_flag1 != NULL 
		&& bot_team_flag2 != NULL) return true;
	else return false;
}

void SpawnItem2 (edict_t *ent, gitem_t *item)
{
//	PrecacheItem (item);

	ent->item = item;
	ent->nextthink = level.time ;    // items start after other solids
	ent->think = droptofloor;
	ent->s.effects = 0;
	ent->s.renderfx = RF_GLOW;
//	if (ent->model)
//		gi.modelindex (ent->model);
	droptofloor (ent);
	ent->s.modelindex = 0;
	ent->nextthink = level.time + 100 * FRAMETIME;    // items start after other solids
	ent->think = G_FreeEdict;
}

//=====================================

//
// BOT�p������
//

qboolean Bot_trace (edict_t *ent,edict_t *other)
{
		trace_t		rs_trace;
		vec3_t	ttx;
		vec3_t	tty;

		VectorCopy (ent->s.origin,ttx);
		VectorCopy (other->s.origin,tty);
		if(ent->maxs[2] >=32)
		{
			if(tty[2] > ttx[2] ) tty[2] += 16;
//			else if(ttx[2] > tty[2] > 100 ) tty[2] += 32;
			ttx[2] += 30;
		}
		else
		{
			ttx[2] -= 12;
		}

		rs_trace = gi.trace (ttx, NULL, NULL, tty ,ent, CONTENTS_SOLID | CONTENTS_WINDOW | CONTENTS_LAVA | CONTENTS_SLIME /*| CONTENTS_TRANSLUCENT*/);
		if(rs_trace.fraction == 1.0 && !rs_trace.allsolid && !rs_trace.startsolid) return true;
		if( ent->maxs[2] < 32 ) return false;

		if(other->classname[6] == 'F'
			|| other->classname[0] == 'w')
		{}
		else if(other->classname[0]=='i')
		{
			if(other->classname[5]=='q'
			|| other->classname[5]=='f'
			|| other->classname[5]=='t'
			|| other->classname[5]=='i'
			|| other->classname[5]=='h'
			|| other->classname[5]=='a'){}
			else return false;
		}
		else return false;

		if(rs_trace.ent != NULL)
		{
			if(rs_trace.ent->classname[0] == 'f' 
				&& rs_trace.ent->classname[5] == 'd'
				&& rs_trace.ent->targetname == NULL) return true;  
		}
		
		if(ent->s.origin[2] < other->s.origin[2]
			|| ent->s.origin[2]-24 >  other->s.origin[2]) return false;
		
		ttx[2] -= 36;
		rs_trace = gi.trace (ttx, NULL, NULL, other->s.origin ,ent, CONTENTS_SOLID | CONTENTS_WINDOW | CONTENTS_LAVA | CONTENTS_SLIME /*|CONTENTS_TRANSLUCENT*/);
		if(rs_trace.fraction == 1.0 && !rs_trace.allsolid && !rs_trace.startsolid) return true;
		return false;
}


qboolean Bot_traceX (edict_t *ent,edict_t *other)
{
		trace_t		rs_trace;
		vec3_t	ttx,tty;
		VectorCopy (ent->s.origin,ttx);
		VectorCopy (other->s.origin,tty);
		ttx[2] += 16;
		tty[2] += 16;

		rs_trace = gi.trace (ttx, NULL, NULL, tty ,ent, CONTENTS_SOLID | CONTENTS_WINDOW | CONTENTS_LAVA | CONTENTS_SLIME);
		if(rs_trace.fraction == 1.0 ) return true;
		return false;
}

qboolean Bot_traceY (edict_t *ent,edict_t *other)
{
		trace_t		rs_trace;
		vec3_t	ttx,tty;
		VectorCopy (ent->s.origin,ttx);
		VectorCopy (other->s.origin,tty);
		if(ent->maxs[2] >=32) ttx[2] += 24;
		else ttx[2] -= 12;
		
		tty[2] += 16;

		rs_trace = gi.trace (ttx, NULL, NULL, tty ,ent, CONTENTS_SOLID | CONTENTS_WINDOW | CONTENTS_LAVA | CONTENTS_SLIME);
		if(rs_trace.fraction == 1.0 ) return true;
		return false;
}

//
// BOT�p������ 2
//

qboolean Bot_trace2 (edict_t *ent,vec3_t ttz)
{
		trace_t		rs_trace;
		vec3_t	ttx;
		VectorCopy (ent->s.origin,ttx);
		if(ent->maxs[2] >=32) ttx[2] += 24;
		else ttx[2] -= 12;

		rs_trace = gi.trace (ttx, NULL, NULL, ttz ,ent, CONTENTS_SOLID | CONTENTS_LAVA | CONTENTS_SLIME /*| CONTENTS_TRANSLUCENT*/);
		if(rs_trace.fraction != 1.0 ) return false;
		return true;
}

//
// BOT�p������ 3
//

qboolean Bot_traceS (edict_t *ent,edict_t *other)
{
	trace_t		rs_trace;
	vec3_t	start,end;
	int		mycont;


	VectorCopy(ent->s.origin,start);
	VectorCopy(other->s.origin,end);

	start[2] += ent->viewheight - 8;
	end[2] += other->viewheight - 8;

	if(Bot[ent->client->zc.botindex].param[BOP_NOSTHRWATER]) goto WATERMODE;

	rs_trace = gi.trace (start, NULL, NULL, end ,ent,CONTENTS_SOLID | CONTENTS_WINDOW | CONTENTS_LAVA | CONTENTS_SLIME);

	if(rs_trace.fraction != 1.0 ) return false;
	return true;

WATERMODE:
	mycont = gi.pointcontents(start);

	if((mycont & CONTENTS_WATER) && !other->waterlevel)
	{
		rs_trace = gi.trace (end, NULL, NULL, start ,ent,CONTENTS_SOLID | CONTENTS_WINDOW | CONTENTS_LAVA | CONTENTS_SLIME | CONTENTS_WATER);
		if(rs_trace.surface)
		{
			if(rs_trace.surface->flags & SURF_WARP) return false;
		}
		rs_trace = gi.trace (start, NULL, NULL, end ,ent,CONTENTS_SOLID | CONTENTS_WINDOW | CONTENTS_LAVA | CONTENTS_SLIME);
		if(rs_trace.fraction != 1.0 ) return false;
		return true;
	}
	else if((mycont & CONTENTS_WATER) && other->waterlevel)
	{
		VectorCopy(other->s.origin,end);
		end[2] -= 16;
		rs_trace = gi.trace (start, NULL, NULL, end ,ent,CONTENTS_SOLID | CONTENTS_WINDOW );
		if(rs_trace.fraction != 1.0 ) return false;	
		return true;
	}

	if(other->waterlevel)
	{
		VectorCopy(other->s.origin,end);
		end[2] += 32;
		rs_trace = gi.trace (start, NULL, NULL, end ,ent,CONTENTS_SOLID | CONTENTS_WINDOW | CONTENTS_WATER);
		if(rs_trace.surface)
		{
			if(rs_trace.surface->flags & SURF_WARP) return false;
		}		
//		if(rs_trace.fraction != 1.0 ) return false;	
//		return true;
	}

	rs_trace = gi.trace (start, NULL, NULL, end ,ent,CONTENTS_SOLID | CONTENTS_WINDOW | CONTENTS_LAVA | CONTENTS_SLIME);
	if(rs_trace.fraction != 1.0 ) return false;
	return true;
}




//
// VEC�l����yaw�𓾂�
//

float Get_yaw (vec3_t vec)
{
		vec3_t		out;
		double		yaw;

		VectorCopy(vec,out);
		out[2] = 0;
		VectorNormalize2 (out, out);

		yaw = acos((double) out[0]);
	//	yaw = (float) yaw;
		yaw = yaw / M_PI * 180;

		if(asin((double) out[1]) < 0 ) yaw *= -1;

		return (float)yaw;
}

float Get_pitch (vec3_t vec)
{
		vec3_t		out;
		float		pitch;

		VectorNormalize2 (vec, out);

		pitch = acos((double) out[2]);
	//	yaw = (float) yaw;
		pitch = ((float)pitch) / M_PI * 180;

//		if(asin((double) out[0]) < 0 ) pitch *= -1;

		pitch -= 90;
		if(pitch < -180) pitch += 360;

		return pitch;
}

//
// VEC�l��yaw�l�̊p�x���𓾂�
//

float Get_vec_yaw (vec3_t vec,float yaw)
{
		float		vecsyaw;

		vecsyaw = Get_yaw (vec);

		if(vecsyaw > yaw) vecsyaw -= yaw;
		else vecsyaw = yaw - vecsyaw;

		if(vecsyaw >180 ) vecsyaw = 360 - vecsyaw;

		return vecsyaw;
}

//yaw �ɑ΂���vec�̑���
float Get_vec_yaw2 (vec3_t vec,float yaw)
{
		float		vecsyaw;

		vecsyaw = Get_yaw (vec);

		vecsyaw -= yaw;
		if(vecsyaw >180 ) vecsyaw -= 360;
		else if(vecsyaw <-180 ) vecsyaw += 360;

		return vecsyaw;
}

//========================================================
//============= BOT TALKING/TAUNTING ROUTINES ============
//========================================================
//=====================================================
// Returns Player with Highest Score.
//=====================================================

edict_t *BestScoreEnt(void) {
	
	edict_t *bestplayer=NULL;
	int i, bestscore=-999;
	edict_t *ent;

	// Search thru all clients
	for(i=0;i < game.maxclients; i++) {
		ent=g_edicts+i+1;
//	if (!G_EntExists(ent)) continue;
		if (ent->client->resp.score > bestscore) {
 			bestplayer=ent; // Found one!
 			bestscore=ent->client->resp.score; 
		} 
	}
	return bestplayer;
}



//=======================================================
// Taunt your victim! Called from ClientObituary()..
//=======================================================
void bTaunt(edict_t *bot, edict_t *other) {

	if ((rand()%5) >= 2) 
		return;

	if (level.time < bot->last_taunt) 
		return;

	// If killed enemy then Taunt them!!
	if ((other->client) && (random() < 0.4))
 		switch (rand()%4) {
 			case 0: // flipoff
 				bot->s.frame = FRAME_flip01-1;
 				bot->client->anim_end = FRAME_flip12;
 				break;
 			case 1: // salute
 				bot->s.frame = FRAME_salute01-1;
 				bot->client->anim_end = FRAME_salute11;
 				break;
 			case 2: // taunt
 				bot->s.frame = FRAME_taunt01-1;
 				bot->client->anim_end = FRAME_taunt17;
 				break;
 			case 3: // point
 				bot->s.frame = FRAME_point01-1;
 				bot->client->anim_end = FRAME_point12;
 				break; 
		}

// Taunt victim but not too often..
	bot->last_taunt = level.time + 60 + 35;
}


//========================================================
void bFakeChat(edict_t *bot) {
	
	gclient_t *bclient=bot->client;

	if (random() < .1)
 		gi.bprintf(PRINT_CHAT, "%s: Bunch of Chicken Shits!\n", bclient->pers.netname);
 	else if (random() < .2)
 		gi.bprintf(PRINT_CHAT, "%s: Tu madre!!!\n", bclient->pers.netname);
 	else if (random() < .3)
 		gi.bprintf(PRINT_CHAT, "%s: Who wants a piece of me?\n", bclient->pers.netname);
 	else if (random() < .4)
 		gi.bprintf(PRINT_CHAT, "%s: Where'd everybody go?\n", bclient->pers.netname);
 	else if (random() < .5)
 		gi.bprintf(PRINT_CHAT, "%s: Yeee pendejos venid por mi! pateare vuestro gordo culo\n", bclient->pers.netname);
 	else
 		gi.bprintf(PRINT_CHAT, "%s: Kickin' Ass!\n", bclient->pers.netname);

// Random chats between 2 minutes and 10 minutes
	bot->last_chat = level.time + 120 + (60*(rand()%8));
}





//========================================================
// Insult the player that the bot just fragged...
//========================================================
void bInsult(edict_t *bot, edict_t *loser) {

	gclient_t *bclient=bot->client;
	gclient_t *lclient=loser->client;

	if ((rand()%5) > 3) 
		return;

	if (level.time < bot->last_insult) 
		return;

	if (bclient->resp.score < lclient->resp.score) {
	
 		if (bclient->resp.score < lclient->resp.score - 20) {
 			if (random() < .1)
 				gi.bprintf(PRINT_CHAT, "%s: Heh... I'm all luck, %s\n", bclient->pers.netname, lclient->pers.netname);
 			else if (random() < .2)
 				gi.bprintf(PRINT_CHAT, "%s: WHEW! Finally got ya, %s!\n", bclient->pers.netname, lclient->pers.netname);
 			else if (random() < .3)
 				gi.bprintf(PRINT_CHAT, "%s: I...I killed %s? I...don't remember... it all happened so fast!\n", bclient->pers.netname, lclient->pers.netname);
 			else if (random() < .4)
 				gi.bprintf(PRINT_CHAT, "%s: Only pussies on this server!\n", bclient->pers.netname);
 			else if (random() < .5)
 				gi.bprintf(PRINT_CHAT, "%s: Sure, I'm losing by a ton, but does that mean I suck? Probably.\n", bclient->pers.netname);
 			else
 				gi.bprintf(PRINT_CHAT, "%s: Not bad for a beginner, eh %s?\n", bclient->pers.netname, lclient->pers.netname); 
		}
 		else if (bclient->resp.score < lclient->resp.score - 10) {
	
 			if (random() < .1)
 				gi.bprintf(PRINT_CHAT, "%s: Well, %s, what can I say? You're good... but not good enough\n", bclient->pers.netname, lclient->pers.netname);
 			else if (random() < .2)
 				gi.bprintf(PRINT_CHAT, "%s: I'll get you %s, and your little dog, too\n", bclient->pers.netname, lclient->pers.netname);
 			else if (random() < .3)
 				gi.bprintf(PRINT_CHAT, "%s: Oh, I get how you play now, %s... you're mine.\n", bclient->pers.netname, lclient->pers.netname);
 			else if (random() < .4)
 				gi.bprintf(PRINT_CHAT, "%s: What's that, %s? Do I smell smoke?\n", bclient->pers.netname, lclient->pers.netname);
 			else if (random() < .5)
 				gi.bprintf(PRINT_CHAT, "%s: Oops! Sorry %s, You REALLY suck!\n", bclient->pers.netname, lclient->pers.netname);
 			else
 				gi.bprintf(PRINT_CHAT, "%s: YEAH BABY, YEAH!\n", bclient->pers.netname); 
		}
 		else if (bclient->resp.score < lclient->resp.score - 5) {
 			if (random() < .1)
 				gi.bprintf(PRINT_CHAT, "%s: Ok, %s, I'm back on track now\n", bclient->pers.netname, lclient->pers.netname);
 			else if (random() < .2)
 				gi.bprintf(PRINT_CHAT, "%s: You aren't gonna win THAT easy, %s.\n", bclient->pers.netname, lclient->pers.netname);
 			else if (random() < .3)
 				gi.bprintf(PRINT_CHAT, "%s: Umm, ok %s, I'd appreciate it if you could not bleed on my clothes next time.\n", bclient->pers.netname, lclient->pers.netname);
 			else if (random() < .4)
 				gi.bprintf(PRINT_CHAT, "%s: You might wanna get that fixed, %s\n", bclient->pers.netname, lclient->pers.netname);
 			else if (random() < .5)
 				gi.bprintf(PRINT_CHAT, "%s: Uh oh... BRB, I have to clean this %s off my shirt before it sets in.\n", bclient->pers.netname, lclient->pers.netname);
 			else
 				gi.bprintf(PRINT_CHAT, "%s: hiiiiiihaaaaaa\n", bclient->pers.netname);
		}
 		else {
 			if (random() < .1)
 				gi.bprintf(PRINT_CHAT, "%s: I can still catch up with you, %s, don't get cocky\n", bclient->pers.netname, lclient->pers.netname);
 			else if (random() < .2)
 				gi.bprintf(PRINT_CHAT, "%s: You're alllll mine, %s.\n", bclient->pers.netname, lclient->pers.netname);
 			else if (random() < .3)
 				gi.bprintf(PRINT_CHAT, "%s: Come on, %s, just you and me.\n", bclient->pers.netname, lclient->pers.netname);
 			else if (random() < .4)
 				gi.bprintf(PRINT_CHAT, "%s: The best part of wakin' uuup is %s gibs in your cuuup!\n", bclient->pers.netname, lclient->pers.netname);
 			else if (random() < .5)
 				gi.bprintf(PRINT_CHAT, "%s: Oh my, %s, that didn't look like it felt very nice.\n", bclient->pers.netname, lclient->pers.netname);
 			else
 				gi.bprintf(PRINT_CHAT, "%s: Well, %s, looks like things might even up.\n", bclient->pers.netname, lclient->pers.netname); 
		}
 	}
 	else if (bclient->resp.score > lclient->resp.score) {
 		if (bclient->resp.score > lclient->resp.score + 10) {
 			if (random() < .1)
 				gi.bprintf(PRINT_CHAT, "%s: You're never going to catch up to me, %s. Just give up.\n", bclient->pers.netname, lclient->pers.netname);
 			else if (random() < .2)
 				gi.bprintf(PRINT_CHAT, "%s: Hey %s, have you tried reading one of those ""DeathMatch for Dummies"" books? HeeeeHaaaaa\n", bclient->pers.netname, lclient->pers.netname);
 			else if (random() < .3)
 				gi.bprintf(PRINT_CHAT, "%s: Oh %s, you make me feel so... alive!\n", bclient->pers.netname, lclient->pers.netname);
 			else if (random() < .4)
 				gi.bprintf(PRINT_CHAT, "%s: Me? Using a bot? No way %s, I'm all skill!\n", bclient->pers.netname, lclient->pers.netname);
 			else if (random() < .5)
 				gi.bprintf(PRINT_CHAT, "%s: Hey %s, are you letting your mom play again?\n", bclient->pers.netname, lclient->pers.netname);
 			else
 				gi.bprintf(PRINT_CHAT, "%s: You do know there's an autorun option, don't you?\n", bclient->pers.netname);
		}
 	else if (bclient->resp.score > lclient->resp.score + 5) {
 		if (random() < .1)
 			gi.bprintf(PRINT_CHAT, "%s: HeeeeHaaaaa\n", bclient->pers.netname);
 		else if (random() < .2)
 			gi.bprintf(PRINT_CHAT, "%s: Don't feel bad %s, you just aren't gifted like me\n", bclient->pers.netname, lclient->pers.netname);
 		else if (random() < .3)
 			gi.bprintf(PRINT_CHAT, "%s: Come on %s, don't give up now!\n", bclient->pers.netname, lclient->pers.netname);
 		else if (random() < .4)
 			gi.bprintf(PRINT_CHAT, "%s: I think you just need to practice more, %s. muhhhhaahhhaaa\n", bclient->pers.netname, lclient->pers.netname);
 		else if (random() < .5)
 			gi.bprintf(PRINT_CHAT, "%s: I just want you to know that I think you're taking this beating very well, %s\n", bclient->pers.netname, lclient->pers.netname);
 		else
 			gi.bprintf(PRINT_CHAT, "%s: Is that freshly cooked whupass I smell, %s?\n", bclient->pers.netname, lclient->pers.netname); }
 	else {
 		if (random() < .1)
 			gi.bprintf(PRINT_CHAT, "%s: Come on, %s, ajajajaaaaaaja I can take you\n", bclient->pers.netname, lclient->pers.netname);
 		else if (random() < .2)
 			gi.bprintf(PRINT_CHAT, "%s: You're goin' down, %s.\n", bclient->pers.netname, lclient->pers.netname);
 		else if (random() < .3)
 			gi.bprintf(PRINT_CHAT, "%s: Oh, so %s, you want some?\n", bclient->pers.netname, lclient->pers.netname);
 		else if (random() < .4)
 			gi.bprintf(PRINT_CHAT, "%s: That's right %s, you know who yo daddy is\n", bclient->pers.netname, lclient->pers.netname);
 		else if (random() < .5)
 			gi.bprintf(PRINT_CHAT, "%s: Better get that taken care of, %s. It could get infected.\n", bclient->pers.netname, lclient->pers.netname);
 		else
 			gi.bprintf(PRINT_CHAT, "%s: Don't ya just love it?\n", bclient->pers.netname); }
 	}
 	else {
 		if (random() < .1)
 			gi.bprintf(PRINT_CHAT, "%s: Oh look, a tie! Well %s, we'll just have to fix that!\n", bclient->pers.netname, lclient->pers.netname);
 		else if (random() < .2)
 			gi.bprintf(PRINT_CHAT, "%s: Time to pay your pimp, %s\n", bclient->pers.netname, lclient->pers.netname);
 		else if (random() < .3)
 			gi.bprintf(PRINT_CHAT, "%s: Come on %s, it's time to ride daddy's rocket\n", bclient->pers.netname, lclient->pers.netname);
 		else if (random() < .4)
 			gi.bprintf(PRINT_CHAT, "%s: Look %s, we're tied... want me to fix that? Ok then!\n", bclient->pers.netname, lclient->pers.netname);
 		else if (random() < .5)
 			gi.bprintf(PRINT_CHAT, "%s: Damn %s, I thought you were better than this\n", bclient->pers.netname, lclient->pers.netname);
 		else
 			gi.bprintf(PRINT_CHAT, "%s: Alright, %s, I'm not showing any mercy this time.\n", bclient->pers.netname, lclient->pers.netname);
	}

// Next insult between 30 sec and 5 minutes
	bot->last_insult = level.time + 30 + (60*(rand()%5));
}
