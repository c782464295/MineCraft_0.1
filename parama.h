#ifndef __PARAMA_H__
#define __PARAMA_H__
#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <string>
#include <windows.h>
#include <gl/GLUT.h>
#include <Digitalv.h>
#include <tchar.h>
#include "Point.h"


#define DELAY 12
#define NUM_OF_LINE 32
#define BLOCK_SIZE 1
#define VIEW_SCALE 2
#define PI 3.1415926535898
#define MAX_CHAR 128
// 跳跃参数
bool jumping = false;
bool falling = false;
float jump_speed = 0.3;
float fall_speed = 0.3;
static float max_height = 3.0;
static float ground_height = 1.00;
//main 中使用
int scr_w;
int scr_h;
float near_sight = 0.1f;
float far_sight = 100;
GLint WindowWidth = 600;
GLint WindowHeight = 600;

// 世界参数
Point center = Point(0, 0, 0);
Point lookAt = Point(5, 5, 5);
Point cameraAt = Point(5, 5, 5);
Point godAt = Point(8, 11, -18);

float last_mm_x = 0;
float last_mm_y = 0;

bool reset_god = false;
int view_person = 1;  // 0 上帝视角，1 第一人称，2 第三人称, 虚拟球
int last_view = 0;
enum { GOD, FIRST_PERSON, THIRD_PERSON, BALL };
enum { HEAD, HAIR, BODY, THIGH_L, THIGH_R, ARM_L, ARMR, EYE_L, EYE_R, MOUTH };


// 视角转换变量
float angle = 0.0, axis[3], trans[3];
float lastPos[3] = { 0.0F, 0.0F, 0.0F };
float look_dy = 0;
int curx, cury;
int startX, startY;
//相对坐标参数
bool left_forward = true;
bool right_forward = false;
bool look_from_left = true;

//飞机模型参数
static int xRot = 0.;
static int yRot = 0;
static int zRot = 0;
static double x_air, y_air, z_air;
static double fly_distance = 20;


bool flying = false;
bool spining = false;
#endif

