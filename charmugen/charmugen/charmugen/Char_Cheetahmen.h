#pragma once

#include <list>
#include "Character.h"
#include "M_Image.h"
#include "M_Sound.h"

#define CHEETAH_MAXHP 500
#define CHEETAH_BDIST 500-height+mapdown

class Char_Cheetahmen :
	public Character
{
private:
	int num;
	list<Collapsebox> bulletlist;
	bool playing;
public:
	Char_Cheetahmen(LPDIRECT3D9 _d3d, LPDIRECT3DDEVICE9 _d3d_dev, AudioDevicePtr _aud_dev);
	~Char_Cheetahmen(void);

	void initialize();
	void deletememory();

	void eventupdatebeforecollapse();
	void eventupdateaftercollapse();
	void setidle();
	void startevent();
	
	void drawevent(bool drawbox);
	void jump();
	void hit();
	void down();
	void BH_5(bool a, bool b);
	void BH_2(bool a, bool b);
	void BH_4(bool a, bool b);
	void BH_6(bool a, bool b);
	void BH_8(bool a, bool b);
	void BH_7(bool a, bool b);
	void BH_9(bool a, bool b);
	void BH_236(bool a, bool b);
	void BH_214(bool a, bool b);
	void BH_22(bool a, bool b);
	void BH_66(bool a, bool b);
	void BH_44(bool a, bool b);
	void BH_623(bool a, bool b);
	void BH_421(bool a, bool b);
	void BH_41236(bool a, bool b);
	void BH_63214(bool a, bool b);
	void BH_236236(bool a, bool b);
	void BH_214214(bool a, bool b);
	void BH_2141236(bool a, bool b);
	void BH_2363214(bool a, bool b);
	void BH_641236(bool a, bool b);
	void BH_463214(bool a, bool b);
	void BH_4123641236(bool a, bool b);
	void BH_6321463214(bool a, bool b);
};

