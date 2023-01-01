#include "Game.h"


Game::Game(LPDIRECT3D9 _d3d, LPDIRECT3DDEVICE9 _d3d_dev)
{
	d3d=_d3d;
	d3d_dev=_d3d_dev;
	aud_dev=OpenDevice();

	keyboard1p=new Keyboard('F','H','T','G','Z','X');
	keyboard2p=new Keyboard(VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN, VK_OEM_PERIOD, VK_OEM_2);
	status=CHARSELECT;

	bgimage=new M_Image(d3d, d3d_dev, L"res\\bg.png", 0x00000000);
	targetimage=new M_Image(d3d, d3d_dev, L"res\\target.png", 0x00000000);
	vsimage=new M_Image(d3d, d3d_dev, L"res\\vs.png", 0x00000000);
	font=new M_Font(d3d, d3d_dev, 16, 32, 1000, L"πŸ≈¡", false);

	movesound=new M_Sound(aud_dev, "res\\01.wav", 0.5f);
	oksound=new M_Sound(aud_dev, "res\\02.wav", 0.5f);
	backsound=new M_Sound(aud_dev, "res\\03.wav", 0.5f);

	initialize();
}


Game::~Game(void)
{	
	if(!charlist.empty()){
		for(int i=0;i<charlist.size();i++){
			delete charlist.at(i);
		}
		charlist.clear();
	}
	if(!charlist2p.empty()){
		for(int i=0;i<charlist2p.size();i++){
			delete charlist2p.at(i);
		}
		charlist2p.clear();
	}
	if(!maplist.empty()){
		for(int i=0;i<maplist.size();i++){
			delete maplist.at(i);
		}
		maplist.clear();
	}

	delete keyboard1p;
	delete keyboard2p;

	delete bgimage;
	delete targetimage;
	delete vsimage;
	delete font;

	delete movesound;
	delete oksound;
	delete backsound;
}

void Game::initialize(){
	Character* chara;
	Gamemap* gmap;

	chara=new Char_YagamiLight(d3d, d3d_dev, aud_dev);
	charlist.push_back(chara);
	chara=new Char_HyugaNeji(d3d, d3d_dev, aud_dev);
	charlist.push_back(chara);
	chara=new Char_Cheetahmen(d3d, d3d_dev, aud_dev);
	charlist.push_back(chara);


	chara=new Char_YagamiLight(d3d, d3d_dev, aud_dev);
	charlist2p.push_back(chara);
	chara=new Char_HyugaNeji(d3d, d3d_dev, aud_dev);
	charlist2p.push_back(chara);
	chara=new Char_Cheetahmen(d3d, d3d_dev, aud_dev);
	charlist2p.push_back(chara);

	gmap=new Map_Grayland(d3d, d3d_dev, aud_dev);
	maplist.push_back(gmap);
	gmap=new Map_Kungfu(d3d, d3d_dev, aud_dev);
	maplist.push_back(gmap);

	p1num=0;
	p2num=charlist.size()-1;
	mapnum=0;
	delay=0;
	p1select=false;
	p2select=false;
	mapselect=false;
}

bool Game::gameloop(){
	switch(status){
	case GAMEPLAY:
		return gameplayloop();
		break;
	case CHARSELECT:
		return charselectloop(true);
		break;
	case MAPSELECT:
		return mapselectloop();
		break;
	default:
		return true;
	}
}

bool Game::charselectloop(bool select){
	int x, y;
	if(select){
		k1=keyboard1p->getkeystate(true);
		k2=keyboard2p->getkeystate(true);

		if(!p1select){
			if(k1==KP_6){
				if(p1num!=charlist.size()-1){
					p1num++;
					movesound->play(true, false);
				}
			}
			if(k1==KP_4){
				if(p1num!=0){
					p1num--;
					movesound->play(true, false);
				}
			}
			if(k1==KP_2){
				if(p1num!=charlist.size()-1){
					p1num+=CHARLISTROW;
					movesound->play(true, false);
					if(p1num>=charlist.size())
						p1num=charlist.size()-1;
				}
			}
			if(k1==KP_8){
				if(p1num!=0){
					p1num-=CHARLISTROW;
					movesound->play(true, false);
					if(p1num<0)
						p1num=0;
				}
			}
			char1p=charlist.at(p1num);
		}
		if(!p2select){
			if(k2==KP_6){
				if(p2num!=charlist.size()-1){
					p2num++;
					movesound->play(true, false);
				}
			}
			if(k2==KP_4){
				if(p2num!=0){
					p2num--;
					movesound->play(true, false);
				}
			}
			if(k2==KP_2){
				if(p2num!=charlist.size()-1){
					p2num+=CHARLISTROW;
					movesound->play(true, false);
					if(p2num>=charlist.size())
						p2num=charlist.size()-1;
				}
			}
			if(k2==KP_8){
				if(p2num!=0){
					p2num-=CHARLISTROW;
					movesound->play(true, false);
					if(p2num<0)
						p2num=0;
				}
			}
			char2p=charlist2p.at(p2num);
		}

		if(keyboard1p->getakey()){
			if(!p1select){
				p1select=true;
				oksound->play(true, false);
			}
		}
		else if(keyboard1p->getbkey()){
			if(p1select){
				p1select=false;
				backsound->play(true, false);
			}
		}
		if(keyboard2p->getakey()){
			if(!p2select){
				p2select=true;
				oksound->play(true, false);
			}
		}
		else if(keyboard2p->getbkey()){
			if(p2select){
				p2select=false;
				backsound->play(true, false);
			}
		}

		if(p1select&&p2select){
			status=MAPSELECT;
		}
	}

	bgimage->draw(0, 0, 0xFFFFFFFF, false, false);
	for(int i=0;i<charlist.size();i++){
		x=(i%CHARLISTROW)*40+104;
		y=(i/CHARLISTROW)*40+54;
		charlist.at(i)->drawface(x, y, true);
		if(i==p1num)
			targetimage->draw(x-4, y-4, 0xFFFFFF00, false, false);
		if(i==p2num)
			targetimage->draw(x-4, y-4, 0xFF7FFFFF, false, false);
	}
	charlist.at(p1num)->drawbigface(0, 300, true, p1select?0xFF7F7F7F:0xFFFFFFFF);
	charlist.at(p2num)->drawbigface(1000, 300, false, p2select?0xFF7F7F7F:0xFFFFFFFF);
	vsimage->draw(500, 450, 0xFFFFFFFF, true, false);
	font->draw(320, 680, 300, 450, 0xFFFFFFFF, char1p->getname(), true, true);
	font->draw(320, 680, 450, 600, 0xFFFFFFFF, char2p->getname(), false, true);
	return false;
}

bool Game::mapselectloop(){
	charselectloop(false);

	if(!mapselect){
		k1=keyboard1p->getkeystate(true);
		k2=keyboard2p->getkeystate(true);

		if((k1==KP_6)||(k2==KP_6)){
			mapnum++;
			movesound->play(true, false);
			if(mapnum>=maplist.size())
				mapnum=0;
		}
		if((k1==KP_4)||(k2==KP_4)){
			mapnum--;
			movesound->play(true, false);
			if(mapnum<0)
				mapnum=maplist.size()-1;
		}
		if(keyboard1p->getakey()||keyboard2p->getakey()){
			mapselect=true;
			oksound->play(true, false);
		}
		if(keyboard1p->getbkey()||keyboard2p->getbkey()){
			status=CHARSELECT;
			backsound->play(true, false);
			if(keyboard1p->getbkey()){
				p1select=false;
			}
			if(keyboard2p->getbkey()){
				p2select=false;
			}
		}
	}
	bgimage->draw(0, 0, 0x7F000000, false, false);
	maplist.at(mapnum)->drawbgimage(500, 300, 0.5f, 0.5f);
	font->draw(300, 700, 50, 130, 0xFFFFFF00, L"MAP SELECT", true);
	font->draw(300, 700, 470, 600, 0xFFFFFF00, maplist.at(mapnum)->getname(), false, false);


	if(mapselect){
		if(delay<60){
			delay++;
			bgimage->draw(0, 0, D3DCOLOR_ARGB(delay*4, 0, 0, 0), false, false);
		}
		else if(delay==60){
			delay++;
			bgimage->draw(0, 0, 0xFF000000, false, false);
		}
		else{
			bgimage->draw(0, 0, 0xFF000000, false, false);
			status=GAMEPLAY;
			map=maplist.at(mapnum);
			map->initialize();
			char1p->charinit(char2p, keyboard1p, map->getleft(), map->getright());
			char2p->charinit(char1p, keyboard2p, map->getleft(), map->getright());
			char1p->setx(150);
			char2p->setx(850);
			map->setchar(char1p, char2p);
		}
	}

	return false;
}

bool Game::gameplayloop(){
	static int flag=0;

	if(!map->getisstart()){
		map->start();
		map->update();
		if(flag!=2)
			flag++;
		else{
			char1p->nextmotion();
			char2p->nextmotion();
			flag=0;
		}
		char1p->setleftright(char2p);
		char2p->setleftright(char1p);
		char1p->setidle();
		char2p->setidle();
		char1p->update();
		char2p->update();
		char1p->move();
		char2p->move();
		map->draw(ISTEST);
	}
	else{
		if(flag!=2){
			flag++;
			char1p->setidle();
			char2p->setidle();
			char1p->update();
			char2p->update();
			char1p->move();
			char2p->move();
			map->draw(ISTEST);
			if(delay>0){
				bgimage->draw(0, 0, D3DCOLOR_ARGB(delay*4, 0, 0, 0), false, false);
			}
			return false;
		}
		flag=0;


		char1p->nextmotion();
		char2p->nextmotion();

		char1p->setleftright(char2p);
		char2p->setleftright(char1p);
		char1p->setbehavior();
		char2p->setbehavior();
		char1p->update();
		char2p->update();
		char1p->move();
		char2p->move();

		char1p->eventupdatebeforecollapse();
		char2p->eventupdatebeforecollapse();

		char1p->collapse(char2p);
		char2p->collapse(char1p);

		char1p->eventupdateaftercollapse();
		char2p->eventupdateaftercollapse();

		//win?

		map->update();
		map->draw(ISTEST);
		//system.draw();
		if(map->getisend()){
			k1=KP_5;
			k2=KP_5;
			status=CHARSELECT;
			map->deletememory();
			char1p->deletememory();
			char2p->deletememory();
			p1select=false;
			p2select=false;
			mapselect=false;
		}
	}
	if(delay>0){
		delay--;
		bgimage->draw(0, 0, D3DCOLOR_ARGB(delay*4, 0, 0, 0), false, false);
	}
	return false;
}