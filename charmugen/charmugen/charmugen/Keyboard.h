#pragma once
#include <Windows.h>
#include <list>
#include "enumstruct.h"

#define KEY_LEFT 0x01
#define KEY_RIGHT 0x02
#define KEY_UP 0x04
#define KEY_DOWN 0x08
#define KEY_A 0x10
#define KEY_B 0x20

using namespace std;
class Keyboard
{
private:
	int leftkey;
	int rightkey;
	int upkey;
	int downkey;
	int akey;
	int bkey;
	list<int> keylist;
	int key;
	int lastkey;
	bool akeypush;
	bool bkeypush;
public:
	Keyboard(int left, int right, int up, int down, int a, int b);
	~Keyboard(void);
	void getkey();
	int getkeycombination();
	void keylistclear(int num);
	KEYPAD getkeystate(bool getonekey);
	bool getakey(){return akeypush;}
	bool getbkey(){return bkeypush;}
	int getlastkey();
};

