#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <audiere.h>
#include <vector>

#include "Character.h"
#include "Gamemap.h"
#include "Keyboard.h"
#include "M_Image.h"

#include "Char_YagamiLight.h"
#include "Char_HyugaNeji.h"
#include "Char_Cheetahmen.h"

#include "Map_Grayland.h"
#include "Map_Kungfu.h"

#define ISTEST true

using namespace audiere;
using namespace std;

#define CHARLISTROW 20

class Game
{
private:
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3d_dev;
	AudioDevicePtr aud_dev;
	Gamemap* map;
	Character* char1p;
	Character* char2p;
	Keyboard* keyboard1p;
	Keyboard* keyboard2p;
	vector<Character*> charlist;
	vector<Character*> charlist2p;
	vector<Gamemap*> maplist;
	GAMESTATUS status;
	M_Image* background;
	int p1num, p2num, mapnum;
	KEYPAD k1, k2;
	bool p1select, p2select, mapselect;
	M_Image* bgimage;
	M_Image* targetimage;
	M_Image* vsimage;
	M_Font* font;
	M_Sound* movesound;
	M_Sound* oksound;
	M_Sound* backsound;
	int delay;
public:
	Game(LPDIRECT3D9 _d3d, LPDIRECT3DDEVICE9 _d3d_dev);
	~Game(void);
	void initialize();
	bool gameloop();
	bool gameplayloop();
	bool charselectloop(bool select);
	bool mapselectloop();
};

