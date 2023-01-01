#include "Keyboard.h"


Keyboard::Keyboard(int left, int right, int up, int down, int a, int b)
{
	leftkey=left;
	rightkey=right;
	upkey=up;
	downkey=down;
	akey=a;
	bkey=b;
}

Keyboard::~Keyboard(void)
{
}

void Keyboard::getkey(){
	key=0;
	if(GetAsyncKeyState(leftkey)&0x8000){
		key|=KEY_LEFT;
	}
	if(GetAsyncKeyState(rightkey)&0x8000){
		key|=KEY_RIGHT;
	}
	if(GetAsyncKeyState(upkey)&0x8000){
		key|=KEY_UP;
	}
	if(GetAsyncKeyState(downkey)&0x8000){
		key|=KEY_DOWN;
	}
	if(GetAsyncKeyState(akey)&0x8000){
		key|=KEY_A;
	}
	if(GetAsyncKeyState(bkey)&0x8000){
		key|=KEY_B;
	}
}

int Keyboard::getkeycombination(){
	int ret=0;
	int ret2=0;
	int count=6-keylist.size();
	for(list<int>::iterator iter=keylist.begin();iter!=keylist.end();iter++){
		ret<<=2;
		ret2<<=2;
		switch(*iter){
		case KEY_LEFT:
			ret|=1;
			ret2|=1;
			break;
		case KEY_RIGHT:
			ret|=3;
			ret2|=3;
			break;
		case KEY_DOWN:
			ret|=2;
			break;
		case KEY_UP:
			ret|=0;
			ret2|=2;
			break;
		case KEY_UP|KEY_LEFT:
			ret2=6;
			break;
		case KEY_UP|KEY_RIGHT:
			ret2=14;
			break;
		default:
			ret|=0;
			ret2|=0;
		}
	}
	ret2<<=12;
	return (ret&0x0FFF)|ret2;
}

void Keyboard::keylistclear(int num){
	if(num==0)
		keylist.clear();
	else{
		while(keylist.size()>num){
			keylist.pop_front();
		}
	}
}

KEYPAD Keyboard::getkeystate(bool getonekey){
	KEYPAD keypad;
	int lastcurkey=0;
	int curkey=0;
	int combkey;
	int flagab;

	flagab=0;
	lastkey=key;
	getkey();
	lastcurkey=curkey&0x0F;
	curkey=(~lastkey)&key&0x3F;
	if(lastcurkey!=(curkey&0x0F)){
		if((curkey&0x0F)!=0)
			keylist.push_back(curkey&0x0F);
	}
	else if((key&0x0F)==0&&lastkey&0x0F)
		keylist.push_back(0);

	if((~lastkey)&key&KEY_A){
		akeypush=true;
	}
	else{
		akeypush=false;
	}
	if((~lastkey)&key&KEY_B){
		bkeypush=true;
	}
	else{
		bkeypush=false;
	}

	while(keylist.size()>6){
		keylist.pop_front();
	}

	combkey=getkeycombination();
	if(getonekey){
		if((combkey&0x3000)!=0x2000){
			switch(combkey&0x03){//한자리비교
			case 0://0
				keypad=KP_5;
				break;
			case 1://끝 l

				keypad=KP_4;
				break;
			case 2://2
				keypad=KP_2;
				break;
			case 3://끝 r
				keypad=KP_6;
				break;
			}
		}
		else{
			keypad=KP_8;
		}
		keylist.push_back(0);
	}

	else{
		if((combkey&0x3000)!=0x2000){
			switch(combkey&0x03){//한자리비교
			case 0://0
				keypad=KP_5;
				break;
			case 1://끝 l
				if((combkey&0x0C)==0x08){//dl
					switch(combkey&0x30){
					case 0x10://ldl
						if((combkey&0xC0)==0x80)//dldl
							keypad=KP_214214;
						else//ldl
							keypad=KP_421;
						break;
					case 0x30://rdl
						switch(combkey&0xC0){//rdl
						case 0x80://drdl
							keypad=KP_2363214;
							break;
						case 0x40:
							if((combkey&0x0F00)==0x0E00)//rdlrdl
								keypad=KP_6321463214;
							else//lrdl
								keypad=KP_463214;
							break;
						default:
							keypad=KP_63214;
						}
						break;
					default://dl
						keypad=KP_214;
					}
				}
				else//l
					if((combkey&0x3C)==0x10)
						keypad=KP_44;
					else
						keypad=KP_4;
				break;
			case 2://2
				if((combkey&0x3C)==0x20)
					keypad=KP_22;
				else
					keypad=KP_2;
				break;
			case 3://끝 r
				if((combkey&0x0C)==0x08){//dr
					switch(combkey&0x30){
					case 0x10://ldr
						switch(combkey&0xC0){
						case 0x80://dldr
							keypad=KP_2141236;
							break;
						case 0xC0://rldr
							if((combkey&0x0F00)==0x0600)//ldrldr
								keypad=KP_4123641236;
							else//rldr
								keypad=KP_641236;
							break;
						default://ldr
							keypad=KP_41236;
						}
						break;
					case 0x30://rdr
						if((combkey&0xC0)==0x80)//drdr
							keypad=KP_236236;
						else//rdr
							keypad=KP_623;
						break;
					default://dr
						keypad=KP_236;
					}
				}
				else//r
					if((combkey&0x3C)==0x30)
						keypad=KP_66;
					else
						keypad=KP_6;
				break;
			}
		}
		else{
			switch(combkey&0xF000){
			case 0x6000:
				keypad=KP_7;
				break;
			case 0xE000:
				keypad=KP_9;
				break;
			default:
				keypad=KP_8;
			}
		}
	}
	return keypad;
}