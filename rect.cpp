/*¼òµ¥¾ØÐÎ*/ 
#include "func.h"

void Initial(){
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
void drawRect(int argc, char* argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400,300);
	glutInitWindowPosition(100,120);
	glutCreateWindow("¾ØÐÎ");
	glutDisplayFunc(Display);
	Initial();
	glutMainLoop();
}

