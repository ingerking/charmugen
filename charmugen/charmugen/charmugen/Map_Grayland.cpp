#include "Map_Grayland.h"


Map_Grayland::Map_Grayland(LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3d_dev, AudioDevicePtr _aud_dev):Gamemap(d3d, d3d_dev, _aud_dev)
{
	startvoice=new M_Sound(_aud_dev, "map\\grayland\\00.wav", 0.5f);
	endvoice=new M_Sound(_aud_dev, "map\\grayland\\01.wav", 0.5f);
	fightvoice=new M_Sound(_aud_dev, "map\\grayland\\02.wav", 0.5f);
	bgimage=new M_Image(d3d, d3d_dev, L"map\\grayland\\background.png", 0x00000000);

	hpbar=NULL;
	sysimage=NULL;
	koimage=NULL;
	roundimage=NULL;
	fightimage=NULL;
	font=NULL;
	numimage[0]=NULL;
	numimage[1]=NULL;
	numimage[2]=NULL;
	numimage[3]=NULL;
	numimage[4]=NULL;
	numimage[5]=NULL;
	numimage[6]=NULL;
	numimage[7]=NULL;
	numimage[8]=NULL;
	numimage[9]=NULL;

	wcscpy(mapname, L"Grayland");
	left=20;
	right=980;
	down=0;
}


Map_Grayland::~Map_Grayland(void)
{
	deletememory();
	delete startvoice;
	delete endvoice;
	delete fightvoice;
	delete bgimage;
}

void Map_Grayland::initialize(){
	hpbar=new M_Image(d3d, d3d_dev, L"map\\grayland\\hpbar.png", 0x00000000);
	sysimage=new M_Image(d3d, d3d_dev, L"map\\grayland\\sys.png", 0x00000000);
	koimage=new M_Image(d3d, d3d_dev, L"map\\grayland\\ko.png", 0x00000000);
	roundimage=new M_Image(d3d, d3d_dev, L"map\\grayland\\round.png", 0x00000000);
	fightimage=new M_Image(d3d, d3d_dev, L"map\\grayland\\fight.png", 0x00000000);
	font=new M_Font(d3d, d3d_dev, 12, 24, 1000, L"±¼¸²", false);
	numimage[0]=new M_Image(d3d, d3d_dev, L"map\\grayland\\num0.png", 0xFF008000);
	numimage[1]=new M_Image(d3d, d3d_dev, L"map\\grayland\\num1.png", 0xFF008000);
	numimage[2]=new M_Image(d3d, d3d_dev, L"map\\grayland\\num2.png", 0xFF008000);
	numimage[3]=new M_Image(d3d, d3d_dev, L"map\\grayland\\num3.png", 0xFF008000);
	numimage[4]=new M_Image(d3d, d3d_dev, L"map\\grayland\\num4.png", 0xFF008000);
	numimage[5]=new M_Image(d3d, d3d_dev, L"map\\grayland\\num5.png", 0xFF008000);
	numimage[6]=new M_Image(d3d, d3d_dev, L"map\\grayland\\num6.png", 0xFF008000);
	numimage[7]=new M_Image(d3d, d3d_dev, L"map\\grayland\\num7.png", 0xFF008000);
	numimage[8]=new M_Image(d3d, d3d_dev, L"map\\grayland\\num8.png", 0xFF008000);
	numimage[9]=new M_Image(d3d, d3d_dev, L"map\\grayland\\num9.png", 0xFF008000);
	
	isstart=false;
	isend=false;
	delay=0;
	kocount=0;
	fightcount=0;
	roundcount=0;
}

void Map_Grayland::deletememory(){
	if(hpbar!=NULL){
		delete hpbar;
		hpbar=NULL;
	}
	if(sysimage!=NULL){
		delete sysimage;
		sysimage=NULL;
	}
	if(koimage!=NULL){
		delete koimage;
		koimage=NULL;
	}
	if(roundimage!=NULL){
		delete roundimage;
		roundimage=NULL;
	}
	if(fightimage!=NULL){
		delete fightimage;
		fightimage=NULL;
	}
	if(font!=NULL){
		delete font;
		font=NULL;
	}
	for(int i=0;i<10;i++){
		if(numimage[i]!=NULL){
			delete numimage[i];
			numimage[i]=NULL;
		}
	}
	startvoice->stopnreset();
	endvoice->stopnreset();
	fightvoice->stopnreset();
}

void Map_Grayland::start(){
	if(delay==0){
		if(wcsncmp(p1->getname(), L"CHEETAHMEN", 10)==0){
			if(wcsncmp(p2->getname(), L"CHEETAHMEN", 10)==0){
				p1->startevent();
			}
			else{
				p1->startevent();
				p2->startevent();
			}
		}
		else{
			if(wcsncmp(p2->getname(), L"CHEETAHMEN", 10)==0){
				p1->startevent();
				p2->startevent();
			}
			else{
				p1->startevent();
				p2->startevent();
			}
		}
		startvoice->play(true, false);
		delay=110;
		roundcount=90;
	}
}

void Map_Grayland::end(){
	endvoice->play(true, false);
	kocount=200;
}

void Map_Grayland::update(){
	if(!isstart){
		delay--;
		if(delay==0){
			fightcount=60;
			isstart=true;
			fightvoice->play(true, false);
		}
	}
	if(!isend){
		isend=(p1->getlost()||p2->getlost());
		if(isend)
			end();
	}
}

void Map_Grayland::draw(bool drawbox){
	bgimage->draw(0.0f, 0.0f, 0xFFFFFFFF, false, false);

	p1->draw(drawbox);
	p1->drawevent(drawbox);
	p2->draw(drawbox);
	p2->drawevent(drawbox);
	drawsys();
}

void Map_Grayland::drawsys(){
	int hitcount=p2->gethitcount();
	if(hitcount>99){
		numimage[hitcount/100]->draw(48, 156, 0xFFFFFFFF, true, false);
		numimage[(hitcount%100)/10]->draw(112, 156, 0xFFFFFFFF, true, false);
		numimage[hitcount%10]->draw(176, 156, 0xFFFFFFFF, true, false);
	}
	else if(hitcount>9){
		numimage[hitcount/10]->draw(48, 156, 0xFFFFFFFF, true, false);
		numimage[hitcount%10]->draw(112, 156, 0xFFFFFFFF, true, false);
	}
	else if(hitcount>1){
		numimage[hitcount%10]->draw(48, 156, 0xFFFFFFFF, true, false);
	}
	hitcount=p1->gethitcount();
	if(hitcount>99){
		numimage[hitcount/100]->draw(824, 156, 0xFFFFFFFF, true, false);
		numimage[(hitcount%100)/10]->draw(888, 156, 0xFFFFFFFF, true, false);
		numimage[hitcount%10]->draw(952, 156, 0xFFFFFFFF, true, false);
	}
	else if(hitcount>9){
		numimage[hitcount/10]->draw(888, 156, 0xFFFFFFFF, true, false);
		numimage[hitcount%10]->draw(952, 156, 0xFFFFFFFF, true, false);
	}
	else if(hitcount>1){
		numimage[hitcount%10]->draw(952, 156, 0xFFFFFFFF, true, false);
	}

	sysimage->draw(500,60,0xFFFFFFFF,true,false);
	//1p
	hpbar->draw(440,70,((float)p1->getprevhp()/(float)p1->getmaxhp()),0xFFFFFFFF,false,true);
	p1->drawface(60, 30, true);
	font->draw(100, 440, 20, 65, 0xFF000000, p1->getname(), true);
	//2p
	hpbar->draw(560,70,((float)p2->getprevhp()/(float)p2->getmaxhp()),0xFFFFFFFF,false,false);
	p2->drawface(940, 30, false);
	font->draw(560, 900, 20, 65, 0xFF000000, p2->getname(), false);

	if(p1->getcutin()>59){
		bgimage->draw(0, 0, D3DCOLOR_ARGB(364-p1->getcutin()*4, 0, 0, 0), false, false);
	}
	else if(p1->getcutin()>29){
		bgimage->draw(0, 0, 0x80000000, false, false);
	}
	else if(p1->getcutin()>0){
		bgimage->draw(0, 0, D3DCOLOR_ARGB(4+p1->getcutin()*4, 0, 0, 0), false, false);
	}
	if(p2->getcutin()>59){
		bgimage->draw(0, 0, D3DCOLOR_ARGB(364-p2->getcutin()*4, 0, 0, 0), false, false);
	}
	else if(p2->getcutin()>29){
		bgimage->draw(0, 0, 0x80000000, false, false);
	}
	else if(p2->getcutin()>0){
		bgimage->draw(0, 0, D3DCOLOR_ARGB(4+p2->getcutin()*4, 0, 0, 0), false, false);
	}
	p1->drawcutin();
	p2->drawcutin();

	if(roundcount>74){
		roundimage->draw(500,300,D3DCOLOR_ARGB(1530-17*roundcount, 255, 255, 255), true, false);
		roundcount--;
	}
	else if(roundcount>14){
		roundimage->draw(500,300,0xFFFFFFFF, true, false);
		roundcount--;
	}
	else if(roundcount>0){
		roundimage->draw(500, 300, D3DCOLOR_ARGB(17*roundcount, 255, 255, 255), true, false);
		roundcount--;
	}
	if(fightcount>14){
		fightimage->draw(500, 300, 0xFFFFFFFF, true, false);
		fightcount--;
	}
	else if(fightcount>0){
		fightimage->draw(500, 300, D3DCOLOR_ARGB(17*fightcount, 255, 255, 255), true, false);
		fightcount--;
	}
	if(kocount>0){
		koimage->draw(500, 300, 0xFFFFFFFF, true, false);
		kocount--;
	}
}