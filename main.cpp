#include "CubeManager.h"
#include "parama.h"
#include "LightMaterial.h"
CubeManager cube_mgr = CubeManager();
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
	glutSwapBuffers();
	//setting_view_person();
}
void passiveMotion(int x, int y)
{

}
void mouseButton(int button, int state, int x, int y)
{

}
void controlup(unsigned char key, int x, int y)
{

}
void control(unsigned char key, int x, int y)
{

}
void mouseMotion(int x, int y)
{

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
	//initCube();
	//initOther();
	glutReshapeFunc(reshape);//改变窗口大小事件
	glutPassiveMotionFunc(passiveMotion);//鼠标没有被按下去时，移动鼠标的情形
	glutMouseFunc(mouseButton);//鼠标按下事件

	glutMotionFunc(mouseMotion);//鼠标移动事件
	glutKeyboardUpFunc(controlup);//键盘按下放开事件
	glutKeyboardFunc(control);//键盘按下事件
	glutMainLoop();//进入循环，除非程序退出，否则不会返回
	return 0;
}