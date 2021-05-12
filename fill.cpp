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
 

class tile    // 基于open gl 的坐标系
{
public:
	enum _toolEnum{_sideLength=10};             // 边长
	
    tile(unsigned int x=0,unsigned int y=0):_x(x),_y(y)
	{
	    _state = 0;
	}
 
	void draw()
	{
	//  画出初始tile(根据不同_state,用不同的颜色)
    //  glClear(GL_COLOR_BUFFER_BIT);
 
		if (_state == 0) // 无色
		{
			glColor3f(255 ,255 ,255);
		
		}
		else if(_state == 1) // 红色
		{
			glColor3f(255,0 ,0);
		
		}
		else if(_state == 2) // 绿色
		{
			glColor3f(0 ,255 ,0);
		}
 
		glBegin(GL_POINTS);
		glVertex2i(_x*20+10,_y*20+10);
        glEnd();
	    glFlush();
	}
 
	inline void op_side()    // 设置成边界红色  
	{ 
		_state = 1;
		draw();
	}
	inline void op_padding() // 设置成填充 绿色
	{
		_state = 2;
		draw();
	}
 
public:
	unsigned int _x; // 瓷砖的横向索引
	unsigned int _y; // 瓷砖的纵向索引
	int _state; // 0代表无色初始状态，1代表红色边框 ，2代表绿色内填充容
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
				tmpVec.push_back(tile(j,i));  // 注意是 j,i 
				cout<<j<<","<<i<<"\t";
			}
			_vecTile.push_back(tmpVec);
			cout<<endl;
		}
	}
 
	void recursive_pad(GLint index_X, GLint index_Y) // 参数是索引
	{
		// 在这计算是哪个为种子点。。
 
		if(index_X<0||index_Y<0||index_X>=20||index_Y>=20)
		{
			return ;
		}
 
		if ((_vecTile[index_Y][index_X])._state == 0 )
		{
			(_vecTile[index_Y][index_X]).op_padding();  // 注意顺序
			// 对上方的砖块递归填充
			recursive_pad(index_X,index_Y+1);
			// 对下方的砖块递归填充
			recursive_pad(index_X,index_Y-1);
			// 对左方的砖块递归填充
			recursive_pad(index_X-1,index_Y);
			// 对右方的砖块递归填充
		    recursive_pad(index_X+1,index_Y);
		}
	}
	// 以下注释仅仅是参考扫描法的栈实现，但是我用的依然是递归实现
	/*
	扫描线种子填充算法可由下列四个步骤实现：
	(1) 初始化一个空的栈用于存放种子点，将种子点(x, y)入栈；
	(2) 判断栈是否为空，如果栈为空则结束算法，否则取出栈顶元素作为当前扫描线的种子点(x, y)，y是当前的扫描线；
	(3) 从种子点(x, y)出发，沿当前扫描线向左、右两个方向填充，直到边界。分别标记区段的左、右端点坐标为xLeft和xRight；
	(4) 分别检查与当前扫描线相邻的y - 1和y + 1两条扫描线在区间[xLeft, xRight]中的像素，从xLeft开始向xRight方向搜索，
	若存在非边界且未填充的像素点，则找出这些相邻的像素点中最右边的一个，并将其作为种子点压入栈中，然后返回第（2）步；*/
	
 
	void scanning_pad(GLint index_X, GLint index_Y)
	{
		// 向种子点index_Y这一行左右填充
		if (index_X<0||index_X>=20||index_Y<0||index_Y>=20 || _vecTile[index_Y][index_X]._state == 1 )
		{
			return ;
		}
		int left = index_X;
		int right = index_X; // 这边出错！！！！
 
		while ( left>=0  &&  _vecTile[index_Y][left]._state!=1)  // 别忘记访问容器前得先判断索引是否是合法的
		{
			// 或许还得稍微过滤下已经绿色的
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
		// 找正上方和正下方的右种子点
 
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
			scanning_pad(up_may_seed_x,index_Y+1);    // 对上面的种子点进行扫描递归处理
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
			scanning_pad(down_may_seed_x,index_Y-1);  // 对下面的种子点进行扫描递归处理
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
 
	unsigned int _hTileNum;   // _hTileNum 是横向的块的个数
	unsigned int _vTileNum;   // _vTileNum 是纵向的块的个数
 
	vector<vector<tile> > _vecTile;//容器vector保存对象好于对象指针~ 因为保存对象的话操作的就是栈上的内存，而指针的话就操作堆上的内存，开销大了。  这样想法是不是错误的？ 
//	stack<tile> _stackTile;
};
       
void init(void);
 
void displayFcn(void);
 
void plotpoint(GLint x, GLint y);
 
void mouse(GLint button, GLint action, GLint x,GLint y);
 
tileLayer g_tileLayer;// 全局对象

void init(void)
{
	glClearColor(1.0,1.0, 1.0, 1.0);   // 重视这句话
	
	glMatrixMode(GL_PROJECTION);//设置投影矩阵
	gluOrtho2D(0 ,400, 0 ,400);//二维视景区域
	
	glColor3f(1.0,0.0,0.0);
	glPointSize(13.0);//点的大小
}
void plotpoint(GLint x, GLint y)
{
	// 先计算是二维容器里的哪个tile，然后这个tile调用边界op
	unsigned int index_X=0,index_Y=0; 
	index_X=x/20;
	index_Y=y/20;
 
    (g_tileLayer._vecTile[index_Y][index_X]).op_side() ;    // 注意顺序
 
}
void displayFcn(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(0 ,0 ,0);
	glBegin(GL_LINES);
	for (int i=0 ;i<=HEIGHT/SUBHEIGHT ;i++)  // 画横线
	{
		glVertex2d(0 ,i*SUBHEIGHT);
		glVertex2d(WIDTH ,i*SUBHEIGHT);
	}
	
	for (int i=0 ;i<=WIDTH/SUBWIDTH ;i++)    // 画竖线
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
		// 执行算法！！
		unsigned int index_X=0,index_Y=0; 
		index_X=x/20;
     	index_Y=(400-y)/20;
 
		//-----------------------
		//  在这边切换2种实现算法,只要注释掉其中一个调用就行了
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
