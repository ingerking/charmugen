#pragma once
#include <d3d9.h>
#include <d3dx9.h>

class M_Font
{
	
private:
	LPD3DXSPRITE FontSprite;
	ID3DXFont* Font;

public:
	M_Font(LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3d_dev, int width, int height, int weight, wchar_t* style, bool italic);
	~M_Font(void);
	void draw(int left, int right, int up, int down, int color, wchar_t* message, bool isleft);
	void draw(int left, int right, int up, int down, int color, wchar_t* message, bool isleft, bool center);
};

