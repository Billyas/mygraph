// 彩色三角形图形 
#include "func.h" 

// 初始化参数
void init2() {
    glClearColor(0.1, 0.1, 0.4, 0.0);
    glShadeModel(GL_SMOOTH);
}
 
// 绘图回调函数
void display2() {

    // 清除之前帧数据
    glClear(GL_COLOR_BUFFER_BIT);
 
    // 绘制三角形
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex3f(-1, -1, -5);
    glColor3f(0, 1, 0);
    glVertex3f(1, -1, -5);
    glColor3f(0, 0, 1);
    glVertex3f(0, 1, -5);
    glEnd();
    // 执行绘图命令
    glFlush();
}
 
// 窗口大小变化回调函数
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 0.1, 100000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
 
void drawTri(int argc, char * argv[]) {
    // 初始化显示模式
    glutInit(&argc, const_cast<char **>(argv));
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
 
    // 初始化窗口
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
 
    init2();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display2);
 
    // 开始主循环绘制
    glutMainLoop();

}

