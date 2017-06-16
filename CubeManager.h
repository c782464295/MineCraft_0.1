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
	void buildAnnexBuilding(int x, int y, int z);  //建造附加建筑
	void buildPyramid(int x, int y, int z);			//三角形（金字塔）
	void buildPool(int x, int y, int z);          //池塘
	void buildTree(int x, int y, int z);         //树
	void buildDiamondBuilding(int x, int y, int z); //钻石建筑
	bool isExist(string);    //
	map<string, TexCube> cubeMap;//Map是一种关联容器，map<Key,T>::iterator it
};
#endif