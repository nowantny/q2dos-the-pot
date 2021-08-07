
#define STAT_CTF_TEAM1_PIC			17
#define STAT_CTF_TEAM1_CAPS			18
#define STAT_CTF_TEAM2_PIC			19
#define STAT_CTF_TEAM2_CAPS			20
#define STAT_CTF_JOINED_TEAM1_PIC	22
#define STAT_CTF_JOINED_TEAM2_PIC	23
#define STAT_CTF_TEAM1_HEADER		24
#define STAT_CTF_TEAM2_HEADER		25
#define STAT_CTF_NOTCAPPED				26
#define STAT_CTF_ID_VIEW			27

typedef enum {
	CTF_NOTEAM,
	CTF_TEAM1,
	CTF_TEAM2
} ctfteam_t;

typedef enum {
	CTF_STATE_START,
	CTF_STATE_PLAYING
} ctfstate_t;

extern cvar_t *teamplay;
extern cvar_t *ctf;
extern cvar_t *ctf_forcejoin;

#define CTF_TEAM1_SKIN "ctf_r"
#define CTF_TEAM2_SKIN "ctf_b"

#define DF_CTF_FORCEJOIN	131072	
#define DF_ARMOR_PROTECT	262144
#define DF_TEAMREBALANCE   524288

void CTFInit (void);
void stuffcmd (edict_t *ent, char *s);

void SP_info_player_team1 (edict_t *self);
void SP_info_player_team2 (edict_t *self);

char *CTFTeamName (int team);
char *CTFOtherTeamName (int team);
void CTFAssignSkin (edict_t *ent, char *s);
void CTFAssignTeam (gclient_t *who);
edict_t *SelectCTFSpawnPoint (edict_t *ent, qboolean *spawnlive);
void CTFCalcScores (void);
void SetCTFStats (edict_t *ent);
void CTFScoreboardMessage (edict_t *ent, edict_t *killer, char string[1400]);
void CTFSetTeam (edict_t *ent, int desired_team);
void CTFTeam_f (edict_t *ent);
void CTFID_f (edict_t *ent);

void CTFOpenJoinMenu (edict_t *ent);
qboolean CTFStartClient (edict_t *ent);

char *CTFCheckRules (void);

void SP_misc_ctf_banner (edict_t *ent);
void SP_misc_ctf_small_banner (edict_t *ent);

extern char *teamplay_statusbar;
extern char *ctf_statusbar;

void UpdateChaseCam (edict_t *ent);
void ChaseNext (edict_t *ent);
void ChasePrev (edict_t *ent);

void SP_trigger_teleport (edict_t *ent);
void SP_info_teleport_destination (edict_t *ent);

void TeamplaySetupSpawnpoint (edict_t *spot);
void TeamplaySpawnpointTouch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf);
void TeamplayMakeObserver (edict_t *ent);
void TeamplayCheckRespawn (void);

qboolean TeamplayCheckCountdown (void);
void TeamplayDoCountdown (void);

qboolean TeamplayCheckRound1 (void);
qboolean TeamplayCheckRound2 (void);
void TeamplayStartRound2 (void);

void TeamplayRebalanceTeams (void);

/* Define this to get some development code for Extinction.
#define EXT_DEVT */
