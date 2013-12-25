#include "CubeViewUI.h"
int main(int argc, char **argv) {
// 定义类CubeViewUI的一个实例
CubeView *cvui=new CubeView();
// 设置FLTK窗口显示模式
Fl::visual(FL_DOUBLE|FL_INDEX);
cvui->show();
// 进入消息循环
return Fl::run();
}
