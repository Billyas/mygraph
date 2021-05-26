 
#define GLUT_DISABLE_ATEXIT_HACK
#include<windows.h>
//#include<gl/gl.h> 
#include"glut.h"
#include<iostream>
#include<cmath>


#include <Windows.h>
//#include "glew.h"
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"./glew32.lib")
#include <math.h>
//
 
#include "glut.h"
#include<stdio.h>
#include<stdlib.h>
 
 
#define drawOneLine(x1,y1,x2,y2) glBegin(GL_LINES);glVertex3f((x1),(y1),0); glVertex3f((x2),(y2),0);glEnd();
 
#define  qingxie_  2.0
// function declear
void init (void)
{
	glClearColor (1.0, 1.0, 1.0, 0.0);  // Set display-window color to white.
	glMatrixMode (GL_PROJECTION);       // Set projection parameters.
	gluOrtho2D (0.0, 200.0, 0.0, 150.0);
}
 
void show_width_lines(int width,float red,float green,float blue)
{
	glColor3f(red,green,blue);
	
	width = 1.0f;
	float PI = 3.1415926;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glColor3f(red,green,blue);
	//禁用反走样
	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);	
	
	// line_1	
	for (int i = 0; i < 8;i++ )
	{
		glLineWidth(width);	
		glBegin(GL_LINE_STRIP);
		glVertex3f(5,5*(i+1), 0.0);
		glVertex3f(100,5*(i+1)-qingxie_,0.0);
		glEnd();
		//直线宽度增加0.5
		width += 2.0;
	}
		
	//启用反走样
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);  // Antialias the lines
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	//初始化直线宽度
	width=1.0;	
	// line_2	
	glColor4f(0,green,0,1.0);
	for (int i = 0; i < 8;i++ )
	{	
		glLineWidth(width);
		glBegin(GL_LINE_STRIP);
		glVertex3f(5, 50+1*(i+1), 0.0);
		//glVertex3f(50,50+2*(i+1)-qingxie_, 0.0);
		glVertex3f(80,50+3*(i+1)+qingxie_, 0.0);
		//glVertex3f(100,50+4*(i+1)-qingxie_, 0.0);
		glVertex3f(120,50+5*(i+1)+qingxie_, 0.0);
		glEnd();
		//宽度累加
		width += 2.0;
	}
	glFlush();
}
 
void Line3f(GLfloat fromX, GLfloat fromY, GLfloat fromZ,
			GLfloat toX, GLfloat toY, GLfloat toZ)
{
	glBegin(GL_LINES);
	glVertex3f(fromX, fromY, fromZ);
	glVertex3f(toX, toY, toZ);
	glEnd();
}
 
 
void show_dot_lines(int width,float red,float green,float blue)
{
	int PatternMode = 0;            //线型模式
 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glColor3f(red,green,blue);
	int Pattern[6]=                  //定义了6种线型
	{
		//点线 1000100010001000, 表示实际画线的点，反序后转换成16进制就是0x1111 dotted
		//.  .  .  .  .  .  .  .  .  .  .  .  .  .
		//0x1111,
		0x0101,
 
		//点划线    1111111111100100  dot dash
		//____ . ____ . _____ . _____. _____
		0x27FF,
		//0x1C47,
 
		//中心线    1111111111001100  centre line
		//_____ _ _____ _ _____ _ _____ _ _____
		0x33FF,
 
		//虚线  1111110011111100   dashed
		//____  ____  ____  ____  ____  ____  ____
		0x3F3F,
 
		//双点划线  1111111100100100  double dot dash
		// ____ . . ____ . . ____ . . ____ . . ____
		0x24FF,
 
		//三点划线  111111110101010 tri_dot_dash
		// ____ . . ____ . . ____ . . ____ . . ____
		0x55FF
	};
 
	static float angle = 0.0;
 
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);  // 反走样的fastest效果，也可以根据需要选择GL_NICEST.etc.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	glEnable(GL_LINE_STIPPLE);	
	
	//初始化直线宽度
	width=10.0;	
	// line_2	
	glColor3f(0,0,blue);
	for (int i = 0; i<6; i++)
	{
		int PatternMode = i;
		glLineStipple(i, Pattern[PatternMode]);
		glLineWidth(width);	
		glBegin(GL_LINES);
		glVertex3f(1,23+i*5, 0.0);
		glVertex3f(50,23+i*5-qingxie_, 0.0);
		glEnd();
	}
 
	width = 1.0;
	glColor3f(red,0,0);
	for (int i = 0; i<6; i++)
	{
		int PatternMode = i;
		glLineStipple(i, Pattern[PatternMode]);
		glLineWidth(width);	
		glBegin(GL_LINES);
		glVertex3f(2,50+i*5, 0.0);
		glVertex3f(50,50+i*5-qingxie_, 0.0);
		glEnd();
	}
 
	glDisable(GL_LINE_STIPPLE); 
	glDisable(GL_BLEND);
	glFlush();
 
}
 
void pointFun()
{
	float red = 1.0,green = 0.5,blue = 0.5;
	glClear (GL_COLOR_BUFFER_BIT);
	
	// 去掉注释就可以看线宽效果了。
	//show_width_lines(5,red,green,blue);
	show_dot_lines(5,red,green,blue);
	glFlush();
}
 
int main (int argc, char** argv)
{
	glutInit (&argc, argv);                         // Initialize GLUT.
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);   // Set display mode.
	glutInitWindowPosition (50, 100);   // Set top-left display-window position.
	glutInitWindowSize (1000, 800);      // Set display-window width and height.
	//glutFullScreen();
	glutCreateWindow ("An Example OpenGL Program By Qiu"); // Create display window.
	init();                           // Execute initialization procedure.
 
	// draw position.
	glTranslatef(50.0f, 50.0f,0.0f);
 
	glutDisplayFunc (pointFun);       // Send graphics to display window.
	glutMainLoop ( );// Send graphics to display window.                  // Display everything and wait.
	return 0;
}

