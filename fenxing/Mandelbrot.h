#pragma once
#include"stdafx.h"
#include"structures.h"
#include"functions.h"
/////////////////函数声明///////////////////////
int MandelbrotView(int wid, int hei);//Mandelbrot集绘制窗体
int M_Initialize(Fractal*mandelbrot, int wid, int hei);//Mandelbrot集窗体初始化
int M_Init_stats(Fractal*mandelbrot, int wid, int hei);//Mandelbrot集-初始化数据
int M_Init_buttons(Fractal*mandelbrot);//Mandelbrot集按钮初始化设定
int M_Init_btsp(Fractal*mandelbrot);//Mandelbrot集确定按钮规格和位置
							   //////////各种按钮数值设定///////////
int M_Init_colorbar(Button*button);
int M_Init_xm(Button*button);
int M_Init_xn(Button*button);
int M_Init_ym(Button*button);
int M_Init_yn(Button*button);
int M_Init_ab(Button*button);
int M_Init_paint(Button*button);
int M_Init_clear(Button*button);
int M_Init_save(Button*button);
int M_Init_back(Button*button);
int M_Init_quit(Button*button);
//////////各种按钮数值设定/////////////
int M_Init_graph(Fractal*mandelbrot);//Mandelbrot集初始化界面
int M_Button_renew(Fractal*mandelbrot);//Fractal刷新按钮
int M_Process(Fractal*mandelbrot);//Mandelbrot集绘制过程
int M_Botton_Management(button_type xxx, Fractal*mandelbrot);//Mandelbrot集按钮处理
int M_IsPaintZone(Fractal*mandelbrot);//Mandelbrot集中操作是否在绘图区内
int M_PaintZone(Fractal*mandelbrot);//Fractal绘图区操作
int M_Enlarge(Fractal*mandelbrot);//Mandelbrot集放大操作
double M_View_k(Fractal*mandelbrot);//获得缩放比
int M_View_refresh(Fractal*mandelbrot);//刷新Mandelbrot集预览图
int M_View_clear(Fractal*mandelbrot);//清空Mandelbrot集预览图
int M_Enlarge_tempxy(Fractal*mandelbrot);//确定缩放后的x,y范围
int M_Paint_enlarge(Fractal*mandelbrot);//加载缩放后的坐标范围
								   /////////////////Fractal按钮事件///////////////////
int M_Button_colorbar(Fractal*mandelbrot);
int M_Button_xm(Fractal*mandelbrot);
int M_Button_xn(Fractal*mandelbrot);
int M_Button_ym(Fractal*mandelbrot);
int M_Button_yn(Fractal*mandelbrot);
int M_Button_ab(Fractal*mandelbrot);
int M_Button_paint(Fractal*mandelbrot);
int M_Button_clear(Fractal*mandelbrot);
int M_Button_save(Fractal*mandelbrot);
int M_Button_back(Fractal*mandelbrot);
int M_Button_quit(Fractal*mandelbrot);
/////////////////Fractal按钮事件///////////////////
int M_Paint(Fractal*mandelbrot);//Mandelbrot集绘制过程-绘图
int M_Analyser(Fractal*mandelbrot, int*paint);//Mandelbrot集绘图-分析
int M_Iterator(long double a, long double b, long double x, long double y, int ColorCount);//Mandelbrot集迭代器
int M_CheckIndex(Fractal*mandelbrot, double*dx, double*dy);//Fractal检查参数是否合法
int M_Show(Fractal*mandelbrot, int*paint);//Mandelbrot集绘图-显示
int M_Paint2(Fractal*mandelbrot);//Mandelbrot集更细致的绘制
int M_Analyser2(Fractal*mandelbrot, float*paint);//Mandelbrot集更细致的绘制-分析
float M_Iterator2(long double a, long double b, long double x, long double y, int ColorCount);//Mandelbrot集更细致的迭代器
int M_Show2(Fractal*mandelbrot, float*paint);//Mandelbrot集更细致的绘制-显示
int M_Finish(Fractal*mandelbrot);//Mandelbrot集窗体-结束
int M_Freer(Fractal*mandelbrot);//Mandelbrot集结束-释放
