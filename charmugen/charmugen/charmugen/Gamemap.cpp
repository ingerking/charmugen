#include "Gamemap.h"

Gamemap::Gamemap(LPDIRECT3D9 _d3d, LPDIRECT3DDEVICE9 _d3d_dev, AudioDevicePtr _aud_dev){
	d3d=_d3d;
	d3d_dev=_d3d_dev;
	aud_dev=_aud_dev;
	isstart=false;
	isend=false;
	delay=0;
	kocount=0;
	fightcount=0;
	roundcount=0;
}

void Gamemap::setchar(Character* a, Character* b){
	p1=a;
	p2=b;
	p1->setmapdown(down);
	p2->setmapdown(down);
	p1->setlookright(true);
	p2->setlookright(false);
}

void Gamemap::drawbgimage(int x, int y, float xsize, float ysize){
	bgimage->draw((float)x, (float)y, xsize, ysize, 0xFFFFFFFF, true, false);
}