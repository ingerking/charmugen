#pragma once

typedef struct Collapsebox{
	int up;
	int down;
	int left;
	int right;
}Collapsebox;

typedef struct Motion{
	int spritenum;
	int soundnum;
	int dmg;
	int freeze;
	int hitsoundnum;
	bool hitcountup;
	bool downhit;
	bool ignoreguarddmg;
	bool absolutedmg;
	Collapsebox atkbox;
	Collapsebox defbox1;
	Collapsebox defbox2;
}MOTION;

enum STATUS{
	IDLE,
	MOVEFRONT,
	MOVEBACK,
	SIT,
	ATTACK,
	DOWN,
	VJUMP,
	RJUMP,
	LJUMP,
	HIT,
	WIN,
	GUARD,
	DASH
};

enum KEYPAD{
	KP_5,
	KP_2,
	KP_4,
	KP_6,
	KP_8,
	KP_7,
	KP_9,
	KP_236,
	KP_214,
	KP_22,
	KP_66,
	KP_44,
	KP_623,
	KP_421,
	KP_41236,
	KP_63214,
	KP_236236,
	KP_214214,
	KP_2141236,
	KP_2363214,
	KP_641236,
	KP_463214,
	KP_4123641236,
	KP_6321463214
};

enum GAMESTATUS{
	CHARSELECT,
	MAPSELECT,
	GAMEPLAY
};








bool iscollapse(Collapsebox* a, Collapsebox* b);