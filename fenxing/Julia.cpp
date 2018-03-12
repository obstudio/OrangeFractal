#include"Julia.h"
using namespace std;
/*许嘉禾*/
//julia集窗口
int JuliaView(int wid, int hei) {
	Fractal julia;//创建Fractal窗体结构
	int cont = 2;
	while (cont == 2) {
		J_Initialize(&julia, wid, hei);//初始化
		cont = J_Process(&julia);//运行过程	
		J_Finish(&julia);//结束
	}
	return cont;
}
//Fractal初始化
int J_Initialize(Fractal*julia, int wid, int hei) {
	J_Init_stats(julia, wid, hei);//初始化数据
	J_Init_graph(julia);//初始化界面
						//	_getch();
	return 0;
}
//Fractal初始化数据
int J_Init_stats(Fractal*julia, int wid, int hei) {
	(*julia).Width = wid;//窗体宽度
	(*julia).Height = hei;//窗体高度
	(*julia).Paint_Size = (*julia).Height;//绘图区边长
	(*julia).View_Size = ((*julia).Width - (*julia).Height) * 0.9;//预览区边长
	(*julia).x = (*julia).Width - ((*julia).Width - (*julia).Height) / 2;//预览区位置
	(*julia).y = ((*julia).Width - (*julia).Height) / 2;
	(*julia).xy.xm = (*julia).xy.xn = (*julia).xy.ym = (*julia).xy.yn = 0;//坐标范围
	(*julia).ColorCount = 500;//分辨率
	(*julia).ColorBar = (RGB*)calloc((*julia).ColorCount, sizeof(RGB));//渐变条数组
	(*julia).pJ = (Juncture*)malloc((*julia).ColorCount * sizeof(Juncture));//关键点集
	(*julia).JunctureCount = 2;//关键点数
	(*julia).pJ[0].rgb = { 0,0,0 };//初始关键点-左端黑
	(*julia).pJ[0].position = 0;
	(*julia).pJ[(*julia).JunctureCount - 1].rgb = { 255,255,255 };//初始关键点-右端白
	(*julia).pJ[(*julia).JunctureCount - 1].position = (*julia).ColorCount - 1;
	ColorBar_Compiler((*julia).pJ, (*julia).JunctureCount, (*julia).ColorBar, (*julia).ColorCount);//初始化渐变条
	J_Init_buttons(julia);//初始化按钮集
	return 0;
}
//Julia集按钮初始化设定
int J_Init_buttons(Fractal*julia) {
	(*julia).ButtonCount = 11;
	(*julia).pB = (Button*)malloc((*julia).ButtonCount * sizeof(Button));
	Button*button = (*julia).pB;
	J_Init_colorbar(button++);
	J_Init_xm(button++);
	J_Init_xn(button++);
	J_Init_ym(button++);
	J_Init_yn(button++);
	J_Init_ab(button++);
	J_Init_paint(button++);
	J_Init_clear(button++);
	J_Init_save(button++);
	J_Init_back(button++);
	J_Init_quit(button++);
	J_Init_btsp(julia);
	return 0;
}
//Julia集确定按钮规格和位置
int J_Init_btsp(Fractal*julia) {
	int wid, hei;//按钮区规格
	int di, dj;//行距，列宽
	int rowCount;//行数
	int count;
	int i;//循环下标
	wid = (*julia).Width - (*julia).Height;//按钮区宽度
	hei = (*julia).Height - wid;//按钮区2高度
	rowCount = Button_rows((*julia).pB, (*julia).ButtonCount);
	di = 1.0*hei / rowCount;//行距
	for (i = 0; i < (*julia).ButtonCount; ++i) {
		(*julia).pB[i].y = (*julia).pB[i].i*di + wid - 0.5*di;//纵坐标

		count = Button_inArow((*julia).pB, (*julia).ButtonCount, (*julia).pB[i].i);
		dj = 1.0*wid / count;//该行列宽
		(*julia).pB[i].x = (*julia).pB[i].j*dj + (*julia).Height - 0.5*dj;//横坐标
		(*julia).pB[i].height = di*0.9;//高度
		(*julia).pB[i].width = dj - wid*0.1;//宽度
	}
	return 0;
}
//////////各种按钮数值设定///////////
int J_Init_colorbar(Button*button) {
	(*button).i = 1;
	(*button).j = 1;
	(*button).type = cOlorbar;
	return 0;
}
int J_Init_xm(Button*button) {
	(*button).i = 2;
	(*button).j = 2;
	(*button).type = xM;
	return 0;
}
int J_Init_xn(Button*button) {
	(*button).i = 2;
	(*button).j = 1;
	(*button).type = xN;
	return 0;
}
int J_Init_ym(Button*button) {
	(*button).i = 3;
	(*button).j = 2;
	(*button).type = yM;
	return 0;
}
int J_Init_yn(Button*button) {
	(*button).i = 3;
	(*button).j = 1;
	(*button).type = yN;
	return 0;
}
int J_Init_ab(Button*button) {
	(*button).i = 4;
	(*button).j = 1;
	(*button).type = aB;
	return 0;
}
int J_Init_paint(Button*button) {
	(*button).i = 5;
	(*button).j = 1;
	(*button).type = pAint;
	return 0;
}
int J_Init_clear(Button*button) {
	(*button).i = 6;
	(*button).j = 1;
	(*button).type = cLear;
	return 0;
}
int J_Init_save(Button*button) {
	(*button).i = 6;
	(*button).j = 2;
	(*button).type = sAve;
	return 0;
}
int J_Init_back(Button*button) {
	(*button).i = 7;
	(*button).j = 1;
	(*button).type = bAck;
	return 0;
}
int J_Init_quit(Button*button) {
	(*button).i = 7;
	(*button).j = 2;
	(*button).type = qUit;
	return 0;
}
//////////各种按钮数值设定/////////////
//Fractal初始化界面
int J_Init_graph(Fractal*julia) {
	cleardevice();//清屏
	setlinecolor(WHITE);//分界线颜色
	line((*julia).Height + 1, 1, (*julia).Height + 1, (*julia).Height);//初始化绘图区
																	   /*初始化预览区*/
	rectangle((*julia).x - (*julia).View_Size / 2, (*julia).y - (*julia).View_Size / 2, (*julia).x + (*julia).View_Size / 2, (*julia).y + (*julia).View_Size / 2);
	//	_getch();
	Button_showbuttons((*julia).pB, (*julia).ButtonCount);
	ColorBar_show((*julia).pB, (*julia).ButtonCount, (*julia).ColorBar, (*julia).ColorCount);
	//	_getch();

	return 0;
}
//Fractal绘图过程
int J_Process(Fractal*julia) {
	int cont = -1;
	while (cont < 0) {
		GetUser(&((*julia).user));
		if (J_IsPaintZone(julia)) {
			J_PaintZone(julia);
			continue;
		}
		cont = J_Botton_Management(Button_Judge((*julia).pB, (*julia).ButtonCount, &((*julia).user)), julia);
		//	_getch();
		ResetUser(&((*julia).user));
		Button_Reset((*julia).pB, (*julia).ButtonCount);
	}
	return cont;
}
//Julia集按钮处理
/*cOlorbar,xM,xN,yM,yN,aB,pAint,cLear,sAve,bAck,qUit*/
int J_Botton_Management(button_type xxx, Fractal*julia) {
	switch (xxx) {
	case cOlorbar:J_Button_colorbar(julia); break;
	case xM:return J_Button_xm(julia);
	case xN:return J_Button_xn(julia);
	case yM:return J_Button_ym(julia);
	case yN:return J_Button_yn(julia);
	case aB:return J_Button_ab(julia);
	case pAint:return J_Button_paint(julia);
	case cLear:return J_Button_clear(julia);//情况2，重新开始Fractal
	case sAve:return J_Button_save(julia);
	case bAck:return J_Button_back(julia);//情况1，回到选择
	case qUit:return J_Button_quit(julia);
	default:
		break;
	}
	return -1;
}
//Julia集中操作是否在绘图区内
int J_IsPaintZone(Fractal*julia) {
	RECT PaintZone;
	PaintZone.left = PaintZone.top = 0;
	PaintZone.right = PaintZone.bottom = (*julia).Paint_Size;
	return IsRectZone(PaintZone, &((*julia).user));
}
//Fractal绘图区操作
int J_PaintZone(Fractal*julia) {
	int d;
	int fx = (*julia).user.F_msg.x;
	int fy = (*julia).user.F_msg.y;
	int lx = (*julia).user.L_msg.x;
	int ly = (*julia).user.L_msg.y;
	d = (fx - lx)*(fx - lx) + (fy - ly)*(fy - ly);
	if (d >= 100)J_Enlarge(julia);
	return d;
}
//Julia集放大操作
int J_Enlarge(Fractal*julia) {
	(*julia).isEnlarge = 1;
	J_View_refresh(julia);
	return 0;
}
//获得缩放比
double J_View_k(Fractal*julia) {
	double k;
	k = (*julia).View_Size / (*julia).Paint_Size;
	return k;
}
//刷新Julia集预览图
int J_View_refresh(Fractal*julia) {
	IMAGE img;
	RECT viewzone;//放大目标范围
	J_View_clear(julia);
	viewzone = RectZone((*julia).x, (*julia).y, (*julia).View_Size, (*julia).View_Size);
	int hei, wid;
	(*julia).EnlargeZone.left = min((*julia).user.F_msg.x, (*julia).user.L_msg.x);
	(*julia).EnlargeZone.right = max((*julia).user.F_msg.x, (*julia).user.L_msg.x);
	(*julia).EnlargeZone.top = min((*julia).user.F_msg.y, (*julia).user.L_msg.y);
	(*julia).EnlargeZone.bottom = max((*julia).user.F_msg.y, (*julia).user.L_msg.y);
	if ((*julia).EnlargeZone.right > (*julia).Paint_Size)(*julia).EnlargeZone.right = (*julia).Paint_Size;
	wid = (*julia).EnlargeZone.right - (*julia).EnlargeZone.left;
	hei = (*julia).EnlargeZone.bottom - (*julia).EnlargeZone.top;
	if (((*julia).user.L_msg.mkCtrl != 0)) {//Ctrl键选择正方形
		wid = hei = min(wid, hei);
		(*julia).EnlargeZone.right = (*julia).EnlargeZone.left + wid;
		(*julia).EnlargeZone.bottom = (*julia).EnlargeZone.top + hei;
	}
	if ((*julia).EnlargeZone.right > (*julia).Paint_Size)(*julia).EnlargeZone.right = (*julia).Paint_Size;
	getimage(&img, (*julia).EnlargeZone.left, (*julia).EnlargeZone.top, wid, hei);
	img = ResizePic(&img, (*julia).View_Size, (*julia).View_Size);
	putimage(viewzone.left, viewzone.top, &img);
	//	putimage(viewzone.left, viewzone.top, (*julia).View_Size, (*julia).View_Size, &img, 0, 0);
	rectangle(viewzone.left, viewzone.top, viewzone.right, viewzone.bottom);
	J_Enlarge_tempxy(julia);
	return 0;
}
//清空Julia集预览图
int J_View_clear(Fractal*julia) {
	RECT viewzone;
	viewzone = RectZone((*julia).x, (*julia).y, (*julia).View_Size, (*julia).View_Size);
	clearrectangle(viewzone.left, viewzone.top, viewzone.right, viewzone.bottom);
	rectangle(viewzone.left, viewzone.top, viewzone.right, viewzone.bottom);
	return 0;
}
//确定缩放后的x,y范围
int J_Enlarge_tempxy(Fractal*julia) {
	(*julia).temp_xy.xn = (*julia).xy.xn + ((*julia).xy.xm - (*julia).xy.xn)*(*julia).EnlargeZone.left / (*julia).Paint_Size;
	(*julia).temp_xy.xm = (*julia).xy.xn + ((*julia).xy.xm - (*julia).xy.xn)*(*julia).EnlargeZone.right / (*julia).Paint_Size;
	(*julia).temp_xy.yn = (*julia).xy.yn + ((*julia).xy.ym - (*julia).xy.yn)*((*julia).Paint_Size - (*julia).EnlargeZone.bottom) / (*julia).Paint_Size;
	(*julia).temp_xy.ym = (*julia).xy.yn + ((*julia).xy.ym - (*julia).xy.yn)*((*julia).Paint_Size - (*julia).EnlargeZone.top) / (*julia).Paint_Size;
	return 0;
}
//加载缩放后的坐标范围
int J_Paint_enlarge(Fractal*julia) {
	(*julia).xy = (*julia).temp_xy;
	J_Button_renew(julia);
	return 0;
}
//Julia集刷新按钮
int J_Button_renew(Fractal*julia) {
	int i;
	char xm[25];
	char xn[25];
	char ym[25];
	char yn[25];
	i = Button_clear((*julia).pB, (*julia).ButtonCount, xM);
	sprintf_s(xm, 25, "xm = %lf", (*julia).xy.xm);
	Button_textout(xm, &((*julia).pB[i]));
	i = Button_clear((*julia).pB, (*julia).ButtonCount, xN);
	sprintf_s(xn, 25, "xn = %lf", (*julia).xy.xn);
	Button_textout(xn, &((*julia).pB[i]));
	i = Button_clear((*julia).pB, (*julia).ButtonCount, yM);
	sprintf_s(ym, 25, "ym = %lf", (*julia).xy.ym);
	Button_textout(ym, &((*julia).pB[i]));
	i = Button_clear((*julia).pB, (*julia).ButtonCount, yN);
	sprintf_s(yn, 25, "yn = %lf", (*julia).xy.yn);
	Button_textout(yn, &((*julia).pB[i]));
	return 0;
}
/////////////////按钮事件///////////////////
int J_Button_colorbar(Fractal*julia) {
	int i, j;
	int Position;
	i = Button_Find((*julia).pB, (*julia).ButtonCount);
	Position = ColorBar_GetPosition(&((*julia).user), &(*julia).pB[i], (*julia).ColorCount);
	j = Juncture_Find(Position, (*julia).pJ, &((*julia).JunctureCount), (*julia).ColorCount);
	Juncture_Edit(&((*julia).pJ[j]));
	Juncture_Sort((*julia).pJ, (*julia).JunctureCount);
	ColorBar_Compiler((*julia).pJ, (*julia).JunctureCount, (*julia).ColorBar, (*julia).ColorCount);
	ColorBar_paint(&((*julia).pB[i]), (*julia).ColorBar, (*julia).ColorCount);
	return -1;
}
//输入x的最大值
int J_Button_xm(Fractal*julia) {
	int i;
	char s[20];
	char r[25];
	InputBox(s, 20, "请输入x的最大值");
	sscanf_s(s, "%lf", &((*julia).xy.xm));
	i = Button_clear((*julia).pB, (*julia).ButtonCount, xM);
	sprintf_s(r, 25, "xm = %lf", (*julia).xy.xm);
	Button_textout(r, &((*julia).pB[i]));
	J_View_clear(julia);
	(*julia).isEnlarge = 0;
	return -1;
}
//输入x的最小值
int J_Button_xn(Fractal*julia) {
	int i;
	char s[20];
	char r[25];
	InputBox(s, 20, "请输入x的最小值");
	sscanf_s(s, "%lf", &((*julia).xy.xn));
	i = Button_clear((*julia).pB, (*julia).ButtonCount, xN);
	sprintf_s(r, 25, "xn = %lf", (*julia).xy.xn);
	Button_textout(r, &((*julia).pB[i]));
	J_View_clear(julia);
	(*julia).isEnlarge = 0;
	return -1;
}
//输入y的最大值
int J_Button_ym(Fractal*julia) {
	int i;
	char s[20];
	char r[25];
	InputBox(s, 20, "请输入y的最大值");
	sscanf_s(s, "%lf", &((*julia).xy.ym));
	i = Button_clear((*julia).pB, (*julia).ButtonCount, yM);
	sprintf_s(r, 25, "ym = %lf", (*julia).xy.ym);
	Button_textout(r, &((*julia).pB[i]));
	J_View_clear(julia);
	(*julia).isEnlarge = 0;
	return -1;
}
//输入y的最小值
int J_Button_yn(Fractal*julia) {
	int i;
	char s[20];
	char r[25];
	InputBox(s, 20, "请输入y的最小值");
	sscanf_s(s, "%lf", &((*julia).xy.yn));
	i = Button_clear((*julia).pB, (*julia).ButtonCount, yN);
	sprintf_s(r, 25, "yn = %lf", (*julia).xy.yn);
	Button_textout(r, &((*julia).pB[i]));
	J_View_clear(julia);
	(*julia).isEnlarge = 0;
	return -1;
}
//输入复数
int J_Button_ab(Fractal*julia) {
	int i;
	char sa[20];
	char sb[20];
	char r[50];
	InputBox(sa, 20, "请输入a");
	sscanf_s(sa, "%lf", &((*julia).a));
	InputBox(sb, 20, "请输入b");
	sscanf_s(sb, "%lf", &((*julia).b));
	i = Button_clear((*julia).pB, (*julia).ButtonCount, aB);
	sprintf_s(r, 50, "c = %lf + %lf * i", (*julia).a, (*julia).b);
	Button_textout(r, &((*julia).pB[i]));
	J_View_clear(julia);
	(*julia).isEnlarge = 0;
	return -1;
}
int J_Button_paint(Fractal*julia) {
//	J_Paint(julia);
	J_Paint2(julia);
	(*julia).isEnlarge = 0;
	return -1;
}
//清除按钮
int J_Button_clear(Fractal*julia) {
	(*julia).isEnlarge = 0;
	return SendDB("Julia", "你确定要清除吗？", 2, -1);
}
//保存
int J_Button_save(Fractal*julia) {
	IMAGE img;
	getimage(&img, 0, 0, (*julia).Paint_Size, (*julia).Paint_Size);
	saveimage("Julia.bmp", &img);
	SendMB("Julia", "保存成功！");
	return -1;
}
//返回按钮
int J_Button_back(Fractal*julia) {
	return SendDB("Julia", "你确定要返回吗？", 1, -1);
}
//退出按钮
int J_Button_quit(Fractal*julia) {
	return SendDB("Julia", "你确定要退出吗？", 0, -1);
}
/////////////////按钮事件///////////////////
//Fractal检查参数是否合法
int J_CheckIndex(Fractal*julia, double*dx, double*dy) {
	*dx = ((*julia).xy.xm - (*julia).xy.xn) / (*julia).Paint_Size;
	*dy = ((*julia).xy.ym - (*julia).xy.yn) / (*julia).Paint_Size;
	if (*dx <= 0 || *dy <= 0)return 0;
	return 1;
}
//Julia集迭代器
int J_Iterator(long double a, long double b, long double x, long double y, int ColorCount) {
	int time;
	long double za, zb;//复数的实虚部
	long double z;//z的模
	for (time = 0; time < ColorCount - 1; ++time) {
		za = x*x - y*y + a;
		zb = 2 * x*y + b;
		x = za;
		y = zb;
		z = x*x + y*y;
		if (z > 4)return time;
	}
	return time;
}
//Julia集绘图-分析
int J_Analyser(Fractal*julia, int*paint) {
	double dx, dy;
	int i, j;
	if (J_CheckIndex(julia, &dx, &dy) == 0) { 
		SendMB("绘图失败", "坐标范围过小");
		return 0;
	}
	double*x = (double*)malloc((*julia).Paint_Size * sizeof(double));
	double*y = (double*)malloc((*julia).Paint_Size * sizeof(double));
	if (x == NULL || y == NULL) {
		SendMB("绘图失败", "分析失败");
		return 0;
	}
	x[0] = (*julia).xy.xn; y[0] = (*julia).xy.yn;
	for (i = 1; i < (*julia).Paint_Size; ++i) x[i] = x[i - 1] + dx;
	for (i = 1; i < (*julia).Paint_Size; ++i) y[i] = y[i - 1] + dy;
	for (i = 0; i < (*julia).Paint_Size; ++i) {
		for (j = 0; j < (*julia).Paint_Size; ++j)
			paint[((*julia).Paint_Size - i - 1)*(*julia).Paint_Size + j] = J_Iterator((*julia).a, (*julia).b, x[j], y[i], (*julia).ColorCount);
	}
	free(x);
	free(y);
	return 1;
}
//Julia集绘图-显示
int J_Show(Fractal*julia, int*paint) {
	int i, j, d;
	RGB rgb;
	for (i = 0; i < (*julia).Paint_Size; ++i) {
		for (j = 0; j < (*julia).Paint_Size; ++j) {
			d = paint[i*(*julia).Paint_Size + j];
			rgb = (*julia).ColorBar[d];
			putpixel(j + 1, i + 1, RGB(rgb.R, rgb.G, rgb.B));
		}
	}
	return 1;
}
int J_Paint(Fractal*julia) {
	if ((*julia).isEnlarge != 0)J_Paint_enlarge(julia);
	int*paint = (int*)malloc((*julia).Paint_Size*(*julia).Paint_Size * sizeof(int));
	if (paint == NULL) {
		SendMB("绘图失败", "绘图信息生成失败");
		return 0;
	}
	if (J_Analyser(julia, paint) == 0) {
		free(paint);
		return 0;
	}
	if (J_Show(julia, paint) == 0) {
		free(paint);
		return 0;
	}
	free(paint);
	return 0;
}
//Julia集更细致的绘制
int J_Paint2(Fractal*julia) {
	if ((*julia).isEnlarge != 0)J_Paint_enlarge(julia);
	float*paint = (float*)malloc((*julia).Paint_Size*(*julia).Paint_Size * sizeof(int));
	if (paint == NULL) {
		SendMB("绘图失败", "绘图信息生成失败");
		return 0;
	}
	if (J_Analyser2(julia, paint) == 0) {
		free(paint);
		return 0;
	}
	if (J_Show2(julia, paint) == 0) {
		free(paint);
		return 0;
	}
	free(paint);
	return 0;
}
//Julia集更细致的绘制-分析
int J_Analyser2(Fractal*julia, float*paint) {
	double dx, dy;
	int i, j;
	if (J_CheckIndex(julia, &dx, &dy) == 0) {
		SendMB("绘图失败", "坐标范围过小");
		return 0;
	}
	double*x = (double*)malloc((*julia).Paint_Size * sizeof(double));
	double*y = (double*)malloc((*julia).Paint_Size * sizeof(double));
	if (x == NULL || y == NULL) {
		SendMB("绘图失败", "分析失败");
		return 0;
	}
	x[0] = (*julia).xy.xn; y[0] = (*julia).xy.yn;
	for (i = 1; i < (*julia).Paint_Size; ++i) x[i] = x[i - 1] + dx;
	for (i = 1; i < (*julia).Paint_Size; ++i) y[i] = y[i - 1] + dy;
	for (i = 0; i < (*julia).Paint_Size; ++i) {
		for (j = 0; j < (*julia).Paint_Size; ++j)
			paint[((*julia).Paint_Size - i - 1)*(*julia).Paint_Size + j] = J_Iterator2((*julia).a, (*julia).b, x[j], y[i], (*julia).ColorCount);
	}
	free(x);
	free(y);
	return 1;
}
//Julia集更细致的迭代器
float J_Iterator2(long double a, long double b, long double x, long double y, int ColorCount) {
	float time;
	long double za, zb;//复数的实虚部
	long double z;//z的模
	for (time = 0; time < ColorCount - 2; ++time) {
		za = x*x - y*y + a;
		zb = 2 * x*y + b;
		x = za;
		y = zb;
		z = x*x + y*y;
		if (z > 4) {
			time += z / 4 / (z / 4 + 1);
			return time;
		}
	}
	return time;
}
//Julia集更细致的绘制-显示
int J_Show2(Fractal*julia, float*paint) {
	int i, j, d;
	float k;
	RGB rgb;
	for (i = 0; i < (*julia).Paint_Size; ++i) {
		for (j = 0; j < (*julia).Paint_Size; ++j) {
			d = paint[i*(*julia).Paint_Size + j];
			k = paint[i*(*julia).Paint_Size + j] - d;
			rgb.R = (*julia).ColorBar[d].R + 
				((*julia).ColorBar[d + 1].R - (*julia).ColorBar[d].R)*k;
			rgb.G = (*julia).ColorBar[d].G +
				((*julia).ColorBar[d + 1].G - (*julia).ColorBar[d].G)*k;
			rgb.B = (*julia).ColorBar[d].B +
				((*julia).ColorBar[d + 1].B - (*julia).ColorBar[d].B)*k;
			putpixel(j + 1, i + 1, RGB(rgb.R, rgb.G, rgb.B));
		}
	}
	return 1;
}
int J_Finish(Fractal*julia) {
	J_Freer(julia);
	cleardevice();
	//	_getch;
	return 0;
}
int J_Freer(Fractal*julia) {
	free((*julia).ColorBar);
	free((*julia).pJ);
	free((*julia).pB);
	return 0;
}
