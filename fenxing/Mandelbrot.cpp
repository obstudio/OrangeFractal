#include"Mandelbrot.h"
using namespace std;
/*朱秋熹*/
//mandelbrot集窗口
int MandelbrotView(int wid, int hei) {
	Fractal mandelbrot;//创建Fractal窗体结构
	int cont = 2;
	while (cont == 2) {
		M_Initialize(&mandelbrot, wid, hei);//初始化
		cont = M_Process(&mandelbrot);//运行过程	
		M_Finish(&mandelbrot);//结束
	}
	return cont;
}
//Fractal初始化
int M_Initialize(Fractal*mandelbrot, int wid, int hei) {
	M_Init_stats(mandelbrot, wid, hei);//初始化数据
	M_Init_graph(mandelbrot);//初始化界面
						//	_getch();
	return 0;
}
//Fractal初始化数据
int M_Init_stats(Fractal*mandelbrot, int wid, int hei) {
	(*mandelbrot).Width = wid;//窗体宽度
	(*mandelbrot).Height = hei;//窗体高度
	(*mandelbrot).Paint_Size = (*mandelbrot).Height;//绘图区边长
	(*mandelbrot).View_Size = ((*mandelbrot).Width - (*mandelbrot).Height) * 0.9;//预览区边长
	(*mandelbrot).x = (*mandelbrot).Width - ((*mandelbrot).Width - (*mandelbrot).Height) / 2;//预览区位置
	(*mandelbrot).y = ((*mandelbrot).Width - (*mandelbrot).Height) / 2;
	(*mandelbrot).xy.xm = (*mandelbrot).xy.xn = (*mandelbrot).xy.ym = (*mandelbrot).xy.yn = 0;//坐标范围
	(*mandelbrot).ColorCount = 500;//分辨率
	(*mandelbrot).ColorBar = (RGB*)calloc((*mandelbrot).ColorCount, sizeof(RGB));//渐变条数组
	(*mandelbrot).pJ = (Juncture*)malloc((*mandelbrot).ColorCount * sizeof(Juncture));//关键点集
	(*mandelbrot).JunctureCount = 2;//关键点数
	(*mandelbrot).pJ[0].rgb = { 0,0,0 };//初始关键点-左端黑
	(*mandelbrot).pJ[0].position = 0;
	(*mandelbrot).pJ[(*mandelbrot).JunctureCount - 1].rgb = { 255,255,255 };//初始关键点-右端白
	(*mandelbrot).pJ[(*mandelbrot).JunctureCount - 1].position = (*mandelbrot).ColorCount - 1;
	ColorBar_Compiler((*mandelbrot).pJ, (*mandelbrot).JunctureCount, (*mandelbrot).ColorBar, (*mandelbrot).ColorCount);//初始化渐变条
	M_Init_buttons(mandelbrot);//初始化按钮集
	return 0;
}
//Mandelbrot集按钮初始化设定
int M_Init_buttons(Fractal*mandelbrot) {
	(*mandelbrot).ButtonCount = 11;
	(*mandelbrot).pB = (Button*)malloc((*mandelbrot).ButtonCount * sizeof(Button));
	Button*button = (*mandelbrot).pB;
	M_Init_colorbar(button++);
	M_Init_xm(button++);
	M_Init_xn(button++);
	M_Init_ym(button++);
	M_Init_yn(button++);
	M_Init_ab(button++);
	M_Init_paint(button++);
	M_Init_clear(button++);
	M_Init_save(button++);
	M_Init_back(button++);
	M_Init_quit(button++);
	M_Init_btsp(mandelbrot);
	return 0;
}
//Mandelbrot集确定按钮规格和位置
int M_Init_btsp(Fractal*mandelbrot) {
	int wid, hei;//按钮区规格
	int di, dj;//行距，列宽
	int rowCount;//行数
	int count;
	int i;//循环下标
	wid = (*mandelbrot).Width - (*mandelbrot).Height;//按钮区宽度
	hei = (*mandelbrot).Height - wid;//按钮区2高度
	rowCount = Button_rows((*mandelbrot).pB, (*mandelbrot).ButtonCount);
	di = 1.0*hei / rowCount;//行距
	for (i = 0; i < (*mandelbrot).ButtonCount; ++i) {
		(*mandelbrot).pB[i].y = (*mandelbrot).pB[i].i*di + wid - 0.5*di;//纵坐标

		count = Button_inArow((*mandelbrot).pB, (*mandelbrot).ButtonCount, (*mandelbrot).pB[i].i);
		dj = 1.0*wid / count;//该行列宽
		(*mandelbrot).pB[i].x = (*mandelbrot).pB[i].j*dj + (*mandelbrot).Height - 0.5*dj;//横坐标
		(*mandelbrot).pB[i].height = di*0.9;//高度
		(*mandelbrot).pB[i].width = dj - wid*0.1;//宽度
	}
	return 0;
}
//////////各种按钮数值设定///////////
int M_Init_colorbar(Button*button) {
	(*button).i = 1;
	(*button).j = 1;
	(*button).type = cOlorbar;
	return 0;
}
int M_Init_xm(Button*button) {
	(*button).i = 2;
	(*button).j = 2;
	(*button).type = xM;
	return 0;
}
int M_Init_xn(Button*button) {
	(*button).i = 2;
	(*button).j = 1;
	(*button).type = xN;
	return 0;
}
int M_Init_ym(Button*button) {
	(*button).i = 3;
	(*button).j = 2;
	(*button).type = yM;
	return 0;
}
int M_Init_yn(Button*button) {
	(*button).i = 3;
	(*button).j = 1;
	(*button).type = yN;
	return 0;
}
int M_Init_ab(Button*button) {
	(*button).i = 4;
	(*button).j = 1;
	(*button).type = aB;
	return 0;
}
int M_Init_paint(Button*button) {
	(*button).i = 5;
	(*button).j = 1;
	(*button).type = pAint;
	return 0;
}
int M_Init_clear(Button*button) {
	(*button).i = 6;
	(*button).j = 1;
	(*button).type = cLear;
	return 0;
}
int M_Init_save(Button*button) {
	(*button).i = 6;
	(*button).j = 2;
	(*button).type = sAve;
	return 0;
}
int M_Init_back(Button*button) {
	(*button).i = 7;
	(*button).j = 1;
	(*button).type = bAck;
	return 0;
}
int M_Init_quit(Button*button) {
	(*button).i = 7;
	(*button).j = 2;
	(*button).type = qUit;
	return 0;
}
//////////各种按钮数值设定/////////////
//Fractal初始化界面
int M_Init_graph(Fractal*mandelbrot) {
	cleardevice();//清屏
	setlinecolor(WHITE);//分界线颜色
	line((*mandelbrot).Height + 1, 1, (*mandelbrot).Height + 1, (*mandelbrot).Height);//初始化绘图区
																	   /*初始化预览区*/
	rectangle((*mandelbrot).x - (*mandelbrot).View_Size / 2, (*mandelbrot).y - (*mandelbrot).View_Size / 2, (*mandelbrot).x + (*mandelbrot).View_Size / 2, (*mandelbrot).y + (*mandelbrot).View_Size / 2);
	//	_getch();
	Button_showbuttons((*mandelbrot).pB, (*mandelbrot).ButtonCount);
	ColorBar_show((*mandelbrot).pB, (*mandelbrot).ButtonCount, (*mandelbrot).ColorBar, (*mandelbrot).ColorCount);
	//	_getch();

	return 0;
}
//Fractal绘图过程
int M_Process(Fractal*mandelbrot) {
	int cont = -1;
	while (cont < 0) {
		GetUser(&((*mandelbrot).user));
		if (M_IsPaintZone(mandelbrot)) {
			M_PaintZone(mandelbrot);
			continue;
		}
		cont = M_Botton_Management(Button_Judge((*mandelbrot).pB, (*mandelbrot).ButtonCount, &((*mandelbrot).user)), mandelbrot);
		//	_getch();
		ResetUser(&((*mandelbrot).user));
		Button_Reset((*mandelbrot).pB, (*mandelbrot).ButtonCount);
	}
	return cont;
}
//Mandelbrot集按钮处理
/*cOlorbar,xM,xN,yM,yN,aB,pAint,cLear,sAve,bAck,qUit*/
int M_Botton_Management(button_type xxx, Fractal*mandelbrot) {
	switch (xxx) {
	case cOlorbar:M_Button_colorbar(mandelbrot); break;
	case xM:return M_Button_xm(mandelbrot);
	case xN:return M_Button_xn(mandelbrot);
	case yM:return M_Button_ym(mandelbrot);
	case yN:return M_Button_yn(mandelbrot);
	case aB:return M_Button_ab(mandelbrot);
	case pAint:return M_Button_paint(mandelbrot);
	case cLear:return M_Button_clear(mandelbrot);//情况2，重新开始Fractal
	case sAve:return M_Button_save(mandelbrot);
	case bAck:return M_Button_back(mandelbrot);//情况1，回到选择
	case qUit:return M_Button_quit(mandelbrot);
	default:
		break;
	}
	return -1;
}
//Mandelbrot集中操作是否在绘图区内
int M_IsPaintZone(Fractal*mandelbrot) {
	RECT PaintZone;
	PaintZone.left = PaintZone.top = 0;
	PaintZone.right = PaintZone.bottom = (*mandelbrot).Paint_Size;
	return IsRectZone(PaintZone, &((*mandelbrot).user));
}
//Fractal绘图区操作
int M_PaintZone(Fractal*mandelbrot) {
	int d;
	int fx = (*mandelbrot).user.F_msg.x;
	int fy = (*mandelbrot).user.F_msg.y;
	int lx = (*mandelbrot).user.L_msg.x;
	int ly = (*mandelbrot).user.L_msg.y;
	d = (fx - lx)*(fx - lx) + (fy - ly)*(fy - ly);
	if (d >= 100)M_Enlarge(mandelbrot);
	return d;
}
//Mandelbrot集放大操作
int M_Enlarge(Fractal*mandelbrot) {
	(*mandelbrot).isEnlarge = 1;
	M_View_refresh(mandelbrot);
	return 0;
}
//获得缩放比
double M_View_k(Fractal*mandelbrot) {
	double k;
	k = (*mandelbrot).View_Size / (*mandelbrot).Paint_Size;
	return k;
}
//刷新Mandelbrot集预览图
int M_View_refresh(Fractal*mandelbrot) {
	IMAGE img;
	RECT viewzone;//放大目标范围
	M_View_clear(mandelbrot);
	viewzone = RectZone((*mandelbrot).x, (*mandelbrot).y, (*mandelbrot).View_Size, (*mandelbrot).View_Size);
	int hei, wid;
	(*mandelbrot).EnlargeZone.left = min((*mandelbrot).user.F_msg.x, (*mandelbrot).user.L_msg.x);
	(*mandelbrot).EnlargeZone.right = max((*mandelbrot).user.F_msg.x, (*mandelbrot).user.L_msg.x);
	(*mandelbrot).EnlargeZone.top = min((*mandelbrot).user.F_msg.y, (*mandelbrot).user.L_msg.y);
	(*mandelbrot).EnlargeZone.bottom = max((*mandelbrot).user.F_msg.y, (*mandelbrot).user.L_msg.y);
	if ((*mandelbrot).EnlargeZone.right > (*mandelbrot).Paint_Size)(*mandelbrot).EnlargeZone.right = (*mandelbrot).Paint_Size;
	wid = (*mandelbrot).EnlargeZone.right - (*mandelbrot).EnlargeZone.left;
	hei = (*mandelbrot).EnlargeZone.bottom - (*mandelbrot).EnlargeZone.top;
	if (((*mandelbrot).user.L_msg.mkCtrl != 0)) {//Ctrl键选择正方形
		wid = hei = min(wid, hei);
		(*mandelbrot).EnlargeZone.right = (*mandelbrot).EnlargeZone.left + wid;
		(*mandelbrot).EnlargeZone.bottom = (*mandelbrot).EnlargeZone.top + hei;
	}
	if ((*mandelbrot).EnlargeZone.right > (*mandelbrot).Paint_Size)(*mandelbrot).EnlargeZone.right = (*mandelbrot).Paint_Size;
	getimage(&img, (*mandelbrot).EnlargeZone.left, (*mandelbrot).EnlargeZone.top, wid, hei);
	img = ResizePic(&img, (*mandelbrot).View_Size, (*mandelbrot).View_Size);
	putimage(viewzone.left, viewzone.top, &img);
	//	putimage(viewzone.left, viewzone.top, (*mandelbrot).View_Size, (*mandelbrot).View_Size, &img, 0, 0);
	rectangle(viewzone.left, viewzone.top, viewzone.right, viewzone.bottom);
	M_Enlarge_tempxy(mandelbrot);
	return 0;
}
//清空Mandelbrot集预览图
int M_View_clear(Fractal*mandelbrot) {
	RECT viewzone;
	viewzone = RectZone((*mandelbrot).x, (*mandelbrot).y, (*mandelbrot).View_Size, (*mandelbrot).View_Size);
	clearrectangle(viewzone.left, viewzone.top, viewzone.right, viewzone.bottom);
	rectangle(viewzone.left, viewzone.top, viewzone.right, viewzone.bottom);
	return 0;
}
//确定缩放后的x,y范围
int M_Enlarge_tempxy(Fractal*mandelbrot) {
	(*mandelbrot).temp_xy.xn = (*mandelbrot).xy.xn + ((*mandelbrot).xy.xm - (*mandelbrot).xy.xn)*(*mandelbrot).EnlargeZone.left / (*mandelbrot).Paint_Size;
	(*mandelbrot).temp_xy.xm = (*mandelbrot).xy.xn + ((*mandelbrot).xy.xm - (*mandelbrot).xy.xn)*(*mandelbrot).EnlargeZone.right / (*mandelbrot).Paint_Size;
	(*mandelbrot).temp_xy.yn = (*mandelbrot).xy.yn + ((*mandelbrot).xy.ym - (*mandelbrot).xy.yn)*((*mandelbrot).Paint_Size - (*mandelbrot).EnlargeZone.bottom) / (*mandelbrot).Paint_Size;
	(*mandelbrot).temp_xy.ym = (*mandelbrot).xy.yn + ((*mandelbrot).xy.ym - (*mandelbrot).xy.yn)*((*mandelbrot).Paint_Size - (*mandelbrot).EnlargeZone.top) / (*mandelbrot).Paint_Size;
	return 0;
}
//加载缩放后的坐标范围
int M_Paint_enlarge(Fractal*mandelbrot) {
	(*mandelbrot).xy = (*mandelbrot).temp_xy;
	M_Button_renew(mandelbrot);
	return 0;
}
//Mandelbrot集刷新按钮
int M_Button_renew(Fractal*mandelbrot) {
	int i;
	char xm[25];
	char xn[25];
	char ym[25];
	char yn[25];
	i = Button_clear((*mandelbrot).pB, (*mandelbrot).ButtonCount, xM);
	sprintf_s(xm, 25, "xm = %lf", (*mandelbrot).xy.xm);
	Button_textout(xm, &((*mandelbrot).pB[i]));
	i = Button_clear((*mandelbrot).pB, (*mandelbrot).ButtonCount, xN);
	sprintf_s(xn, 25, "xn = %lf", (*mandelbrot).xy.xn);
	Button_textout(xn, &((*mandelbrot).pB[i]));
	i = Button_clear((*mandelbrot).pB, (*mandelbrot).ButtonCount, yM);
	sprintf_s(ym, 25, "ym = %lf", (*mandelbrot).xy.ym);
	Button_textout(ym, &((*mandelbrot).pB[i]));
	i = Button_clear((*mandelbrot).pB, (*mandelbrot).ButtonCount, yN);
	sprintf_s(yn, 25, "yn = %lf", (*mandelbrot).xy.yn);
	Button_textout(yn, &((*mandelbrot).pB[i]));
	return 0;
}
/////////////////按钮事件///////////////////
int M_Button_colorbar(Fractal*mandelbrot) {
	int i, j;
	int Position;
	i = Button_Find((*mandelbrot).pB, (*mandelbrot).ButtonCount);
	Position = ColorBar_GetPosition(&((*mandelbrot).user), &(*mandelbrot).pB[i], (*mandelbrot).ColorCount);
	j = Juncture_Find(Position, (*mandelbrot).pJ, &((*mandelbrot).JunctureCount), (*mandelbrot).ColorCount);
	Juncture_Edit(&((*mandelbrot).pJ[j]));
	Juncture_Sort((*mandelbrot).pJ, (*mandelbrot).JunctureCount);
	ColorBar_Compiler((*mandelbrot).pJ, (*mandelbrot).JunctureCount, (*mandelbrot).ColorBar, (*mandelbrot).ColorCount);
	ColorBar_paint(&((*mandelbrot).pB[i]), (*mandelbrot).ColorBar, (*mandelbrot).ColorCount);
	return -1;
}
//输入x的最大值
int M_Button_xm(Fractal*mandelbrot) {
	int i;
	char s[20];
	char r[25];
	InputBox(s, 20, "请输入x的最大值");
	sscanf_s(s, "%lf", &((*mandelbrot).xy.xm));
	i = Button_clear((*mandelbrot).pB, (*mandelbrot).ButtonCount, xM);
	sprintf_s(r, 25, "xm = %lf", (*mandelbrot).xy.xm);
	Button_textout(r, &((*mandelbrot).pB[i]));
	M_View_clear(mandelbrot);
	(*mandelbrot).isEnlarge = 0;
	return -1;
}
//输入x的最小值
int M_Button_xn(Fractal*mandelbrot) {
	int i;
	char s[20];
	char r[25];
	InputBox(s, 20, "请输入x的最小值");
	sscanf_s(s, "%lf", &((*mandelbrot).xy.xn));
	i = Button_clear((*mandelbrot).pB, (*mandelbrot).ButtonCount, xN);
	sprintf_s(r, 25, "xn = %lf", (*mandelbrot).xy.xn);
	Button_textout(r, &((*mandelbrot).pB[i]));
	M_View_clear(mandelbrot);
	(*mandelbrot).isEnlarge = 0;
	return -1;
}
//输入y的最大值
int M_Button_ym(Fractal*mandelbrot) {
	int i;
	char s[20];
	char r[25];
	InputBox(s, 20, "请输入y的最大值");
	sscanf_s(s, "%lf", &((*mandelbrot).xy.ym));
	i = Button_clear((*mandelbrot).pB, (*mandelbrot).ButtonCount, yM);
	sprintf_s(r, 25, "ym = %lf", (*mandelbrot).xy.ym);
	Button_textout(r, &((*mandelbrot).pB[i]));
	M_View_clear(mandelbrot);
	(*mandelbrot).isEnlarge = 0;
	return -1;
}
//输入y的最小值
int M_Button_yn(Fractal*mandelbrot) {
	int i;
	char s[20];
	char r[25];
	InputBox(s, 20, "请输入y的最小值");
	sscanf_s(s, "%lf", &((*mandelbrot).xy.yn));
	i = Button_clear((*mandelbrot).pB, (*mandelbrot).ButtonCount, yN);
	sprintf_s(r, 25, "yn = %lf", (*mandelbrot).xy.yn);
	Button_textout(r, &((*mandelbrot).pB[i]));
	M_View_clear(mandelbrot);
	(*mandelbrot).isEnlarge = 0;
	return -1;
}
//输入复数
int M_Button_ab(Fractal*mandelbrot) {
	int i;
	char sa[20];
	char sb[20];
	char r[50];
	InputBox(sa, 20, "请输入a");
	sscanf_s(sa, "%lf", &((*mandelbrot).a));
	InputBox(sb, 20, "请输入b");
	sscanf_s(sb, "%lf", &((*mandelbrot).b));
	i = Button_clear((*mandelbrot).pB, (*mandelbrot).ButtonCount, aB);
	sprintf_s(r, 50, "c = %lf + %lf * i", (*mandelbrot).a, (*mandelbrot).b);
	Button_textout(r, &((*mandelbrot).pB[i]));
	M_View_clear(mandelbrot);
	(*mandelbrot).isEnlarge = 0;
	return -1;
}
int M_Button_paint(Fractal*mandelbrot) {
	//	M_Paint(mandelbrot);
	M_Paint2(mandelbrot);
	(*mandelbrot).isEnlarge = 0;
	return -1;
}
//清除按钮
int M_Button_clear(Fractal*mandelbrot) {
	(*mandelbrot).isEnlarge = 0;
	return SendDB("Mandelbrot", "你确定要清除吗？", 2, -1);
}
//保存
int M_Button_save(Fractal*mandelbrot) {
	IMAGE img;
	getimage(&img, 0, 0, (*mandelbrot).Paint_Size, (*mandelbrot).Paint_Size);
	saveimage("Mandelbrot.bmp", &img);
	SendMB("Mandelbrot", "保存成功！");
	return -1;
}
//返回按钮
int M_Button_back(Fractal*mandelbrot) {
	return SendDB("Mandelbrot", "你确定要返回吗？", 1, -1);
}
//退出按钮
int M_Button_quit(Fractal*mandelbrot) {
	return SendDB("Mandelbrot", "你确定要退出吗？", 0, -1);
}
/////////////////按钮事件///////////////////
//Fractal检查参数是否合法
int M_CheckIndex(Fractal*mandelbrot, double*dx, double*dy) {
	*dx = ((*mandelbrot).xy.xm - (*mandelbrot).xy.xn) / (*mandelbrot).Paint_Size;
	*dy = ((*mandelbrot).xy.ym - (*mandelbrot).xy.yn) / (*mandelbrot).Paint_Size;
	if (*dx <= 0 || *dy <= 0)return 0;
	return 1;
}
//Mandelbrot集迭代器
int M_Iterator(long double a, long double b, long double x, long double y, int ColorCount) {
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
//Mandelbrot集绘图-分析
int M_Analyser(Fractal*mandelbrot, int*paint) {
	double dx, dy;
	int i, j;
	if (M_CheckIndex(mandelbrot, &dx, &dy) == 0) {
		SendMB("绘图失败", "坐标范围过小");
		return 0;
	}
	double*x = (double*)malloc((*mandelbrot).Paint_Size * sizeof(double));
	double*y = (double*)malloc((*mandelbrot).Paint_Size * sizeof(double));
	if (x == NULL || y == NULL) {
		SendMB("绘图失败", "分析失败");
		return 0;
	}
	x[0] = (*mandelbrot).xy.xn; y[0] = (*mandelbrot).xy.yn;
	for (i = 1; i < (*mandelbrot).Paint_Size; ++i) x[i] = x[i - 1] + dx;
	for (i = 1; i < (*mandelbrot).Paint_Size; ++i) y[i] = y[i - 1] + dy;
	for (i = 0; i < (*mandelbrot).Paint_Size; ++i) {
		for (j = 0; j < (*mandelbrot).Paint_Size; ++j)
			paint[((*mandelbrot).Paint_Size - i - 1)*(*mandelbrot).Paint_Size + j] = M_Iterator((*mandelbrot).a, (*mandelbrot).b, x[j], y[i], (*mandelbrot).ColorCount);
	}
	free(x);
	free(y);
	return 1;
}
//Mandelbrot集绘图-显示
int M_Show(Fractal*mandelbrot, int*paint) {
	int i, j, d;
	RGB rgb;
	for (i = 0; i < (*mandelbrot).Paint_Size; ++i) {
		for (j = 0; j < (*mandelbrot).Paint_Size; ++j) {
			d = paint[i*(*mandelbrot).Paint_Size + j];
			rgb = (*mandelbrot).ColorBar[d];
			putpixel(j + 1, i + 1, RGB(rgb.R, rgb.G, rgb.B));
		}
	}
	return 1;
}
int M_Paint(Fractal*mandelbrot) {
	if ((*mandelbrot).isEnlarge != 0)M_Paint_enlarge(mandelbrot);
	int*paint = (int*)malloc((*mandelbrot).Paint_Size*(*mandelbrot).Paint_Size * sizeof(int));
	if (paint == NULL) {
		SendMB("绘图失败", "绘图信息生成失败");
		return 0;
	}
	if (M_Analyser(mandelbrot, paint) == 0) {
		free(paint);
		return 0;
	}
	if (M_Show(mandelbrot, paint) == 0) {
		free(paint);
		return 0;
	}
	free(paint);
	return 0;
}
//Mandelbrot集更细致的绘制
int M_Paint2(Fractal*mandelbrot) {
	if ((*mandelbrot).isEnlarge != 0)M_Paint_enlarge(mandelbrot);
	float*paint = (float*)malloc((*mandelbrot).Paint_Size*(*mandelbrot).Paint_Size * sizeof(int));
	if (paint == NULL) {
		SendMB("绘图失败", "绘图信息生成失败");
		return 0;
	}
	if (M_Analyser2(mandelbrot, paint) == 0) {
		free(paint);
		return 0;
	}
	if (M_Show2(mandelbrot, paint) == 0) {
		free(paint);
		return 0;
	}
	free(paint);
	return 0;
}
//Mandelbrot集更细致的绘制-分析
int M_Analyser2(Fractal*mandelbrot, float*paint) {
	double dx, dy;
	int i, j;
	if (M_CheckIndex(mandelbrot, &dx, &dy) == 0) {
		SendMB("绘图失败", "坐标范围过小");
		return 0;
	}
	double*x = (double*)malloc((*mandelbrot).Paint_Size * sizeof(double));
	double*y = (double*)malloc((*mandelbrot).Paint_Size * sizeof(double));
	if (x == NULL || y == NULL) {
		SendMB("绘图失败", "分析失败");
		return 0;
	}
	x[0] = (*mandelbrot).xy.xn; y[0] = (*mandelbrot).xy.yn;
	for (i = 1; i < (*mandelbrot).Paint_Size; ++i) x[i] = x[i - 1] + dx;
	for (i = 1; i < (*mandelbrot).Paint_Size; ++i) y[i] = y[i - 1] + dy;
	for (i = 0; i < (*mandelbrot).Paint_Size; ++i) {
		for (j = 0; j < (*mandelbrot).Paint_Size; ++j)
			paint[((*mandelbrot).Paint_Size - i - 1)*(*mandelbrot).Paint_Size + j] = M_Iterator2((*mandelbrot).a, (*mandelbrot).b, x[j], y[i], (*mandelbrot).ColorCount);
	}
	free(x);
	free(y);
	return 1;
}
//Mandelbrot集更细致的迭代器
float M_Iterator2(long double a, long double b, long double x, long double y, int ColorCount) {
	float time;
	long double za, zb;//复数的实虚部
	long double z;//z的模
	for (time = 0; time < ColorCount - 2; ++time) {
		za = a*a - b*b + x;
		zb = 2 * a*b + y;
		a = za;
		b = zb;
		z = a*a + b*b;
		if (z > 4) {
			time += z / 4 / (z / 4 + 1);
			return time;
		}
	}
	return time;
}
//Mandelbrot集更细致的绘制-显示
int M_Show2(Fractal*mandelbrot, float*paint) {
	int i, j, d;
	float k;
	RGB rgb;
	for (i = 0; i < (*mandelbrot).Paint_Size; ++i) {
		for (j = 0; j < (*mandelbrot).Paint_Size; ++j) {
			d = paint[i*(*mandelbrot).Paint_Size + j];
			k = paint[i*(*mandelbrot).Paint_Size + j] - d;
			rgb.R = (*mandelbrot).ColorBar[d].R +
				((*mandelbrot).ColorBar[d + 1].R - (*mandelbrot).ColorBar[d].R)*k;
			rgb.G = (*mandelbrot).ColorBar[d].G +
				((*mandelbrot).ColorBar[d + 1].G - (*mandelbrot).ColorBar[d].G)*k;
			rgb.B = (*mandelbrot).ColorBar[d].B +
				((*mandelbrot).ColorBar[d + 1].B - (*mandelbrot).ColorBar[d].B)*k;
			putpixel(j + 1, i + 1, RGB(rgb.R, rgb.G, rgb.B));
		}
	}
	return 1;
}
int M_Finish(Fractal*mandelbrot) {
	M_Freer(mandelbrot);
	cleardevice();
	//	_getch;
	return 0;
}
int M_Freer(Fractal*mandelbrot) {
	free((*mandelbrot).ColorBar);
	free((*mandelbrot).pJ);
	free((*mandelbrot).pB);
	return 0;
}
