#include "func.h"
void init3(void)
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
    glColor3f(0,1,0);
    glPointSize(2.0f);
    int a, b, d;
    
}
 
void MidpointLine(int x0, int y0, int x1, int y1)
{
	if((x0 != x1) && (y0 != y1))
	{
		int a, b, deltal, delta2, d, x, y;
		a = y0 - y1;
		b = x1 - x0;
		d = 2 * a + b;
		deltal = 2 * a;
		delta2 = 2 * (a + b);
		x = x0;
		y = y0;
		glVertex2i(x, y);
		while(x < x1)
		{
			if(d < 0)
			{
				x++;
				y++;
				d += delta2;
			}
			else
			{
				x++;
				d += deltal;
			}
			glVertex2i(x, y);
		}
	}
	else
	{
		int min, d;
		if(x0 == x1)
		{
			int x = x0, y;
			y = (y0<=y1) ? y0 : y1;
			d = fabs((double)(y0 - y1));
			while (d <= 0)
			{
				glVertex2i(x, y);
				y++;
				d--;
			}
		}
	}
}
 

// ���ڴ�С�ı�ʱ���õĵǼǺ���
void ChangeSize2(GLsizei w, GLsizei h)
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
void display3(void)
{
    // �õ�ǰ����ɫ��䴰�ڣ������д�������֮ǰ��ͼ��
    glClear(GL_COLOR_BUFFER_BIT);

    int x1 = 20, y1 = 20, x2 = 160, y2 = 80;
    int x12 = 20, y12 = 40, x22 = 160, y22 = 100;
    LineDDA(x1, y1, x2, y2);
    LineBres(x12, y12, x22, y22);
    MidpointLine(0, 0, 100, 100);
}

void drawLine(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Line");
    glutDisplayFunc(display3);
    glutReshapeFunc(ChangeSize2);
    init3();
    glutMainLoop();
}

