#include <iostream>
#include <vector>
#include <stack>
#include <iterator>
#include<windows.h> 
#include<gl/glut.h>
//#include<gl/gl.h>
using namespace std;
 
//
#define  WIDTH      400
#define  HEIGHT     400
#define  SUBWIDTH   20
#define  SUBHEIGHT  20
 

class tile    // ����open gl ������ϵ
{
public:
	enum _toolEnum{_sideLength=10};             // �߳�
	
    tile(unsigned int x=0,unsigned int y=0):_x(x),_y(y)
	{
	    _state = 0;
	}
 
	void draw()
	{
	//  ������ʼtile(���ݲ�ͬ_state,�ò�ͬ����ɫ)
    //  glClear(GL_COLOR_BUFFER_BIT);
 
		if (_state == 0) // ��ɫ
		{
			glColor3f(255 ,255 ,255);
		
		}
		else if(_state == 1) // ��ɫ
		{
			glColor3f(255,0 ,0);
		
		}
		else if(_state == 2) // ��ɫ
		{
			glColor3f(0 ,255 ,0);
		}
 
		glBegin(GL_POINTS);
		glVertex2i(_x*20+10,_y*20+10);
        glEnd();
	    glFlush();
	}
 
	inline void op_side()    // ���óɱ߽��ɫ  
	{ 
		_state = 1;
		draw();
	}
	inline void op_padding() // ���ó���� ��ɫ
	{
		_state = 2;
		draw();
	}
 
public:
	unsigned int _x; // ��ש�ĺ�������
	unsigned int _y; // ��ש����������
	int _state; // 0������ɫ��ʼ״̬��1�����ɫ�߿� ��2������ɫ�������
};
 
 
class tileLayer
{
public:
	tileLayer(unsigned int h=20,unsigned int v=20):_hTileNum(h),_vTileNum(v)
	{
		init();
	}
 
    void init()
	{
		for (int i=0;i<_vTileNum;i++)  
		{
			vector<tile> tmpVec;
			for (int j=0;j<_hTileNum;j++)
			{
				tmpVec.push_back(tile(j,i));  // ע���� j,i 
				cout<<j<<","<<i<<"\t";
			}
			_vecTile.push_back(tmpVec);
			cout<<endl;
		}
	}
 
	void recursive_pad(GLint index_X, GLint index_Y) // ����������
	{
		// ����������ĸ�Ϊ���ӵ㡣��
 
		if(index_X<0||index_Y<0||index_X>=20||index_Y>=20)
		{
			return ;
		}
 
		if ((_vecTile[index_Y][index_X])._state == 0 )
		{
			(_vecTile[index_Y][index_X]).op_padding();  // ע��˳��
			// ���Ϸ���ש��ݹ����
			recursive_pad(index_X,index_Y+1);
			// ���·���ש��ݹ����
			recursive_pad(index_X,index_Y-1);
			// ���󷽵�ש��ݹ����
			recursive_pad(index_X-1,index_Y);
			// ���ҷ���ש��ݹ����
		    recursive_pad(index_X+1,index_Y);
		}
	}
	// ����ע�ͽ����ǲο�ɨ�跨��ջʵ�֣��������õ���Ȼ�ǵݹ�ʵ��
	/*
	ɨ������������㷨���������ĸ�����ʵ�֣�
	(1) ��ʼ��һ���յ�ջ���ڴ�����ӵ㣬�����ӵ�(x, y)��ջ��
	(2) �ж�ջ�Ƿ�Ϊ�գ����ջΪ��������㷨������ȡ��ջ��Ԫ����Ϊ��ǰɨ���ߵ����ӵ�(x, y)��y�ǵ�ǰ��ɨ���ߣ�
	(3) �����ӵ�(x, y)�������ص�ǰɨ��������������������䣬ֱ���߽硣�ֱ������ε����Ҷ˵�����ΪxLeft��xRight��
	(4) �ֱ����뵱ǰɨ�������ڵ�y - 1��y + 1����ɨ����������[xLeft, xRight]�е����أ���xLeft��ʼ��xRight����������
	�����ڷǱ߽���δ�������ص㣬���ҳ���Щ���ڵ����ص������ұߵ�һ������������Ϊ���ӵ�ѹ��ջ�У�Ȼ�󷵻صڣ�2������*/
	
 
	void scanning_pad(GLint index_X, GLint index_Y)
	{
		// �����ӵ�index_Y��һ���������
		if (index_X<0||index_X>=20||index_Y<0||index_Y>=20 || _vecTile[index_Y][index_X]._state == 1 )
		{
			return ;
		}
		int left = index_X;
		int right = index_X; // ��߳���������
 
		while ( left>=0  &&  _vecTile[index_Y][left]._state!=1)  // �����Ƿ�������ǰ�����ж������Ƿ��ǺϷ���
		{
			// ��������΢�������Ѿ���ɫ��
			if (_vecTile[index_Y][left]._state!=2)
			{
				_vecTile[index_Y][left].op_padding();
			}
			left=left-1;
		}
		left=left+1;
 
		while (right<20 && _vecTile[index_Y][right]._state!=1)
		{
			if (_vecTile[index_Y][right]._state!=2)
			{
				_vecTile[index_Y][right].op_padding();
			}	
			right=right+1;
		}
		right=right-1;
		// �����Ϸ������·��������ӵ�
 
		int up_index=left;
		int down_index=left;
 
		int up_may_seed_x=left;
		while (index_Y+1<20&&up_index<=right) 		{
			if ( _vecTile[index_Y+1][up_index]._state==0)
			{
				up_may_seed_x=up_index;
			}
			up_index=up_index+1;
		}
 
		up_index=up_index-1;
		if ( (index_X+1)<20  &&  _vecTile[index_Y+1][up_may_seed_x]._state == 0)
		{
			scanning_pad(up_may_seed_x,index_Y+1);    // ����������ӵ����ɨ��ݹ鴦��
		}
		
 
		int down_may_seed_x=left;
		while (index_Y-1>=0 && down_index<=right )
		{
			if ( _vecTile[index_Y-1][down_index]._state==0)
			{
				down_may_seed_x=down_index;
			}
			down_index=down_index+1;
		}
		down_index=down_index-1;
		if ( (index_Y-1)>=0  &&  _vecTile[index_Y-1][down_may_seed_x]._state == 0 )
		{
			scanning_pad(down_may_seed_x,index_Y-1);  // ����������ӵ����ɨ��ݹ鴦��
		}
	}
 
	void redraw()
	{
		for (int i=0;i<_vTileNum;i++)  
		{
			for (int j=0;j<_hTileNum;j++)
			{
				_vecTile[i][j].draw();
			}
		}
	}
 
	unsigned int _hTileNum;   // _hTileNum �Ǻ���Ŀ�ĸ���
	unsigned int _vTileNum;   // _vTileNum ������Ŀ�ĸ���
 
	vector<vector<tile> > _vecTile;//����vector���������ڶ���ָ��~ ��Ϊ�������Ļ������ľ���ջ�ϵ��ڴ棬��ָ��Ļ��Ͳ������ϵ��ڴ棬�������ˡ�  �����뷨�ǲ��Ǵ���ģ� 
//	stack<tile> _stackTile;
};
       
void init(void);
 
void displayFcn(void);
 
void plotpoint(GLint x, GLint y);
 
void mouse(GLint button, GLint action, GLint x,GLint y);
 
tileLayer g_tileLayer;// ȫ�ֶ���

void init(void)
{
	glClearColor(1.0,1.0, 1.0, 1.0);   // ������仰
	
	glMatrixMode(GL_PROJECTION);//����ͶӰ����
	gluOrtho2D(0 ,400, 0 ,400);//��ά�Ӿ�����
	
	glColor3f(1.0,0.0,0.0);
	glPointSize(13.0);//��Ĵ�С
}
void plotpoint(GLint x, GLint y)
{
	// �ȼ����Ƕ�ά��������ĸ�tile��Ȼ�����tile���ñ߽�op
	unsigned int index_X=0,index_Y=0; 
	index_X=x/20;
	index_Y=y/20;
 
    (g_tileLayer._vecTile[index_Y][index_X]).op_side() ;    // ע��˳��
 
}
void displayFcn(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(0 ,0 ,0);
	glBegin(GL_LINES);
	for (int i=0 ;i<=HEIGHT/SUBHEIGHT ;i++)  // ������
	{
		glVertex2d(0 ,i*SUBHEIGHT);
		glVertex2d(WIDTH ,i*SUBHEIGHT);
	}
	
	for (int i=0 ;i<=WIDTH/SUBWIDTH ;i++)    // ������
	{
		glVertex2d(i*SUBWIDTH ,0);
		glVertex2d(i*SUBWIDTH ,HEIGHT);
	}
 
	glEnd();
    glFlush();
}
void mouse(GLint button, GLint action, GLint x,GLint y)
{
	if (button==GLUT_LEFT_BUTTON && action==GLUT_DOWN)
	{
		plotpoint(x,400-y);
	}
	//glFlush();
	if (button==GLUT_RIGHT_BUTTON && action==GLUT_DOWN)
	{
		// ִ���㷨����
		unsigned int index_X=0,index_Y=0; 
		index_X=x/20;
     	index_Y=(400-y)/20;
 
		//-----------------------
		//  ������л�2��ʵ���㷨,ֻҪע�͵�����һ�����þ�����
		//-----------------------
		g_tileLayer.recursive_pad(index_X,index_Y); 
	//	g_tileLayer.scanning_pad(index_X,index_Y);
	}	
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("mouse");
	
	init();
	glutDisplayFunc(displayFcn);
	glutMouseFunc(mouse);  
	glutMainLoop();

}
