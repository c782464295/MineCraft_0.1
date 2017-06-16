#include "Cube.h"
#include <stdio.h>
#include <Windows.h>
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
// ��ȡһ��BMP�ļ���Ϊ����
GLuint Cube::load_texture(const char* file_name)
{
	GLint width, height, total_bytes;  //ͼƬ�߿��ͼƬҪ������ֽ���
	GLubyte *pixels = 0; // ָ��ͼƬ���ݵ�ָ��
	GLuint last_texture_ID = 0, texture_ID = 0;

	// ���ļ������ʧ�ܣ�����
	FILE *pFile = fopen(file_name, "rb");  // rb��ʾ��д
	if (pFile == 0)
		return 0;
	
	// ��ȡ�ļ��е�ͼ��߿�
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);

	// ����ÿ��������ռ���ֽ����������ݴ˼����������ֽ���
	{
		GLint line_bytes = width * 3; // Ϊʲô*3��
		while (line_bytes % 4 != 0) // ʹ���ֽ�����Ϊ4�ı���������洢
			++line_bytes;
		total_bytes = line_bytes * height;
	}
	//�����������ֽڷ����ڴ�
	pixels = (GLubyte*)malloc(total_bytes);
	if (pixels == 0)
	{
		fclose(pFile);
		return 0;
	}
	 
	//��ȡ��������
	if (fread(pixels, total_bytes, 1, pFile) <= 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// �ھɰ汾��OpenGL��
	// ���ͼ��Ŀ�Ⱥ͸߶Ȳ��ǵ������η�������Ҫ��������
	// ���ﲢû�м��OpenGL�汾�����ڶ԰汾�����ԵĿ��ǣ����ɰ汾����
	// ���⣬�����Ǿɰ汾�����°汾��
	// ��ͼ��Ŀ�Ⱥ͸߶ȳ�����ǰOpenGLʵ����֧�ֵ����ֵʱ��ҲҪ��������
	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max); // �õ��������֧�ִ洢��max��
		if (!power_of_two(width)
			|| !power_of_two(height)
			|| width > max
			|| height > max)
		{
			const GLint new_width = 256;
			const GLint new_height = 256; // ���ź�������α߳�
			GLint new_line_bytes, new_total_bytes;
			GLubyte *new_pixels = 0;

			//����ÿ����Ҫ���ֽ��������ֽ���
			new_line_bytes = new_width * 3;
			while (new_line_bytes % 4 != 0)
				++new_line_bytes;
			new_total_bytes = new_line_bytes * new_height;

			// �����ڴ�
			new_pixels = (GLubyte*)malloc(new_total_bytes);
			if (new_pixels == 0)
			{
				free(pixels);
				fclose(pFile);
				return 0;
			}
			// ������������
			gluScaleImage(GL_RGB,
				width, height, GL_UNSIGNED_BYTE, pixels,
				new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

			// �ͷ�ԭ�����������ݣ���pixelsָ���µ��������ݣ�����������width��height
			free(pixels);
			pixels = new_pixels;
			width = new_width;
			height = new_height;
		}
	}
	// ����һ���µ������
	glGenTextures(1, &texture_ID);
	if (texture_ID == 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}
	// �������������������ò�������
	// �ڰ�ǰ���Ȼ��ԭ���󶨵�����ţ��Ա��������лָ�
	GLint lid = last_texture_ID;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &lid);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, last_texture_ID);
	
	
	// ֮ǰΪpixels������ڴ����ʹ��glTexImage2D�Ժ��ͷ�
	// ��Ϊ��ʱ���������Ѿ���OpenGL���б�����һ�ݣ����ܱ����浽ר�ŵ�ͼ��Ӳ���У�
	free(pixels);

	return texture_ID;
}
void Cube::createCube() 
{
	float x = _x;
	float y = _y;
	float z = _z;
	float size = _size;
	
	
	
	//����
	glBindTexture(GL_TEXTURE_2D, _bot);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + size, y, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + size, y, z + size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z + size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();



	//������
	glBindTexture(GL_TEXTURE_2D, _side);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + size, y, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + size, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + size, y + size, z);
	glEnd();


	//���涫
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + size);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + size, y, z + size);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + size, y + size, z + size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + size, z + size);
	glEnd();



	//������
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + size, y, z + size);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + size, y, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + size, y + size, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + size, y + size, z + size);
	glEnd();
	//���汱
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + size);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + size, z + size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + size, z);
	glEnd();

	//����
	glBindTexture(GL_TEXTURE_2D, _top);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y + size, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + size, z + size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + size, y + size, z + size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + size, y + size, z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
}
//��ʼ������
void Cube::initCubeTexture()
{
	texRedStone = Cube::load_texture("img/redStone.bmp");
	texGrass = Cube::load_texture("img/grass.bmp");
	texSoil = Cube::load_texture("img/soil.bmp");
	texStone = Cube::load_texture("img/stone.bmp");
	texWater = Cube::load_texture("img/water.bmp");
	texWood = Cube::load_texture("img/wood.bmp");
	texDirt = Cube::load_texture("img/dirt.bmp");;
	texBrick = Cube::load_texture("img/brick.bmp");
	texTabletop = Cube::load_texture("img/tabletop.bmp");
	texTableside = Cube::load_texture("img/tableside1.bmp");
	texDiamond = Cube::load_texture("img/diamond.bmp");
	texTnttop = Cube::load_texture("img/tnttop.bmp");
	texTntside = Cube::load_texture("img/tntside.bmp");
	texTreetop = Cube::load_texture("img/treetop.bmp");
	texTreeside = Cube::load_texture("img/treeside.bmp");
	texLeaf = Cube::load_texture("img/leaf.bmp");
	texBookshelf = Cube::load_texture("img/bookshelf.bmp");
	texRedSand = Cube::load_texture("img/redsand.bmp");
	texSand = Cube::load_texture("img/sand.bmp");
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
