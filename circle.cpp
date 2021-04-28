 
#define GLUT_DISABLE_ATEXIT_HACK
#include<windows.h>
//#include<gl/gl.h> 
#include"glut.h"
#include<iostream>
#include<cmath>
#include<cmath>

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
void drawpoint(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
    glFlush();
}

void Midpoint(int x0, int y0, int x1, int y1)
{
    glColor3f(0.0, 1.0, 0.0);       // ��ɫ
    glPointSize(2.0f);
    int a,b,d1,d2,d,_x,_y;
    a = y0-y1, b = x1-x0, d=2*a+b;
    d1= 2*a,d2=2*(a+b);
    _x=x0,_y=y0;
    drawpoint(_x,_y);

    while(_x<x1)
    {
        if(d<0){
            _x++, _y++, d+=d2;
        }else{
            _x++,d+=d1;
        }
        drawpoint(_x,_y);
    }

}

//���
void MidPointLine(int x1,int y1,int x2,int y2)
{
	int a,b,dt1,dt2,d,x,y;
	a = y1 - y2;
	b = x2 - x1;
	d = a + a + b;	//Ϊ�˱���С��������ȡ2��
	dt1 = a + b + a +b;
	dt2 = a + a;
	x = x1;
	y = y1;
 
	glColor3f(0.0,1.0,0.0);
	glPointSize(2.0f);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
	while(x < x2)
	{
		if(d < 0)
		{
			x++;
			y++;
			d += dt1;
		}
		else
		{
			x++;
			d += dt2;
		}
		glBegin(GL_POINTS);
		glVertex2i(x,y);
		glEnd();
		   glFlush();
	}
 
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
///////////////////////////////////////////////////////////////////
//Բ�������㷨 
void f(int x, int y, int r)
{
	int tx = x, ty = y;
	x = 0, y = r;
	int d = 3 - 2 * r;
	glColor3f(0.0,1.0,0.0);
	glPointSize(2.0f);
	glBegin(GL_POINTS);
	while (x < y)
	{
		glVertex2i(x + tx, y + ty);//x,y
		glVertex2i(y + tx, x + ty);//y,x
		glVertex2i(-x + tx, y + ty);//-x,y
		glVertex2i(-y + tx,x + ty);//-y,x
		glVertex2i(-y + tx, -x + ty);//-y,-x
		glVertex2i(-x + tx, -y + ty);//-x,-y
		glVertex2i(x + tx, -y + ty);//x,-y
		glVertex2i(y + tx, -x + ty);//y,-x
		if (d < 0)
			d = d + 4 * x + 6;
		else {
			d = d + 4 * (x - y) + 10;
			y--;
		}
		x++;
		if (x == y)
		{
			glVertex2i(x + tx, y + ty);//x,y
			glVertex2i(-x + tx, y + ty);//-x,y
			glVertex2i(-x + tx, -y + ty);//-x,-y
			glVertex2i(x + tx, -y + ty);//x,-y
		}
	}
	glEnd();
	glFlush();
}
//////////////////////////Bresenham_Circle/////////////////////////////////////////
void putpixel(int x, int y)
{
	glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();		
}
void Circle_Bresenham(int x, int y, int r)
{
	int tx = 0, ty = r, d = 3 - 2 * r;
 	glColor3f(0.0,0.0,1.0);
	glPointSize(2.0f);
	while (tx <= ty)
	{
		// ����Բ�İ˷ֶԳ��Ի���
		putpixel(x + tx, y + ty);
		putpixel(x + tx, y - ty);
		putpixel(x - tx, y + ty);
		putpixel(x - tx, y - ty);
		putpixel(x + ty, y + tx);
		putpixel(x + ty, y - tx);
		putpixel(x - ty, y + tx);
		putpixel(x - ty, y - tx);
 
		if (d < 0)		// ȡ����ĵ�
			d += 4 * tx + 6;
		else			// ȡ����ĵ�
			d += 4 * (tx - ty) + 10, ty--;
 
		tx++;
	}
}


//////////////////////////////////�е㻭Բ��//////////////////////////////////
void drawPixel(int x, int y)
{
	glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();		
}
void drawEightPoints(int xc,int yc,int addx,int addy)
{
    drawPixel(xc+addx, yc+addy);
    drawPixel(xc-addx, yc+addy);
    drawPixel(xc+addx, yc-addy);
    drawPixel(xc-addx, yc-addy);
    drawPixel(xc+addy, yc+addx);
    drawPixel(xc-addy, yc+addx);
    drawPixel(xc+addy, yc-addx);
    drawPixel(xc-addy, yc-addx);
}
void drawCircle(int xc,int yc,int r)
{
	glColor3f(0.0,1.0,0.0);
	glPointSize(2.0f);
    int p,addx,addy;
    p=1-r;
    addx=0;
    addy=r;
    drawEightPoints(xc, yc, addx, addy);
    while(addx<addy){
        addx++;
        if(p<0){
            p+=2*addx+1;
        }
        else{
            addy--;
            p+=2*(addx-addy)+1;
        }
        drawEightPoints(xc, yc, addx, addy);
    }
}
//////////////////////////////////////////////////////////////////////////
/*

*/
void display(void)
{
    // �õ�ǰ����ɫ��䴰�ڣ������д�������֮ǰ��ͼ��
    glClear(GL_COLOR_BUFFER_BIT);


	//�е㻭Բ
 	drawCircle(60,60,30); 
 	Circle_Bresenham(100,100,30);

}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Line");
    glutDisplayFunc(display);
    glutReshapeFunc(ChangeSize);
    init();
    glutMainLoop();
    return 0;
}

 
