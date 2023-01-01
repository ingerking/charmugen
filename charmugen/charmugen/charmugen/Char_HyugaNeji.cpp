#include "Char_HyugaNeji.h"


Char_HyugaNeji::Char_HyugaNeji(LPDIRECT3D9 _d3d, LPDIRECT3DDEVICE9 _d3d_dev, AudioDevicePtr _aud_dev):Character(_d3d, _d3d_dev, _aud_dev)
{
	M_Sound* sound;
	char str[64];
	cutincanchangedist=true;

	wcscpy(cname, L"HYUGA NEJI");
	face=new M_Image(d3d, d3d_dev, L"character\\hyuganeji\\image\\face.png", 0xFF008000);
	bigface=new M_Image(d3d, d3d_dev, L"character\\hyuganeji\\image\\bigface.png", 0xFF008000);
	cutin=new M_Image(d3d, d3d_dev, L"character\\hyuganeji\\image\\cutin.png", 0xFF008000);

	for(int i=0;i<9;i++){
		sprintf_s(str, 64, "character\\HyugaNeji\\sound\\%02d.wav", i);
		sound=new M_Sound(_aud_dev, str, 0.5f);
		soundlist.push_back(sound);
	}
}


Char_HyugaNeji::~Char_HyugaNeji(void)
{
	deletememory();
	delete face;
	delete bigface;
	delete cutin;
	for(int i=0;i<soundlist.size();i++){
		delete soundlist.at(i);
	}
}

void Char_HyugaNeji::initialize(){
	wchar_t str[64];

	maxhp=NEJI_MAXHP;
	nowhp=maxhp;
	prevhp=nowhp;
	height=58;
	uppertime=0;
	ha64time=0;
	ha64flag=false;

	Motion basemotion;
	Motion motion;
	basemotion.atkbox.up=-1;
	basemotion.defbox1.up=-54;
	basemotion.defbox1.down=54;
	basemotion.defbox1.left=-27;
	basemotion.defbox1.right=8;
	basemotion.defbox2.up=-1;
	basemotion.absolutedmg=false;
	basemotion.dmg=-1;
	basemotion.downhit=false;
	basemotion.ignoreguarddmg=false;
	basemotion.hitcountup=false;
	basemotion.spritenum=0;
	basemotion.freeze=-1;
	basemotion.soundnum=-1;
	basemotion.hitsoundnum=-1;

	for(int i=0;i<88;i++){
		motion=basemotion;
		motion.spritenum=i;
		swprintf(str, 64, L"character\\HyugaNeji\\image\\%02d.png", i);
		M_Image* image=new M_Image(d3d, d3d_dev, str, 0xFF008000);
		imagelist.push_back(image);
		///////////////////////18=가드, 23=히트, 24~27=다운
		//////////28 29 30 31 32 a  33 34 35 36 37 38 b
		/////39 40 41 42 43 44 ~53 회천
		///////a b 54 55 56 57 58 59 60 61 어퍼
		//63 64 65 우회전 66 67 68 좌회전 69 70 2장
		/////71 72 73 74 75 76 64장
		switch(i){
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
			motion.defbox1.up=-58;
			motion.defbox1.down=54;
			motion.defbox1.left=-20;
			motion.defbox1.right=17;
			break;
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
			motion.defbox1.up=-34;
			motion.defbox1.down=54;
			motion.defbox1.left=-40;
			motion.defbox1.right=40;
			break;
		case 18:
			break;
		case 19:
		case 20:
			motion.defbox1.up=-52;
			motion.defbox1.down=54;
			motion.defbox1.left=-17;
			motion.defbox1.right=20;
			break;
		case 21:
		case 22:
			motion.defbox1.up=-43;
			motion.defbox1.down=54;
			motion.defbox1.left=-17;
			motion.defbox1.right=20;
			break;
		case 23:
			motion.defbox1.up+=10;
			motion.defbox1.left-=10;
			break;
		case 24:
		case 25:
		case 26:
		case 27:
			motion.defbox1.up=-1;
			break;
		case 29:
			motion.atkbox.up=-15;
			motion.atkbox.left=-15;
			motion.atkbox.down=5;
			motion.atkbox.right=5;
			motion.hitcountup=true;
			motion.dmg=15;
			motion.downhit=false;
			motion.freeze=0;
			break;
		case 30:
			motion.defbox1.up=-48;
			motion.defbox1.down=54;
			motion.defbox1.left=-15;
			motion.defbox1.right=35;
			motion.atkbox.up=-23;
			motion.atkbox.left=25;
			motion.atkbox.down=-3;
			motion.atkbox.right=65;
			motion.hitcountup=true;
			break;
		case 31:
			motion.defbox1.up=-50;
			motion.defbox1.down=54;
			motion.defbox1.left=-15;
			motion.defbox1.right=37;
			motion.atkbox.up=-29;
			motion.atkbox.left=25;
			motion.atkbox.down=-3;
			motion.atkbox.right=65;
			motion.hitcountup=true;
			break;
		case 32:
			motion.defbox1.up=-50;
			motion.defbox1.down=54;
			motion.defbox1.left=-15;
			motion.defbox1.right=37;
			motion.atkbox.up=-29;
			motion.atkbox.left=25;
			motion.atkbox.down=-3;
			motion.atkbox.right=65;
			motion.hitcountup=true;
			break;
		case 33:
		case 34:
			motion.defbox1.up=-50;
			motion.defbox1.down=54;
			motion.defbox1.left=-15;
			motion.defbox1.right=26;
			break;
		case 35:
			motion.defbox1.up=-44;
			motion.defbox1.down=54;
			motion.defbox1.left=-15;
			motion.defbox1.right=26;
			motion.atkbox.up=-33;
			motion.atkbox.left=17;
			motion.atkbox.down=-7;
			motion.atkbox.right=57;
			motion.hitcountup=true;
			motion.dmg=20;
			motion.downhit=true;
			motion.freeze=0;
			break;
		case 36:
		case 37:
		case 38:
			motion.defbox1.up=-44;
			motion.defbox1.down=54;
			motion.defbox1.left=-15;
			motion.defbox1.right=26;
			motion.atkbox.up=-33;
			motion.atkbox.left=17;
			motion.atkbox.down=-7;
			motion.atkbox.right=57;
			motion.hitcountup=true;
			break;
		case 39:
			motion.defbox1.up=-48;
			motion.defbox1.down=54;
			motion.defbox1.left=-29;
			motion.defbox1.right=2;
			break;
		case 40:
		case 46:
			motion.defbox1.up=-48;
			motion.defbox1.down=54;
			motion.defbox1.left=-27;
			motion.defbox1.right=24;
			break;
		case 43:
		case 44:
			motion.defbox1.up=300;
			motion.defbox1.down=301;
			motion.defbox1.left=0;
			motion.defbox1.right=1;
			motion.atkbox.up=-100;
			motion.atkbox.left=-100;
			motion.atkbox.down=78;
			motion.atkbox.right=100;
			motion.hitcountup=true;
			motion.dmg=4;
			motion.downhit=false;
			motion.freeze=0;
			break;
		case 42:
			motion.defbox1.up=-40;
			motion.defbox1.down=54;
			motion.defbox1.left=-27;
			motion.defbox1.right=29;
			break;
		case 45:
			motion.defbox1.up=-40;
			motion.defbox1.down=54;
			motion.defbox1.left=-27;
			motion.defbox1.right=29;
			motion.atkbox.up=-100;
			motion.atkbox.left=-100;
			motion.atkbox.down=78;
			motion.atkbox.right=100;
			motion.hitcountup=true;
			motion.dmg=4;
			motion.downhit=true;
			motion.freeze=0;
			break;
		case 41:
		case 48:
		case 49:
		case 50:
		case 51:
			motion.defbox1.up=-40;
			motion.defbox1.down=54;
			motion.defbox1.left=-27;
			motion.defbox1.right=29;
			break;
		case 47:
		case 52:
		case 53:
			motion.defbox1.up=-44;
			motion.defbox1.down=54;
			motion.defbox1.left=-27;
			motion.defbox1.right=22;
			break;
		case 54:

			motion.defbox1.up=-50;
			motion.defbox1.down=54;
			motion.defbox1.left=-29;
			motion.defbox1.right=6;
			break;
		case 55:
			motion.defbox1.up=-46;
			motion.defbox1.down=54;
			motion.defbox1.left=-23;
			motion.defbox1.right=12;
			break;
		case 56:
			motion.defbox1.up=-36;
			motion.defbox1.down=54;
			motion.defbox1.left=-45;
			motion.defbox1.right=12;
			break;
		case 57:
			motion.defbox1.up=-36;
			motion.defbox1.down=54;
			motion.defbox1.left=-35;
			motion.defbox1.right=20;
			motion.atkbox.up=-7;
			motion.atkbox.left=-20;
			motion.atkbox.down=5;
			motion.atkbox.right=10;
			motion.hitcountup=true;
			motion.dmg=20;
			motion.downhit=true;
			motion.freeze=0;
			break;
		case 58:
		case 59:
		case 60:
		case 61:
			motion.defbox1.up=-44;
			motion.defbox1.down=54;
			motion.defbox1.left=-15;
			motion.defbox1.right=20;
			motion.atkbox.up=-62;
			motion.atkbox.left=10;
			motion.atkbox.down=-7;
			motion.atkbox.right=32;
			motion.downhit=true;
			motion.hitcountup=true;
			break;
		case 62:
			motion.defbox1.up=-30;
			motion.defbox1.down=54;
			motion.defbox1.left=-27;
			motion.defbox1.right=28;
			motion.atkbox.up=-30;
			motion.atkbox.left=-20;
			motion.atkbox.down=54;
			motion.atkbox.right=130;
			motion.hitcountup=false;
			motion.dmg=0;
			motion.downhit=false;
			motion.freeze=35;
			break;
		case 63:
			motion.defbox1.up=-36;
			motion.defbox1.down=54;
			motion.defbox1.left=-22;
			motion.defbox1.right=28;
			break;
		case 64:
			motion.defbox1.up=-40;
			motion.defbox1.down=54;
			motion.defbox1.left=-16;
			motion.defbox1.right=28;
			break;
		case 65:
			motion.defbox1.up=-40;
			motion.defbox1.down=54;
			motion.defbox1.left=-16;
			motion.defbox1.right=28;
			break;
		case 66:
			motion.defbox1.up=-40;
			motion.defbox1.down=54;
			motion.defbox1.left=-20;
			motion.defbox1.right=24;
			break;
		case 67:
			motion.defbox1.up=-40;
			motion.defbox1.down=54;
			motion.defbox1.left=-22;
			motion.defbox1.right=16;
			break;
		case 68:
			motion.defbox1.up=-40;
			motion.defbox1.down=54;
			motion.defbox1.left=-20;
			motion.defbox1.right=18;
			break;
		case 69:
		case 70:
			motion.defbox1.up=-40;
			motion.defbox1.down=54;
			motion.defbox1.left=-35;
			motion.defbox1.right=2;
			motion.atkbox.up=-40;
			motion.atkbox.left=0;
			motion.atkbox.down=20;
			motion.atkbox.right=65;
			motion.hitcountup=true;
			motion.dmg=2;
			motion.downhit=false;
			motion.freeze=10;
			break;
		case 71:
			motion.defbox1.up=-32;
			motion.defbox1.down=54;
			motion.defbox1.left=-40;
			motion.defbox1.right=2;
			break;
		case 72:

			motion.defbox1.up=-32;
			motion.defbox1.down=54;
			motion.defbox1.left=-30;
			motion.defbox1.right=22;
			motion.atkbox.up=10;
			motion.atkbox.left=0;
			motion.atkbox.down=25;
			motion.atkbox.right=37;
			motion.hitcountup=true;
			motion.dmg=4;
			motion.downhit=true;
			motion.freeze=0;
			break;
		case 73:
		case 74:
		case 75:
		case 76:
			motion.defbox1.up=-32;
			motion.defbox1.down=54;
			motion.defbox1.left=-30;
			motion.defbox1.right=22;
			motion.atkbox.up=10;
			motion.atkbox.left=0;
			motion.atkbox.down=25;
			motion.atkbox.right=25;
			motion.downhit=true;
			break;
		case 77:
		case 78:
		case 79:
		case 80:
		case 82:
		case 83:
		case 84:
		case 85:
		case 86:
			motion.defbox1.up=-32;
			motion.defbox1.down=54;
			motion.defbox1.left=-30;
			motion.defbox1.right=22;
			motion.atkbox.up=-15;
			motion.atkbox.left=-20;
			motion.atkbox.down=15;
			motion.atkbox.right=65;
			motion.hitcountup=true;
			motion.dmg=2;
			motion.downhit=false;
			motion.freeze=0;
			break;

		case 81:
		case 87:
			motion.defbox1.up=-32;
			motion.defbox1.down=54;
			motion.defbox1.left=-30;
			motion.defbox1.right=22;
			motion.atkbox.up=-15;
			motion.atkbox.left=-20;
			motion.atkbox.down=15;
			motion.atkbox.right=65;
			motion.hitcountup=false;
			motion.dmg=0;
			motion.downhit=false;
			motion.freeze=6;
			break;
		}

		motionlist.push_back(motion);
	}
	motion=motionlist[83];
	motionlist.push_back(motion);
	motion=motionlist[35];
	motion.downhit=false;
	motion.freeze=8;
	motionlist.push_back(motion);
	motion=motionlist[70];
	motion.hitcountup=false;
	motion.dmg=0;
	motionlist.push_back(motion);
	motion=motionlist[80];
	motionlist.push_back(motion);
	motion=motionlist[86];
	motionlist.push_back(motion);
	motion=motionlist[80];
	motionlist.push_back(motion);
	motion=motionlist[86];
	motionlist.push_back(motion);
	motion=motionlist[62];
	motionlist.push_back(motion);
	
	motionlist[95].soundnum=1;
	motionlist[69].soundnum=2;
	motionlist[91].soundnum=3;
	motionlist[92].soundnum=4;
	motionlist[93].soundnum=5;
	motionlist[94].soundnum=6;
	motionlist[72].soundnum=7;
	motionlist[41].soundnum=8;
}
void Char_HyugaNeji::deletememory(){
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
}

void Char_HyugaNeji::eventupdatebeforecollapse(){
	if(ha64time==0){
		if(nowmotionnum==62){
			if(collapse(enemy))
				ha64flag=true;
			ha64time=50;
		}
	}
	else if(ha64time>1){
		ha64time--;
		if(collapse(enemy))
			ha64flag=true;
	}
	else if(ha64time==-1){
		if(ischarlookright){
			if(x>mapright-50){
				x=mapright-50;
			}
			enemy->setx(x+45);
		}
		else{
			if(x<mapleft+50){
				x=mapleft+50;
			}
			enemy->setx(x-45);
		}
	}
}
void Char_HyugaNeji::eventupdateaftercollapse(){
	if((ha64time==1)&&ha64flag){
		ha64time=-1;
		motionnumlist.clear();
		motionnumlist.push_back(63);
		motionnumlist.push_back(64);
		motionnumlist.push_back(65);

		//2장
		motionnumlist.push_back(69);
		//	motionnumlist.push_back(69);
		motionnumlist.push_back(70);
		motionnumlist.push_back(90);
		motionnumlist.push_back(90);
		motionnumlist.push_back(90);
		motionnumlist.push_back(90);
		motionnumlist.push_back(90);
		motionnumlist.push_back(90);
		motionnumlist.push_back(90);
		motionnumlist.push_back(90);
		motionnumlist.push_back(90);
		motionnumlist.push_back(90);
		motionnumlist.push_back(90);
		motionnumlist.push_back(90);
		motionnumlist.push_back(90);
		motionnumlist.push_back(90);
		motionnumlist.push_back(90);


		//4장
		motionnumlist.push_back(77);
		//	motionnumlist.push_back(77);
		motionnumlist.push_back(91);
		motionnumlist.push_back(81);
		motionnumlist.push_back(81);
		motionnumlist.push_back(81);
		motionnumlist.push_back(81);
		motionnumlist.push_back(81);
		motionnumlist.push_back(81);
		motionnumlist.push_back(81);
		motionnumlist.push_back(81);
		motionnumlist.push_back(81);
		motionnumlist.push_back(81);


		motionnumlist.push_back(66);
		motionnumlist.push_back(67);
		motionnumlist.push_back(68);

		//8장
		motionnumlist.push_back(88);
		//	motionnumlist.push_back(83);
		//	motionnumlist.push_back(83);
		motionnumlist.push_back(84);
		motionnumlist.push_back(85);
		motionnumlist.push_back(92);
		motionnumlist.push_back(87);
		motionnumlist.push_back(87);
		motionnumlist.push_back(87);
		motionnumlist.push_back(87);
		motionnumlist.push_back(87);
		motionnumlist.push_back(87);
		motionnumlist.push_back(87);
		motionnumlist.push_back(87);
		motionnumlist.push_back(87);
		motionnumlist.push_back(87);



		motionnumlist.push_back(63);
		motionnumlist.push_back(64);
		motionnumlist.push_back(65);


		//16장
		motionnumlist.push_back(77);
		//	motionnumlist.push_back(77);
		motionnumlist.push_back(78);
		motionnumlist.push_back(79);
		motionnumlist.push_back(80);
		motionnumlist.push_back(82);
		motionnumlist.push_back(78);
		motionnumlist.push_back(79);
		motionnumlist.push_back(93);
		motionnumlist.push_back(81);
		motionnumlist.push_back(81);
		motionnumlist.push_back(81);
		motionnumlist.push_back(81);
		motionnumlist.push_back(81);
		motionnumlist.push_back(81);
		motionnumlist.push_back(81);
		motionnumlist.push_back(81);
		motionnumlist.push_back(81);
		motionnumlist.push_back(81);

		motionnumlist.push_back(66);
		motionnumlist.push_back(67);
		motionnumlist.push_back(68);


		//32장
		motionnumlist.push_back(88);
		//	motionnumlist.push_back(83);
		//	motionnumlist.push_back(83);
		motionnumlist.push_back(84);
		motionnumlist.push_back(85);
		motionnumlist.push_back(86);
		motionnumlist.push_back(83);
		motionnumlist.push_back(84);
		motionnumlist.push_back(85);
		motionnumlist.push_back(86);
		motionnumlist.push_back(83);
		motionnumlist.push_back(84);
		motionnumlist.push_back(85);
		motionnumlist.push_back(94);
		motionnumlist.push_back(83);
		motionnumlist.push_back(84);
		motionnumlist.push_back(85);
		motionnumlist.push_back(86);
		motionnumlist.push_back(87);
		motionnumlist.push_back(87);
		motionnumlist.push_back(87);
		motionnumlist.push_back(87);
		motionnumlist.push_back(87);
		motionnumlist.push_back(87);
		motionnumlist.push_back(87);
		motionnumlist.push_back(87);
		motionnumlist.push_back(87);
		motionnumlist.push_back(87);




		motionnumlist.push_back(63);
		motionnumlist.push_back(64);
		motionnumlist.push_back(65);

		//64장
		motionnumlist.push_back(77);
		//	motionnumlist.push_back(77);
		motionnumlist.push_back(78);
		motionnumlist.push_back(79);
		motionnumlist.push_back(80);
		motionnumlist.push_back(82);
		motionnumlist.push_back(78);
		motionnumlist.push_back(79);
		motionnumlist.push_back(80);
		motionnumlist.push_back(82);
		motionnumlist.push_back(78);
		motionnumlist.push_back(79);
		motionnumlist.push_back(80);
		motionnumlist.push_back(82);
		motionnumlist.push_back(78);
		motionnumlist.push_back(79);
		motionnumlist.push_back(80);
		motionnumlist.push_back(82);
		motionnumlist.push_back(78);
		motionnumlist.push_back(79);
		motionnumlist.push_back(80);
		motionnumlist.push_back(82);
		motionnumlist.push_back(78);
		motionnumlist.push_back(79);
		motionnumlist.push_back(80);
		motionnumlist.push_back(82);
		motionnumlist.push_back(78);
		motionnumlist.push_back(79);
		motionnumlist.push_back(80);
		motionnumlist.push_back(82);
		motionnumlist.push_back(78);
		motionnumlist.push_back(79);

		motionnumlist.push_back(71);
		//	motionnumlist.push_back(71);
		motionnumlist.push_back(72);
		motionnumlist.push_back(73);
		motionnumlist.push_back(74);
		motionnumlist.push_back(75);
		motionnumlist.push_back(76);

		motionnumlist.push_back(76);
		motionnumlist.push_back(76);
		motionnumlist.push_back(76);
		motionnumlist.push_back(76);
		motionnumlist.push_back(76);
		motionnumlist.push_back(76);
		motionnumlist.push_back(76);
		motionnumlist.push_back(76);
	}
	switch(nowmotionnum){
	case 55:
	case 56:
	case 57:
	case 64:
	case 65:
	case 69:
	case 77:
		ischarlookright?x+=20:x-=20;
		break;
	case 71:
		ischarlookright?x+=30:x-=30;
		break;
	case 88:
		ischarlookright?x+=60:x-=60;
		break;
	}
}

void Char_HyugaNeji::setidle(){
	if(status!=ATTACK){
		ha64time=0;
		ha64flag=false;
	}
	if(!isjump&&!islost){
		switch(status){
		case MOVEFRONT:
			if(motionnumlist.size()==0){
				for(int i=6;i<12;i++){
					motionnumlist.push_back(i);
					motionnumlist.push_back(i);
					motionnumlist.push_back(i);
				}
			}
			break;
		case MOVEBACK:
			if(motionnumlist.size()==0){
				for(int i=11;i>=6;i--){
					motionnumlist.push_back(i);
					motionnumlist.push_back(i);
					motionnumlist.push_back(i);
				}
			}
			break;
		case DASH:
			if(motionnumlist.size()==0){
				for(int i=12;i<18;i++){
					motionnumlist.push_back(i);
					motionnumlist.push_back(i);
				}
			}
			break;
		case DOWN:
			if((motionnumlist.size()==0)&&(freezetime==0)){
				motionnumlist.push_back(0);
				motionnumlist.push_back(0);
				motionnumlist.push_back(0);
				motionnumlist.push_back(1);
				motionnumlist.push_back(1);
				motionnumlist.push_back(1);
				motionnumlist.push_back(2);
				motionnumlist.push_back(2);
				motionnumlist.push_back(2);
				motionnumlist.push_back(3);
				motionnumlist.push_back(3);
				motionnumlist.push_back(3);
				motionnumlist.push_back(4);
				motionnumlist.push_back(4);
				motionnumlist.push_back(4);
				motionnumlist.push_back(5);
				motionnumlist.push_back(5);
				motionnumlist.push_back(5);
				status=IDLE;
				nextdmg=-1;
				hitcount=0;
			}
			break;
		default:
			if(motionnumlist.size()==0){
				motionnumlist.push_back(0);
				motionnumlist.push_back(0);
				motionnumlist.push_back(0);
				motionnumlist.push_back(1);
				motionnumlist.push_back(1);
				motionnumlist.push_back(1);
				motionnumlist.push_back(2);
				motionnumlist.push_back(2);
				motionnumlist.push_back(2);
				motionnumlist.push_back(3);
				motionnumlist.push_back(3);
				motionnumlist.push_back(3);
				motionnumlist.push_back(4);
				motionnumlist.push_back(4);
				motionnumlist.push_back(4);
				motionnumlist.push_back(5);
				motionnumlist.push_back(5);
				motionnumlist.push_back(5);
				status=IDLE;
				nextdmg=-1;
				hitcount=0;
			}
		}
	}
}

void Char_HyugaNeji::jump(){
	isjump=true;
	vy=18;
	keyboard->keylistclear(0);
	motionnumlist.clear();
	for(int i=19;i<23;i++){
		motionnumlist.push_back(i);
		motionnumlist.push_back(i);
	}
}

void Char_HyugaNeji::hit(){
	ha64time=0;
	if(nowhp>0){
		status=HIT;
		vy=0;
		nowmotionnum=23;
		motionnumlist.clear();
		motionnumlist.push_back(23);
		motionnumlist.push_back(23);
		motionnumlist.push_back(23);
		motionnumlist.push_back(23);
		motionnumlist.push_back(23);
		nextmotion();
	}
	else
		down();
}
void Char_HyugaNeji::down(){
	ha64time=0;
	status=DOWN;
	freezetime=20;
	motionnumlist.clear();
	motionnumlist.push_back(23);
	motionnumlist.push_back(23);
	motionnumlist.push_back(24);
	motionnumlist.push_back(24);
	motionnumlist.push_back(25);
	motionnumlist.push_back(25);
	motionnumlist.push_back(26);
	motionnumlist.push_back(26);
	motionnumlist.push_back(27);
	motionnumlist.push_back(27);
	nextmotion();
	vy=15;
	if(nowhp<=0){
		islost=true;
			soundlist[0]->play(true, false);
	}
}
void Char_HyugaNeji::BH_5(bool a, bool b){
	if(!isjump){
		if(a){
			if(status!=ATTACK){
				motionnumlist.clear();
				motionnumlist.push_back(28);
				motionnumlist.push_back(29);
				motionnumlist.push_back(30);
				motionnumlist.push_back(31);
				motionnumlist.push_back(31);
				motionnumlist.push_back(32);
				motionnumlist.push_back(32);
				status=ATTACK;
			}
		}
		else if(b){
			if(status!=ATTACK){
				motionnumlist.clear();
				motionnumlist.push_back(33);
				motionnumlist.push_back(34);
				motionnumlist.push_back(35);
				motionnumlist.push_back(36);
				motionnumlist.push_back(37);
				motionnumlist.push_back(37);
				motionnumlist.push_back(38);
				motionnumlist.push_back(38);
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
void Char_HyugaNeji::BH_2(bool a, bool b){
	BH_5(a, b);
}
void Char_HyugaNeji::BH_4(bool a, bool b){
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
void Char_HyugaNeji::BH_6(bool a, bool b){
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

void Char_HyugaNeji::BH_8(bool a, bool b){
	if(!isjump){
		status=VJUMP;
		jump();
	}
}
void Char_HyugaNeji::BH_7(bool a, bool b){
	if(!isjump){
		status=LJUMP;
		jump();
	}
}
void Char_HyugaNeji::BH_9(bool a, bool b){
	if(!isjump){
		status=RJUMP;
		jump();
	}
}

void Char_HyugaNeji::BH_236(bool a, bool b){
	if(!isjump&&ischarlookright&&(a||b)){
		if(status!=ATTACK){
			status=ATTACK;
			motionnumlist.clear();
			motionnumlist.push_back(28);
			motionnumlist.push_back(29);
			motionnumlist.push_back(30);
			motionnumlist.push_back(34);
			motionnumlist.push_back(89);
			motionnumlist.push_back(36);
			motionnumlist.push_back(37);
			motionnumlist.push_back(56);
			motionnumlist.push_back(57);
			motionnumlist.push_back(58);
			motionnumlist.push_back(59);
			motionnumlist.push_back(60);
			motionnumlist.push_back(61);
			motionnumlist.push_back(61);
		}
	}
	else
		BH_6(a, b);
}

void Char_HyugaNeji::BH_214(bool a, bool b){
	if(!isjump&&!ischarlookright&&(a||b)){
		if(status!=ATTACK){
			status=ATTACK;
			motionnumlist.clear();
			motionnumlist.push_back(28);
			motionnumlist.push_back(29);
			motionnumlist.push_back(30);
			motionnumlist.push_back(34);
			motionnumlist.push_back(89);
			motionnumlist.push_back(36);
			motionnumlist.push_back(37);
			motionnumlist.push_back(56);
			motionnumlist.push_back(57);
			motionnumlist.push_back(58);
			motionnumlist.push_back(59);
			motionnumlist.push_back(60);
			motionnumlist.push_back(61);
			motionnumlist.push_back(61);
		}
	}
	else
		BH_4(a, b);
}
void Char_HyugaNeji::BH_22(bool a, bool b){BH_2(a, b);}

void Char_HyugaNeji::BH_66(bool a, bool b){
	if(!isjump){
		if(ischarlookright&&!(a||b)){
			if(status!=DASH){
				motionnumlist.clear();
				status=DASH;
			}
		}
		else
			BH_6(a, b);
	}
}

void Char_HyugaNeji::BH_44(bool a, bool b){if(!isjump){
	if(!ischarlookright&&!(a||b)){
		if(status!=DASH){
			motionnumlist.clear();
			status=DASH;
		}
	}
	else
		BH_4(a, b);
}
}

void Char_HyugaNeji::BH_623(bool a, bool b){
	if(!isjump&&ischarlookright&&(a||b)){
		if(status!=ATTACK){
			status=ATTACK;
			motionnumlist.clear();
			motionnumlist.push_back(39);
			motionnumlist.push_back(40);
			motionnumlist.push_back(41);
			motionnumlist.push_back(42);
			motionnumlist.push_back(43);
			motionnumlist.push_back(44);
			motionnumlist.push_back(43);
			motionnumlist.push_back(44);
			motionnumlist.push_back(43);
			motionnumlist.push_back(44);
			motionnumlist.push_back(43);
			motionnumlist.push_back(44);
			motionnumlist.push_back(45);
			motionnumlist.push_back(46);
			motionnumlist.push_back(47);
			motionnumlist.push_back(48);
			motionnumlist.push_back(49);
			motionnumlist.push_back(50);
			motionnumlist.push_back(51);
			motionnumlist.push_back(52);
			motionnumlist.push_back(53);
			motionnumlist.push_back(39);
		}
	}
	else
		BH_6(a, b);
}

void Char_HyugaNeji::BH_421(bool a, bool b){
	if(!isjump&&!ischarlookright&&(a||b)){
		if(status!=ATTACK){
			status=ATTACK;
			motionnumlist.clear();
			motionnumlist.push_back(39);
			motionnumlist.push_back(40);
			motionnumlist.push_back(41);
			motionnumlist.push_back(42);
			motionnumlist.push_back(43);
			motionnumlist.push_back(44);
			motionnumlist.push_back(43);
			motionnumlist.push_back(44);
			motionnumlist.push_back(43);
			motionnumlist.push_back(44);
			motionnumlist.push_back(43);
			motionnumlist.push_back(44);
			motionnumlist.push_back(45);
			motionnumlist.push_back(46);
			motionnumlist.push_back(47);
			motionnumlist.push_back(48);
			motionnumlist.push_back(49);
			motionnumlist.push_back(50);
			motionnumlist.push_back(51);
			motionnumlist.push_back(52);
			motionnumlist.push_back(53);
			motionnumlist.push_back(39);
		}
	}
	else
		BH_4(a, b);
}

void Char_HyugaNeji::BH_41236(bool a, bool b){BH_236(a, b);}
void Char_HyugaNeji::BH_63214(bool a, bool b){BH_214(a, b);}
void Char_HyugaNeji::BH_236236(bool a, bool b){

	BH_236(a, b);
}
void Char_HyugaNeji::BH_214214(bool a, bool b){BH_214(a, b);}
void Char_HyugaNeji::BH_2141236(bool a, bool b){
	if(!isjump&&ischarlookright&&(a||b)){
		if(status!=ATTACK){
			setcutin();
			status=ATTACK;
			motionnumlist.clear();
				motionnumlist.push_back(95);
			for(int i=0;i<50;i++)
				motionnumlist.push_back(62);
			nextmotion();
		}
	}
	else
		BH_6(a, b);
}
void Char_HyugaNeji::BH_2363214(bool a, bool b){
	if(!isjump&&!ischarlookright&&(a||b)){
		if(status!=ATTACK){
			setcutin();
			status=ATTACK;
			motionnumlist.clear();
				motionnumlist.push_back(95);
			for(int i=0;i<50;i++)
				motionnumlist.push_back(62);
			nextmotion();
		}
	}
	else
		BH_4(a, b);
}
void Char_HyugaNeji::BH_641236(bool a, bool b){BH_236(a, b);}
void Char_HyugaNeji::BH_463214(bool a, bool b){BH_214(a, b);}
void Char_HyugaNeji::BH_4123641236(bool a, bool b){BH_236(a, b);}
void Char_HyugaNeji::BH_6321463214(bool a, bool b){BH_214(a, b);}