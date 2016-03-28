#include <windows.h>
#include <GL/glut.h>

#define N 1000       //maximum line numbers
int ww,hh;     // for display window width and height
int line[N][4], k=0;  //for line's endpoint coordinates and line number

void Myinit(void);
void Reshape(int w, int h);
void myMouse(int button,int state,int x,int y);
void myMotion(int x,int y);
void Display(void);
void  drawlines();

int main()
{

	char *argv[] = {"hello ", " "};
	int argc = 2; // must/should match the number of strings in argv

	 glutInit(&argc, argv);  //初始化GLUT库；
     glutInitWindowSize(800, 600);  //设置显示窗口大小
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  //设置显示模式；（注意双缓冲）
     glutCreateWindow("鼠标画线小程序演示"); // 创建显示窗口
      Myinit();
       glutDisplayFunc(Display);  //注册显示回调函数
    glutMouseFunc(myMouse);    //注册鼠标按钮回调函数
    glutMotionFunc(myMotion);  //注册鼠标移动回调函数
    glutReshapeFunc(Reshape);  //注册窗口改变回调函数
       glutMainLoop();  //进入事件处理循环
      return 0;
}

void Myinit(void)
{
glClearColor(0.0,0.0,0.0,0.0);
glLineWidth(3.0);
}

//渲染绘制子程序--------------------------------------------------------------------------
void Display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);   //刷新颜色缓冲区；
	drawlines();  //画线子程序；
    glutSwapBuffers();  //双缓冲的刷新模式；
}

//-----------------------------------------------
void Reshape(int w, int h)  //窗口改变时自动获取显示窗口的宽w和高h
{
   glMatrixMode(GL_PROJECTION);  //投影矩阵模式
   glLoadIdentity();     //矩阵堆栈清空
   glViewport(0, 0, w, h);  //设置视区大小
   gluOrtho2D(0, w, 0, h);   //设置裁剪窗口大小
   ww=w;
   hh=h;
}


//鼠标按钮响应事件..
void myMouse(int button,int state,int x,int y)
{
	if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
	{
	   line[k][0]=x;   //线段起点x坐标
	   line[k][1]=hh-y;  //线段终点y坐标
	}

	if(button==GLUT_LEFT_BUTTON&&state==GLUT_UP)
	{
			line[k][2]=x;   //线段起点x坐标
			line[k][3]=hh-y;   //线段终点y坐标
			k++;
		glutPostRedisplay();
	 }
}

//鼠标移动时获得鼠标移动中的坐标-----------------------------------------------------
void myMotion(int x,int y)
{
   	  //get the line's motion point
		line[k][2]=x;   //动态终点的x坐标
		line[k][3]=hh-y;  //动态终点的y坐标
	glutPostRedisplay();
}

//画线子程序
void  drawlines()
{
	   for(int i=0;i<=k;i++) //********
		{
		    glRectd(line[i][0],line[i][1],line[i][2],line[i][3]);
		    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); //线框模式
		    glLineWidth(2.0); //设置线宽
		}
}
