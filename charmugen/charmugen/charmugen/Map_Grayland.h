#pragma once
#include "gamemap.h"
#include "M_Image.h"
class Map_Grayland :
	public Gamemap
{
private:

public:
	Map_Grayland(LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3d_dev, AudioDevicePtr _aud_dev);
	~Map_Grayland(void);
	void initialize();
	void deletememory();
	void start();
	void end();
	void update();
	void draw(bool drawbox);
	void drawsys();
};

