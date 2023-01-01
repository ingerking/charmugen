#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <audiere.h>
#include "M_Image.h"
#include "M_Sound.h"
#include "M_Font.h"
#include "Character.h"
using namespace audiere;
class Gamemap{
protected:
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3d_dev;
	AudioDevicePtr aud_dev;
	M_Image* bgimage;
	M_Image* hpbar;
	M_Image* sysimage;
	M_Image* koimage;
	M_Image* roundimage;
	M_Image* fightimage;
	M_Image* numimage[10];
	Character* p1;
	Character* p2;
	M_Font* font;
	M_Sound* startvoice;
	M_Sound* fightvoice;
	M_Sound* endvoice;
	M_Sound* bgm;
	bool isstart;
	bool isend;
	int delay;
	int kocount;
	int roundcount;
	int fightcount;
	int left, right, down;
	wchar_t mapname[32];
public:
	Gamemap(LPDIRECT3D9 _d3d, LPDIRECT3DDEVICE9 _d3d_dev, AudioDevicePtr _aud_dev);
	virtual ~Gamemap(){;}
	void setchar(Character* a, Character* b);
	int getleft(){return left;}
	int getright(){return right;}
	bool getisstart(){return isstart;}
	bool getisend(){return (isend&&kocount==0);}
	void drawbgimage(int x, int y, float xsize, float ysize);
	wchar_t* getname(){return mapname;}
	virtual void start(){;}
	virtual void initialize(){;}
	virtual void deletememory(){;}
	virtual void update(){;}
	virtual void draw(bool drawbox){;}
	virtual void drawsys(){;}
};