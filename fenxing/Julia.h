#pragma once
#include"stdafx.h"
#include"structures.h"
#include"functions.h"
/////////////////函数声明///////////////////////
int JuliaView(int wid, int hei);//Julia集绘制窗体
int J_Initialize(Fractal*julia, int wid, int hei);//Julia集窗体初始化
int J_Init_stats(Fractal*julia, int wid, int hei);//Julia集-初始化数据
int J_Init_buttons(Fractal*julia);//Julia集按钮初始化设定
int J_Init_btsp(Fractal*julia);//Julia集确定按钮规格和位置
//////////各种按钮数值设定///////////
int J_Init_colorbar(Button*button);
int J_Init_xm(Button*button);
int J_Init_xn(Button*button);
int J_Init_ym(Button*button);
int J_Init_yn(Button*button);
int J_Init_ab(Button*button);
int J_Init_paint(Button*button);
int J_Init_clear(Button*button);
int J_Init_save(Button*button);
int J_Init_back(Button*button);
int J_Init_quit(Button*button);
//////////各种按钮数值设定/////////////
int J_Init_graph(Fractal*julia);//Julia集初始化界面
int J_Button_renew(Fractal*julia);//Fractal刷新按钮
int J_Process(Fractal*julia);//Julia集绘制过程
int J_Botton_Management(button_type xxx, Fractal*julia);//Julia集按钮处理
int J_IsPaintZone(Fractal*julia);//Julia集中操作是否在绘图区内
int J_PaintZone(Fractal*julia);//Fractal绘图区操作
int J_Enlarge(Fractal*julia);//Julia集放大操作
double J_View_k(Fractal*julia);//获得缩放比
int J_View_refresh(Fractal*julia);//刷新Julia集预览图
int J_View_clear(Fractal*julia);//清空Julia集预览图
int J_Enlarge_tempxy(Fractal*julia);//确定缩放后的x,y范围
int J_Paint_enlarge(Fractal*julia);//加载缩放后的坐标范围
/////////////////Fractal按钮事件///////////////////
int J_Button_colorbar(Fractal*julia);
int J_Button_xm(Fractal*julia);
int J_Button_xn(Fractal*julia);
int J_Button_ym(Fractal*julia);
int J_Button_yn(Fractal*julia);
int J_Button_ab(Fractal*julia);
int J_Button_paint(Fractal*julia);
int J_Button_clear(Fractal*julia);
int J_Button_save(Fractal*julia);
int J_Button_back(Fractal*julia);
int J_Button_quit(Fractal*julia);
/////////////////Fractal按钮事件///////////////////
int J_Paint(Fractal*julia);//Julia集绘制过程-绘图
int J_Analyser(Fractal*julia, int*paint);//Julia集绘图-分析
int J_Iterator(long double a, long double b, long double x, long double y, int ColorCount);//Julia集迭代器
int J_CheckIndex(Fractal*julia, double*dx, double*dy);//Fractal检查参数是否合法
int J_Show(Fractal*julia, int*paint);//Julia集绘图-显示
int J_Paint2(Fractal*julia);//Julia集更细致的绘制
int J_Analyser2(Fractal*julia, float*paint);//Julia集更细致的绘制-分析
float J_Iterator2(long double a, long double b, long double x, long double y, int ColorCount);//Julia集更细致的迭代器
int J_Show2(Fractal*julia, float*paint);//Julia集更细致的绘制-显示
int J_Finish(Fractal*julia);//Julia集窗体-结束
int J_Freer(Fractal*julia);//Julia集结束-释放