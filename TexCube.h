#ifndef __TEXCUBE_H__
#define __TEXCUBE_H__
#include"Cube.h"

// 纹理相关设置
enum CubeTex {
	Wood,
	Water,
	Soil,
	Stone,
	RedStone,
	Dirt,
	Brick,
	Table,
	Diamond,
	Tnt,
	Tree,
	Leaf,
	Bookshelf,
	RedSand,
	Sand
};
class TexCube : public Cube
{
public:
	TexCube(float, float, float, float, CubeTex);
	TexCube() {};
	void createCube();
	~TexCube();
private:
	GLuint _top;
	GLuint _bot;
	GLuint _side;
};

#endif