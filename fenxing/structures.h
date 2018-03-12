#pragma once
#include"stdafx.h"
/*许嘉禾*/
enum button_type { jUlia, hElp, cOlorbar, xM, xN, yM, yN, aB, pAint, cLear, sAve, bAck, qUit,  tAn90 };
///////////////结构体定义/////////////////////
struct XYRange {//坐标范围
	double xn;
	double xm;
	double yn;
	double ym;
};
struct User {//用户操作
//鼠标
	MOUSEMSG F_msg;//按下时的鼠标信息
	MOUSEMSG L_msg;//松开时的鼠标信息
};
struct Button {
	int i; int j;//行次、列次
	int x; int y;//位置
	int width; int height;//宽高
	button_type type;//按钮类型
	int IsTriggerd = 0;//是否被按下
};
struct RGB {//RGB颜色
	int R;
	int G;
	int B;
};
struct Juncture {
	int position;//渐变条上的位置
	RGB rgb;//颜色值
};
struct Fractal {
	int Width; int Height;//窗体总宽和总高
	int Paint_Size; int View_Size;//绘图区，预览区大小
	int x; int y;//预览区位置
	int isEnlarge = 0;//缩放绘制标记，初始为否
	RECT EnlargeZone;//缩放区域
	XYRange xy;//坐标范围
	XYRange temp_xy;//暂存坐标范围
	double a = 0; double b = 0; double c = 0; double d = 0;//各种参数
	RGB*ColorBar;//渐变条
	int ColorCount;//颜色数（颜色条分辨率）
	Juncture* pJ;//关键色点
	int JunctureCount;//色点数
	Button* pB;//按钮集
	int ButtonCount;//按钮数
	User user;//操作
};
