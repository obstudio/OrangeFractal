#include"guangyiJulia.h"
using namespace std;
/*周宇*/
//guangyijulia集窗口
int gJuliaView(int wid, int hei) {
	Fractal gjulia;//创建Fractal窗体结构
	int cont = 2;
	while (cont == 2) {
		gJ_Initialize(&gjulia, wid, hei);//初始化
		cont = gJ_Process(&gjulia);//运行过程	
		gJ_Finish(&gjulia);//结束
	}
	return cont;
}
//Fractal初始化
int gJ_Initialize(Fractal*gjulia, int wid, int hei) {
	gJ_Init_stats(gjulia, wid, hei);//初始化数据
	gJ_Init_graph(gjulia);//初始化界面
						//	_getch();
	return 0;
}
//Fractal初始化数据
int gJ_Init_stats(Fractal*gjulia, int wid, int hei) {
	(*gjulia).Width = wid;//窗体宽度
	(*gjulia).Height = hei;//窗体高度
	(*gjulia).Paint_Size = (*gjulia).Height;//绘图区边长
	(*gjulia).View_Size = ((*gjulia).Width - (*gjulia).Height) * 0.9;//预览区边长
	(*gjulia).x = (*gjulia).Width - ((*gjulia).Width - (*gjulia).Height) / 2;//预览区位置
	(*gjulia).y = ((*gjulia).Width - (*gjulia).Height) / 2;
	(*gjulia).xy.xm = (*gjulia).xy.xn = (*gjulia).xy.ym = (*gjulia).xy.yn = 0;//坐标范围
	(*gjulia).ColorCount = 300;//分辨率
	(*gjulia).ColorBar = (RGB*)calloc((*gjulia).ColorCount, sizeof(RGB));//渐变条数组
	(*gjulia).pJ = (Juncture*)malloc((*gjulia).ColorCount * sizeof(Juncture));//关键点集
	(*gjulia).JunctureCount = 2;//关键点数
	(*gjulia).pJ[0].rgb = { 0,0,0 };//初始关键点-左端黑
	(*gjulia).pJ[0].position = 0;
	(*gjulia).pJ[(*gjulia).JunctureCount - 1].rgb = { 255,255,255 };//初始关键点-右端白
	(*gjulia).pJ[(*gjulia).JunctureCount - 1].position = (*gjulia).ColorCount - 1;
	ColorBar_Compiler((*gjulia).pJ, (*gjulia).JunctureCount, (*gjulia).ColorBar, (*gjulia).ColorCount);//初始化渐变条
	gJ_Init_buttons(gjulia);//初始化按钮集
	return 0;
}
//guangyiJulia集按钮初始化设定
int gJ_Init_buttons(Fractal*gjulia) {
	(*gjulia).ButtonCount = 11;
	(*gjulia).pB = (Button*)malloc((*gjulia).ButtonCount * sizeof(Button));
	Button*button = (*gjulia).pB;
	gJ_Init_colorbar(button++);
	gJ_Init_xm(button++);
	gJ_Init_xn(button++);
	gJ_Init_ym(button++);
	gJ_Init_yn(button++);
	gJ_Init_ab(button++);
	gJ_Init_paint(button++);
	gJ_Init_clear(button++);
	gJ_Init_save(button++);
	gJ_Init_back(button++);
	gJ_Init_quit(button++);
	gJ_Init_btsp(gjulia);
	return 0;
}
//guangyiJulia集确定按钮规格和位置
int gJ_Init_btsp(Fractal*gjulia) {
	int wid, hei;//按钮区规格
	int di, dj;//行距，列宽
	int rowCount;//行数
	int count;
	int i;//循环下标
	wid = (*gjulia).Width - (*gjulia).Height;//按钮区宽度
	hei = (*gjulia).Height - wid;//按钮区2高度
	rowCount = Button_rows((*gjulia).pB, (*gjulia).ButtonCount);
	di = 1.0*hei / rowCount;//行距
	for (i = 0; i < (*gjulia).ButtonCount; ++i) {
		(*gjulia).pB[i].y = (*gjulia).pB[i].i*di + wid - 0.5*di;//纵坐标

		count = Button_inArow((*gjulia).pB, (*gjulia).ButtonCount, (*gjulia).pB[i].i);
		dj = 1.0*wid / count;//该行列宽
		(*gjulia).pB[i].x = (*gjulia).pB[i].j*dj + (*gjulia).Height - 0.5*dj;//横坐标
		(*gjulia).pB[i].height = di*0.9;//高度
		(*gjulia).pB[i].width = dj - wid*0.1;//宽度
	}
	return 0;
}
//////////各种按钮数值设定///////////
int gJ_Init_colorbar(Button*button) {
	(*button).i = 1;
	(*button).j = 1;
	(*button).type = cOlorbar;
	return 0;
}
int gJ_Init_xm(Button*button) {
	(*button).i = 2;
	(*button).j = 2;
	(*button).type = xM;
	return 0;
}
int gJ_Init_xn(Button*button) {
	(*button).i = 2;
	(*button).j = 1;
	(*button).type = xN;
	return 0;
}
int gJ_Init_ym(Button*button) {
	(*button).i = 3;
	(*button).j = 2;
	(*button).type = yM;
	return 0;
}
int gJ_Init_yn(Button*button) {
	(*button).i = 3;
	(*button).j = 1;
	(*button).type = yN;
	return 0;
}
int gJ_Init_ab(Button*button) {
	(*button).i = 4;
	(*button).j = 1;
	(*button).type = aB;
	return 0;
}
int gJ_Init_paint(Button*button) {
	(*button).i = 5;
	(*button).j = 1;
	(*button).type = pAint;
	return 0;
}
int gJ_Init_clear(Button*button) {
	(*button).i = 6;
	(*button).j = 1;
	(*button).type = cLear;
	return 0;
}
int gJ_Init_save(Button*button) {
	(*button).i = 6;
	(*button).j = 2;
	(*button).type = sAve;
	return 0;
}
int gJ_Init_back(Button*button) {
	(*button).i = 7;
	(*button).j = 1;
	(*button).type = bAck;
	return 0;
}
int gJ_Init_quit(Button*button) {
	(*button).i = 7;
	(*button).j = 2;
	(*button).type = qUit;
	return 0;
}
//////////各种按钮数值设定/////////////
//Fractal初始化界面
int gJ_Init_graph(Fractal*gjulia) {
	cleardevice();//清屏
	setlinecolor(WHITE);//分界线颜色
	line((*gjulia).Height + 1, 1, (*gjulia).Height + 1, (*gjulia).Height);//初始化绘图区
																	   /*初始化预览区*/
	rectangle((*gjulia).x - (*gjulia).View_Size / 2, (*gjulia).y - (*gjulia).View_Size / 2, (*gjulia).x + (*gjulia).View_Size / 2, (*gjulia).y + (*gjulia).View_Size / 2);
	//	_getch();
	Button_showbuttons((*gjulia).pB, (*gjulia).ButtonCount);
	ColorBar_show((*gjulia).pB, (*gjulia).ButtonCount, (*gjulia).ColorBar, (*gjulia).ColorCount);
	//	_getch();

	return 0;
}
//Fractal绘图过程
int gJ_Process(Fractal*gjulia) {
	int cont = -1;
	while (cont < 0) {
		GetUser(&((*gjulia).user));
		if (gJ_IsPaintZone(gjulia)) {
			gJ_PaintZone(gjulia);
			continue;
		}
		cont = gJ_Botton_Management(Button_Judge((*gjulia).pB, (*gjulia).ButtonCount, &((*gjulia).user)), gjulia);
		//	_getch();
		ResetUser(&((*gjulia).user));
		Button_Reset((*gjulia).pB, (*gjulia).ButtonCount);
	}
	return cont;
}
//guangyiJulia集按钮处理
/*cOlorbar,xM,xN,yM,yN,aB,pAint,cLear,sAve,bAck,qUit*/
int gJ_Botton_Management(button_type xxx, Fractal*gjulia) {
	switch (xxx) {
	case cOlorbar:gJ_Button_colorbar(gjulia); break;
	case xM:return gJ_Button_xm(gjulia);
	case xN:return gJ_Button_xn(gjulia);
	case yM:return gJ_Button_ym(gjulia);
	case yN:return gJ_Button_yn(gjulia);
	case aB:return gJ_Button_ab(gjulia);
	case pAint:return gJ_Button_paint(gjulia);
	case cLear:return gJ_Button_clear(gjulia);//情况2，重新开始Fractal
	case sAve:return gJ_Button_save(gjulia);
	case bAck:return gJ_Button_back(gjulia);//情况1，回到选择
	case qUit:return gJ_Button_quit(gjulia);
	default:
		break;
	}
	return -1;
}
//guangyiJulia集中操作是否在绘图区内
int gJ_IsPaintZone(Fractal*gjulia) {
	RECT PaintZone;
	PaintZone.left = PaintZone.top = 0;
	PaintZone.right = PaintZone.bottom = (*gjulia).Paint_Size;
	return IsRectZone(PaintZone, &((*gjulia).user));
}
//Fractal绘图区操作
int gJ_PaintZone(Fractal*gjulia) {
	int d;
	int fx = (*gjulia).user.F_msg.x;
	int fy = (*gjulia).user.F_msg.y;
	int lx = (*gjulia).user.L_msg.x;
	int ly = (*gjulia).user.L_msg.y;
	d = (fx - lx)*(fx - lx) + (fy - ly)*(fy - ly);
	if (d >= 100)gJ_Enlarge(gjulia);
	return d;
}
//guangyiJulia集放大操作
int gJ_Enlarge(Fractal*gjulia) {
	(*gjulia).isEnlarge = 1;
	gJ_View_refresh(gjulia);
	return 0;
}
//获得缩放比
double gJ_View_k(Fractal*gjulia) {
	double k;
	k = (*gjulia).View_Size / (*gjulia).Paint_Size;
	return k;
}
//刷新guangyiJulia集预览图
int gJ_View_refresh(Fractal*gjulia) {
	IMAGE img;
	RECT viewzone;//放大目标范围
	gJ_View_clear(gjulia);
	viewzone = RectZone((*gjulia).x, (*gjulia).y, (*gjulia).View_Size, (*gjulia).View_Size);
	int hei, wid;
	(*gjulia).EnlargeZone.left = min((*gjulia).user.F_msg.x, (*gjulia).user.L_msg.x);
	(*gjulia).EnlargeZone.right = max((*gjulia).user.F_msg.x, (*gjulia).user.L_msg.x);
	(*gjulia).EnlargeZone.top = min((*gjulia).user.F_msg.y, (*gjulia).user.L_msg.y);
	(*gjulia).EnlargeZone.bottom = max((*gjulia).user.F_msg.y, (*gjulia).user.L_msg.y);
	if ((*gjulia).EnlargeZone.right > (*gjulia).Paint_Size)(*gjulia).EnlargeZone.right = (*gjulia).Paint_Size;
	wid = (*gjulia).EnlargeZone.right - (*gjulia).EnlargeZone.left;
	hei = (*gjulia).EnlargeZone.bottom - (*gjulia).EnlargeZone.top;
	if (((*gjulia).user.L_msg.mkCtrl != 0)) {//Ctrl键选择正方形
		wid = hei = min(wid, hei);
		(*gjulia).EnlargeZone.right = (*gjulia).EnlargeZone.left + wid;
		(*gjulia).EnlargeZone.bottom = (*gjulia).EnlargeZone.top + hei;
	}
	if ((*gjulia).EnlargeZone.right > (*gjulia).Paint_Size)(*gjulia).EnlargeZone.right = (*gjulia).Paint_Size;
	getimage(&img, (*gjulia).EnlargeZone.left, (*gjulia).EnlargeZone.top, wid, hei);
	img = ResizePic(&img, (*gjulia).View_Size, (*gjulia).View_Size);
	putimage(viewzone.left, viewzone.top, &img);
	//	putimage(viewzone.left, viewzone.top, (*julia).View_Size, (*julia).View_Size, &img, 0, 0);
	rectangle(viewzone.left, viewzone.top, viewzone.right, viewzone.bottom);
	gJ_Enlarge_tempxy(gjulia);
	return 0;
}
//清空guangyiJulia集预览图
int gJ_View_clear(Fractal*gjulia) {
	RECT viewzone;
	viewzone = RectZone((*gjulia).x, (*gjulia).y, (*gjulia).View_Size, (*gjulia).View_Size);
	clearrectangle(viewzone.left, viewzone.top, viewzone.right, viewzone.bottom);
	rectangle(viewzone.left, viewzone.top, viewzone.right, viewzone.bottom);
	return 0;
}
//确定缩放后的x,y范围
int gJ_Enlarge_tempxy(Fractal*gjulia) {
	(*gjulia).temp_xy.xn = (*gjulia).xy.xn + ((*gjulia).xy.xm - (*gjulia).xy.xn)*(*gjulia).EnlargeZone.left / (*gjulia).Paint_Size;
	(*gjulia).temp_xy.xm = (*gjulia).xy.xn + ((*gjulia).xy.xm - (*gjulia).xy.xn)*(*gjulia).EnlargeZone.right / (*gjulia).Paint_Size;
	(*gjulia).temp_xy.yn = (*gjulia).xy.yn + ((*gjulia).xy.ym - (*gjulia).xy.yn)*((*gjulia).Paint_Size - (*gjulia).EnlargeZone.bottom) / (*gjulia).Paint_Size;
	(*gjulia).temp_xy.ym = (*gjulia).xy.yn + ((*gjulia).xy.ym - (*gjulia).xy.yn)*((*gjulia).Paint_Size - (*gjulia).EnlargeZone.top) / (*gjulia).Paint_Size;
	return 0;
}
//加载缩放后的坐标范围
int gJ_Paint_enlarge(Fractal*gjulia) {
	(*gjulia).xy = (*gjulia).temp_xy;
	gJ_Button_renew(gjulia);
	return 0;
}
//guangyiJulia集刷新按钮
int gJ_Button_renew(Fractal*gjulia) {
	int i;
	char xm[25];
	char xn[25];
	char ym[25];
	char yn[25];
	i = Button_clear((*gjulia).pB, (*gjulia).ButtonCount, xM);
	sprintf_s(xm, 25, "xm = %lf", (*gjulia).xy.xm);
	Button_textout(xm, &((*gjulia).pB[i]));
	i = Button_clear((*gjulia).pB, (*gjulia).ButtonCount, xN);
	sprintf_s(xn, 25, "xn = %lf", (*gjulia).xy.xn);
	Button_textout(xn, &((*gjulia).pB[i]));
	i = Button_clear((*gjulia).pB, (*gjulia).ButtonCount, yM);
	sprintf_s(ym, 25, "ym = %lf", (*gjulia).xy.ym);
	Button_textout(ym, &((*gjulia).pB[i]));
	i = Button_clear((*gjulia).pB, (*gjulia).ButtonCount, yN);
	sprintf_s(yn, 25, "yn = %lf", (*gjulia).xy.yn);
	Button_textout(yn, &((*gjulia).pB[i]));
	return 0;
}
/////////////////按钮事件///////////////////
int gJ_Button_colorbar(Fractal*gjulia) {
	int i, j;
	int Position;
	i = Button_Find((*gjulia).pB, (*gjulia).ButtonCount);
	Position = ColorBar_GetPosition(&((*gjulia).user), &(*gjulia).pB[i], (*gjulia).ColorCount);
	j = Juncture_Find(Position, (*gjulia).pJ, &((*gjulia).JunctureCount), (*gjulia).ColorCount);
	Juncture_Edit(&((*gjulia).pJ[j]));
	Juncture_Sort((*gjulia).pJ, (*gjulia).JunctureCount);
	ColorBar_Compiler((*gjulia).pJ, (*gjulia).JunctureCount, (*gjulia).ColorBar, (*gjulia).ColorCount);
	ColorBar_paint(&((*gjulia).pB[i]), (*gjulia).ColorBar, (*gjulia).ColorCount);
	return -1;
}
//输入x的最大值
int gJ_Button_xm(Fractal*gjulia) {
	int i;
	char s[20];
	char r[25];
	InputBox(s, 20, "请输入x的最大值");
	sscanf_s(s, "%lf", &((*gjulia).xy.xm));
	i = Button_clear((*gjulia).pB, (*gjulia).ButtonCount, xM);
	sprintf_s(r, 25, "xm = %lf", (*gjulia).xy.xm);
	Button_textout(r, &((*gjulia).pB[i]));
	gJ_View_clear(gjulia);
	(*gjulia).isEnlarge = 0;
	return -1;
}
//输入x的最小值
int gJ_Button_xn(Fractal*gjulia) {
	int i;
	char s[20];
	char r[25];
	InputBox(s, 20, "请输入x的最小值");
	sscanf_s(s, "%lf", &((*gjulia).xy.xn));
	i = Button_clear((*gjulia).pB, (*gjulia).ButtonCount, xN);
	sprintf_s(r, 25, "xn = %lf", (*gjulia).xy.xn);
	Button_textout(r, &((*gjulia).pB[i]));
	gJ_View_clear(gjulia);
	(*gjulia).isEnlarge = 0;
	return -1;
}
//输入y的最大值
int gJ_Button_ym(Fractal*gjulia) {
	int i;
	char s[20];
	char r[25];
	InputBox(s, 20, "请输入y的最大值");
	sscanf_s(s, "%lf", &((*gjulia).xy.ym));
	i = Button_clear((*gjulia).pB, (*gjulia).ButtonCount, yM);
	sprintf_s(r, 25, "ym = %lf", (*gjulia).xy.ym);
	Button_textout(r, &((*gjulia).pB[i]));
	gJ_View_clear(gjulia);
	(*gjulia).isEnlarge = 0;
	return -1;
}
//输入y的最小值
int gJ_Button_yn(Fractal*gjulia) {
	int i;
	char s[20];
	char r[25];
	InputBox(s, 20, "请输入y的最小值");
	sscanf_s(s, "%lf", &((*gjulia).xy.yn));
	i = Button_clear((*gjulia).pB, (*gjulia).ButtonCount, yN);
	sprintf_s(r, 25, "yn = %lf", (*gjulia).xy.yn);
	Button_textout(r, &((*gjulia).pB[i]));
	gJ_View_clear(gjulia);
	(*gjulia).isEnlarge = 0;
	return -1;
}
//输入复数
int gJ_Button_ab(Fractal*gjulia) {
	int i;
	char sa[20];
	char sb[20];
	char r[50];
	InputBox(sa, 20, "请输入a");
	sscanf_s(sa, "%lf", &((*gjulia).a));
	InputBox(sb, 20, "请输入b");
	sscanf_s(sb, "%lf", &((*gjulia).b));
	i = Button_clear((*gjulia).pB, (*gjulia).ButtonCount, aB);
	sprintf_s(r, 50, "c = %lf + %lf * i", (*gjulia).a, (*gjulia).b);
	Button_textout(r, &((*gjulia).pB[i]));
	gJ_View_clear(gjulia);
	(*gjulia).isEnlarge = 0;
	return -1;
}
int gJ_Button_paint(Fractal*gjulia) {
	//	guangyiJ_Paint(guangyijulia);
	gJ_Paint2(gjulia);
	(*gjulia).isEnlarge = 0;
	return -1;
}
//清除按钮
int gJ_Button_clear(Fractal*gjulia) {
	(*gjulia).isEnlarge = 0;
	return SendDB("gJulia", "你确定要清除吗？", 2, -1);
}
//保存
int gJ_Button_save(Fractal*gjulia) {
	IMAGE img;
	getimage(&img, 0, 0, (*gjulia).Paint_Size, (*gjulia).Paint_Size);
	saveimage("gJulia.bmp", &img);
	SendMB("gJulia", "保存成功！");
	return -1;
}
//返回按钮
int gJ_Button_back(Fractal*gjulia) {
	return SendDB("gJulia", "你确定要返回吗？", 1, -1);
}
//退出按钮
int gJ_Button_quit(Fractal*gjulia) {
	return SendDB("gJulia", "你确定要退出吗？", 0, -1);
}
/////////////////按钮事件///////////////////
//Fractal检查参数是否合法
int gJ_CheckIndex(Fractal*gjulia, double*dx, double*dy) {
	*dx = ((*gjulia).xy.xm - (*gjulia).xy.xn) / (*gjulia).Paint_Size;
	*dy = ((*gjulia).xy.ym - (*gjulia).xy.yn) / (*gjulia).Paint_Size;
	if (*dx <= 0 || *dy <= 0)return 0;
	return 1;
}
//guangyiJulia集迭代器
int gJ_Iterator(long double a, long double b, long double x, long double y, int ColorCount) {
	int time;
	int n=3,i;
	long double c, p;
	long double za, zb;//复数的实虚部
	long double z;//z的模
	long double zam, zbm;
	for (time = 0; time < ColorCount - 1; ++time) {
	//	p = sqrt(x*x + y*y);
	//	c = atan(y / x);
	//	za = pow(p, n)*cos(n*c)+a;
	//	zb = pow(p, n)*sin(n*c) + b; //Zn=Zn-1^n+C
		for (i = 1; i <= n; i++)
		{
			zam = x*x - y*y;
			zbm = 2 * x*y;
			x = zam;
			y = zbm;

		}
		za = x + a;
		zb = y + b;
		
									//Zn=Zn-1^n+C
		x = za;
		y = zb;
		z = x*x + y*y;
		if (z > 12)return time;
	}
	return time;
}


//guangyiJulia集绘图-分析
int gJ_Analyser(Fractal*gjulia, int*paint) {
	double dx, dy;
	int i, j;
	if (gJ_CheckIndex(gjulia, &dx, &dy) == 0) {
		SendMB("绘图失败", "坐标范围过小");
		return 0;
	}
	double*x = (double*)malloc((*gjulia).Paint_Size * sizeof(double));
	double*y = (double*)malloc((*gjulia).Paint_Size * sizeof(double));
	if (x == NULL || y == NULL) {
		SendMB("绘图失败", "分析失败");
		return 0;
	}
	x[0] = (*gjulia).xy.xn; y[0] = (*gjulia).xy.yn;
	for (i = 1; i < (*gjulia).Paint_Size; ++i) x[i] = x[i - 1] + dx;
	for (i = 1; i < (*gjulia).Paint_Size; ++i) y[i] = y[i - 1] + dy;
	for (i = 0; i < (*gjulia).Paint_Size; ++i) {
		for (j = 0; j < (*gjulia).Paint_Size; ++j)
			paint[((*gjulia).Paint_Size - i - 1)*(*gjulia).Paint_Size + j] = gJ_Iterator((*gjulia).a, (*gjulia).b, x[j], y[i], (*gjulia).ColorCount);
	}
	free(x);
	free(y);
	return 1;
}
//guangyiJulia集绘图-显示
int gJ_Show(Fractal*gjulia, int*paint) {
	int i, j, d;
	RGB rgb;
	for (i = 0; i < (*gjulia).Paint_Size; ++i) {
		for (j = 0; j < (*gjulia).Paint_Size; ++j) {
			d = paint[i*(*gjulia).Paint_Size + j];
			rgb = (*gjulia).ColorBar[d];
			putpixel(j + 1, i + 1, RGB(rgb.R, rgb.G, rgb.B));
		}
	}
	return 1;
}
int gJ_Paint(Fractal*gjulia) {
	if ((*gjulia).isEnlarge != 0)gJ_Paint_enlarge(gjulia);
	int*paint = (int*)malloc((*gjulia).Paint_Size*(*gjulia).Paint_Size * sizeof(int));
	if (paint == NULL) {
		SendMB("绘图失败", "绘图信息生成失败");
		return 0;
	}
	if (gJ_Analyser(gjulia, paint) == 0) {
		free(paint);
		return 0;
	}
	if (gJ_Show(gjulia, paint) == 0) {
		free(paint);
		return 0;
	}
	free(paint);
	return 0;
}
//guangyiJulia集更细致的绘制
int gJ_Paint2(Fractal*gjulia) {
	if ((*gjulia).isEnlarge != 0)gJ_Paint_enlarge(gjulia);
	float*paint = (float*)malloc((*gjulia).Paint_Size*(*gjulia).Paint_Size * sizeof(int));
	if (paint == NULL) {
		SendMB("绘图失败", "绘图信息生成失败");
		return 0;
	}
	if (gJ_Analyser2(gjulia, paint) == 0) {
		free(paint);
		return 0;
	}
	if (gJ_Show2(gjulia, paint) == 0) {
		free(paint);
		return 0;
	}
	free(paint);
	return 0;
}
//guangyiJulia集更细致的绘制-分析
int gJ_Analyser2(Fractal*gjulia, float*paint) {
	double dx, dy;
	int i, j;
	if (gJ_CheckIndex(gjulia, &dx, &dy) == 0) {
		SendMB("绘图失败", "坐标范围过小");
		return 0;
	}
	double*x = (double*)malloc((*gjulia).Paint_Size * sizeof(double));
	double*y = (double*)malloc((*gjulia).Paint_Size * sizeof(double));
	if (x == NULL || y == NULL) {
		SendMB("绘图失败", "分析失败");
		return 0;
	}
	x[0] = (*gjulia).xy.xn; y[0] = (*gjulia).xy.yn;
	for (i = 1; i < (*gjulia).Paint_Size; ++i) x[i] = x[i - 1] + dx;
	for (i = 1; i < (*gjulia).Paint_Size; ++i) y[i] = y[i - 1] + dy;
	for (i = 0; i < (*gjulia).Paint_Size; ++i) {
		for (j = 0; j < (*gjulia).Paint_Size; ++j)
			paint[((*gjulia).Paint_Size - i - 1)*(*gjulia).Paint_Size + j] = gJ_Iterator2((*gjulia).a, (*gjulia).b, x[j], y[i], (*gjulia).ColorCount);
	}
	free(x);
	free(y);
	return 1;
}
//guangyiJulia集更细致的迭代器
float gJ_Iterator2(long double a, long double b, long double x, long double y, int ColorCount) {
	float time;
	long double za, zb;//复数的实虚部
	long double z;//z的模
	long double c, p;
	long double zam, zbm;
	int n = 3,i;
	for (time = 0; time < ColorCount - 2; ++time) {
	//	p = sqrt(x*x + y*y);
	//	c = atan(y / x);
	//	za = pow(p, n)*cos(n*c) + a;
	//	zb = pow(p, n)*sin(n*c) + b;
		for (i = 1; i <= n; i++)
		{
			zam = x*x - y*y;
			zbm = 2 * x*y;
			x = zam;
			y = zbm;

		}
		za = x + a;
		zb = y + b;
										//Zn=Zn-1^n+C				
		x = za;
		y = zb;
		z = x*x + y*y;
			
		if (z > 12) {
			time += z / 4 / (z / 4 + 1);
			return time;
		}
	}
	return time;
}
//guangyiJulia集更细致的绘制-显示
int gJ_Show2(Fractal*gjulia, float*paint) {
	int i, j, d;
	float k;
	RGB rgb;
	for (i = 0; i < (*gjulia).Paint_Size; ++i) {
		for (j = 0; j < (*gjulia).Paint_Size; ++j) {
			d = paint[i*(*gjulia).Paint_Size + j];
			k = paint[i*(*gjulia).Paint_Size + j] - d;
			rgb.R = (*gjulia).ColorBar[d].R +
				((*gjulia).ColorBar[d + 1].R - (*gjulia).ColorBar[d].R)*k;
			rgb.G = (*gjulia).ColorBar[d].G +
				((*gjulia).ColorBar[d + 1].G - (*gjulia).ColorBar[d].G)*k;
			rgb.B = (*gjulia).ColorBar[d].B +
				((*gjulia).ColorBar[d + 1].B - (*gjulia).ColorBar[d].B)*k;
			putpixel(j + 1, i + 1, RGB(rgb.R, rgb.G, rgb.B));
		}
	}
	return 1;
}
int gJ_Finish(Fractal*gjulia) {
	gJ_Freer(gjulia);
	cleardevice();
	//	_getch;
	return 0;
}
int gJ_Freer(Fractal*gjulia) {
	free((*gjulia).ColorBar);
	free((*gjulia).pJ);
	free((*gjulia).pB);
	return 0;
}
