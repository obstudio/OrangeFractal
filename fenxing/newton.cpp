#include"Newton.h"
using namespace std;
/*周宇*/
//newton集窗口
int NewtonView(int wid, int hei) {
	Fractal newton;//创建Fractal窗体结构
	int cont = 2;
	while (cont == 2) {
		N_Initialize(&newton, wid, hei);//初始化
		cont = N_Process(&newton);//运行过程	
		N_Finish(&newton);//结束
	}
	return cont;
}
//Fractal初始化
int N_Initialize(Fractal*newton, int wid, int hei) {
	N_Init_stats(newton, wid, hei);//初始化数据
	N_Init_graph(newton);//初始化界面
						 //	_getch();
	return 0;
}
//Fractal初始化数据
int N_Init_stats(Fractal*newton, int wid, int hei) {
	(*newton).Width = wid;//窗体宽度
	(*newton).Height = hei;//窗体高度
	(*newton).Paint_Size = (*newton).Height;//绘图区边长
	(*newton).View_Size = ((*newton).Width - (*newton).Height) * 0.9;//预览区边长
	(*newton).x = (*newton).Width - ((*newton).Width - (*newton).Height) / 2;//预览区位置
	(*newton).y = ((*newton).Width - (*newton).Height) / 2;
	(*newton).xy.xm = (*newton).xy.xn = (*newton).xy.ym = (*newton).xy.yn = 0;//坐标范围
	(*newton).ColorCount = 200;//分辨率
	(*newton).ColorBar = (RGB*)calloc((*newton).ColorCount, sizeof(RGB));//渐变条数组
	(*newton).pJ = (Juncture*)malloc((*newton).ColorCount * sizeof(Juncture));//关键点集
	(*newton).JunctureCount = 2;//关键点数
	(*newton).pJ[0].rgb = { 0,0,0 };//初始关键点-左端黑
	(*newton).pJ[0].position = 0;
	(*newton).pJ[(*newton).JunctureCount - 1].rgb = { 255,255,255 };//初始关键点-右端白
	(*newton).pJ[(*newton).JunctureCount - 1].position = (*newton).ColorCount - 1;
	ColorBar_Compiler((*newton).pJ, (*newton).JunctureCount, (*newton).ColorBar, (*newton).ColorCount);//初始化渐变条
	N_Init_buttons(newton);//初始化按钮集
	return 0;
}
//Newton集按钮初始化设定
int N_Init_buttons(Fractal*newton) {
	(*newton).ButtonCount = 11;
	(*newton).pB = (Button*)malloc((*newton).ButtonCount * sizeof(Button));
	Button*button = (*newton).pB;
	N_Init_colorbar(button++);
	N_Init_xm(button++);
	N_Init_xn(button++);
	N_Init_ym(button++);
	N_Init_yn(button++);
	N_Init_ab(button++);
	N_Init_paint(button++);
	N_Init_clear(button++);
	N_Init_save(button++);
	N_Init_back(button++);
	N_Init_quit(button++);
	N_Init_btsp(newton);
	return 0;
}
//Newton集确定按钮规格和位置
int N_Init_btsp(Fractal*newton) {
	int wid, hei;//按钮区规格
	int di, dj;//行距，列宽
	int rowCount;//行数
	int count;
	int i;//循环下标
	wid = (*newton).Width - (*newton).Height;//按钮区宽度
	hei = (*newton).Height - wid;//按钮区2高度
	rowCount = Button_rows((*newton).pB, (*newton).ButtonCount);
	di = 1.0*hei / rowCount;//行距
	for (i = 0; i < (*newton).ButtonCount; ++i) {
		(*newton).pB[i].y = (*newton).pB[i].i*di + wid - 0.5*di;//纵坐标

		count = Button_inArow((*newton).pB, (*newton).ButtonCount, (*newton).pB[i].i);
		dj = 1.0*wid / count;//该行列宽
		(*newton).pB[i].x = (*newton).pB[i].j*dj + (*newton).Height - 0.5*dj;//横坐标
		(*newton).pB[i].height = di*0.9;//高度
		(*newton).pB[i].width = dj - wid*0.1;//宽度
	}
	return 0;
}
//////////各种按钮数值设定///////////
int N_Init_colorbar(Button*button) {
	(*button).i = 1;
	(*button).j = 1;
	(*button).type = cOlorbar;
	return 0;
}
int N_Init_xm(Button*button) {
	(*button).i = 2;
	(*button).j = 2;
	(*button).type = xM;
	return 0;
}
int N_Init_xn(Button*button) {
	(*button).i = 2;
	(*button).j = 1;
	(*button).type = xN;
	return 0;
}
int N_Init_ym(Button*button) {
	(*button).i = 3;
	(*button).j = 2;
	(*button).type = yM;
	return 0;
}
int N_Init_yn(Button*button) {
	(*button).i = 3;
	(*button).j = 1;
	(*button).type = yN;
	return 0;
}
int N_Init_ab(Button*button) {
	(*button).i = 4;
	(*button).j = 1;
	(*button).type = aB;
	return 0;
}
int N_Init_paint(Button*button) {
	(*button).i = 5;
	(*button).j = 1;
	(*button).type = pAint;
	return 0;
}
int N_Init_clear(Button*button) {
	(*button).i = 6;
	(*button).j = 1;
	(*button).type = cLear;
	return 0;
}
int N_Init_save(Button*button) {
	(*button).i = 6;
	(*button).j = 2;
	(*button).type = sAve;
	return 0;
}
int N_Init_back(Button*button) {
	(*button).i = 7;
	(*button).j = 1;
	(*button).type = bAck;
	return 0;
}
int N_Init_quit(Button*button) {
	(*button).i = 7;
	(*button).j = 2;
	(*button).type = qUit;
	return 0;
}
//////////各种按钮数值设定/////////////
//Fractal初始化界面
int N_Init_graph(Fractal*newton) {
	cleardevice();//清屏
	setlinecolor(WHITE);//分界线颜色
	line((*newton).Height + 1, 1, (*newton).Height + 1, (*newton).Height);//初始化绘图区
																		  /*初始化预览区*/
	rectangle((*newton).x - (*newton).View_Size / 2, (*newton).y - (*newton).View_Size / 2, (*newton).x + (*newton).View_Size / 2, (*newton).y + (*newton).View_Size / 2);
	//	_getch();
	Button_showbuttons((*newton).pB, (*newton).ButtonCount);
	ColorBar_show((*newton).pB, (*newton).ButtonCount, (*newton).ColorBar, (*newton).ColorCount);
	//	_getch();

	return 0;
}
//Fractal绘图过程
int N_Process(Fractal*newton) {
	int cont = -1;
	while (cont < 0) {
		GetUser(&((*newton).user));
		if (N_IsPaintZone(newton)) {
			N_PaintZone(newton);
			continue;
		}
		cont = N_Botton_Management(Button_Judge((*newton).pB, (*newton).ButtonCount, &((*newton).user)), newton);
		//	_getch();
		ResetUser(&((*newton).user));
		Button_Reset((*newton).pB, (*newton).ButtonCount);
	}
	return cont;
}
//Newton集按钮处理
/*cOlorbar,xM,xN,yM,yN,aB,pAint,cLear,sAve,bAck,qUit*/
int N_Botton_Management(button_type xxx, Fractal*newton) {
	switch (xxx) {
	case cOlorbar:N_Button_colorbar(newton); break;
	case xM:return N_Button_xm(newton);
	case xN:return N_Button_xn(newton);
	case yM:return N_Button_ym(newton);
	case yN:return N_Button_yn(newton);
	case aB:return N_Button_ab(newton);
	case pAint:return N_Button_paint(newton);
	case cLear:return N_Button_clear(newton);//情况2，重新开始Fractal
	case sAve:return N_Button_save(newton);
	case bAck:return N_Button_back(newton);//情况1，回到选择
	case qUit:return N_Button_quit(newton);
	default:
		break;
	}
	return -1;
}
//Newton集中操作是否在绘图区内
int N_IsPaintZone(Fractal*newton) {
	RECT PaintZone;
	PaintZone.left = PaintZone.top = 0;
	PaintZone.right = PaintZone.bottom = (*newton).Paint_Size;
	return IsRectZone(PaintZone, &((*newton).user));
}
//Fractal绘图区操作
int N_PaintZone(Fractal*newton) {
	int d;
	int fx = (*newton).user.F_msg.x;
	int fy = (*newton).user.F_msg.y;
	int lx = (*newton).user.L_msg.x;
	int ly = (*newton).user.L_msg.y;
	d = (fx - lx)*(fx - lx) + (fy - ly)*(fy - ly);
	if (d >= 100)N_Enlarge(newton);
	return d;
}
//Newton集放大操作
int N_Enlarge(Fractal*newton) {
	(*newton).isEnlarge = 1;
	N_View_refresh(newton);
	return 0;
}
//获得缩放比
double N_View_k(Fractal*newton) {
	double k;
	k = (*newton).View_Size / (*newton).Paint_Size;
	return k;
}
//刷新Newton集预览图
int N_View_refresh(Fractal*newton) {
	IMAGE img;
	RECT viewzone;//放大目标范围
	N_View_clear(newton);
	viewzone = RectZone((*newton).x, (*newton).y, (*newton).View_Size, (*newton).View_Size);
	int hei, wid;
	(*newton).EnlargeZone.left = min((*newton).user.F_msg.x, (*newton).user.L_msg.x);
	(*newton).EnlargeZone.right = max((*newton).user.F_msg.x, (*newton).user.L_msg.x);
	(*newton).EnlargeZone.top = min((*newton).user.F_msg.y, (*newton).user.L_msg.y);
	(*newton).EnlargeZone.bottom = max((*newton).user.F_msg.y, (*newton).user.L_msg.y);
	if ((*newton).EnlargeZone.right > (*newton).Paint_Size)(*newton).EnlargeZone.right = (*newton).Paint_Size;
	wid = (*newton).EnlargeZone.right - (*newton).EnlargeZone.left;
	hei = (*newton).EnlargeZone.bottom - (*newton).EnlargeZone.top;
	if (((*newton).user.L_msg.mkCtrl != 0)) {//Ctrl键选择正方形
		wid = hei = min(wid, hei);
		(*newton).EnlargeZone.right = (*newton).EnlargeZone.left + wid;
		(*newton).EnlargeZone.bottom = (*newton).EnlargeZone.top + hei;
	}
	if ((*newton).EnlargeZone.right > (*newton).Paint_Size)(*newton).EnlargeZone.right = (*newton).Paint_Size;
	getimage(&img, (*newton).EnlargeZone.left, (*newton).EnlargeZone.top, wid, hei);
	img = ResizePic(&img, (*newton).View_Size, (*newton).View_Size);
	putimage(viewzone.left, viewzone.top, &img);
	//	putimage(viewzone.left, viewzone.top, (*newton).View_Size, (*newton).View_Size, &img, 0, 0);
	rectangle(viewzone.left, viewzone.top, viewzone.right, viewzone.bottom);
	N_Enlarge_tempxy(newton);
	return 0;
}
//清空Newton集预览图
int N_View_clear(Fractal*newton) {
	RECT viewzone;
	viewzone = RectZone((*newton).x, (*newton).y, (*newton).View_Size, (*newton).View_Size);
	clearrectangle(viewzone.left, viewzone.top, viewzone.right, viewzone.bottom);
	rectangle(viewzone.left, viewzone.top, viewzone.right, viewzone.bottom);
	return 0;
}
//确定缩放后的x,y范围
int N_Enlarge_tempxy(Fractal*newton) {
	(*newton).temp_xy.xn = (*newton).xy.xn + ((*newton).xy.xm - (*newton).xy.xn)*(*newton).EnlargeZone.left / (*newton).Paint_Size;
	(*newton).temp_xy.xm = (*newton).xy.xn + ((*newton).xy.xm - (*newton).xy.xn)*(*newton).EnlargeZone.right / (*newton).Paint_Size;
	(*newton).temp_xy.yn = (*newton).xy.yn + ((*newton).xy.ym - (*newton).xy.yn)*((*newton).Paint_Size - (*newton).EnlargeZone.bottom) / (*newton).Paint_Size;
	(*newton).temp_xy.ym = (*newton).xy.yn + ((*newton).xy.ym - (*newton).xy.yn)*((*newton).Paint_Size - (*newton).EnlargeZone.top) / (*newton).Paint_Size;
	return 0;
}
//加载缩放后的坐标范围
int N_Paint_enlarge(Fractal*newton) {
	(*newton).xy = (*newton).temp_xy;
	N_Button_renew(newton);
	return 0;
}
//Newton集刷新按钮
int N_Button_renew(Fractal*newton) {
	int i;
	char xm[25];
	char xn[25];
	char ym[25];
	char yn[25];
	i = Button_clear((*newton).pB, (*newton).ButtonCount, xM);
	sprintf_s(xm, 25, "xm = %lf", (*newton).xy.xm);
	Button_textout(xm, &((*newton).pB[i]));
	i = Button_clear((*newton).pB, (*newton).ButtonCount, xN);
	sprintf_s(xn, 25, "xn = %lf", (*newton).xy.xn);
	Button_textout(xn, &((*newton).pB[i]));
	i = Button_clear((*newton).pB, (*newton).ButtonCount, yM);
	sprintf_s(ym, 25, "ym = %lf", (*newton).xy.ym);
	Button_textout(ym, &((*newton).pB[i]));
	i = Button_clear((*newton).pB, (*newton).ButtonCount, yN);
	sprintf_s(yn, 25, "yn = %lf", (*newton).xy.yn);
	Button_textout(yn, &((*newton).pB[i]));
	return 0;
}
/////////////////按钮事件///////////////////
int N_Button_colorbar(Fractal*newton) {
	int i, j;
	int Position;
	i = Button_Find((*newton).pB, (*newton).ButtonCount);
	Position = ColorBar_GetPosition(&((*newton).user), &(*newton).pB[i], (*newton).ColorCount);
	j = Juncture_Find(Position, (*newton).pJ, &((*newton).JunctureCount), (*newton).ColorCount);
	Juncture_Edit(&((*newton).pJ[j]));
	Juncture_Sort((*newton).pJ, (*newton).JunctureCount);
	ColorBar_Compiler((*newton).pJ, (*newton).JunctureCount, (*newton).ColorBar, (*newton).ColorCount);
	ColorBar_paint(&((*newton).pB[i]), (*newton).ColorBar, (*newton).ColorCount);
	return -1;
}
//输入x的最大值
int N_Button_xm(Fractal*newton) {
	int i;
	char s[20];
	char r[25];
	InputBox(s, 20, "请输入x的最大值");
	sscanf_s(s, "%lf", &((*newton).xy.xm));
	i = Button_clear((*newton).pB, (*newton).ButtonCount, xM);
	sprintf_s(r, 25, "xm = %lf", (*newton).xy.xm);
	Button_textout(r, &((*newton).pB[i]));
	N_View_clear(newton);
	(*newton).isEnlarge = 0;
	return -1;
}
//输入x的最小值
int N_Button_xn(Fractal*newton) {
	int i;
	char s[20];
	char r[25];
	InputBox(s, 20, "请输入x的最小值");
	sscanf_s(s, "%lf", &((*newton).xy.xn));
	i = Button_clear((*newton).pB, (*newton).ButtonCount, xN);
	sprintf_s(r, 25, "xn = %lf", (*newton).xy.xn);
	Button_textout(r, &((*newton).pB[i]));
	N_View_clear(newton);
	(*newton).isEnlarge = 0;
	return -1;
}
//输入y的最大值
int N_Button_ym(Fractal*newton) {
	int i;
	char s[20];
	char r[25];
	InputBox(s, 20, "请输入y的最大值");
	sscanf_s(s, "%lf", &((*newton).xy.ym));
	i = Button_clear((*newton).pB, (*newton).ButtonCount, yM);
	sprintf_s(r, 25, "ym = %lf", (*newton).xy.ym);
	Button_textout(r, &((*newton).pB[i]));
	N_View_clear(newton);
	(*newton).isEnlarge = 0;
	return -1;
}
//输入y的最小值
int N_Button_yn(Fractal*newton) {
	int i;
	char s[20];
	char r[25];
	InputBox(s, 20, "请输入y的最小值");
	sscanf_s(s, "%lf", &((*newton).xy.yn));
	i = Button_clear((*newton).pB, (*newton).ButtonCount, yN);
	sprintf_s(r, 25, "yn = %lf", (*newton).xy.yn);
	Button_textout(r, &((*newton).pB[i]));
	N_View_clear(newton);
	(*newton).isEnlarge = 0;
	return -1;
}
//输入复数
int N_Button_ab(Fractal*newton) {
	int i;
	char sa[20];
	char sb[20];
	char r[50];
	InputBox(sa, 20, "请输入a");
	sscanf_s(sa, "%lf", &((*newton).a));
	InputBox(sb, 20, "请输入b");
	sscanf_s(sb, "%lf", &((*newton).b));
	i = Button_clear((*newton).pB, (*newton).ButtonCount, aB);
	sprintf_s(r, 50, "c = %lf + %lf * i", (*newton).a, (*newton).b);
	Button_textout(r, &((*newton).pB[i]));
	N_View_clear(newton);
	(*newton).isEnlarge = 0;
	return -1;
}
int N_Button_paint(Fractal*newton) {
	//	N_Paint(newton);
	N_Paint2(newton);
	(*newton).isEnlarge = 0;
	return -1;
}
//清除按钮
int N_Button_clear(Fractal*newton) {
	(*newton).isEnlarge = 0;
	return SendDB("Newton", "你确定要清除吗？", 2, -1);
}
//保存
int N_Button_save(Fractal*newton) {
	IMAGE img;
	getimage(&img, 0, 0, (*newton).Paint_Size, (*newton).Paint_Size);
	saveimage("Newton.bmp", &img);
	SendMB("Newton", "保存成功！");
	return -1;
}
//返回按钮
int N_Button_back(Fractal*newton) {
	return SendDB("Newton", "你确定要返回吗？", 1, -1);
}
//退出按钮
int N_Button_quit(Fractal*newton) {
	return SendDB("Newton", "你确定要退出吗？", 0, -1);
}
/////////////////按钮事件///////////////////
//Fractal检查参数是否合法
int N_CheckIndex(Fractal*newton, double*dx, double*dy) {
	*dx = ((*newton).xy.xm - (*newton).xy.xn) / (*newton).Paint_Size;
	*dy = ((*newton).xy.ym - (*newton).xy.yn) / (*newton).Paint_Size;
	if (*dx <= 0 || *dy <= 0)return 0;
	return 1;
}
//Newton集迭代器
int N_Iterator(long double a, long double b, long double x, long double y, int ColorCount) {
	int time,i,n;
	long double za, zb;//复数的实虚部
	long double z;//z的模
	long double seta, pn, p;
	n = a;
	for (time = 0; time < ColorCount - 1; ++time) 
	{
		
		p = sqrt(x*x + y*y);
		pn = 1;
		for (i=1; i <= n-1; i++)
		{
			pn = p*pn;
		}
		seta = atan(y / x);
		za = ((n - 1)*p*cos(seta) +(1/ pn)*cos((1 - n)*seta)) / n;
		zb = ((n - 1)*p*sin(seta) +(1/ pn)*sin((1 - n)*seta)) / n;
		x = za;
		y = zb;
		z = x*x + y*y;

		if (z < 2)return time;
	}
	return time;
}
//Newton集绘图-分析
int N_Analyser(Fractal*newton, int*paint) {
	double dx, dy;
	int i, j;
	if (N_CheckIndex(newton, &dx, &dy) == 0) {
		SendMB("绘图失败", "坐标范围过小");
		return 0;
	}
	double*x = (double*)malloc((*newton).Paint_Size * sizeof(double));
	double*y = (double*)malloc((*newton).Paint_Size * sizeof(double));
	if (x == NULL || y == NULL) {
		SendMB("绘图失败", "分析失败");
		return 0;
	}
	x[0] = (*newton).xy.xn; y[0] = (*newton).xy.yn;
	for (i = 1; i < (*newton).Paint_Size; ++i) x[i] = x[i - 1] + dx;
	for (i = 1; i < (*newton).Paint_Size; ++i) y[i] = y[i - 1] + dy;
	for (i = 0; i < (*newton).Paint_Size; ++i) {
		for (j = 0; j < (*newton).Paint_Size; ++j)
			paint[((*newton).Paint_Size - i - 1)*(*newton).Paint_Size + j] = N_Iterator((*newton).a, (*newton).b, x[j], y[i], (*newton).ColorCount);
	}
	free(x);
	free(y);
	return 1;
}
//Newton集绘图-显示
int N_Show(Fractal*newton, int*paint) {
	int i, j, d;
	RGB rgb;
	for (i = 0; i < (*newton).Paint_Size; ++i) {
		for (j = 0; j < (*newton).Paint_Size; ++j) {
			d = paint[i*(*newton).Paint_Size + j];
			rgb = (*newton).ColorBar[d];
			putpixel(j + 1, i + 1, RGB(rgb.R, rgb.G, rgb.B));
		}
	}
	return 1;
}
int N_Paint(Fractal*newton) {
	if ((*newton).isEnlarge != 0)N_Paint_enlarge(newton);
	int*paint = (int*)malloc((*newton).Paint_Size*(*newton).Paint_Size * sizeof(int));
	if (paint == NULL) {
		SendMB("绘图失败", "绘图信息生成失败");
		return 0;
	}
	if (N_Analyser(newton, paint) == 0) {
		free(paint);
		return 0;
	}
	if (N_Show(newton, paint) == 0) {
		free(paint);
		return 0;
	}
	free(paint);
	return 0;
}
//Newton集更细致的绘制
int N_Paint2(Fractal*newton) {
	if ((*newton).isEnlarge != 0)N_Paint_enlarge(newton);
	float*paint = (float*)malloc((*newton).Paint_Size*(*newton).Paint_Size * sizeof(int));
	if (paint == NULL) {
		SendMB("绘图失败", "绘图信息生成失败");
		return 0;
	}
	if (N_Analyser2(newton, paint) == 0) {
		free(paint);
		return 0;
	}
	if (N_Show2(newton, paint) == 0) {
		free(paint);
		return 0;
	}
	free(paint);
	return 0;
}
//Newton集更细致的绘制-分析
int N_Analyser2(Fractal*newton, float*paint) {
	double dx, dy;
	int i, j;
	if (N_CheckIndex(newton, &dx, &dy) == 0) {
		SendMB("绘图失败", "坐标范围过小");
		return 0;
	}
	double*x = (double*)malloc((*newton).Paint_Size * sizeof(double));
	double*y = (double*)malloc((*newton).Paint_Size * sizeof(double));
	if (x == NULL || y == NULL) {
		SendMB("绘图失败", "分析失败");
		return 0;
	}
	x[0] = (*newton).xy.xn; y[0] = (*newton).xy.yn;
	for (i = 1; i < (*newton).Paint_Size; ++i) x[i] = x[i - 1] + dx;
	for (i = 1; i < (*newton).Paint_Size; ++i) y[i] = y[i - 1] + dy;
	for (i = 0; i < (*newton).Paint_Size; ++i) {
		for (j = 0; j < (*newton).Paint_Size; ++j)
			paint[((*newton).Paint_Size - i - 1)*(*newton).Paint_Size + j] = N_Iterator2((*newton).a, (*newton).b, x[j], y[i], (*newton).ColorCount);
	}
	free(x);
	free(y);
	return 1;
}
//Newton集更细致的迭代器
float N_Iterator2(long double a, long double b, long double x, long double y, int ColorCount) {
	float time;
	long double za, zb;//复数的实虚部
	long double z;//z的模
	long double p, seta,pn;
	int n,i;
	n = a;
	for (time = 0; time < ColorCount - 2; ++time) 
	{
		p = sqrt(x*x + y*y);
		pn = 1;
		for (i = 1; i <= n - 1; i++)
		{
			pn = p*pn;
		}
		seta = atan(y / x);
		za = ((n - 1)*p*cos(seta) + (1 / pn)*cos((1 - n)*seta)) / n;
		zb = ((n - 1)*p*sin(seta) + (1 / pn)*sin((1 - n)*seta)) / n;
		x = za;
		y = zb;
		z = x*x + y*y;
		
		if (z <2)
		{
			time += z / 2 / (z / 2 + 1);
			return time;
		}
	}
	return time;
}
//Newton集更细致的绘制-显示
int N_Show2(Fractal*newton, float*paint) {
	int i, j, d;
	float k;
	RGB rgb;
	for (i = 0; i < (*newton).Paint_Size; ++i) {
		for (j = 0; j < (*newton).Paint_Size; ++j) {
			d = paint[i*(*newton).Paint_Size + j];
			k = paint[i*(*newton).Paint_Size + j] - d;
			rgb.R = (*newton).ColorBar[d].R +
				((*newton).ColorBar[d + 1].R - (*newton).ColorBar[d].R)*k;
			rgb.G = (*newton).ColorBar[d].G +
				((*newton).ColorBar[d + 1].G - (*newton).ColorBar[d].G)*k;
			rgb.B = (*newton).ColorBar[d].B +
				((*newton).ColorBar[d + 1].B - (*newton).ColorBar[d].B)*k;
			putpixel(j + 1, i + 1, RGB(rgb.R, rgb.G, rgb.B));
		}
	}
	return 1;
}
int N_Finish(Fractal*newton) {
	N_Freer(newton);
	cleardevice();
	//	_getch;
	return 0;
}
int N_Freer(Fractal*newton) {
	free((*newton).ColorBar);
	free((*newton).pJ);
	free((*newton).pB);
	return 0;
}
