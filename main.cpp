#include "CubeManager.h"
#include "parama.h"
#include "LightMaterial.h"
#include "Lable.h"
#include "Man.h"
CubeManager cube_mgr = CubeManager();
LightMaterial lightMaterial;
// 物体
Man man;
int changePos(float pos)
{
	if (pos < 0)
	{
		return pos - 0.5;
	}
	else
	{
		return pos + 0.5;
	}
}
void refresh(int c)
{
	//center.y = -(1 - sin(-left_thigh_angle / 180.0 * PI)) * basic_size * THIGH_SCALE_X + basic_size * FOOT_SCALE_Y / 2;
	if (man.isMoving())
	{
		if (man.ltangle < -60)
		{
			left_forward = false;
		}
		else if (man.ltangle > 60)
		{
			left_forward = true;
		}
		if (man.rtangle < -60)
		{
			right_forward = false;
		}
		else if (man.rtangle > 60)
		{
			right_forward = true;
		}
		if (left_forward)
		{
			man.ltangle--;
			man.laangle++;
		}
		else
		{
			man.ltangle++;
			man.laangle--;
		}
		if (right_forward)
		{
			man.rtangle--;
			man.raangle++;
		}
		else
		{
			man.rtangle++;
			man.raangle--;
		}

	}
	else
	{
		man.raangle = 0;
		man.laangle = 0;
		man.rtangle = 0;
		man.ltangle = 0;
	}
	glutTimerFunc(DELAY, refresh, 0);
	glutPostRedisplay();
}
void human()
{
	//跳跃函数
	if (jumping == true && man.y < max_height && falling == false)
	{
		man.y += jump_speed;
		jump_speed -= 0.05;
		if (jump_speed <= 0)
		{
			falling = true;
			jumping = false;
			jump_speed = 0.3;
		}
	}
	if (falling == true)
	{
		man.y -= fall_speed;
		fall_speed += 0.05;
		if (man.y - 0.05 <= ground_height)
		{
			fall_speed = 0.3;
			falling = false;
		}
	}


	// 人
	glPushMatrix();
	glTranslatef(man.x, man.y, man.z);
	glRotatef(man.vangle, 0, 1, 0);

	////////////////////////////Hair//////////////////////////
	glColor3f(0.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(man.hair.x, man.hair.y, man.hair.z);
	glScalef(man.hair_scale.x, man.hair_scale.y, man.hair_scale.z);
	glutSolidCube(1);
	glPopMatrix();

	///////////////////////////Head////////////////////////////
	// head
	glColor3f(139.0 / 255, 115.0 / 255, 85.0 / 255);
	glPushMatrix();
	glTranslatef(man.head.x, man.head.y, man.head.z);
	glScalef(man.head_scale.x, man.head_scale.y, man.head_scale.z);
	glutSolidCube(1);
	glPopMatrix();

	// left eye
	glColor3f(0.9f, 0.9f, 0.9f);
	glPushMatrix();
	glTranslatef(man.eyeL.x, man.eyeL.y, man.eyeL.z);
	glScalef(man.eye_scale.x, man.eye_scale.y, man.eye_scale.z);
	glutSolidCube(1);
	glPopMatrix();

	// right eye
	glColor3f(0.9f, 0.9f, 0.9f);
	glPushMatrix();
	glTranslatef(man.eyeR.x, man.eyeR.y, man.eyeR.z);
	glScalef(man.eye_scale.x, man.eye_scale.y, man.eye_scale.z);
	glutSolidCube(1);
	glPopMatrix();

	// mouth
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(man.mouth.x, man.mouth.y, man.mouth.z);
	glScalef(man.mouth_scale.x, man.mouth_scale.y, man.mouth_scale.z);
	glutSolidCube(1);
	glPopMatrix();


	///////////////////////////Body////////////////////////////
	glColor3f(0.0f, 206.0 / 255, 209.0 / 255);
	glPushMatrix();
	glTranslatef(man.body.x, man.body.y, man.body.z);
	glScalef(man.body_scale.x, man.body_scale.y, man.body_scale.z);
	glutSolidCube(1);
	glPopMatrix();

	/////////////////////////Leg/////////////////////////
	//Left leg
	glColor3f(67.0 / 255, 110.0 / 255, 238.0 / 255);
	glPushMatrix();
	glTranslatef(man.thighL.x, 2 * man.thighL.y, man.thighL.z);
	glRotatef(man.ltangle, 0, 0, 1);
	glTranslatef(0, -man.thighR.y, 0);
	glScalef(man.thigh_scale.x, man.thigh_scale.y, man.thigh_scale.z);
	glutSolidCube(1);
	glPopMatrix();

	//Right leg
	glColor3f(67.0 / 255, 110.0 / 255, 238.0 / 255);
	glPushMatrix();
	glTranslatef(man.thighR.x, 2 * man.thighR.y, man.thighR.z);
	glRotatef(man.rtangle, 0, 0, 1);
	glTranslatef(0, -man.thighR.y, 0);
	glScalef(man.thigh_scale.x, man.thigh_scale.y, man.thigh_scale.z);
	glutSolidCube(1);
	glPopMatrix();

	///////////////////////Arm////////////////////////

	//Left Arm
	glColor3f(139.0 / 255, 115.0 / 255, 85.0 / 255);
	glPushMatrix();
	glTranslatef(man.armL.x, man.arm_scale.y / 2 + man.armL.y, man.armL.z);
	glRotatef(man.laangle, 0, 0, 1);
	glTranslatef(0, -man.arm_scale.y / 2, 0);
	glScalef(man.arm_scale.x, man.arm_scale.y, man.arm_scale.z);
	glutSolidCube(1);
	glPopMatrix();

	//Right Arm
	glColor3f(139.0 / 255, 115.0 / 255, 85.0 / 255);
	glPushMatrix();
	glTranslatef(man.armR.x, man.arm_scale.y / 2 + man.armR.y, man.armR.z);
	glRotatef(man.raangle, 0, 0, 1);
	glTranslatef(0, -man.arm_scale.y / 2, 0);
	glScalef(man.arm_scale.x, man.arm_scale.y, man.arm_scale.z);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();
}
// 方块初始化
void initCube()
{
	//启用2D纹理和材质初始化
	glEnable(GL_TEXTURE_2D);
	// 在这里做一些初始化
	glEnable(GL_DEPTH_TEST);
	glTexParameterf(GL_NEAREST, GL_TEXTURE_WRAP_S, GL_REPEAT);
	refresh(0);

	Cube::initCubeTexture();

	int num_cube = 25;

	for (int i = num_cube; i >= (-num_cube); i--)
	{
		for (int j = num_cube; j >= (-num_cube); j--)
		{
			cube_mgr.insertCube(TexCube(i, 0, j, 1.0f, Soil));
		}
	}
	//////////////////////地面//////////////////////////

	cube_mgr.insertCube(TexCube(0, 1, 0, 1.0f, Table));

	cube_mgr.buildPool(8, 1, -10);
	cube_mgr.buildPyramid(1, 1, 1);
	cube_mgr.buildDiamondBuilding(-8, 1, 1);
	for (int i = 1; i <= 6; i++)
	{
		cube_mgr.buildTree(-1, 1, -4 * i);
		cube_mgr.buildTree(19, 1, -4 * i);
	}

}
//display中视角切换设置
void setting_view_person()
{
	if (view_person == FIRST_PERSON)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		cameraAt.x = man.x + 1.3 * cos(man.vangle / 180.0 * PI);
		cameraAt.y = man.y + man.head.y;
		cameraAt.z = man.z - 1.3 * sin(man.vangle / 180.0 * PI);

		lookAt.x = man.x + 5 * cos(man.vangle / 180.0 * PI);
		lookAt.y = man.y + man.hair.y - look_dy;
		lookAt.z = man.z - 5 * sin(man.vangle / 180.0 * PI);
		gluLookAt(cameraAt.x, cameraAt.y, cameraAt.z,
			lookAt.x, lookAt.y, lookAt.z,
			0.0f, 1.0f, 0.0f);
	}
	else if (view_person == GOD)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		if (!reset_god)
		{
			cameraAt = godAt;
			lookAt.x = 10;
			lookAt.y = 0;
			lookAt.z = 0;
			reset_god = true;
		}

		gluLookAt(cameraAt.x, cameraAt.y, cameraAt.z,
			lookAt.x, lookAt.y, lookAt.z,
			0.0f, 1.0f, 0.0f);
	}
	else if (view_person == THIRD_PERSON)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		cameraAt.x = man.x - 10 * cos(man.vangle / 180.0 * PI);
		cameraAt.y = man.head.y + 10;
		cameraAt.z = man.z + 10 * sin(man.vangle / 180.0 * PI);

		lookAt.x = man.x;
		lookAt.y = man.hair.y;
		lookAt.z = man.z;

		gluLookAt(cameraAt.x, cameraAt.y, cameraAt.z,
			lookAt.x, lookAt.y, lookAt.z,
			0.0f, 1.0f, 0.0f);
	}
	else if (view_person == BALL)
	{

	}
}
void UnProject(float mouse_x, float mouse_y, int c) //鼠标位置
{
	int x = mouse_x;				/* 屏幕坐标 */
	int y = mouse_y;
	GLint viewport[4];
	GLdouble mvmatrix[16], projmatrix[16];
	GLfloat winx, winy, winz;
	GLdouble posx, posy, posz;

	glPushMatrix();

	//glScalef(0.1, 0.1, 0.1);
	glGetIntegerv(GL_VIEWPORT, viewport);			/* 获取三个矩阵 */
	glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);

	glPopMatrix();

	winx = x;
	winy = scr_h - y;

	glReadPixels((int)winx, (int)winy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winz);			/* 获取深度 */
	gluUnProject(winx, winy, winz, mvmatrix, projmatrix, viewport, &posx, &posy, &posz);	/* 获取三维坐标 */
	int xx = changePos(posx);
	int yy = changePos(posy);
	int zz = changePos(posz);
	if (c == GLUT_LEFT_BUTTON)
	{
		cube_mgr.insertCube(TexCube(xx, yy, zz, 1.0f, Tnt));
	}
	else
	{
		//torch_arr.push_back(Point(xx, yy, zz));
	}
}
// 写文字
void drawString(const char* str) {
	static int isFirstCall = 1;
	static GLuint lists;

	if (isFirstCall) { // 如果是第一次调用，执行初始化
					   // 为每一个ASCII字符产生一个显示列表
		isFirstCall = 0;

		// 申请MAX_CHAR个连续的显示列表编号
		lists = glGenLists(MAX_CHAR);

		// 把每个字符的绘制命令都装到对应的显示列表中
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	// 调用每个字符对应的显示列表，绘制每个字符
	for (; *str != '\0'; ++str)
		glCallList(lists + *str);
}
void music()
{
	MCI_OPEN_PARMS op;                                     //播放背景音乐
	op.dwCallback = NULL;
	op.lpstrAlias = NULL;
	op.lpstrDeviceType =_T("MPEGAudio");
	op.lpstrElementName = _T("music.mp3");
	op.wDeviceID = NULL;
	UINT rs;
	rs = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)&op);
	if (rs == 0)
	{
		MCI_PLAY_PARMS pp;
		pp.dwCallback = NULL;
		pp.dwFrom = 0;
		//mciSendCommand(op.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)&pp);
		mciSendCommand(op.wDeviceID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)&pp);

	}
}
void floor()
{
	glColor3f(0.3f, 1.0f, 0.3f);
	cube_mgr.createAllCube();
	glBindTexture(GL_TEXTURE_2D, 0);
}
void reshape(int w, int h)
{
	scr_w = w;
	scr_h = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0, (GLfloat)scr_w / scr_h, near_sight, far_sight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	floor();
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glRasterPos2f(0.0f, 0.0f);
	//drawString("Hello, World!");
	human();
	glutSwapBuffers();
	setting_view_person();
}
void setPosition()
{

	man.x = 8;
	man.y = 1;
	man.z = -10;

	x_air = 8.0f;
	y_air = 8.0f;
	z_air = -10.0f;
}

void passiveMotion(int x, int y)
{
	float r = 0.06;
	man.vangle -= 0.1*(x - last_mm_x);

	if (x < r*scr_w && last_mm_x>x)
	{
		x = (1 - r) * scr_w;
		SetCursorPos(x, y);
	}
	else if (x > (1 - r) * scr_w && last_mm_x < x)
	{
		x = r * scr_w;
		SetCursorPos(x, y);
	}
	if (view_person == FIRST_PERSON)
	{
		look_dy += 0.01*(y - last_mm_y);
	}
	last_mm_x = x;
	last_mm_y = y;
}
void mouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		switch (state)
		{
		case GLUT_DOWN:
			if (view_person == FIRST_PERSON)
			{
				UnProject(x, y, GLUT_LEFT_BUTTON);
			}
			cameraAt.x /= VIEW_SCALE;
			cameraAt.y /= VIEW_SCALE;
			cameraAt.z /= VIEW_SCALE;
			//startMotion(x, y);
			break;
		case GLUT_UP:
			//stopMotion(x, y);
			break;

		}
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		// 视角收缩
		if (state == GLUT_DOWN)
		{
			if (view_person == FIRST_PERSON)
			{
				UnProject(x, y, GLUT_RIGHT_BUTTON);
			}
			cameraAt.x *= VIEW_SCALE;
			cameraAt.y *= VIEW_SCALE;
			cameraAt.z *= VIEW_SCALE;
		}
	}
	TexCube* newCube = new TexCube(man.x + 1, man.y, man.z + 1, 1.0f, Stone);
	newCube->createCube();
}
void controlup(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		man.move = false;
		break;
	case 's':
		man.move = false;
		break;
	case 'a':
		man.move = false;
		break;
	case 'd':
		man.move = false;
		break;
	}
}
void control(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 32:
		jumping = true;
		break;
	case 'a':
		man.move = true;
		man.x -= man.speed * sin(man.vangle / 180 * PI);
		man.z -= man.speed * cos(man.vangle / 180 * PI);
		break;
	case 'd':
		man.move = true;
		man.x += man.speed * sin(man.vangle / 180 * PI);
		man.z += man.speed * cos(man.vangle / 180 * PI);
		break;
	case 'w':
		man.move = true;
		man.x += man.speed * cos(man.vangle / 180 * PI);
		man.z -= man.speed * sin(man.vangle / 180 * PI);
		break;
	case 's':
		man.move = true;
		man.x -= man.speed * cos(man.vangle / 180 * PI);
		man.z += man.speed * sin(man.vangle / 180 * PI);
		break;
	case 'h':
		reset_god = false;
		if (view_person >= 3)
		{
			view_person = 0;
		}
		else
		{
			view_person++;
		}
		break;
	case 'r':
		if (view_person != 3)
		{
			last_view = view_person;
			view_person = 3;
		}
		else
		{
			view_person = last_view;
		}
		break;
	case 'z':
		x_air = 8.0;
		y_air = 8.0;
		z_air = -10.0;
		zRot = 0;
		flying = false;
		spining = false;
		break;
	case 'f':
		flying = true;
		spining = true;
		break;
	case 27:
		exit(0);
	default:
		break;
	}

}
// 空闲回调函数
void idle()
{
	// 如果鼠标发生移动，则后面自动转动
	//if (redrawContinue) glutPostRedisplay();
}
void mouseMotion(int x, int y)
{
	//trackball_ptov(x, y, scr_w, scr_h, curPos);
	//trackMouse();
	//glutPostRedisplay();
}
void init()
{
	glShadeModel(GL_FLAT);//平滑着色
	glEnable(GL_DEPTH_TEST);//启用深度测试
	glEnable(GL_CULL_FACE);//开启剔除操作
	glFrontFace(GL_CCW);//GL_CCW 表示窗口坐标上投影多边形的顶点顺序为逆时针方向的表面为正面
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);//设置颜色混合 GL_ONE： 表示使用1.0作为因子，实际上相当于完全的使用了这种颜色参与混合运算。GL_SRC_ALPHA：表示使用源颜色的alpha值来作为因子。
	glEnable(GL_COLOR_MATERIAL);//开启颜色追踪
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//显示模式 双缓冲 RGB 深度缓冲区

	glutInitWindowSize(WindowWidth, WindowHeight);

	GLint screenWidth = glutGet(GLUT_SCREEN_WIDTH);
	GLint screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
	glutInitWindowPosition((screenWidth-WindowWidth) / 2,(screenHeight - WindowHeight) / 2);
	glutCreateWindow("Craft");
	init();

	lastTime = clock();//启动时首次设定当前时间
	
	music();//音乐
	glutDisplayFunc(display);//刷新显示事件

	//ShowCursor(false);//不显示鼠标
	initCube();
	//initOther();//动物的初始化
	glutReshapeFunc(reshape);//改变窗口大小事件
	glutPassiveMotionFunc(passiveMotion);//鼠标没有被按下去时，移动鼠标的情形
	glutMouseFunc(mouseButton);//鼠标按下事件

	glutMotionFunc(mouseMotion);//鼠标移动事件
	glutKeyboardUpFunc(controlup);//键盘按下放开事件
	glutKeyboardFunc(control);//键盘按下事件
	glutMainLoop();//进入循环，除非程序退出，否则不会返回
	return 0;
}