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

	 glutInit(&argc, argv);  //��ʼ��GLUT�⣻
     glutInitWindowSize(800, 600);  //������ʾ���ڴ�С
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  //������ʾģʽ����ע��˫���壩
     glutCreateWindow("��껭��С������ʾ"); // ������ʾ����
      Myinit();
       glutDisplayFunc(Display);  //ע����ʾ�ص�����
    glutMouseFunc(myMouse);    //ע����갴ť�ص�����
    glutMotionFunc(myMotion);  //ע������ƶ��ص�����
    glutReshapeFunc(Reshape);  //ע�ᴰ�ڸı�ص�����
       glutMainLoop();  //�����¼�����ѭ��
      return 0;
}

void Myinit(void)
{
glClearColor(0.0,0.0,0.0,0.0);
glLineWidth(3.0);
}

//��Ⱦ�����ӳ���--------------------------------------------------------------------------
void Display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);   //ˢ����ɫ��������
	drawlines();  //�����ӳ���
    glutSwapBuffers();  //˫�����ˢ��ģʽ��
}

//-----------------------------------------------
void Reshape(int w, int h)  //���ڸı�ʱ�Զ���ȡ��ʾ���ڵĿ�w�͸�h
{
   glMatrixMode(GL_PROJECTION);  //ͶӰ����ģʽ
   glLoadIdentity();     //�����ջ���
   glViewport(0, 0, w, h);  //����������С
   gluOrtho2D(0, w, 0, h);   //���òü����ڴ�С
   ww=w;
   hh=h;
}


//��갴ť��Ӧ�¼�..
void myMouse(int button,int state,int x,int y)
{
	if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
	{
	   line[k][0]=x;   //�߶����x����
	   line[k][1]=hh-y;  //�߶��յ�y����
	}

	if(button==GLUT_LEFT_BUTTON&&state==GLUT_UP)
	{
			line[k][2]=x;   //�߶����x����
			line[k][3]=hh-y;   //�߶��յ�y����
			k++;
		glutPostRedisplay();
	 }
}

//����ƶ�ʱ�������ƶ��е�����-----------------------------------------------------
void myMotion(int x,int y)
{
   	  //get the line's motion point
		line[k][2]=x;   //��̬�յ��x����
		line[k][3]=hh-y;  //��̬�յ��y����
	glutPostRedisplay();
}

//�����ӳ���
void  drawlines()
{
	   for(int i=0;i<=k;i++) //********
		{
		    glRectd(line[i][0],line[i][1],line[i][2],line[i][3]);
		    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); //�߿�ģʽ
		    glLineWidth(2.0); //�����߿�
		}
}
