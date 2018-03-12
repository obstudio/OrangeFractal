#include"guangyiJulia.h"
using namespace std;
/*����*/
//guangyijulia������
int gJuliaView(int wid, int hei) {
	Fractal gjulia;//����Fractal����ṹ
	int cont = 2;
	while (cont == 2) {
		gJ_Initialize(&gjulia, wid, hei);//��ʼ��
		cont = gJ_Process(&gjulia);//���й���	
		gJ_Finish(&gjulia);//����
	}
	return cont;
}
//Fractal��ʼ��
int gJ_Initialize(Fractal*gjulia, int wid, int hei) {
	gJ_Init_stats(gjulia, wid, hei);//��ʼ������
	gJ_Init_graph(gjulia);//��ʼ������
						//	_getch();
	return 0;
}
//Fractal��ʼ������
int gJ_Init_stats(Fractal*gjulia, int wid, int hei) {
	(*gjulia).Width = wid;//������
	(*gjulia).Height = hei;//����߶�
	(*gjulia).Paint_Size = (*gjulia).Height;//��ͼ���߳�
	(*gjulia).View_Size = ((*gjulia).Width - (*gjulia).Height) * 0.9;//Ԥ�����߳�
	(*gjulia).x = (*gjulia).Width - ((*gjulia).Width - (*gjulia).Height) / 2;//Ԥ����λ��
	(*gjulia).y = ((*gjulia).Width - (*gjulia).Height) / 2;
	(*gjulia).xy.xm = (*gjulia).xy.xn = (*gjulia).xy.ym = (*gjulia).xy.yn = 0;//���귶Χ
	(*gjulia).ColorCount = 300;//�ֱ���
	(*gjulia).ColorBar = (RGB*)calloc((*gjulia).ColorCount, sizeof(RGB));//����������
	(*gjulia).pJ = (Juncture*)malloc((*gjulia).ColorCount * sizeof(Juncture));//�ؼ��㼯
	(*gjulia).JunctureCount = 2;//�ؼ�����
	(*gjulia).pJ[0].rgb = { 0,0,0 };//��ʼ�ؼ���-��˺�
	(*gjulia).pJ[0].position = 0;
	(*gjulia).pJ[(*gjulia).JunctureCount - 1].rgb = { 255,255,255 };//��ʼ�ؼ���-�Ҷ˰�
	(*gjulia).pJ[(*gjulia).JunctureCount - 1].position = (*gjulia).ColorCount - 1;
	ColorBar_Compiler((*gjulia).pJ, (*gjulia).JunctureCount, (*gjulia).ColorBar, (*gjulia).ColorCount);//��ʼ��������
	gJ_Init_buttons(gjulia);//��ʼ����ť��
	return 0;
}
//guangyiJulia����ť��ʼ���趨
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
//guangyiJulia��ȷ����ť����λ��
int gJ_Init_btsp(Fractal*gjulia) {
	int wid, hei;//��ť�����
	int di, dj;//�о࣬�п�
	int rowCount;//����
	int count;
	int i;//ѭ���±�
	wid = (*gjulia).Width - (*gjulia).Height;//��ť�����
	hei = (*gjulia).Height - wid;//��ť��2�߶�
	rowCount = Button_rows((*gjulia).pB, (*gjulia).ButtonCount);
	di = 1.0*hei / rowCount;//�о�
	for (i = 0; i < (*gjulia).ButtonCount; ++i) {
		(*gjulia).pB[i].y = (*gjulia).pB[i].i*di + wid - 0.5*di;//������

		count = Button_inArow((*gjulia).pB, (*gjulia).ButtonCount, (*gjulia).pB[i].i);
		dj = 1.0*wid / count;//�����п�
		(*gjulia).pB[i].x = (*gjulia).pB[i].j*dj + (*gjulia).Height - 0.5*dj;//������
		(*gjulia).pB[i].height = di*0.9;//�߶�
		(*gjulia).pB[i].width = dj - wid*0.1;//���
	}
	return 0;
}
//////////���ְ�ť��ֵ�趨///////////
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
//////////���ְ�ť��ֵ�趨/////////////
//Fractal��ʼ������
int gJ_Init_graph(Fractal*gjulia) {
	cleardevice();//����
	setlinecolor(WHITE);//�ֽ�����ɫ
	line((*gjulia).Height + 1, 1, (*gjulia).Height + 1, (*gjulia).Height);//��ʼ����ͼ��
																	   /*��ʼ��Ԥ����*/
	rectangle((*gjulia).x - (*gjulia).View_Size / 2, (*gjulia).y - (*gjulia).View_Size / 2, (*gjulia).x + (*gjulia).View_Size / 2, (*gjulia).y + (*gjulia).View_Size / 2);
	//	_getch();
	Button_showbuttons((*gjulia).pB, (*gjulia).ButtonCount);
	ColorBar_show((*gjulia).pB, (*gjulia).ButtonCount, (*gjulia).ColorBar, (*gjulia).ColorCount);
	//	_getch();

	return 0;
}
//Fractal��ͼ����
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
//guangyiJulia����ť����
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
	case cLear:return gJ_Button_clear(gjulia);//���2�����¿�ʼFractal
	case sAve:return gJ_Button_save(gjulia);
	case bAck:return gJ_Button_back(gjulia);//���1���ص�ѡ��
	case qUit:return gJ_Button_quit(gjulia);
	default:
		break;
	}
	return -1;
}
//guangyiJulia���в����Ƿ��ڻ�ͼ����
int gJ_IsPaintZone(Fractal*gjulia) {
	RECT PaintZone;
	PaintZone.left = PaintZone.top = 0;
	PaintZone.right = PaintZone.bottom = (*gjulia).Paint_Size;
	return IsRectZone(PaintZone, &((*gjulia).user));
}
//Fractal��ͼ������
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
//guangyiJulia���Ŵ����
int gJ_Enlarge(Fractal*gjulia) {
	(*gjulia).isEnlarge = 1;
	gJ_View_refresh(gjulia);
	return 0;
}
//������ű�
double gJ_View_k(Fractal*gjulia) {
	double k;
	k = (*gjulia).View_Size / (*gjulia).Paint_Size;
	return k;
}
//ˢ��guangyiJulia��Ԥ��ͼ
int gJ_View_refresh(Fractal*gjulia) {
	IMAGE img;
	RECT viewzone;//�Ŵ�Ŀ�귶Χ
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
	if (((*gjulia).user.L_msg.mkCtrl != 0)) {//Ctrl��ѡ��������
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
//���guangyiJulia��Ԥ��ͼ
int gJ_View_clear(Fractal*gjulia) {
	RECT viewzone;
	viewzone = RectZone((*gjulia).x, (*gjulia).y, (*gjulia).View_Size, (*gjulia).View_Size);
	clearrectangle(viewzone.left, viewzone.top, viewzone.right, viewzone.bottom);
	rectangle(viewzone.left, viewzone.top, viewzone.right, viewzone.bottom);
	return 0;
}
//ȷ�����ź��x,y��Χ
int gJ_Enlarge_tempxy(Fractal*gjulia) {
	(*gjulia).temp_xy.xn = (*gjulia).xy.xn + ((*gjulia).xy.xm - (*gjulia).xy.xn)*(*gjulia).EnlargeZone.left / (*gjulia).Paint_Size;
	(*gjulia).temp_xy.xm = (*gjulia).xy.xn + ((*gjulia).xy.xm - (*gjulia).xy.xn)*(*gjulia).EnlargeZone.right / (*gjulia).Paint_Size;
	(*gjulia).temp_xy.yn = (*gjulia).xy.yn + ((*gjulia).xy.ym - (*gjulia).xy.yn)*((*gjulia).Paint_Size - (*gjulia).EnlargeZone.bottom) / (*gjulia).Paint_Size;
	(*gjulia).temp_xy.ym = (*gjulia).xy.yn + ((*gjulia).xy.ym - (*gjulia).xy.yn)*((*gjulia).Paint_Size - (*gjulia).EnlargeZone.top) / (*gjulia).Paint_Size;
	return 0;
}
//�������ź�����귶Χ
int gJ_Paint_enlarge(Fractal*gjulia) {
	(*gjulia).xy = (*gjulia).temp_xy;
	gJ_Button_renew(gjulia);
	return 0;
}
//guangyiJulia��ˢ�°�ť
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
/////////////////��ť�¼�///////////////////
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
//����x�����ֵ
int gJ_Button_xm(Fractal*gjulia) {
	int i;
	char s[20];
	char r[25];
	InputBox(s, 20, "������x�����ֵ");
	sscanf_s(s, "%lf", &((*gjulia).xy.xm));
	i = Button_clear((*gjulia).pB, (*gjulia).ButtonCount, xM);
	sprintf_s(r, 25, "xm = %lf", (*gjulia).xy.xm);
	Button_textout(r, &((*gjulia).pB[i]));
	gJ_View_clear(gjulia);
	(*gjulia).isEnlarge = 0;
	return -1;
}
//����x����Сֵ
int gJ_Button_xn(Fractal*gjulia) {
	int i;
	char s[20];
	char r[25];
	InputBox(s, 20, "������x����Сֵ");
	sscanf_s(s, "%lf", &((*gjulia).xy.xn));
	i = Button_clear((*gjulia).pB, (*gjulia).ButtonCount, xN);
	sprintf_s(r, 25, "xn = %lf", (*gjulia).xy.xn);
	Button_textout(r, &((*gjulia).pB[i]));
	gJ_View_clear(gjulia);
	(*gjulia).isEnlarge = 0;
	return -1;
}
//����y�����ֵ
int gJ_Button_ym(Fractal*gjulia) {
	int i;
	char s[20];
	char r[25];
	InputBox(s, 20, "������y�����ֵ");
	sscanf_s(s, "%lf", &((*gjulia).xy.ym));
	i = Button_clear((*gjulia).pB, (*gjulia).ButtonCount, yM);
	sprintf_s(r, 25, "ym = %lf", (*gjulia).xy.ym);
	Button_textout(r, &((*gjulia).pB[i]));
	gJ_View_clear(gjulia);
	(*gjulia).isEnlarge = 0;
	return -1;
}
//����y����Сֵ
int gJ_Button_yn(Fractal*gjulia) {
	int i;
	char s[20];
	char r[25];
	InputBox(s, 20, "������y����Сֵ");
	sscanf_s(s, "%lf", &((*gjulia).xy.yn));
	i = Button_clear((*gjulia).pB, (*gjulia).ButtonCount, yN);
	sprintf_s(r, 25, "yn = %lf", (*gjulia).xy.yn);
	Button_textout(r, &((*gjulia).pB[i]));
	gJ_View_clear(gjulia);
	(*gjulia).isEnlarge = 0;
	return -1;
}
//���븴��
int gJ_Button_ab(Fractal*gjulia) {
	int i;
	char sa[20];
	char sb[20];
	char r[50];
	InputBox(sa, 20, "������a");
	sscanf_s(sa, "%lf", &((*gjulia).a));
	InputBox(sb, 20, "������b");
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
//�����ť
int gJ_Button_clear(Fractal*gjulia) {
	(*gjulia).isEnlarge = 0;
	return SendDB("gJulia", "��ȷ��Ҫ�����", 2, -1);
}
//����
int gJ_Button_save(Fractal*gjulia) {
	IMAGE img;
	getimage(&img, 0, 0, (*gjulia).Paint_Size, (*gjulia).Paint_Size);
	saveimage("gJulia.bmp", &img);
	SendMB("gJulia", "����ɹ���");
	return -1;
}
//���ذ�ť
int gJ_Button_back(Fractal*gjulia) {
	return SendDB("gJulia", "��ȷ��Ҫ������", 1, -1);
}
//�˳���ť
int gJ_Button_quit(Fractal*gjulia) {
	return SendDB("gJulia", "��ȷ��Ҫ�˳���", 0, -1);
}
/////////////////��ť�¼�///////////////////
//Fractal�������Ƿ�Ϸ�
int gJ_CheckIndex(Fractal*gjulia, double*dx, double*dy) {
	*dx = ((*gjulia).xy.xm - (*gjulia).xy.xn) / (*gjulia).Paint_Size;
	*dy = ((*gjulia).xy.ym - (*gjulia).xy.yn) / (*gjulia).Paint_Size;
	if (*dx <= 0 || *dy <= 0)return 0;
	return 1;
}
//guangyiJulia��������
int gJ_Iterator(long double a, long double b, long double x, long double y, int ColorCount) {
	int time;
	int n=3,i;
	long double c, p;
	long double za, zb;//������ʵ�鲿
	long double z;//z��ģ
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


//guangyiJulia����ͼ-����
int gJ_Analyser(Fractal*gjulia, int*paint) {
	double dx, dy;
	int i, j;
	if (gJ_CheckIndex(gjulia, &dx, &dy) == 0) {
		SendMB("��ͼʧ��", "���귶Χ��С");
		return 0;
	}
	double*x = (double*)malloc((*gjulia).Paint_Size * sizeof(double));
	double*y = (double*)malloc((*gjulia).Paint_Size * sizeof(double));
	if (x == NULL || y == NULL) {
		SendMB("��ͼʧ��", "����ʧ��");
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
//guangyiJulia����ͼ-��ʾ
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
		SendMB("��ͼʧ��", "��ͼ��Ϣ����ʧ��");
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
//guangyiJulia����ϸ�µĻ���
int gJ_Paint2(Fractal*gjulia) {
	if ((*gjulia).isEnlarge != 0)gJ_Paint_enlarge(gjulia);
	float*paint = (float*)malloc((*gjulia).Paint_Size*(*gjulia).Paint_Size * sizeof(int));
	if (paint == NULL) {
		SendMB("��ͼʧ��", "��ͼ��Ϣ����ʧ��");
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
//guangyiJulia����ϸ�µĻ���-����
int gJ_Analyser2(Fractal*gjulia, float*paint) {
	double dx, dy;
	int i, j;
	if (gJ_CheckIndex(gjulia, &dx, &dy) == 0) {
		SendMB("��ͼʧ��", "���귶Χ��С");
		return 0;
	}
	double*x = (double*)malloc((*gjulia).Paint_Size * sizeof(double));
	double*y = (double*)malloc((*gjulia).Paint_Size * sizeof(double));
	if (x == NULL || y == NULL) {
		SendMB("��ͼʧ��", "����ʧ��");
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
//guangyiJulia����ϸ�µĵ�����
float gJ_Iterator2(long double a, long double b, long double x, long double y, int ColorCount) {
	float time;
	long double za, zb;//������ʵ�鲿
	long double z;//z��ģ
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
//guangyiJulia����ϸ�µĻ���-��ʾ
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
