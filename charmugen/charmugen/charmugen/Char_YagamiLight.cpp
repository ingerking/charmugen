#include "Char_YagamiLight.h"


Char_YagamiLight::Char_YagamiLight(LPDIRECT3D9 _d3d, LPDIRECT3DDEVICE9 _d3d_dev, AudioDevicePtr _aud_dev):Character(_d3d, _d3d_dev, _aud_dev)
{
	M_Sound* sound;
	char str[64];
	cutincanchangedist=false;

	wcscpy(cname, L"YAGAMI LIGHT");
	face=new M_Image(d3d, d3d_dev, L"character\\yagamilight\\image\\face.png", 0x00000000);
	bigface=new M_Image(d3d, d3d_dev, L"character\\yagamilight\\image\\bigface.png", 0x00000000);
	cutin=new M_Image(d3d, d3d_dev, L"character\\yagamilight\\image\\cutin.png", 0x00000000);

	for(int i=0;i<3;i++){
		sprintf_s(str, 64, "character\\yagamilight\\sound\\%02d.wav", i);
		sound=new M_Sound(_aud_dev, str, 0.5f);
		soundlist.push_back(sound);
	}
}


Char_YagamiLight::~Char_YagamiLight(void)
{
	deletememory();
	delete face;
	delete bigface;
	delete cutin;
	for(int i=0;i<soundlist.size();i++){
		delete soundlist.at(i);
	}
}

void Char_YagamiLight::initialize(){
	wchar_t str[64];

	maxhp=YAGAMI_MAXHP;
	nowhp=maxhp;
	prevhp=nowhp;
	height=54;
	dnoteflag=-1;
	delay=0;


	Motion motion;
	motion.atkbox.up=-1;
	motion.defbox1.up=-54;
	motion.defbox1.down=54;
	motion.defbox1.left=-20;
	motion.defbox1.right=17;
	motion.defbox2.up=-1;
	motion.absolutedmg=false;
	motion.dmg=-1;
	motion.downhit=false;
	motion.ignoreguarddmg=false;
	motion.hitcountup=false;
	motion.spritenum=0;
	motion.freeze=-1;
	motion.soundnum=-1;
	motion.hitsoundnum=-1;

	for(int i=0;i<28;i++){
		motion.spritenum=i;
		swprintf(str, 64, L"character\\yagamilight\\image\\%02d.png", i);
		M_Image* image=new M_Image(d3d, d3d_dev, str, D3DCOLOR_XRGB(0, 132, 0));
		imagelist.push_back(image);
		if(i==9){
			Motion tmotion=motion;
			tmotion.defbox1.left=-27;
			tmotion.defbox1.right=10;
			motionlist.push_back(tmotion);
		}
		else if(i==10){
			Motion tmotion=motion;
			tmotion.defbox1.up=-1;
			motionlist.push_back(tmotion);
		}
		else if(i>=20){
			Motion tmotion=motion;
			tmotion.defbox1.left=-17;
			tmotion.defbox1.right=20;
			motionlist.push_back(tmotion);
		}
		else{
			motionlist.push_back(motion);
		}
	}

	motion.atkbox.up=-9999;
	motion.atkbox.down=9999;
	motion.atkbox.left=-9999;
	motion.atkbox.right=9999;


	motion.freeze=600;
	motion.dmg=0;
	motion.hitcountup=false;
	motion.hitsoundnum=-1;
	motion.downhit=false;
	motion.ignoreguarddmg=true;
	motion.spritenum=0;

	motion.soundnum=2;//계획대로
	motionlist.push_back(motion);

	motion.soundnum=1;//두근
	motionlist.push_back(motion);

	motion.soundnum=-1;
	motion.dmg=1000000;
	motion.downhit=true;
	motion.hitcountup=true;
	motionlist.push_back(motion);

	deathnotelist.push_back(5);
	deathnotelist.push_back(5);
	deathnotelist.push_back(4);
	deathnotelist.push_back(4);
	deathnotelist.push_back(5);
	deathnotelist.push_back(5);
	deathnotelist.push_back(4);
	deathnotelist.push_back(4);
	deathnotelist.push_back(5);
	deathnotelist.push_back(5);
	deathnotelist.push_back(3);
	deathnotelist.push_back(3);
	deathnotelist.push_back(4);
	deathnotelist.push_back(4);
	deathnotelist.push_back(3);
	deathnotelist.push_back(3);
	deathnotelist.push_back(5);
	deathnotelist.push_back(5);
	deathnotelist.push_back(3);
	deathnotelist.push_back(3);
	deathnotelist.push_back(4);
	deathnotelist.push_back(4);
	deathnotelist.push_back(3);
	deathnotelist.push_back(3);
	deathnotelist.push_back(7);
	deathnotelist.push_back(8);
}

void Char_YagamiLight::deletememory(){
	if(!imagelist.empty()){
		for(int i=0;i<imagelist.size();i++){
			delete imagelist.at(i);
		}
		imagelist.clear();
	}
	if(!motionlist.empty()){
		motionlist.clear();
	}
	if(!motionnumlist.empty()){
		motionnumlist.clear();
	}
	if(!deathnotelist.empty()){
		deathnotelist.clear();
	}
	for(int i=0;i<soundlist.size();i++){
		soundlist.at(i)->stopnreset();
	}
}



void Char_YagamiLight::eventupdatebeforecollapse(){
	if(dnoteflag==-1){
		if(nowmotionnum==7)
			dnoteflag=242;
		else if(dnoteflag<=0){
			if(deathnotelist.size()==0)
				dnoteflag=242;
		}
	}
	else if(dnoteflag==2){
		setcutin();
		soundlist[2]->play(true, false);
		delay=120;
		dnoteflag=1;
	}
	else if(dnoteflag==1){
		if(delay==0){
			enemy->setdamage(0, 90, false, false);
			soundlist.at(1)->play(true, false);
			delay=45;
			dnoteflag=0;
		}
	}
	else if(dnoteflag==0){
		if(delay==0){
			enemy->setdamage(1000000, 0, false, true);
			dnoteflag=-1;
		}
	}
	else if(dnoteflag>=0)
		dnoteflag--;
	if(delay>0)
		delay--;
}
void Char_YagamiLight::eventupdateaftercollapse(){
	if(status==ATTACK){
		if(deathnotelist.size()!=0)
			deathnotelist.pop_front();
	}
}

void Char_YagamiLight::setidle(){
	if(!isjump&&!islost){
		switch(status){
		case MOVEFRONT:
			if(motionnumlist.size()==0){
				for(int i=12;i<20;i++){
					motionnumlist.push_back(i);
					motionnumlist.push_back(i);
				}
			}
			break;
		case MOVEBACK:
			if(motionnumlist.size()==0){
				for(int i=20;i<28;i++){
					motionnumlist.push_back(i);
					motionnumlist.push_back(i);
				}
			}
			break;
		case DOWN:
			if((motionnumlist.size()==0)&&(freezetime==0)){
				motionnumlist.push_back(0);
				status=IDLE;
				nextdmg=-1;
				hitcount=0;
			}
			break;
		default:
			if(motionnumlist.size()==0){
				motionnumlist.push_back(0);
				status=IDLE;
				nextdmg=-1;
				hitcount=0;
			}
		}
	}
}

void Char_YagamiLight::jump(){
	isjump=true;
	vy=16;
	keyboard->keylistclear(0);
	motionnumlist.clear();
	motionnumlist.push_back(15);
}

void Char_YagamiLight::hit(){
	if(nowhp>0){
		status=HIT;
		nowmotionnum=9;
		vy=0;
		motionnumlist.clear();
		motionnumlist.push_back(9);
		motionnumlist.push_back(9);
		motionnumlist.push_back(9);
		motionnumlist.push_back(9);
		motionnumlist.push_back(9);
		nextmotion();
	}
	else
		down();
}
void Char_YagamiLight::down(){
	status=DOWN;
	freezetime=20;
	motionnumlist.clear();
	motionnumlist.push_back(10);
	motionnumlist.push_back(10);
	motionnumlist.push_back(10);
	motionnumlist.push_back(10);
	motionnumlist.push_back(10);
	motionnumlist.push_back(10);
	motionnumlist.push_back(10);
	motionnumlist.push_back(10);
	motionnumlist.push_back(10);
	motionnumlist.push_back(10);
	motionnumlist.push_back(10);
	motionnumlist.push_back(10);
	motionnumlist.push_back(10);
	motionnumlist.push_back(10);
	motionnumlist.push_back(10);
	nextmotion();
	vy=15;
	if(nowhp<=0){
		islost=true;
		soundlist[0]->play(true, false);
	}
}
void Char_YagamiLight::BH_5(bool a, bool b){
	if(!isjump){
		if(a||b){
			if(status!=ATTACK){
				motionnumlist.clear();
				motionnumlist.push_back(1);
				motionnumlist.push_back(2);
				motionnumlist.push_back(3);
				for(list<int>::iterator iter=deathnotelist.begin();iter!=deathnotelist.end();iter++){
					int i=*iter;
					motionnumlist.push_back(i);
				}
				status=ATTACK;
			}
		}
		else{
			switch(status){
			case DASH:
			case MOVEFRONT:
			case MOVEBACK:
			case SIT:
				motionnumlist.clear();
				status=IDLE;
				break;
			}
		}
	}
}
void Char_YagamiLight::BH_2(bool a, bool b){
	if(!isjump){
		if(a||b){
			if(status!=ATTACK){
				motionnumlist.clear();
				motionnumlist.push_back(1);
				motionnumlist.push_back(2);
				motionnumlist.push_back(3);
				for(list<int>::iterator iter=deathnotelist.begin();iter!=deathnotelist.end();iter++){
					int i=*iter;
					motionnumlist.push_back(i);
				}
				status=ATTACK;
			}
		}
		else{
			switch(status){
			case DASH:
			case MOVEFRONT:
			case MOVEBACK:
			case IDLE:
				motionnumlist.clear();
				status=SIT;
				break;
			}
		}
	}
}
void Char_YagamiLight::BH_4(bool a, bool b){
	if(!isjump){
		if(a||b)
			BH_5(a, b);
		else{
			if(ischarlookright){
				if(status!=MOVEBACK){
					motionnumlist.clear();
					status=MOVEBACK;
				}
			}
			else{
				if(status!=MOVEFRONT){
					motionnumlist.clear();
					status=MOVEFRONT;
				}
			}
		}
	}
}
void Char_YagamiLight::BH_6(bool a, bool b){
	if(!isjump){
		if(a||b)
			BH_5(a, b);
		else{
			if(ischarlookright){
				if(status!=MOVEFRONT){
					motionnumlist.clear();
					status=MOVEFRONT;
				}
			}
			else{
				if(status!=MOVEBACK){
					motionnumlist.clear();
					status=MOVEBACK;
				}
			}
		}
	}
}

void Char_YagamiLight::BH_8(bool a, bool b){
	if(!isjump){
		status=VJUMP;
		jump();
	}
}
void Char_YagamiLight::BH_7(bool a, bool b){
	if(!isjump){
		status=LJUMP;
		jump();
	}
}
void Char_YagamiLight::BH_9(bool a, bool b){
	if(!isjump){
		status=RJUMP;
		jump();
	}
}

void Char_YagamiLight::BH_236(bool a, bool b){BH_6(a, b);}
void Char_YagamiLight::BH_214(bool a, bool b){BH_4(a, b);}
void Char_YagamiLight::BH_22(bool a, bool b){BH_2(a, b);}

void Char_YagamiLight::BH_66(bool a, bool b){
	BH_6(a, b);
}
void Char_YagamiLight::BH_44(bool a, bool b){
	BH_4(a, b);
}

void Char_YagamiLight::BH_623(bool a, bool b){BH_6(a, b);}
void Char_YagamiLight::BH_421(bool a, bool b){BH_4(a, b);}
void Char_YagamiLight::BH_41236(bool a, bool b){BH_6(a, b);}
void Char_YagamiLight::BH_63214(bool a, bool b){BH_4(a, b);}
void Char_YagamiLight::BH_236236(bool a, bool b){BH_6(a, b);}
void Char_YagamiLight::BH_214214(bool a, bool b){BH_4(a, b);}
void Char_YagamiLight::BH_2141236(bool a, bool b){BH_6(a, b);}
void Char_YagamiLight::BH_2363214(bool a, bool b){BH_4(a, b);}
void Char_YagamiLight::BH_641236(bool a, bool b){BH_6(a, b);}
void Char_YagamiLight::BH_463214(bool a, bool b){BH_4(a, b);}
void Char_YagamiLight::BH_4123641236(bool a, bool b){BH_6(a, b);}
void Char_YagamiLight::BH_6321463214(bool a, bool b){BH_4(a, b);}