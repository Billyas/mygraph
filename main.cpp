 
#define GLUT_DISABLE_ATEXIT_HACK
#include<windows.h>
#include<gl/gl.h> 
#include<gl/glut.h>
#include<iostream>
#include<cmath>
#include<cmath>
/*�򵥾���*/ 
/*void Initial(){
	glClearColor(1.0f,1.0f,1.0f,1.0f);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,200.0,0.0,150.0);
}
void Display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f,0.0f,0.0f);
	glRectf(50.0f,100.0f,150.0f,50.0f);
	glFlush();
} 
int main(int argc,char *argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400,300);
	glutInitWindowPosition(100,120);
	glutCreateWindow("����");
	glutDisplayFunc(Display);
	Initial();
	glutMainLoop();
	return 0;
}*/ 




/////////////////////////////////////////////////////////////////////////////////////////// 
using namespace std;

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);  // Set display-window color to white.
    glMatrixMode(GL_PROJECTION);       // Set projection parameters.
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

/*
    ��ֵ΢�ַ�������
*/
void LineDDA(int x1, int y1, int x2, int y2)
{
    glColor3f(1.0, 0.0, 0.0);       // ��ɫ
    glPointSize(2.0f);

    /*
        �����غ���δ�ж�
    */

    int dm = 0;
    if (abs(x2 - x1) >= abs(y2 - y1))
    {
        dm = abs(x2 - x1);              // x Ϊ�Ƴ�����
    }
    else
    {
        dm = abs(y2 - y1);              // y Ϊ�Ƴ�����
    }
    float dx = (float)(x2 - x1) / dm;   // �� x Ϊ�Ƴ�����dx = 1
    float dy = (float)(y2 - y1) / dm;   // �� y Ϊ�Ƴ�����dy = 1
    float x = x1;
    float y = y1;

    for (int i = 0; i < dm; ++i)
    {
        glBegin(GL_POINTS);
        glVertex2f((int)x, (int)y);
        glEnd();
        glFlush();
        x += dx;
        y += dy;
    }
}

/*
    ��������int ���͵ı�����ֵ
*/
void swap_value(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/*
    Bresenham ���߷�
*/
void LineBres(int x1, int y1, int x2, int y2)
{
    glColor3f(0.0, 0.0, 1.0);       // ��ɫ
    glPointSize(2.0f);

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    // �����غ�
    if (dx == 0 && dy == 0)
    {
        glBegin(GL_POINTS);
            glVertex2f(x1, y1);
        glEnd();
        glFlush();
        return ;
    }

    int flag = 0;       // ��б�ʱ任�� 0 <= |k| <= 1 ����
    if (dx < dy)
    {
        flag = 1;
        swap_value(&x1, &y1);
        swap_value(&x2, &y2);
        swap_value(&dx, &dy);
    }

    int tx = (x2 - x1) > 0 ? 1 : -1;
    int ty = (y2 - y1) > 0 ? 1 : -1;
    int curx = x1;
    int cury = y1;
    int dS = 2 * dy;
    int dT = 2 * (dy - dx);
    int d = dS - dx;
    while (curx != x2)
    {
        if (d < 0)
            d += dS;
        else
        {
            cury += ty;
            d += dT;
        }

        if (flag)
        {
            glBegin(GL_POINTS);
                glVertex2f(cury, curx);
            glEnd();
            glFlush();
        }
        else
        {
            glBegin(GL_POINTS);
                glVertex2f(curx, cury);
            glEnd();
            glFlush();
        }
        curx += tx;
    }

}

void Midpoint(int x1, int y1, int x2, int y2)
{
    
}


// ���ڴ�С�ı�ʱ���õĵǼǺ���
void ChangeSize(GLsizei w, GLsizei h)
{

    if (h == 0)     h = 1;

    // ���������ߴ�
    glViewport(0, 0, w, h);

    // ��������ϵͳ
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // �����޼��ռ�ķ�Χ
    if (w <= h)
        glOrtho(0.0f, 250.0f, 0.0f, 250.0f*h / w, 1.0, -1.0);
    else
        glOrtho(0.0f, 250.0f*w / h, 0.0f, 250.0f, 1.0, -1.0);

}

/*

*/
void display(void)
{
    // �õ�ǰ����ɫ��䴰�ڣ������д�������֮ǰ��ͼ��
    glClear(GL_COLOR_BUFFER_BIT);

    int x1 = 20, y1 = 20, x2 = 160, y2 = 80;
    int x12 = 20, y12 = 40, x22 = 160, y22 = 100;
    LineDDA(x1, y1, x2, y2);
    LineBres(x12, y12, x22, y22);
    
//	MidpointLine(0, 0, 100, 100);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Line");
    glutDisplayFunc(display);
    glutReshapeFunc(ChangeSize);
    init();
    glutMainLoop();
    return 0;
}

 

///////////////////////////////////////////////////////////////////////////////////////////////
// ��ɫ������ͼ�� 
 
/* 
// ��ʼ������
void init() {
    glClearColor(0.1, 0.1, 0.4, 0.0);
    glShadeModel(GL_SMOOTH);
}
 
// ��ͼ�ص�����
void display() {

    // ���֮ǰ֡����
    glClear(GL_COLOR_BUFFER_BIT);
 
    // ����������
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex3f(-1, -1, -5);
    glColor3f(0, 1, 0);
    glVertex3f(1, -1, -5);
    glColor3f(0, 0, 1);
    glVertex3f(0, 1, -5);
    glEnd();
    // ִ�л�ͼ����
    glFlush();
}
 
// ���ڴ�С�仯�ص�����
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 0.1, 100000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
 
int main(int argc, const char * argv[]) {
    // ��ʼ����ʾģʽ
    glutInit(&argc, const_cast<char **>(argv));
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
 
    // ��ʼ������
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
 
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
 
    // ��ʼ��ѭ������
    glutMainLoop();
    return 0;
}*/ 
