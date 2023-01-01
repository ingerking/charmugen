#include "M_Font.h"


M_Font::M_Font(LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3d_dev, int width, int height, int weight, wchar_t* style, bool italic)
{
	D3DXFONT_DESC fontDesc;	//폰트의 정보를 담을 구조체를 일단 정의한다.

	ZeroMemory(&fontDesc, sizeof(fontDesc)); //폰트의 구조체를 초기화시킴
	fontDesc.Height = height; //폰트의 높이(대체로 너비의 2배쯤이 적당함)
	fontDesc.Width = width; //폰트의 너비
	fontDesc.Weight = weight; //폰트의 굵기 (0(얉음)~ 1000(굵음)의 값을 정함)
	fontDesc.Italic = italic; //이탤릭?
	fontDesc.CharSet = DEFAULT_CHARSET; //디폴트로 선택하기
	wcscpy_s(fontDesc.FaceName, style); // 글꼴 스타일

	D3DXCreateFontIndirect(d3d_dev, &fontDesc, &Font); //폰트를 만든다.
	D3DXCreateSprite(d3d_dev, &FontSprite);
}


M_Font::~M_Font(void)
{
	Font->Release();
	FontSprite->Release();
}

void M_Font::draw(int left, int right, int up, int down, int color, wchar_t* message, bool isleft){
	RECT rc={left, up, right, down};
	FontSprite->Begin(D3DXSPRITE_ALPHABLEND);
	Font->DrawTextW(FontSprite, message, wcslen(message), &rc, (isleft?DT_LEFT:DT_RIGHT) | DT_BOTTOM | DT_WORDBREAK, color);
	FontSprite->End();
}

void M_Font::draw(int left, int right, int up, int down, int color, wchar_t* message, bool isleft, bool center){
	RECT rc={left, up, right, down};
	FontSprite->Begin(D3DXSPRITE_ALPHABLEND);
	Font->DrawTextW(FontSprite, message, wcslen(message), &rc, (isleft?DT_LEFT:DT_RIGHT) | (center?DT_VCENTER:DT_TOP) | DT_WORDBREAK, color);
	FontSprite->End();
}