#include "Cube.h"
Cube::Cube(float x, float y, float z, float size, GLuint top, GLuint bot, GLuint side)
	:_x(x), _y(y), _z(z), _size(size), _top(top), _bot(bot), _side(side)
{
}

Cube::~Cube()
{
}
// ���һ�������Ƿ�Ϊ2�������η�������ǣ�����1�����򷵻�0
int Cube::power_of_two(int n)
{
	if (n <= 0)
		return 0;
	return ((n & (n - 1)) == 0);
}
//��ȡһ��BMP�ļ���Ϊ����
GLuint Cube::load_texture(const char* file_name)
{

}
void Cube::createCube() 
{
}
//��ʼ������
void Cube::initCubeTexture()
{
}
GLuint Cube::texRedStone = 0;
GLuint Cube::texGrass = 0;
GLuint Cube::texSoil = 0;
GLuint Cube::texStone = 0;
GLuint Cube::texWater = 0;
GLuint Cube::texWood = 0;
GLuint Cube::texDirt = 0;
GLuint Cube::texBrick = 0;
GLuint Cube::texTabletop = 0;
GLuint Cube::texTableside = 0;
GLuint Cube::texDiamond = 0;
GLuint Cube::texTnttop = 0;
GLuint Cube::texTntside = 0;
GLuint Cube::texTreetop = 0;
GLuint Cube::texTreeside = 0;
GLuint Cube::texLeaf = 0;
GLuint Cube::texBookshelf = 0;
GLuint Cube::texRedSand = 0;
GLuint Cube::texSand = 0;
