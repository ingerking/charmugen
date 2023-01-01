#include "M_Font.h"


M_Font::M_Font(LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3d_dev, int width, int height, int weight, wchar_t* style, bool italic)
{
	D3DXFONT_DESC fontDesc;	//��Ʈ�� ������ ���� ����ü�� �ϴ� �����Ѵ�.

	ZeroMemory(&fontDesc, sizeof(fontDesc)); //��Ʈ�� ����ü�� �ʱ�ȭ��Ŵ
	fontDesc.Height = height; //��Ʈ�� ����(��ü�� �ʺ��� 2������ ������)
	fontDesc.Width = width; //��Ʈ�� �ʺ�
	fontDesc.Weight = weight; //��Ʈ�� ���� (0(����)~ 1000(����)�� ���� ����)
	fontDesc.Italic = italic; //���Ÿ�?
	fontDesc.CharSet = DEFAULT_CHARSET; //����Ʈ�� �����ϱ�
	wcscpy_s(fontDesc.FaceName, style); // �۲� ��Ÿ��

	D3DXCreateFontIndirect(d3d_dev, &fontDesc, &Font); //��Ʈ�� �����.
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