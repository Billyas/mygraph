#define GLUT_DISABLE_ATEXIT_HACK
#include<gl/gl.h> 
#include<gl/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include<windows.h>

#include<iostream>

#define LEFT_EDGE   1
#define RIGHT_EDGE  2
#define BOTTOM_EDGE 4
#define TOP_EDGE    8

/*
 
int x0,y0,x1,y1;
 
void LineGL(int x0,int y0,int x1,int y1)
{
	glBegin(GL_LINES);
	glColor3f(1.0,0.0,0.0); glVertex2f(x0,y0);
	glColor3f(0.0,1.0,0.0); glVertex2f(x1,y1);	
	glEnd();
}
 
 struct Recta
{
	float xmin,xmax,ymin,ymax;
};
 

Recta rect;
 
int CompCode(int x,int y,  Recta rect)
{
	int code = 0x00;
	if(y < rect.ymin)
		code = code|4;
	if(y > rect.ymax)
		code = code|8;
	if(x >rect.xmax)
		code = code|2;
	if(x < rect.xmin)
		code = code|1;
	return code;
}
 
int cohensutherlandlineclip(Recta rect,int &x0,int &y0,int &x1,int &y1)//此处&不能删除，否则导致错误
{
	int accept,done;
	float x,y;
	done = 0;


	int code0,code1,codeout;
	code0 = CompCode(x0,y0,rect);
	code1 = CompCode(x1,y1,rect);
	do{
		if(!(code0 | code1))
		{
			accept =1;
			done=1;
		}
		else if(code0 &code1)
			done =1;
		else {
			if(code0!=0)
				codeout = code0;
			else
				codeout = code1;
 
			if(codeout&LEFT_EDGE){
				y=y0+(y1-y0)*(rect.xmin-x0)/(x1-x0);
				x=(float)rect.xmin;
			}
			else if(codeout&RIGHT_EDGE){
				y=y0+(y1-y0)*(rect.xmax-x0)/(x1-x0);
				x=(float)rect.xmax;
			}
 
			else if(codeout&BOTTOM_EDGE){
				x=x0+(x1-x0)*(rect.ymin-y0)/(y1-y0);
				y=(float)rect.ymin;}
			else if(codeout&TOP_EDGE){
					x=x0+(x1-x0)*(rect.ymax-y0)/(y1-y0);
					y=(float)rect.ymax;
				}
 
			if(codeout == code0 )
			{
				x0=x;
				y0=y;
				code0 = CompCode(x0,y0,rect);
			}
			else
			{
				x1 = x;
				y1=y;
				code1 = CompCode(x1,y1,rect);
			}
			}
		}while(!done);
 
		if(accept)
			LineGL(x0,y0,x1,y1);
		return accept;
	}
 
	void myDisplay()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0,0.0,0.0);
		glRectf(rect.xmin,rect.ymin,rect.xmax,rect.ymax);
 
		LineGL(x0,y0,x1,y1);
 
		glFlush();
 
	}
 
	void Init()
	{
		glClearColor(0.0,0.0,0.0,0.0);
		glShadeModel(GL_FLAT);
 
		rect.xmin=100;
		rect.xmax=300;
		rect.ymin=100;
		rect.ymax=300;
 
		x0=450,y0=0,x1=0,y1=450;
		printf("Press key 'c' to Clip!\n");
		printf("Press key 'r' to Restore!\n");
	}
 
	void Reshape(int w,int h)
	{
		glViewport(0,0,(GLsizei)w, (GLsizei)h );
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0.0,(GLdouble)w,0.0,(GLdouble)h );
	}
 
	void keyboard(unsigned char key,int x,int y)
	{
		switch (key)
		{
		case 'c':
			cohensutherlandlineclip(rect, x0,y0,x1,y1);
			glutPostRedisplay();
			break;
		case 'r':
			Init();
			glutPostRedisplay();
			break;
		case 'x':
			exit(0);
			break;
		default:
			break;
		}
	}
 
 
int main(int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,480);
	glutCreateWindow("Hello world!");
 
	Init();
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
*/

 
#include <windows.h>

#include <math.h>

float xmin,xmax,ymin,ymax;
 
 
void myinit(void)
{
    glShadeModel (GL_FLAT);
    glClearColor (1.0, 1.0, 1.0, 0.0);
}
 
 
void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h) 
	gluOrtho2D (0.0, 1.0, 0.0, 1.0*(GLfloat)h/(GLfloat)w);
    else 
	gluOrtho2D (0.0, 1.0*(GLfloat)w/(GLfloat)h, 0.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}
 
int Clip(float p,float q,float *tL,float *tU) 
{  
	int flag=1;/*flag为标志变量0表示舍弃1表示可见*/ 
	float r; 
 
	if (p<0.0) 
	{ 
		r=q/p; 
		if (r>*tU)
			flag=0; 
		else if (r>*tL) {
			*tL = r;/*m取进入点最大参数值*/ 
		} 
	} 
	else if (p>0.0) { 
		r=q/p; 
		if (r<*tL)
			flag=0; 
		else if (r<*tU) {
			*tU = r;/*n取离开点的最小值*/ 
		} 
	} 
 
	else if (q<0 && p==0) //平行于边界而且在界外的线 
		flag=0; 
	return flag; 
}
void myclip()
// line clipping algorithm 
{
	float dx, dy, x1,tL,tU, x2, y1, y2;
	tL = 0, tU = 1.0;
	printf("请输入线段的两个顶点坐标x1,y1,x2,y2:\n");
	scanf("%f%f%f%f",&x1,&y1,&x2,&y2);
 
	glBegin(GL_LINES); 
	glColor4f (0.0, 0.0, 0.0, 0.0); 
	glVertex2f(x1, y1); // line startpoint 
	glVertex2f(x2, y2); // line endpoint 
	glEnd(); 
 
	dx=x2-x1; 
  
	if (Clip(-dx, x1 - xmin, &tL, &tU))
		if (Clip(dx, xmax - x1, &tL, &tU)){
			dy=y2-y1; 
			if (Clip(-dy, y1 - ymin, &tL, &tU))
				if (Clip(dy, ymax - y1, &tL, &tU))
				{ 
					if (tU<1.0) 
					{ 
						x2 = x1 + tU*dx;//通过n求得裁剪后的p2端点 
						y2 = y1 + tU*dy;
					} 
					if (tL>0.0)
					{ 
						x1 = x1 + tL*dx;//通过m求得裁剪后的p1端点 
						y1 = y1 + tL*dy;
					} 
					glBegin(GL_LINES); 
					glColor4f (1.0, 0.0, 0.0, 1.0); 
					glVertex2f( x1, y1); // clipped line startpoint 
					glVertex2f( x2, y2); // clipped line endpoint 
					glEnd();
				} 
		} 
 
}
 
void display(void)
 {
    glClear(GL_COLOR_BUFFER_BIT);
 
	printf("请分别输入矩形的左右下上边界：\n");
	scanf("%f%f%f%f",&xmin,&xmax,&ymin,&ymax);
    glColor4f (1.0, 1.0, 0.0, 0.75);
	glBegin(GL_POLYGON);
	glVertex2f( xmin, ymin); // Bottom Left
	glVertex2f( xmax, ymin); // Bottom Left
	glVertex2f( xmax, ymax); // Bottom Right
	glVertex2f( xmin, ymax); // Bottom Right
	glEnd();
 
   myclip();
    glFlush();
}
 
 
/*  Main Loop
 *  Open window with initial window size, title bar, 
 *  RGBA display mode, and handle input events.
 */
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
   //define size and the relative positon of the applicaiton window on the display
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
 	//init the defined window with "argv[1]" as topic showed on the top the window
   glutCreateWindow (argv[0]);
	// opengl setup
   myinit ();
 
	//define callbacks
   glutDisplayFunc(display); 
   glutReshapeFunc(myReshape);
   //enter the loop for display
   glutMainLoop();
 
	return 1;
}
