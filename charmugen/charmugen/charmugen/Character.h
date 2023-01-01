#pragma once

#include <list>
#include <vector>
#include <d3d9.h>
#include <d3dx9.h>
#include <audiere.h>

#include "enumstruct.h"
#include "M_Image.h"
#include "M_Sound.h"
#include "Keyboard.h"

#define YDIST 500-y-height+mapdown

using namespace std;
using namespace audiere;

class Character{
protected:
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3d_dev;
	AudioDevicePtr aud_dev;
	Keyboard* keyboard;
	Character* enemy;
	wchar_t cname[32];
	int nowhp;
	int prevhp;
	int maxhp;
	int height;
	int cutintime;
	int x, y, vy;
	M_Image* face;
	M_Image* bigface;
	M_Image* cutin;
	vector<M_Image*> imagelist;
	vector<M_Sound*> soundlist;
	vector<Motion> motionlist;
	list<int> motionnumlist;
	int nowmotionnum;
	bool isjump;
	bool ischarlookright;
	bool hitcountup;
	bool nexthitdown;
	bool guardignore;
	bool cutinisright;
	bool cutincanchangedist;
	bool islost;
	bool leftright;
	int nextdmg;
	int nextfreeze;
	int freezetime;
	int hitcount;
	int hitsoundnum;
	int mapleft, mapright, mapdown;
	STATUS status;
public:
	Character(LPDIRECT3D9 _d3d, LPDIRECT3DDEVICE9 _d3d_dev, AudioDevicePtr _aud_dev);
	virtual ~Character(){;}
	int getnowhp(){return nowhp;}
	int getprevhp(){return prevhp;}
	int getmaxhp(){return maxhp;}
	int getnextdmg(){return nextdmg;}
	int getnextfreeze(){return nextfreeze;}
	int gety(){return y;}
	int getx(){return x;}
	void setx(int _x){x=_x;}
	wchar_t* getname(){return cname;}
	int getcutin(){return cutintime;}
	bool getlost(){return islost;}
	int gethitcount(){return hitcount;}
	void setmapdown(int _down){mapdown=_down;}
	void setlookright(bool _isright){ischarlookright=_isright;}

	void charinit(Character* enemy, Keyboard* _keyboard, int _mapleft, int _mapright);
	Motion getmotion();
	void setdamage(int damage, int freezetime, bool hitcountup, bool isdown);
	
	void update();
	void setleftright(Character* enemy);
	void setbehavior();
	void move();
	bool collapse(Character* enemy);
	void nextmotion();
	void draw(bool drawbox);
	void drawface(int x, int y, bool lookright);
	void drawbigface(int x, int y, bool lookright, int color);
	void drawcutin();
	void setcutin();

	virtual void initialize(){;}
	virtual void deletememory(){;}
	virtual void startevent(){;}
	
	virtual void eventupdatebeforecollapse(){;}
	virtual void eventupdateaftercollapse(){;}
	virtual void setidle(){;}
	virtual void drawevent(bool drawbox){;}

	virtual void jump(){;}
	virtual void hit(){;}
	virtual void down(){;}
	virtual void BH_5(bool a, bool b){;}
	virtual void BH_2(bool a, bool b){;}
	virtual void BH_4(bool a, bool b){;}
	virtual void BH_6(bool a, bool b){;}
	virtual void BH_8(bool a, bool b){;}
	virtual void BH_7(bool a, bool b){;}
	virtual void BH_9(bool a, bool b){;}
	virtual void BH_236(bool a, bool b){;}
	virtual void BH_214(bool a, bool b){;}
	virtual void BH_22(bool a, bool b){;}
	virtual void BH_66(bool a, bool b){;}
	virtual void BH_44(bool a, bool b){;}
	virtual void BH_623(bool a, bool b){;}
	virtual void BH_421(bool a, bool b){;}
	virtual void BH_41236(bool a, bool b){;}
	virtual void BH_63214(bool a, bool b){;}
	virtual void BH_236236(bool a, bool b){;}
	virtual void BH_214214(bool a, bool b){;}
	virtual void BH_2141236(bool a, bool b){;}
	virtual void BH_2363214(bool a, bool b){;}
	virtual void BH_641236(bool a, bool b){;}
	virtual void BH_463214(bool a, bool b){;}
	virtual void BH_4123641236(bool a, bool b){;}
	virtual void BH_6321463214(bool a, bool b){;}
};







