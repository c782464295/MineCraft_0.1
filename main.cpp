#include "CubeManager.h"
#include "parama.h"
#include "LightMaterial.h"
CubeManager cube_mgr = CubeManager();
void music()
{
	MCI_OPEN_PARMS op;                                     //���ű�������
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
	glShadeModel(GL_FLAT);//ƽ����ɫ
	glEnable(GL_DEPTH_TEST);//������Ȳ���
	glEnable(GL_CULL_FACE);//�����޳�����
	glFrontFace(GL_CCW);//GL_CCW ��ʾ����������ͶӰ����εĶ���˳��Ϊ��ʱ�뷽��ı���Ϊ����
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);//������ɫ��� GL_ONE�� ��ʾʹ��1.0��Ϊ���ӣ�ʵ�����൱����ȫ��ʹ����������ɫ���������㡣GL_SRC_ALPHA����ʾʹ��Դ��ɫ��alphaֵ����Ϊ���ӡ�
	glEnable(GL_COLOR_MATERIAL);//������ɫ׷��
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//��ʾģʽ ˫���� RGB ��Ȼ�����

	glutInitWindowSize(WindowWidth, WindowHeight);

	GLint screenWidth = glutGet(GLUT_SCREEN_WIDTH);
	GLint screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
	glutInitWindowPosition((screenWidth-WindowWidth) / 2,(screenHeight - WindowHeight) / 2);
	glutCreateWindow("Craft");
	init();

	lastTime = clock();//����ʱ�״��趨��ǰʱ��
	
	music();//����
	glutDisplayFunc(display);//ˢ����ʾ�¼�

	//ShowCursor(false);//����ʾ���
	//initCube();
	//initOther();
	glutReshapeFunc(reshape);//�ı䴰�ڴ�С�¼�
	glutPassiveMotionFunc(passiveMotion);//���û�б�����ȥʱ���ƶ���������
	glutMouseFunc(mouseButton);//��갴���¼�

	glutMotionFunc(mouseMotion);//����ƶ��¼�
	glutKeyboardUpFunc(controlup);//���̰��·ſ��¼�
	glutKeyboardFunc(control);//���̰����¼�
	glutMainLoop();//����ѭ�������ǳ����˳������򲻻᷵��
	return 0;
}