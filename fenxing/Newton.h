#pragma once
#pragma once
#include"stdafx.h"
#include"structures.h"
#include"functions.h"
/*周宇*/
/////////////////函数声明///////////////////////
int NewtonView(int wid, int hei);//newton集绘制窗体
int N_Initialize(Fractal*newton, int wid, int hei);//newton集窗体初始化
int N_Init_stats(Fractal*newton, int wid, int hei);//newton集-初始化数据
int N_Init_buttons(Fractal*newton);//newton集按钮初始化设定
int N_Init_btsp(Fractal*newton);//newton集确定按钮规格和位置
								//////////各种按钮数值设定///////////
int N_Init_colorbar(Button*button);
int N_Init_xm(Button*button);
int N_Init_xn(Button*button);
int N_Init_ym(Button*button);
int N_Init_yn(Button*button);
int N_Init_ab(Button*button);
int N_Init_paint(Button*button);
int N_Init_clear(Button*button);
int N_Init_save(Button*button);
int N_Init_back(Button*button);
int N_Init_quit(Button*button);
//////////各种按钮数值设定/////////////
int N_Init_graph(Fractal*newton);//newton集初始化界面
int N_Button_renew(Fractal*newton);//Fractal刷新按钮
int N_Process(Fractal*newton);//newton集绘制过程
int N_Botton_Management(button_type xxx, Fractal*julia);//newton集按钮处理
int N_IsPaintZone(Fractal*newton);//newton集中操作是否在绘图区内
int N_PaintZone(Fractal*newton);//Fractal绘图区操作
int N_Enlarge(Fractal*newton);//newton集放大操作
double N_View_k(Fractal*newton);//获得缩放比
int N_View_refresh(Fractal*newton);//刷新newton集预览图
int N_View_clear(Fractal*newton);//清空newton集预览图
int N_Enlarge_tempxy(Fractal*newton);//确定缩放后的x,y范围
int N_Paint_enlarge(Fractal*newton);//加载缩放后的坐标范围
									/////////////////Fractal按钮事件///////////////////
int N_Button_colorbar(Fractal*newton);
int N_Button_xm(Fractal*newton);
int N_Button_xn(Fractal*newton);
int N_Button_ym(Fractal*newton);
int N_Button_yn(Fractal*newton);
int N_Button_ab(Fractal*newton);
int N_Button_paint(Fractal*newton);
int N_Button_clear(Fractal*newton);
int N_Button_save(Fractal*newton);
int N_Button_back(Fractal*newton);
int N_Button_quit(Fractal*newton);
/////////////////Fractal按钮事件///////////////////
int N_Paint(Fractal*newton);//newton集绘制过程-绘图
int N_Analyser(Fractal*newton, int*paint);//newton集绘图-分析
int N_Iterator(long double a, long double b, long double x, long double y, int ColorCount);//newton集迭代器
int N_CheckIndex(Fractal*newton, double*dx, double*dy);//Fractal检查参数是否合法
int N_Show(Fractal*newton, int*paint);//newton集绘图-显示
int N_Paint2(Fractal*newton);//newton集更细致的绘制
int N_Analyser2(Fractal*newton, float*paint);//newton集更细致的绘制-分析
float N_Iterator2(long double a, long double b, long double x, long double y, int ColorCount);//newton集更细致的迭代器
int N_Show2(Fractal*newton, float*paint);//newton集更细致的绘制-显示
int N_Finish(Fractal*newton);//newton集窗体-结束
int N_Freer(Fractal*newton);//newton集结束-释放
