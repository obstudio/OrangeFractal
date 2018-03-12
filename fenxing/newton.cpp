#include"Newton.h"
using namespace std;
/*����*/
//newton������
int NewtonView(int wid, int hei) {
	Fractal newton;//����Fractal����ṹ
	int cont = 2;
	while (cont == 2) {
		N_Initialize(&newton, wid, hei);//��ʼ��
		cont = N_Process(&newton);//���й���	
		N_Finish(&newton);//����
	}
	return cont;
}
//Fractal��ʼ��
int N_Initialize(Fractal*newton, int wid, int hei) {
	N_Init_stats(newton, wid, hei);//��ʼ������
	N_Init_graph(newton);//��ʼ������
						 //	_getch();
	return 0;
}
//Fractal��ʼ������
int N_Init_stats(Fractal*newton, int wid, int hei) {
	(*newton).Width = wid;//������
	(*newton).Height = hei;//����߶�
	(*newton).Paint_Size = (*newton).Height;//��ͼ���߳�
	(*newton).View_Size = ((*newton).Width - (*newton).Height) * 0.9;//Ԥ�����߳�
	(*newton).x = (*newton).Width - ((*newton).Width - (*newton).Height) / 2;//Ԥ����λ��
	(*newton).y = ((*newton).Width - (*newton).Height) / 2;
	(*newton).xy.xm = (*newton).xy.xn = (*newton).xy.ym = (*newton).xy.yn = 0;//���귶Χ
	(*newton).ColorCount = 200;//�ֱ���
	(*newton).ColorBar = (RGB*)calloc((*newton).ColorCount, sizeof(RGB));//����������
	(*newton).pJ = (Juncture*)malloc((*newton).ColorCount * sizeof(Juncture));//�ؼ��㼯
	(*newton).JunctureCount = 2;//�ؼ�����
	(*newton).pJ[0].rgb = { 0,0,0 };//��ʼ�ؼ���-��˺�
	(*newton).pJ[0].position = 0;
	(*newton).pJ[(*newton).JunctureCount - 1].rgb = { 255,255,255 };//��ʼ�ؼ���-�Ҷ˰�
	(*newton).pJ[(*newton).JunctureCount - 1].position = (*newton).ColorCount - 1;
	ColorBar_Compiler((*newton).pJ, (*newton).JunctureCount, (*newton).ColorBar, (*newton).ColorCount);//��ʼ��������
	N_Init_buttons(newton);//��ʼ����ť��
	return 0;
}
//Newton����ť��ʼ���趨
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
//Newton��ȷ����ť����λ��
int N_Init_btsp(Fractal*newton) {
	int wid, hei;//��ť�����
	int di, dj;//�о࣬�п�
	int rowCount;//����
	int count;
	int i;//ѭ���±�
	wid = (*newton).Width - (*newton).Height;//��ť�����
	hei = (*newton).Height - wid;//��ť��2�߶�
	rowCount = Button_rows((*newton).pB, (*newton).ButtonCount);
	di = 1.0*hei / rowCount;//�о�
	for (i = 0; i < (*newton).ButtonCount; ++i) {
		(*newton).pB[i].y = (*newton).pB[i].i*di + wid - 0.5*di;//������

		count = Button_inArow((*newton).pB, (*newton).ButtonCount, (*newton).pB[i].i);
		dj = 1.0*wid / count;//�����п�
		(*newton).pB[i].x = (*newton).pB[i].j*dj + (*newton).Height - 0.5*dj;//������
		(*newton).pB[i].height = di*0.9;//�߶�
		(*newton).pB[i].width = dj - wid*0.1;//���
	}
	return 0;
}
//////////���ְ�ť��ֵ�趨///////////
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
//////////���ְ�ť��ֵ�趨/////////////
//Fractal��ʼ������
int N_Init_graph(Fractal*newton) {
	cleardevice();//����
	setlinecolor(WHITE);//�ֽ�����ɫ
	line((*newton).Height + 1, 1, (*newton).Height + 1, (*newton).Height);//��ʼ����ͼ��
																		  /*��ʼ��Ԥ����*/
	rectangle((*newton).x - (*newton).View_Size / 2, (*newton).y - (*newton).View_Size / 2, (*newton).x + (*newton).View_Size / 2, (*newton).y + (*newton).View_Size / 2);
	//	_getch();
	Button_showbuttons((*newton).pB, (*newton).ButtonCount);
	ColorBar_show((*newton).pB, (*newton).ButtonCount, (*newton).ColorBar, (*newton).ColorCount);
	//	_getch();

	return 0;
}
//Fractal��ͼ����
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
//Newton����ť����
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
	case cLear:return N_Button_clear(newton);//���2�����¿�ʼFractal
	case sAve:return N_Button_save(newton);
	case bAck:return N_Button_back(newton);//���1���ص�ѡ��
	case qUit:return N_Button_quit(newton);
	default:
		break;
	}
	return -1;
}
//Newton���в����Ƿ��ڻ�ͼ����
int N_IsPaintZone(Fractal*newton) {
	RECT PaintZone;
	PaintZone.left = PaintZone.top = 0;
	PaintZone.right = PaintZone.bottom = (*newton).Paint_Size;
	return IsRectZone(PaintZone, &((*newton).user));
}
//Fractal��ͼ������
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
//Newton���Ŵ����
int N_Enlarge(Fractal*newton) {
	(*newton).isEnlarge = 1;
	N_View_refresh(newton);
	return 0;
}
//������ű�
double N_View_k(Fractal*newton) {
	double k;
	k = (*newton).View_Size / (*newton).Paint_Size;
	return k;
}
//ˢ��Newton��Ԥ��ͼ
int N_View_refresh(Fractal*newton) {
	IMAGE img;
	RECT viewzone;//�Ŵ�Ŀ�귶Χ
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
	if (((*newton).user.L_msg.mkCtrl != 0)) {//Ctrl��ѡ��������
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
//���Newton��Ԥ��ͼ
int N_View_clear(Fractal*newton) {
	RECT viewzone;
	viewzone = RectZone((*newton).x, (*newton).y, (*newton).View_Size, (*newton).View_Size);
	clearrectangle(viewzone.left, viewzone.top, viewzone.right, viewzone.bottom);
	rectangle(viewzone.left, viewzone.top, viewzone.right, viewzone.bottom);
	return 0;
}
//ȷ�����ź��x,y��Χ
int N_Enlarge_tempxy(Fractal*newton) {
	(*newton).temp_xy.xn = (*newton).xy.xn + ((*newton).xy.xm - (*newton).xy.xn)*(*newton).EnlargeZone.left / (*newton).Paint_Size;
	(*newton).temp_xy.xm = (*newton).xy.xn + ((*newton).xy.xm - (*newton).xy.xn)*(*newton).EnlargeZone.right / (*newton).Paint_Size;
	(*newton).temp_xy.yn = (*newton).xy.yn + ((*newton).xy.ym - (*newton).xy.yn)*((*newton).Paint_Size - (*newton).EnlargeZone.bottom) / (*newton).Paint_Size;
	(*newton).temp_xy.ym = (*newton).xy.yn + ((*newton).xy.ym - (*newton).xy.yn)*((*newton).Paint_Size - (*newton).EnlargeZone.top) / (*newton).Paint_Size;
	return 0;
}
//�������ź�����귶Χ
int N_Paint_enlarge(Fractal*newton) {
	(*newton).xy = (*newton).temp_xy;
	N_Button_renew(newton);
	return 0;
}
//Newton��ˢ�°�ť
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
/////////////////��ť�¼�///////////////////
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
//����x�����ֵ
int N_Button_xm(Fractal*newton) {
	int i;
	char s[20];
	char r[25];
	InputBox(s, 20, "������x�����ֵ");
	sscanf_s(s, "%lf", &((*newton).xy.xm));
	i = Button_clear((*newton).pB, (*newton).ButtonCount, xM);
	sprintf_s(r, 25, "xm = %lf", (*newton).xy.xm);
	Button_textout(r, &((*newton).pB[i]));
	N_View_clear(newton);
	(*newton).isEnlarge = 0;
	return -1;
}
//����x����Сֵ
int N_Button_xn(Fractal*newton) {
	int i;
	char s[20];
	char r[25];
	InputBox(s, 20, "������x����Сֵ");
	sscanf_s(s, "%lf", &((*newton).xy.xn));
	i = Button_clear((*newton).pB, (*newton).ButtonCount, xN);
	sprintf_s(r, 25, "xn = %lf", (*newton).xy.xn);
	Button_textout(r, &((*newton).pB[i]));
	N_View_clear(newton);
	(*newton).isEnlarge = 0;
	return -1;
}
//����y�����ֵ
int N_Button_ym(Fractal*newton) {
	int i;
	char s[20];
	char r[25];
	InputBox(s, 20, "������y�����ֵ");
	sscanf_s(s, "%lf", &((*newton).xy.ym));
	i = Button_clear((*newton).pB, (*newton).ButtonCount, yM);
	sprintf_s(r, 25, "ym = %lf", (*newton).xy.ym);
	Button_textout(r, &((*newton).pB[i]));
	N_View_clear(newton);
	(*newton).isEnlarge = 0;
	return -1;
}
//����y����Сֵ
int N_Button_yn(Fractal*newton) {
	int i;
	char s[20];
	char r[25];
	InputBox(s, 20, "������y����Сֵ");
	sscanf_s(s, "%lf", &((*newton).xy.yn));
	i = Button_clear((*newton).pB, (*newton).ButtonCount, yN);
	sprintf_s(r, 25, "yn = %lf", (*newton).xy.yn);
	Button_textout(r, &((*newton).pB[i]));
	N_View_clear(newton);
	(*newton).isEnlarge = 0;
	return -1;
}
//���븴��
int N_Button_ab(Fractal*newton) {
	int i;
	char sa[20];
	char sb[20];
	char r[50];
	InputBox(sa, 20, "������a");
	sscanf_s(sa, "%lf", &((*newton).a));
	InputBox(sb, 20, "������b");
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
//�����ť
int N_Button_clear(Fractal*newton) {
	(*newton).isEnlarge = 0;
	return SendDB("Newton", "��ȷ��Ҫ�����", 2, -1);
}
//����
int N_Button_save(Fractal*newton) {
	IMAGE img;
	getimage(&img, 0, 0, (*newton).Paint_Size, (*newton).Paint_Size);
	saveimage("Newton.bmp", &img);
	SendMB("Newton", "����ɹ���");
	return -1;
}
//���ذ�ť
int N_Button_back(Fractal*newton) {
	return SendDB("Newton", "��ȷ��Ҫ������", 1, -1);
}
//�˳���ť
int N_Button_quit(Fractal*newton) {
	return SendDB("Newton", "��ȷ��Ҫ�˳���", 0, -1);
}
/////////////////��ť�¼�///////////////////
//Fractal�������Ƿ�Ϸ�
int N_CheckIndex(Fractal*newton, double*dx, double*dy) {
	*dx = ((*newton).xy.xm - (*newton).xy.xn) / (*newton).Paint_Size;
	*dy = ((*newton).xy.ym - (*newton).xy.yn) / (*newton).Paint_Size;
	if (*dx <= 0 || *dy <= 0)return 0;
	return 1;
}
//Newton��������
int N_Iterator(long double a, long double b, long double x, long double y, int ColorCount) {
	int time,i,n;
	long double za, zb;//������ʵ�鲿
	long double z;//z��ģ
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
//Newton����ͼ-����
int N_Analyser(Fractal*newton, int*paint) {
	double dx, dy;
	int i, j;
	if (N_CheckIndex(newton, &dx, &dy) == 0) {
		SendMB("��ͼʧ��", "���귶Χ��С");
		return 0;
	}
	double*x = (double*)malloc((*newton).Paint_Size * sizeof(double));
	double*y = (double*)malloc((*newton).Paint_Size * sizeof(double));
	if (x == NULL || y == NULL) {
		SendMB("��ͼʧ��", "����ʧ��");
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
//Newton����ͼ-��ʾ
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
		SendMB("��ͼʧ��", "��ͼ��Ϣ����ʧ��");
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
//Newton����ϸ�µĻ���
int N_Paint2(Fractal*newton) {
	if ((*newton).isEnlarge != 0)N_Paint_enlarge(newton);
	float*paint = (float*)malloc((*newton).Paint_Size*(*newton).Paint_Size * sizeof(int));
	if (paint == NULL) {
		SendMB("��ͼʧ��", "��ͼ��Ϣ����ʧ��");
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
//Newton����ϸ�µĻ���-����
int N_Analyser2(Fractal*newton, float*paint) {
	double dx, dy;
	int i, j;
	if (N_CheckIndex(newton, &dx, &dy) == 0) {
		SendMB("��ͼʧ��", "���귶Χ��С");
		return 0;
	}
	double*x = (double*)malloc((*newton).Paint_Size * sizeof(double));
	double*y = (double*)malloc((*newton).Paint_Size * sizeof(double));
	if (x == NULL || y == NULL) {
		SendMB("��ͼʧ��", "����ʧ��");
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
//Newton����ϸ�µĵ�����
float N_Iterator2(long double a, long double b, long double x, long double y, int ColorCount) {
	float time;
	long double za, zb;//������ʵ�鲿
	long double z;//z��ģ
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
//Newton����ϸ�µĻ���-��ʾ
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
