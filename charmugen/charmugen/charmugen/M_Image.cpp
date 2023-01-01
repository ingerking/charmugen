#include "M_Image.h"


M_Image::M_Image(LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3d_dev, wchar_t* name, DWORD colorkey)
{
	D3DXIMAGE_INFO info;

	sprite=NULL;
	texture=NULL;

	D3DXCreateSprite(d3d_dev, &sprite);
	D3DXGetImageInfoFromFile(name, &info);
	D3DXCreateTextureFromFileEx(d3d_dev, name, info.Width, info.Height, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, colorkey, NULL, NULL, &texture);

	width=0.0f-(float)info.Width/2.0f;
	height=0.0f-(float)info.Height/2.0f;
}


M_Image::~M_Image(void)
{
	if(sprite!=NULL)
		sprite->Release();
	if(texture!=NULL)
		texture->Release();
}

void M_Image::draw(float x, float y, int color, bool center, bool reverse){
	D3DXVECTOR3 vec(0.0f, 0.0f, 0.0f);
	D3DXMATRIX centermatr;
	D3DXMATRIX sizematr;
	D3DXMATRIX matrt;
	D3DXMATRIX matrs;
	D3DXMatrixTranslation(&matrt, x, y, 0.0f);
	D3DXMatrixScaling(&matrs, reverse?-1.0f:1.0f, 1.0f, 1.0f);

	if(center){
		D3DXMatrixTranslation(&centermatr, width, height, 0.0f);
		D3DXMatrixMultiply(&matrs, &centermatr, &matrs);
	}

	D3DXMatrixMultiply(&matrt, &matrs, &matrt);

	sprite->SetTransform(&matrt);
	
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, NULL, NULL, &vec, color);
	sprite->End();
}

void M_Image::draw(float x, float y, float size, int color, bool center, bool reverse){
	D3DXVECTOR3 vec(0.0f, 0.0f, 0.0f);
	D3DXMATRIX centermatr;
	D3DXMATRIX sizematr;
	D3DXMATRIX matrt;
	D3DXMATRIX matrs;
	D3DXMatrixTranslation(&matrt, x, y, 0.0f);
	D3DXMatrixScaling(&matrs, reverse?-size:size, 1.0f, 1.0f);

	if(center){
		D3DXMatrixTranslation(&centermatr, width, height, 0.0f);
		D3DXMatrixMultiply(&matrs, &centermatr, &matrs);
	}

	D3DXMatrixMultiply(&matrt, &matrs, &matrt);

	sprite->SetTransform(&matrt);
	
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, NULL, NULL, &vec, color);
	sprite->End();
}

void M_Image::draw(float x, float y, float xsize, float ysize, int color, bool center, bool reverse){
	D3DXVECTOR3 vec(0.0f, 0.0f, 0.0f);
	D3DXMATRIX centermatr;
	D3DXMATRIX sizematr;
	D3DXMATRIX matrt;
	D3DXMATRIX matrs;
	D3DXMatrixTranslation(&matrt, x, y, 0.0f);
	D3DXMatrixScaling(&matrs, reverse?-xsize:xsize, ysize, 1.0f);

	if(center){
		D3DXMatrixTranslation(&centermatr, width, height, 0.0f);
		D3DXMatrixMultiply(&matrs, &centermatr, &matrs);
	}

	D3DXMatrixMultiply(&matrt, &matrs, &matrt);

	sprite->SetTransform(&matrt);
	
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, NULL, NULL, &vec, color);
	sprite->End();
}