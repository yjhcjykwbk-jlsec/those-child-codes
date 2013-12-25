#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
// 派生类CubeView的定义
class CubeView : public Fl_Gl_Window {
public:
double size; // 定义小立方体的大小，供glScalef（）函数使用
// 构造函数，派生自Fl_Gl_Window，定义窗口大小和标题
CubeView(int x=0,int y=0,int w=1,int h=1,const char *l=0);
// 设置和取得垂直方向的旋转角度，供组件标尺调用
void v_angle(float angle){vAng=angle;};
float v_angle(){return vAng;};
// 设置和取得水平方向的旋转角度，供组件标尺调用
void h_angle(float angle){hAng=angle;};
float h_angle(){return hAng;};
// 设置水平和垂直方向的偏移量
void panx(float x){xshift=x;};
void pany(float y){yshift=y;};

void draw();
private:
void drawCube();
float vAng,hAng;
float xshift,yshift;
float boxv0[3];float boxv1[3];
float boxv2[3];float boxv3[3];
float boxv4[3];float boxv5[3];
float boxv6[3];float boxv7[3];
};

// 构造函数的定义
CubeView::CubeView(int x,int y,int w,int h,const char *l)
: Fl_Gl_Window(x,y,w,h,l)
{
// 设置变换初值
vAng = 0.0;
hAng=0.0;
size=10.0;
// 设置小立方体顶点参数
boxv0[0] = -0.5; boxv0[1] = -0.5; boxv0[2] = -0.5;
boxv1[0] = 0.5; boxv1[1] = -0.5; boxv1[2] = -0.5;
boxv2[0] = 0.5; boxv2[1] = 0.5; boxv2[2] = -0.5;
boxv3[0] = -0.5; boxv3[1] = 0.5; boxv3[2] = -0.5;
boxv4[0] = -0.5; boxv4[1] = -0.5; boxv4[2] = 0.5;
boxv5[0] = 0.5; boxv5[1] = -0.5; boxv5[2] = 0.5;
boxv6[0] = 0.5; boxv6[1] = 0.5; boxv6[2] = 0.5;
boxv7[0] = -0.5; boxv7[1] = 0.5; boxv7[2] = 0.5;
};

void CubeView::drawCube() {
// 绘制一个半透明的立方体
#define ALPHA 0.5
glShadeModel(GL_FLAT);
// 用不同的颜色绘制六个面
glBegin(GL_QUADS);
glColor4f (0.0, 0.0, 1.0, ALPHA );
glVertex3fv ( boxv0 ); glVertex3fv ( boxv1 ); glVertex3fv ( boxv2 ); glVertex3fv( boxv3 );

glColor4f(1.0, 1.0, 0.0, ALPHA);
glVertex3fv ( boxv0 ); glVertex3fv ( boxv4 ); glVertex3fv ( boxv5 ); glVertex3fv ( boxv1 );

glColor4f(0.0, 1.0, 1.0, ALPHA);
glVertex3fv ( boxv2 ); glVertex3fv ( boxv6 ); glVertex3fv ( boxv7 ); glVertex3fv ( boxv3 );

glColor4f(1.0, 0.0, 0.0, ALPHA);
glVertex3fv ( boxv4 ); glVertex3fv ( boxv5 ); glVertex3fv ( boxv6 ); glVertex3fv ( boxv7 );

glColor4f(1.0, 0.0, 1.0, ALPHA);
glVertex3fv ( boxv0 ); glVertex3fv ( boxv3 ); glVertex3fv ( boxv7 ); glVertex3fv ( boxv4 );

glColor4f(0.0, 1.0, 0.0, ALPHA);
glVertex3fv ( boxv1 ); glVertex3fv ( boxv5 ); glVertex3fv ( boxv6 ); glVertex3fv ( boxv2 );
glEnd();

// 绘制立方体的轮廓线，一共12条
glColor3f(1.0, 1.0, 1.0);
glBegin(GL_LINES);
glVertex3fv ( boxv0 ); glVertex3fv ( boxv1 );
glVertex3fv ( boxv1 ); glVertex3fv ( boxv2 );
glVertex3fv ( boxv2 ); glVertex3fv ( boxv3 );
glVertex3fv ( boxv3 ); glVertex3fv ( boxv0 );
glVertex3fv ( boxv4 ); glVertex3fv ( boxv5 );
glVertex3fv ( boxv5 ); glVertex3fv ( boxv6 );
glVertex3fv ( boxv6 ); glVertex3fv ( boxv7 );
glVertex3fv ( boxv7 ); glVertex3fv ( boxv4 );
glVertex3fv ( boxv0 ); glVertex3fv ( boxv4 );
glVertex3fv ( boxv1 ); glVertex3fv ( boxv5 );
glVertex3fv ( boxv2 ); glVertex3fv ( boxv6 );
glVertex3fv ( boxv3 ); glVertex3fv ( boxv7 );
glEnd();
};

void CubeView::draw() {
if (!valid ( ) ) {
//valid（）当窗口大小改变时改变，导致这一部分内容被执行，重新设置窗口
glLoadIdentity();
glViewport(0,0,w(),h());
glOrtho(-10,10,-10,10,-20000,10000);
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
glPushMatrix ( );
// 变换。参数绘被外部函数修改
glTranslatef ( xshift, yshift, 0);
glRotatef ( hAng, 0, 1, 0 ); glRotatef ( vAng, 1, 0, 0 );
glScalef ( float ( size ), float ( size ) , float ( size ) );
// 绘制立方体
drawCube ( );
glPopMatrix ( );
};
