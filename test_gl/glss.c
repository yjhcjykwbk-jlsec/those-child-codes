#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 定义允许的最大多边形数、多边形允许的最大顶点数和可镶嵌的最大三角形数*/
#define MAX_POINTS 256
#define MAX_CONTOURS 32
#define MAX_TRIANGLES 256

/* 用于菜单选项的枚举类型 */
typedef enum{ QUIT, TESSELATE, CLEAR } menu_entries;
static int mode;
/* 定义绘制模式的枚举类型 */
typedef enum{ DEFINE, TESSELATED } mode_type;
static int menu;
static GLsizei width, height; /* OpenGL窗口的大小 */
static GLuint contour_cnt; /* 记录多边形数目 */
static GLuint triangle_cnt; /* 记录三角形数目 */
static GLuint list_start; /* 用于显示列表 */

/* 多边形结构 */
static struct {
GLfloat p[MAX_POINTS][2];
GLuint point_cnt;
} contours [ MAX_CONTOURS ] ;

/* 三角形结构 */
static struct {
GLsizei no;
GLfloat p [3] [2];
GLclampf color [3] [3];
} triangles [ MAX_TRIANGLES ];

/* 窗口大小改变时，设定width和height值，用于重新绘制网格 */
void set_screen_wh ( GLsizei w, GLsizei h )
{ width = w; height = h; }

void tesse ( void )
{ /* 镶嵌函数，调用gluTess* 函数实现*/ }

/* 对点击鼠标左键事件的响应函数：更新当前多边形顶点数组，并重新绘制 */
void left_down ( int x1, int y1 )
{
GLfloat P[2];
GLuint point_cnt;

/* 将GLUT窗口坐标变换为GL坐标：前者（0，0）在左上角而后者在左下角*/
P[0] = x1; P[1] = height - y1;

/* 更新顶点数据 */
point_cnt = contours [ contour_cnt ] . point_cnt;
contours [ contour_cnt ] . p [ point_cnt ][ 0 ] = P [ 0 ];
contours [ contour_cnt ]. p [ point_cnt ] [ 1 ] = P [ 1 ];

/* 绘制新添加的边，若为第一个点，则绘制一个点 */
glBegin ( GL_LINES );
if ( point_cnt ) {
glVertex2fv ( contours[contour_cnt].p[point_cnt-1] );
glVertex2fv ( P );
}
else {
glVertex2fv ( P );
glVertex2fv ( P );
}
glEnd();
glFinish();
contours[contour_cnt].point_cnt++;
}

/* 点击鼠标中键的响应事件，有些系统可以用同时点击左右键模拟：结束一个多边形 */
void middle_down( int x1, int y1 )
{
GLuint point_cnt;
(void) x1;
(void) y1;
point_cnt = contours[contour_cnt].point_cnt;
/* 连接起始点和最后一个点，构成一个完整的多边形 */
if ( point_cnt > 2 )
{
glBegin( GL_LINES );
glVertex2fv( contours[contour_cnt].p[0] );
glVertex2fv( contours[contour_cnt].p[point_cnt-1] );
contours[contour_cnt].p[point_cnt][0] = -1;
glEnd();
glFinish();
contour_cnt++;
contours[contour_cnt].point_cnt = 0;
}
}

/* 处理鼠标响应的函数，根据按键的类型调用不同的函数：左键和中键。 */
void mouse_clicked( int button, int state, int x, int y )
{
/* 将OpenGL的像素坐标换为背景的网格坐标，背景网格为边长为10的小正方形 */
x -= x%10;
y -= y%10;
switch ( button ) {
case GLUT_LEFT_BUTTON: /* GLUT发现左键被点击 */
if ( state == GLUT_DOWN ) {
left_down( x, y );
}
break;
case GLUT_MIDDLE_BUTTON: /* 中键被点击 */
if ( state == GLUT_DOWN ) {
middle_down( x, y );
}
break;
}
}
/* OpenGL绘制函数，有两种模式 */
void display( void )
{
GLuint i,j;
GLuint point_cnt;

glClear( GL_COLOR_BUFFER_BIT );
switch ( mode )
{
case DEFINE: /* 多边形定义阶段 */
/* 绘制网格，单个网格大小为10像素，网格数目取决于OpenGL窗口大小 */
glColor3f ( 0.6, 0.5, 0.5 );
glBegin ( GL_LINES );
for ( i = 0 ; i < width ; i += 10 ){
for ( j = 0 ; j < height ; j += 10 ) {
glVertex2i ( 0, j );
glVertex2i ( width, j );
glVertex2i ( i, height );
glVertex2i ( i, 0 );
}
}
/* 绘制多边形 */
glColor3f( 1.0, 1.0, 0.0 );
for ( i = 0 ; i <= contour_cnt ; i++ ) {
point_cnt = contours[i].point_cnt;
glBegin( GL_LINES );
switch ( point_cnt ) {
case 0:
break;
case 1:
glVertex2fv ( contours[i].p[0] );
glVertex2fv ( contours[i].p[0] );
break;
case 2:
glVertex2fv( contours[i].p[0] );
glVertex2fv( contours[i].p[1] );
break;
default:
--point_cnt;
for ( j = 0 ; j < point_cnt ; j++ ) {
glVertex2fv ( contours [ i ]. p [ j ] );
glVertex2fv ( contours [ i ] .p [ j+1 ] );
}
if ( contours [ i ].p [ j+1 ] [ 0 ] == -1 )
{
glVertex2fv ( contours [ i ]. p [ 0 ] );
glVertex2fv ( contours [ i ] .p [ j ] );
}
break;
}
glEnd();
}
glFinish();
break;

case TESSELATED: /* 绘制镶嵌后的多边形，显示列表由函数tesse（）给出 */
glColor3f( 0.7, 0.7, 0.0 );
glCallList( list_start );
glLineWidth( 2.0 );
glCallList( list_start + 1 );
glLineWidth( 1.0 );
glFlush();
break;
}
glColor3f( 1.0, 1.0, 0.0 );
}

/* 菜单选项clear的响应函数，将所有变量清零，绘制模式设为DEFINE */
void clear( void )
{
contour_cnt = 0;
contours[0].point_cnt = 0;
triangle_cnt = 0;
mode = DEFINE;
glDeleteLists( list_start, 2 );
list_start = 0;
}

/* 菜单选项quit的响应函数，退出程序 */
void quit( void )
{
exit( 0 );
}

/* 定义菜单的响应函数 */
void menu_selected( int entry )
{
switch ( entry ) {
case CLEAR:
clear ( );
break;
case TESSELATE:
tesse ( );
break;
case QUIT:
quit ( );
break;
}
/* 选择菜单后重绘OpenGL窗口 */
glutPostRedisplay();
}

/* 定义快捷键响应函数 */
void key_pressed( unsigned char key, int x, int y )
{
/* 在此例子中，不需要用表明鼠标位置的变量x和y */
( void ) x; ( void ) y;
/* 针对不同按键，定义动作 */
switch ( key ) {
case 'c':
case 'C':
clear();
break;
case 't':
case 'T':
tesse();
break;
case 'q':
case 'Q':
quit();
break;
}
/* 按键后重绘窗口 */
glutPostRedisplay();
}

/* 执行一些程序的初始化过程 */
void myinit( void )
{
/* 设置窗口背景颜色*/
glClearColor( 0.4, 0.4, 0.4, 0.0 );
glShadeModel( GL_FLAT );
glPolygonMode( GL_FRONT, GL_FILL );

/* 创建一个菜单，并定义菜单项及该菜单对应的响应函数 */
menu = glutCreateMenu( menu_selected );
glutAddMenuEntry( "clear", CLEAR );
glutAddMenuEntry( "tesselate", TESSELATE );
glutAddMenuEntry( "quit", QUIT );
/* 定义菜单动作方式：点击右键弹出 */
glutAttachMenu( GLUT_RIGHT_BUTTON );

/* 注册鼠标事件响应函数 */
glutMouseFunc( mouse_clicked );
/* 注册键盘事件响应函数 */
glutKeyboardFunc( key_pressed );

contour_cnt = 0;
mode = DEFINE;
}

/* 定义窗口大小改变时的响应 */
static void reshape( GLsizei w, GLsizei h )
{
glViewport( 0, 0, w, h );

glMatrixMode( GL_PROJECTION );
glLoadIdentity();
glOrtho( 0.0, (GLdouble)w, 0.0, (GLdouble)h, -1.0, 1.0 );
glMatrixMode( GL_MODELVIEW );
glLoadIdentity();
set_screen_wh( w, h );
}

int main( int argc, char **argv )
{
/* 创建窗口 */
glutInit ( & argc, argv );
glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB );
glutInitWindowSize ( 400, 400 );
glutCreateWindow( argv[0] );

myinit();

glutDisplayFunc( display );
glutReshapeFunc( reshape );

glutMainLoop();
return 0;
}
