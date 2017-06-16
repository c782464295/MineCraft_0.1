#ifndef __CUBEMANAGER_H__
#define __CUBEMANEGER_H__
#include "TexCube.h"
#include <map>
#include <string>
using namespace std;
class CubeManager
{
public:
	void insertCube(TexCube &texcube);
	CubeManager() {};
	~CubeManager() {};
	void createAllCube();
	void buildAnnexBuilding(int x, int y, int z);  //���츽�ӽ���
	void buildPyramid(int x, int y, int z);			//�����Σ���������
	void buildPool(int x, int y, int z);          //����
	void buildTree(int x, int y, int z);         //��
	void buildDiamondBuilding(int x, int y, int z); //��ʯ����
	bool isExist(string);    //
	map<string, TexCube> cubeMap;//Map��һ�ֹ���������map<Key,T>::iterator it
};
#endif