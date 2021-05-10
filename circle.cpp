 
#define GLUT_DISABLE_ATEXIT_HACK
#include<windows.h>
#include<gl/gl.h>
#include<gl/glut.h>
#include<iostream>
#include<cmath>
#include<math.h>

using namespace std;
///初始化函数
///////////////////////////////////////////////////////////////
void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);  // Set display-window color to white.
    glMatrixMode(GL_PROJECTION);       // Set projection parameters.
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

// 窗口大小改变时调用的登记函数
void ChangeSize(GLsizei w, GLsizei h)
{

    if (h == 0)     h = 1;

    // 设置视区尺寸
    glViewport(0, 0, w, h);

    // 重置坐标系统
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // 建立修剪空间的范围
    if (w <= h)
        glOrtho(0.0f, 250.0f, 0.0f, 250.0f*h / w, 1.0, -1.0);
    else
        glOrtho(0.0f, 250.0f*w / h, 0.0f, 250.0f, 1.0, -1.0);

}
///////////////////////////////////////////////////////////////////
//圆的生成算法 
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
		// 利用圆的八分对称性画点
		putpixel(x + tx, y + ty);
		putpixel(x + tx, y - ty);
		putpixel(x - tx, y + ty);
		putpixel(x - tx, y - ty);
		putpixel(x + ty, y + tx);
		putpixel(x + ty, y - tx);
		putpixel(x - ty, y + tx);
		putpixel(x - ty, y - tx);
 
		if (d < 0)		// 取上面的点
			d += 4 * tx + 6;
		else			// 取下面的点
			d += 4 * (tx - ty) + 10, ty--;
 
		tx++;
	}
}


//////////////////////////////////中点画圆法//////////////////////////////////
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
////////////////////////////////开方算法（勾股算法）//////////////////////////
void circleSqr(int xc, int yc, int r)
{
    int start = xc - r;
    int end = xc + r;
    for (int i = start; i <= end; i++){
        int p = sqrt(float(r*r - pow(xc-i,2)));
        drawPixel(i,yc+p);
        drawPixel(i,yc-p);
    }
}
//////////////////////////////////////////////////////////////////////////
/*

*/
void display(void)
{
    // 用当前背景色填充窗口，如果不写这句会残留之前的图像
    glClear(GL_COLOR_BUFFER_BIT);


	//中点画圆
 	drawCircle(60,60,30);
 	Circle_Bresenham(100,100,30);
    circleSqr(130,130,30);
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

 
