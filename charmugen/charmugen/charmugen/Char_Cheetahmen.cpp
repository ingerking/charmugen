#include "Char_Cheetahmen.h"


Char_Cheetahmen::Char_Cheetahmen(LPDIRECT3D9 _d3d, LPDIRECT3DDEVICE9 _d3d_dev, AudioDevicePtr _aud_dev):Character(_d3d, _d3d_dev, _aud_dev)
{
	M_Sound* sound;
	cutincanchangedist=false;
	leftright=false;

	wcscpy(cname, L"CHEETAHMEN");
	face=new M_Image(d3d, d3d_dev, L"character\\cheetahmen\\image\\face.png", 0x00000000);
	bigface=new M_Image(d3d, d3d_dev, L"character\\cheetahmen\\image\\bigface.png", 0xFFABE7FF);
	cutin=new M_Image(d3d, d3d_dev, L"character\\cheetahmen\\image\\face.png", 0x00000000);

	sound=new M_Sound(_aud_dev, "character\\cheetahmen\\sound\\00.mp3", 0.5f);
	soundlist.push_back(sound);
	sound=new M_Sound(_aud_dev, "character\\cheetahmen\\sound\\01.wav", 0.5f);
	soundlist.push_back(sound);
	sound=new M_Sound(_aud_dev, "character\\cheetahmen\\sound\\02.wav", 0.5f);
	soundlist.push_back(sound);
}


Char_Cheetahmen::~Char_Cheetahmen(void)
{
	deletememory();
	delete face;
	delete bigface;
	delete cutin;
	for(int i=0;i<soundlist.size();i++){
		delete soundlist.at(i);
	}
}

void Char_Cheetahmen::initialize(){
	wchar_t str[64];

	maxhp=CHEETAH_MAXHP;
	nowhp=maxhp;
	prevhp=nowhp;
	height=64;
	num=0;
	playing=false;


	Motion motion;
	motion.atkbox.up=-1;
	motion.defbox1.up=-32;
	motion.defbox1.down=64;
	motion.defbox1.left=-24;
	motion.defbox1.right=24;
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

	for(int i=0;i<13;i++){
		motion.spritenum=i;
		swprintf(str, 64, L"character\\cheetahmen\\image\\%02d.png", i);
		M_Image* image=new M_Image(d3d, d3d_dev, str, 0xFFABE7FF);
		imagelist.push_back(image);
		motion.spritenum=i;
		motionlist.push_back(motion);
	}
	motionlist.at(5).defbox1.up=-64;
	motionlist.at(4).defbox1.up=-64;
	motionlist.at(3).defbox1.up=-1;
	motionlist.at(7).defbox1.up=-1;
	motionlist.at(11).defbox1.up=-1;

	motion.spritenum=10;
	motion.defbox1.right=54;
	motionlist[10]=motion;

	motion.spritenum=2;
	motion.dmg=15;
	motion.freeze=0;
	motion.hitsoundnum=1;
	motion.hitcountup=false;
	motion.downhit=false;
	motion.ignoreguarddmg=false;
	motion.absolutedmg=false;
	motion.atkbox.up=-34;
	motion.atkbox.down=14;
	motion.atkbox.left=25;
	motion.atkbox.right=60;
	motion.defbox1.right=40;
	motionlist[2]=motion;

	motion.spritenum=6;
	motion.dmg=20;
	motion.hitsoundnum=1;
	motion.atkbox.up=-43;
	motion.atkbox.down=-10;
	motion.atkbox.left=25;
	motion.atkbox.right=55;
	motion.defbox1.up=-53;
	motion.defbox1.right=47;
	motionlist[6]=motion;

	motion=motionlist.at(2);
	motion.dmg=-1;
	motionlist.push_back(motion);//13-num0
	motion=motionlist.at(6);
	motion.dmg=-1;
	motionlist.push_back(motion);//14-num1
	motion=motionlist.at(10);
	motion.dmg=-1;
	motionlist.push_back(motion);//15-num2
	////////12 = 화살
	/////13 14 15 = 공격
}

void Char_Cheetahmen::deletememory(){
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
	for(int i=0;i<soundlist.size();i++){
		soundlist.at(i)->stopnreset();
	}
	if(!bulletlist.empty())
		bulletlist.clear();
}



void Char_Cheetahmen::eventupdatebeforecollapse(){
	;
}
void Char_Cheetahmen::eventupdateaftercollapse(){
	list<Collapsebox>::iterator iter=bulletlist.begin();
	bool flag=false;
	Motion enemymotion=enemy->getmotion();
	Collapsebox motion;
	while(iter!=bulletlist.end()){
		flag=false;
		motion.up=CHEETAH_BDIST-1-iter->up;
		motion.down=CHEETAH_BDIST+1-iter->up;
		if(iter->right<0){
			motion.left=iter->left-8+iter->right;
			motion.right=iter->left+8;
		}
		else{
			motion.left=iter->left-8;
			motion.right=iter->left+8+iter->right;
		}
		iter->left+=iter->right;
		if(iscollapse(&motion, &enemymotion.defbox1))
			flag=true;
		else if(iscollapse(&motion, &enemymotion.defbox2))
			flag=true;
		if(flag){
			enemy->setdamage(10, 0, true, false);
			soundlist.at(1)->play(true, false);
			iter=bulletlist.erase(iter);
		}
		else if(iter->left<-30||iter->left>970)
			iter=bulletlist.erase(iter);
		else
			iter++;
	}
}

void Char_Cheetahmen::setidle(){
	static int flag=0;
	if(!isjump&&!islost){
		switch(status){
		case MOVEFRONT:
		case MOVEBACK:
			if(flag==4){
				if(nowmotionnum%4==0)
					nowmotionnum=num*4+1;
				else
					nowmotionnum=num*4;
				flag=0;
			}
			else
				flag++;
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
				if(nowmotionnum==num*4+2)
					nowmotionnum=num*4;
				status=IDLE;
				nextdmg=-1;
				hitcount=0;
			}
		}
	}
}

void Char_Cheetahmen::jump(){
	soundlist.at(2)->play(true, false);
	isjump=true;
	vy=16;
	keyboard->keylistclear(0);
	motionnumlist.clear();
	motionnumlist.push_back(num*4);
}

void Char_Cheetahmen::hit(){
	if(nowhp>0){
		status=HIT;
		vy=0;
		motionnumlist.clear();
		switch(num){
		case 0:
			nowmotionnum=0;
			motionnumlist.push_back(0);
			motionnumlist.push_back(0);
			motionnumlist.push_back(0);
			motionnumlist.push_back(0);
			motionnumlist.push_back(0);
			break;
		case 1:
			nowmotionnum=4;
			motionnumlist.push_back(4);
			motionnumlist.push_back(4);
			motionnumlist.push_back(4);
			motionnumlist.push_back(4);
			motionnumlist.push_back(4);
			break;
		default:
			nowmotionnum=8;
			motionnumlist.push_back(8);
			motionnumlist.push_back(8);
			motionnumlist.push_back(8);
			motionnumlist.push_back(8);
			motionnumlist.push_back(8);
			break;
		}
		nextmotion();
	}
	else
		down();
}
void Char_Cheetahmen::down(){
	status=DOWN;
	freezetime=20;
	motionnumlist.clear();
	switch(num){
	case 0:
		motionnumlist.push_back(3);
		motionnumlist.push_back(3);
		motionnumlist.push_back(3);
		motionnumlist.push_back(3);
		motionnumlist.push_back(3);
		motionnumlist.push_back(3);
		motionnumlist.push_back(3);
		motionnumlist.push_back(3);
		motionnumlist.push_back(3);
		motionnumlist.push_back(3);
		motionnumlist.push_back(3);
		motionnumlist.push_back(3);
		motionnumlist.push_back(3);
		motionnumlist.push_back(3);
		motionnumlist.push_back(3);
		break;
	case 1:
		motionnumlist.push_back(7);
		motionnumlist.push_back(7);
		motionnumlist.push_back(7);
		motionnumlist.push_back(7);
		motionnumlist.push_back(7);
		motionnumlist.push_back(7);
		motionnumlist.push_back(7);
		motionnumlist.push_back(7);
		motionnumlist.push_back(7);
		motionnumlist.push_back(7);
		motionnumlist.push_back(7);
		motionnumlist.push_back(7);
		motionnumlist.push_back(7);
		motionnumlist.push_back(7);
		motionnumlist.push_back(7);
		break;
	default:
		motionnumlist.push_back(11);
		motionnumlist.push_back(11);
		motionnumlist.push_back(11);
		motionnumlist.push_back(11);
		motionnumlist.push_back(11);
		motionnumlist.push_back(11);
		motionnumlist.push_back(11);
		motionnumlist.push_back(11);
		motionnumlist.push_back(11);
		motionnumlist.push_back(11);
		motionnumlist.push_back(11);
		motionnumlist.push_back(11);
		motionnumlist.push_back(11);
		motionnumlist.push_back(11);
		motionnumlist.push_back(11);
	}
	nextmotion();
	vy=15;
	if(nowhp<=0){
		islost=true;
	}
}
void Char_Cheetahmen::BH_5(bool a, bool b){
	if(a){
		if(status!=ATTACK){
			motionnumlist.clear();
			status=ATTACK;
			int atknum=num*4+2;
			motionnumlist.push_back(atknum);
			motionnumlist.push_back(13+num);
			motionnumlist.push_back(13+num);
			motionnumlist.push_back(13+num);
			motionnumlist.push_back(13+num);
			motionnumlist.push_back(13+num);
			atknum-=2;
			motionnumlist.push_back(atknum);
			motionnumlist.push_back(atknum);
			if(num==2){
				Collapsebox motion;
				motion.left=x;
				motion.up=y+14;
				motion.right=ischarlookright?24:-24;
				bulletlist.push_back(motion);
			}
		}
	}
	else if(b){
		if(num!=2)
			num++;
		else
			num=0;
		nowmotionnum=num*4;
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

void Char_Cheetahmen::BH_2(bool a, bool b){
	BH_5(a, b);
}

void Char_Cheetahmen::BH_4(bool a, bool b){
	if(!isjump){
		ischarlookright=false;
		if(a||b)
			BH_5(a, b);
		else{
			if(ischarlookright){
				if(status!=MOVEBACK){
					motionnumlist.clear();
					nowmotionnum=num*4+1;
					status=MOVEBACK;
				}
			}
			else{
				if(status!=MOVEFRONT){
					motionnumlist.clear();
					nowmotionnum=num*4+1;
					status=MOVEFRONT;
				}
			}
		}
	}
	else if(a||b)
		BH_5(a, b);
}
void Char_Cheetahmen::BH_6(bool a, bool b){
	if(!isjump){
		ischarlookright=true;
		if(a||b)
			BH_5(a, b);
		else{
			if(ischarlookright){
				if(status!=MOVEFRONT){
					motionnumlist.clear();
					nowmotionnum=num*4+1;
					status=MOVEFRONT;
				}
			}
			else{
				if(status!=MOVEBACK){
					motionnumlist.clear();
					nowmotionnum=num*4+1;
					status=MOVEBACK;
				}
			}
		}
	}
	else if(a||b)
		BH_5(a, b);
}

void Char_Cheetahmen::BH_8(bool a, bool b){
	if(!isjump){
		status=VJUMP;
		jump();
	}
}
void Char_Cheetahmen::BH_7(bool a, bool b){
	if(!isjump){
		ischarlookright=false;
		status=LJUMP;
		jump();
	}
}
void Char_Cheetahmen::BH_9(bool a, bool b){
	if(!isjump){
		ischarlookright=true;
		status=RJUMP;
		jump();
	}
}

void Char_Cheetahmen::BH_236(bool a, bool b){BH_6(a, b);}
void Char_Cheetahmen::BH_214(bool a, bool b){BH_4(a, b);}
void Char_Cheetahmen::BH_22(bool a, bool b){BH_2(a, b);}

void Char_Cheetahmen::BH_66(bool a, bool b){
	BH_6(a, b);
}
void Char_Cheetahmen::BH_44(bool a, bool b){
	BH_4(a, b);
}

void Char_Cheetahmen::BH_623(bool a, bool b){BH_6(a, b);}
void Char_Cheetahmen::BH_421(bool a, bool b){BH_4(a, b);}
void Char_Cheetahmen::BH_41236(bool a, bool b){BH_6(a, b);}
void Char_Cheetahmen::BH_63214(bool a, bool b){BH_4(a, b);}
void Char_Cheetahmen::BH_236236(bool a, bool b){BH_6(a, b);}
void Char_Cheetahmen::BH_214214(bool a, bool b){BH_4(a, b);}
void Char_Cheetahmen::BH_2141236(bool a, bool b){BH_6(a, b);}
void Char_Cheetahmen::BH_2363214(bool a, bool b){BH_4(a, b);}
void Char_Cheetahmen::BH_641236(bool a, bool b){BH_6(a, b);}
void Char_Cheetahmen::BH_463214(bool a, bool b){BH_4(a, b);}
void Char_Cheetahmen::BH_4123641236(bool a, bool b){BH_6(a, b);}
void Char_Cheetahmen::BH_6321463214(bool a, bool b){BH_4(a, b);}

void Char_Cheetahmen::drawevent(bool drawbox){
	for(list<Collapsebox>::iterator iter=bulletlist.begin();iter!=bulletlist.end();iter++){
		imagelist.at(12)->draw(iter->left, CHEETAH_BDIST-iter->up, 0xFFFFFFFF, true, !ischarlookright);
	}
}

void Char_Cheetahmen::startevent(){
	if(!playing){
		playing=true;
		soundlist.at(0)->play(true, true);
	}
}