#pragma once
#include <d3d9.h>
#include <d3dx9.h>
class M_Image
{private:
	LPD3DXSPRITE sprite;
	LPDIRECT3DTEXTURE9 texture;
	float width;
	float height;

public:
	M_Image(LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3d_dev, wchar_t* name, DWORD colorkey);
	~M_Image(void);
	void draw(float x, float y, int color, bool center, bool reverse);
	void draw(float x, float y, float size, int color, bool center, bool reverse);
	void draw(float x, float y, float xsize, float ysize, int color, bool center, bool reverse);
};

