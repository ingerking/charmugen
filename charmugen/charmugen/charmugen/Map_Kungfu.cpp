#include "Map_Kungfu.h"


Map_Kungfu::Map_Kungfu(LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3d_dev, AudioDevicePtr _aud_dev):Gamemap(d3d, d3d_dev, _aud_dev)
{
	bgm=new M_Sound(_aud_dev, "map\\kungfu\\00.wav", 0.5f);
	bgimage=new M_Image(d3d, d3d_dev, L"map\\kungfu\\background.png", 0x00000000);

	hpbar=NULL;
	font=NULL;
	scofont=NULL;

	wcscpy(mapname, L"Kungfu");
	left=85;
	right=915;
	down=36;
}


Map_Kungfu::~Map_Kungfu(void)
{
	deletememory();
	delete bgm;
	delete bgimage;
}

void Map_Kungfu::initialize(){
	hpbar=new M_Image(d3d, d3d_dev, L"map\\kungfu\\hpbar.png", 0x00000000);
	font=new M_Font(d3d, d3d_dev, 9, 18, 1000, L"±¼¸²", false);
	scofont=new M_Font(d3d, d3d_dev, 20, 24, 1600, L"±¼¸²", false);
	isstart=false;
	isend=false;
	delay=0;
	kocount=0;
	fightcount=0;
	roundcount=0;
	maxhit=0;
}

void Map_Kungfu::deletememory(){
	if(hpbar!=NULL){
		delete hpbar;
		hpbar=NULL;
	}
	if(font!=NULL){
		delete font;
		font=NULL;
	}
	if(scofont!=NULL){
		delete scofont;
		scofont=NULL;
	}
	bgm->stopnreset();
}

void Map_Kungfu::start(){
	if(delay==0){
		if(wcsncmp(p1->getname(), L"CHEETAHMEN", 10)==0){
			if(wcsncmp(p2->getname(), L"CHEETAHMEN", 10)==0){
				p1->startevent();
				delay=1;
			}
			else{
				p1->startevent();
				p2->startevent();
				delay=1;
			}
		}
		else{
			if(wcsncmp(p2->getname(), L"CHEETAHMEN", 10)==0){
				p1->startevent();
				p2->startevent();
				delay=1;
			}
			else{
				p1->startevent();
				p2->startevent();
				bgm->play(true, true);
				delay=210;
			}
		}
	}
}

void Map_Kungfu::end(){
	kocount=150;
}

void Map_Kungfu::update(){
	if(!isstart){
		delay--;
		if(delay==0){
			isstart=true;
		}
	}
	if(!isend){
		isend=(p1->getlost()||p2->getlost());
		if(isend)
			end();
	}
}

void Map_Kungfu::draw(bool drawbox){
	bgimage->draw(0.0f, 0.0f, 0xFFFFFFFF, false, false);

	p1->draw(drawbox);
	p1->drawevent(drawbox);
	p2->draw(drawbox);
	p2->drawevent(drawbox);
	drawsys();
}

void Map_Kungfu::drawsys(){
	int hitcount=p2->gethitcount();
	wchar_t str[32];
	swprintf(str, 32, L"SCORE\n%d", hitcount*100);
	scofont->draw(0, 265, 0, 60, 0xFFFFFFFF, str, false);
	if(hitcount>maxhit)
		maxhit=hitcount;

	hitcount=p1->gethitcount();
	swprintf(str, 32, L"SCORE\n%d", hitcount*100);
	scofont->draw(600, 895, 0, 60, 0xFFFFFFFF, str, false);
	if(hitcount>maxhit)
		maxhit=hitcount;

	swprintf(str, 32, L"HI-SCORE\n%d¡¡", maxhit*100);
	scofont->draw(200, 610, 0, 60, 0xFFFFFFFF, str, false);

	float percent;
	//1p
	percent=(float)p1->getprevhp()/(float)p1->getmaxhp();
	hpbar->draw(442,90,percent,percent>0.3f?0xFF4868F4:0xFFB02020,false,true);
	font->draw(180, 442, 100, 130, 0xFFFFFFFF, p1->getname(), true);
	//2p
	percent=(float)p2->getprevhp()/(float)p2->getmaxhp();
	hpbar->draw(558,90,percent,percent>0.3f?0xFF4868F4:0xFFB02020,false,false);
	font->draw(563, 825, 100, 130, 0xFFFFFFFF, p2->getname(), false);

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

	if(kocount>0)
		kocount--;
}