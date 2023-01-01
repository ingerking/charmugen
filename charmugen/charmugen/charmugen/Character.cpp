#include "Character.h"
Character::Character(LPDIRECT3D9 _d3d, LPDIRECT3DDEVICE9 _d3d_dev, AudioDevicePtr _aud_dev){
	d3d=_d3d;
	d3d_dev=_d3d_dev;
	aud_dev=_aud_dev;
	leftright=true;
}

void Character::charinit(Character* _enemy, Keyboard* _keyboard, int _mapleft, int _mapright){
	enemy=_enemy;
	mapleft=_mapleft;
	mapright=_mapright;
	keyboard=_keyboard;
	nowmotionnum=0;
	isjump=false;
	ischarlookright=false;
	hitcountup=false;
	nexthitdown=false;
	guardignore=false;
	islost=false;
	hitsoundnum=-1;
	nextdmg=-1;
	nextfreeze=0;
	freezetime=0;
	hitcount=0;
	hitsoundnum=-1;
	status=IDLE;
	y=0;
	keyboard->keylistclear(0);

	initialize();
}

Motion Character::getmotion(){
	Collapsebox a, b, c;
	int i=YDIST;
	Motion retmotion=motionlist[nowmotionnum];
	a=retmotion.atkbox;
	b=retmotion.defbox1;
	c=retmotion.defbox2;
	int ic, id;

	if(a.up!=-1){
		a.up+=i;
		a.down+=i;
		ic=ischarlookright?x+a.left:x-a.right-1;
		id=ischarlookright?x+a.right:x-a.left-1;
		a.left=ic;
		a.right=id;
	}
	if(b.up!=-1){
		b.up+=i;
		b.down+=i;
		ic=ischarlookright?x+b.left:x-b.right-1;
		id=ischarlookright?x+b.right:x-b.left-1;
		b.left=ic;
		b.right=id;
	}
	if(c.up!=-1){
		c.up+=i;
		c.down+=i;
		ic=ischarlookright?x+c.left:x-c.right-1;
		id=ischarlookright?x+c.right:x-c.left-1;
		c.left=ic;
		c.right=id;
	}

	retmotion.atkbox=a;
	retmotion.defbox1=b;
	retmotion.defbox2=c;
	return retmotion;
}

void Character::setdamage(int damage, int freezetime, bool hitcountup, bool isdown){
	nowhp-=damage;
	if(nowhp<0)
		nowhp=0;
	if(freezetime!=-1)
		this->freezetime=freezetime;
	if(hitcountup)
		this->hitcount++;
	if(isdown)
		down();
	else
		hit();
}

void Character::update(){
	if(cutintime>0)
		cutintime--;
	if(prevhp>nowhp){
		if(prevhp>nowhp+4){
			prevhp-=(prevhp-nowhp)>>2;
		}
		else
			prevhp--;
		if(prevhp<nowhp)
			prevhp=nowhp;
	}
}

void Character::setleftright(Character* enemy){
	if(leftright&&!islost){
		if(status==IDLE||status==MOVEFRONT||status==MOVEBACK){
			if(enemy->getx()>x){
				ischarlookright=true;
			}
			else
				ischarlookright=false;
		}
	}
}

void Character::setbehavior(){
	if(islost)
		return;

	KEYPAD key=keyboard->getkeystate(false);
	bool a=keyboard->getakey();
	bool b=keyboard->getbkey();
	if(a||b)
		keyboard->keylistclear(1);

	if(freezetime>0)
		return;
	switch(status){
	case VJUMP:
	case RJUMP:
	case LJUMP:
	case IDLE:
	case DASH:
	case MOVEFRONT:
	case GUARD:
	case MOVEBACK:
	case SIT:
		switch(key){
		case KP_5:
			BH_5(a, b);
			break;
		case KP_2:
			BH_2(a, b);
			break;
		case KP_4:
			BH_4(a, b);
			break;
		case KP_6:
			BH_6(a, b);
			break;
		case KP_8:
			BH_8(a, b);
			break;
		case KP_7:
			BH_7(a, b);
			break;
		case KP_9:
			BH_9(a, b);
			break;
		case KP_236:
			BH_236(a, b);
			break;
		case KP_214:
			BH_214(a, b);
			break;
		case KP_22:
			BH_22(a, b);
			break;
		case KP_66:
			BH_66(a, b);
			break;
		case KP_44:
			BH_44(a, b);
			break;
		case KP_623:
			BH_623(a, b);
			break;
		case KP_421:
			BH_421(a, b);
			break;
		case KP_41236:
			BH_41236(a, b);
			break;
		case KP_63214:
			BH_63214(a, b);
			break;
		case KP_236236:
			BH_236236(a, b);
			break;
		case KP_214214:
			BH_214214(a, b);
			break;
		case KP_2141236:
			BH_2141236(a, b);
			break;
		case KP_2363214:
			BH_2363214(a, b);
			break;
		case KP_641236:
			BH_641236(a, b);
			break;
		case KP_463214:
			BH_463214(a, b);
			break;
		case KP_4123641236:
			BH_4123641236(a, b);
			break;
		case KP_6321463214:
			BH_6321463214(a, b);
			break;
		default:
			;
		}
		break;
	default:
		;
	}
}

void Character::move(){
	switch(status){
	case MOVEFRONT:
		ischarlookright?x+=2:x-=2;
		break;
	case MOVEBACK:
		ischarlookright?x-=2:x+=2;
		break;
	case DASH:
		ischarlookright?x+=4:x-=4;
		break;
	case RJUMP:
		y+=vy;
		vy--;
		x+=2;
		if(y<0){
			y=0;
			status=IDLE;
			vy=0;
			isjump=false;
			motionnumlist.clear();
			setidle();
			nextmotion();
		}
		break;
	case LJUMP:
		y+=vy;
		vy--;
		x-=2;
		if(y<0){
			y=0;
			status=IDLE;
			vy=0;
			isjump=false;
			motionnumlist.clear();
			setidle();
			nextmotion();
		}
		break;
	case VJUMP:
		y+=vy;
		vy--;
		if(y<0){
			y=0;
			status=IDLE;
			vy=0;
			isjump=false;
			motionnumlist.clear();
			setidle();
			nextmotion();
		}
		break;
	case DOWN:
		y+=vy;
		vy--;
		if(y<0){
			y=0;
			isjump=false;
		}
		else
			ischarlookright?x-=2:x+=2;
		break;
	default:
			y+=vy;
			vy--;
			if(y<=0){
				y=0;
				isjump=false;
			}
	}

	if(x<mapleft)
		x=mapleft;
	else if(x>=mapright)
		x=mapright-1;
}

bool Character::collapse(Character* enemy){
	Motion enemymotion=enemy->getmotion();
	Motion mymotion=getmotion();
	bool ret=false;

	if(getnextdmg()!=-1){
		if(iscollapse(&mymotion.atkbox, &enemymotion.defbox1)){
			enemy->setdamage(nextdmg, nextfreeze, hitcountup, nexthitdown);
			nextdmg=-1;
			if(hitsoundnum!=-1){
				soundlist[hitsoundnum]->play(true, false);
				hitsoundnum=-1;
			}
			ret=true;
		}
		else if(iscollapse(&mymotion.atkbox, &enemymotion.defbox2)){
			enemy->setdamage(nextdmg, nextfreeze, hitcountup, nexthitdown);
			nextdmg=-1;
			if(hitsoundnum!=-1){
				soundlist[hitsoundnum]->play(true, false);
				hitsoundnum=-1;
			}
			ret=true;
		}
	}
	return ret;
}

void Character::nextmotion(){
		if(status!=DOWN&&freezetime>0)
			freezetime--;
		else{
			if(status==DOWN&&freezetime>0)
				freezetime--;
			if(motionnumlist.size()!=0){
				Motion motion;
				list<int>::iterator iter=motionnumlist.begin();
				nowmotionnum=*iter;
				motionnumlist.pop_front();
				motion=motionlist[nowmotionnum];
				if(motion.soundnum!=-1)
					soundlist[motion.soundnum]->play(true, false);
				if(motion.dmg!=-1)
					nextdmg=motion.dmg;
				if(motion.freeze!=-1)
					nextfreeze=motion.freeze;
				if(motion.hitsoundnum!=-1)
					hitsoundnum=motion.hitsoundnum;
				hitcountup=motion.hitcountup;
				nexthitdown=motion.downhit;
				guardignore=motion.ignoreguarddmg;
			}
		}
}

void Character::draw(bool drawbox){
	imagelist[motionlist[nowmotionnum].spritenum]->draw(x, YDIST, 0xFFFFFFFF, true, !ischarlookright);
	
	if(drawbox){
		D3DXVECTOR2 p[5];
		ID3DXLine* line;
		Motion motion;
		motion=getmotion();

		D3DXCreateLine(d3d_dev, &line);
		line->SetWidth(1);
		line->SetAntialias(false);
		line->Begin();
		if(motion.atkbox.up!=-1){
			p[0].x=motion.atkbox.left;p[0].y=motion.atkbox.up;
			p[1].x=motion.atkbox.left;p[1].y=motion.atkbox.down;
			p[2].x=motion.atkbox.right;p[2].y=motion.atkbox.down;
			p[3].x=motion.atkbox.right;p[3].y=motion.atkbox.up;
			p[4].x=motion.atkbox.left;p[4].y=motion.atkbox.up;
			line->Draw(p, 5, D3DCOLOR_XRGB(255, 0, 0));
		}
		if(motion.defbox1.up!=-1){
			p[0].x=motion.defbox1.left;p[0].y=motion.defbox1.up;
			p[1].x=motion.defbox1.left;p[1].y=motion.defbox1.down;
			p[2].x=motion.defbox1.right;p[2].y=motion.defbox1.down;
			p[3].x=motion.defbox1.right;p[3].y=motion.defbox1.up;
			p[4].x=motion.defbox1.left;p[4].y=motion.defbox1.up;
			line->Draw(p, 5, D3DCOLOR_XRGB(0, 0, 255));
		}
		if(motion.defbox2.up!=-1){
			p[0].x=motion.defbox2.left;p[0].y=motion.defbox2.up;
			p[1].x=motion.defbox2.left;p[1].y=motion.defbox2.down;
			p[2].x=motion.defbox2.right;p[2].y=motion.defbox2.down;
			p[3].x=motion.defbox2.right;p[3].y=motion.defbox2.up;
			p[4].x=motion.defbox2.left;p[4].y=motion.defbox2.up;
			line->Draw(p, 5, D3DCOLOR_XRGB(0, 0, 255));
		}
		line->End();
		line->Release();
	}
}

void Character::drawface(int x, int y, bool lookright){
	face->draw((float)x, (float)y, 0xFFFFFFFF, false, !lookright);
}
void Character::drawbigface(int x, int y, bool lookright, int color){
	bigface->draw((float)x, (float)y, color, false, !lookright);
}
void Character::drawcutin(){
	if(cutintime>59){
		if(cutinisright)
			cutin->draw(1400-cutintime*20, 300, 0xFFFFFFFF, true, false);
		else
			cutin->draw(cutintime*20-400, 300, 0xFFFFFFFF, true, cutincanchangedist);
	}
	else if(cutintime>29){
		if(cutinisright)
			cutin->draw(200, 300, 0xFFFFFFFF, true, false);
		else
			cutin->draw(800, 300, 0xFFFFFFFF, true, cutincanchangedist);
	}
	else if(cutintime>0){
		if(cutinisright)
			cutin->draw(350-cutintime*5, 300, D3DCOLOR_ARGB(cutintime*8+15, 255, 255, 255), true, false);
		else
			cutin->draw(650+cutintime*5, 300, D3DCOLOR_ARGB(cutintime*8+15, 255, 255, 255), true, cutincanchangedist);
	}
}
void Character::setcutin(){
	cutintime=90;
	cutinisright=ischarlookright;
}