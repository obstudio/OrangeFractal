#pragma once
#include"stdafx.h"
#include"structures.h"
#include"functions.h"
/*周宇*/
/////////////////函数声明///////////////////////
int gJuliaView(int wid, int hei);//Julia集绘制窗体
int gJ_Initialize(Fractal*gjulia, int wid, int hei);//Julia集窗体初始化
int gJ_Init_stats(Fractal*gjulia, int wid, int hei);//Julia集-初始化数据
int gJ_Init_buttons(Fractal*gjulia);//Julia集按钮初始化设定
int gJ_Init_btsp(Fractal*gjulia);//Julia集确定按钮规格和位置
							   //////////各种按钮数值设定///////////
int gJ_Init_colorbar(Button*button);
int gJ_Init_xm(Button*button);
int gJ_Init_xn(Button*button);
int gJ_Init_ym(Button*button);
int gJ_Init_yn(Button*button);
int gJ_Init_ab(Button*button);
int gJ_Init_paint(Button*button);
int gJ_Init_clear(Button*button);
int gJ_Init_save(Button*button);
int gJ_Init_back(Button*button);
int gJ_Init_quit(Button*button);
//////////各种按钮数值设定/////////////
int gJ_Init_graph(Fractal*gjulia);//Julia集初始化界面
int gJ_Button_renew(Fractal*gjulia);//Fractal刷新按钮
int gJ_Process(Fractal*gjulia);//Julia集绘制过程
int gJ_Botton_Management(button_type xxx, Fractal*julia);//Julia集按钮处理
int gJ_IsPaintZone(Fractal*gjulia);//Julia集中操作是否在绘图区内
int gJ_PaintZone(Fractal*gjulia);//Fractal绘图区操作
int gJ_Enlarge(Fractal*gjulia);//Julia集放大操作
double gJ_View_k(Fractal*gjulia);//获得缩放比
int gJ_View_refresh(Fractal*gjulia);//刷新Julia集预览图
int gJ_View_clear(Fractal*gjulia);//清空Julia集预览图
int gJ_Enlarge_tempxy(Fractal*gjulia);//确定缩放后的x,y范围
int gJ_Paint_enlarge(Fractal*gjulia);//加载缩放后的坐标范围
								   /////////////////Fractal按钮事件///////////////////
int gJ_Button_colorbar(Fractal*gjulia);
int gJ_Button_xm(Fractal*gjulia);
int gJ_Button_xn(Fractal*gjulia);
int gJ_Button_ym(Fractal*gjulia);
int gJ_Button_yn(Fractal*gjulia);
int gJ_Button_ab(Fractal*gjulia);
int gJ_Button_paint(Fractal*gjulia);
int gJ_Button_clear(Fractal*gjulia);
int gJ_Button_save(Fractal*gjulia);
int gJ_Button_back(Fractal*gjulia);
int gJ_Button_quit(Fractal*gjulia);
/////////////////Fractal按钮事件///////////////////
int gJ_Paint(Fractal*gjulia);//Julia集绘制过程-绘图
int gJ_Analyser(Fractal*gjulia, int*paint);//Julia集绘图-分析
int gJ_Iterator(long double a, long double b, long double x, long double y, int ColorCount);//Julia集迭代器
int gJ_CheckIndex(Fractal*gjulia, double*dx, double*dy);//Fractal检查参数是否合法
int gJ_Show(Fractal*gjulia, int*paint);//Julia集绘图-显示
int gJ_Paint2(Fractal*gjulia);//Julia集更细致的绘制
int gJ_Analyser2(Fractal*gjulia, float*paint);//Julia集更细致的绘制-分析
float gJ_Iterator2(long double a, long double b, long double x, long double y, int ColorCount);//Julia集更细致的迭代器
int gJ_Show2(Fractal*gjulia, float*paint);//Julia集更细致的绘制-显示
int gJ_Finish(Fractal*gjulia);//Julia集窗体-结束
int gJ_Freer(Fractal*gjulia);//Julia集结束-释放