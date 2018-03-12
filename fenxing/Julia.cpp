#include"Julia.h"
using namespace std;
/*��κ�*/
//julia������
int JuliaView(int wid, int hei) {
	Fractal julia;//����Fractal����ṹ
	int cont = 2;
	while (cont == 2) {
		J_Initialize(&julia, wid, hei);//��ʼ��
		cont = J_Process(&julia);//���й���	
		J_Finish(&julia);//����
	}
	return cont;
}
//Fractal��ʼ��
int J_Initialize(Fractal*julia, int wid, int hei) {
	J_Init_stats(julia, wid, hei);//��ʼ������
	J_Init_graph(julia);//��ʼ������
						//	_getch();
	return 0;
}
//Fractal��ʼ������
int J_Init_stats(Fractal*julia, int wid, int hei) {
	(*julia).Width = wid;//������
	(*julia).Height = hei;//����߶�
	(*julia).Paint_Size = (*julia).Height;//��ͼ���߳�
	(*julia).View_Size = ((*julia).Width - (*julia).Height) * 0.9;//Ԥ�����߳�
	(*julia).x = (*julia).Width - ((*julia).Width - (*julia).Height) / 2;//Ԥ����λ��
	(*julia).y = ((*julia).Width - (*julia).Height) / 2;
	(*julia).xy.xm = (*julia).xy.xn = (*julia).xy.ym = (*julia).xy.yn = 0;//���귶Χ
	(*julia).ColorCount = 500;//�ֱ���
	(*julia).ColorBar = (RGB*)calloc((*julia).ColorCount, sizeof(RGB));//����������
	(*julia).pJ = (Juncture*)malloc((*julia).ColorCount * sizeof(Juncture));//�ؼ��㼯
	(*julia).JunctureCount = 2;//�ؼ�����
	(*julia).pJ[0].rgb = { 0,0,0 };//��ʼ�ؼ���-��˺�
	(*julia).pJ[0].position = 0;
	(*julia).pJ[(*julia).JunctureCount - 1].rgb = { 255,255,255 };//��ʼ�ؼ���-�Ҷ˰�
	(*julia).pJ[(*julia).JunctureCount - 1].position = (*julia).ColorCount - 1;
	ColorBar_Compiler((*julia).pJ, (*julia).JunctureCount, (*julia).ColorBar, (*julia).ColorCount);//��ʼ��������
	J_Init_buttons(julia);//��ʼ����ť��
	return 0;
}
//Julia����ť��ʼ���趨
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
//Julia��ȷ����ť����λ��
int J_Init_btsp(Fractal*julia) {
	int wid, hei;//��ť�����
	int di, dj;//�о࣬�п�
	int rowCount;//����
	int count;
	int i;//ѭ���±�
	wid = (*julia).Width - (*julia).Height;//��ť�����
	hei = (*julia).Height - wid;//��ť��2�߶�
	rowCount = Button_rows((*julia).pB, (*julia).ButtonCount);
	di = 1.0*hei / rowCount;//�о�
	for (i = 0; i < (*julia).ButtonCount; ++i) {
		(*julia).pB[i].y = (*julia).pB[i].i*di + wid - 0.5*di;//������

		count = Button_inArow((*julia).pB, (*julia).ButtonCount, (*julia).pB[i].i);
		dj = 1.0*wid / count;//�����п�
		(*julia).pB[i].x = (*julia).pB[i].j*dj + (*julia).Height - 0.5*dj;//������
		(*julia).pB[i].height = di*0.9;//�߶�
		(*julia).pB[i].width = dj - wid*0.1;//���
	}
	return 0;
}
//////////���ְ�ť��ֵ�趨///////////
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
//////////���ְ�ť��ֵ�趨/////////////
//Fractal��ʼ������
int J_Init_graph(Fractal*julia) {
	cleardevice();//����
	setlinecolor(WHITE);//�ֽ�����ɫ
	line((*julia).Height + 1, 1, (*julia).Height + 1, (*julia).Height);//��ʼ����ͼ��
																	   /*��ʼ��Ԥ����*/
	rectangle((*julia).x - (*julia).View_Size / 2, (*julia).y - (*julia).View_Size / 2, (*julia).x + (*julia).View_Size / 2, (*julia).y + (*julia).View_Size / 2);
	//	_getch();
	Button_showbuttons((*julia).pB, (*julia).ButtonCount);
	ColorBar_show((*julia).pB, (*julia).ButtonCount, (*julia).ColorBar, (*julia).ColorCount);
	//	_getch();

	return 0;
}
//Fractal��ͼ����
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
//Julia����ť����
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
	case cLear:return J_Button_clear(julia);//���2�����¿�ʼFractal
	case sAve:return J_Button_save(julia);
	case bAck:return J_Button_back(julia);//���1���ص�ѡ��
	case qUit:return J_Button_quit(julia);
	default:
		break;
	}
	return -1;
}
//Julia���в����Ƿ��ڻ�ͼ����
int J_IsPaintZone(Fractal*julia) {
	RECT PaintZone;
	PaintZone.left = PaintZone.top = 0;
	PaintZone.right = PaintZone.bottom = (*julia).Paint_Size;
	return IsRectZone(PaintZone, &((*julia).user));
}
//Fractal��ͼ������
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
//Julia���Ŵ����
int J_Enlarge(Fractal*julia) {
	(*julia).isEnlarge = 1;
	J_View_refresh(julia);
	return 0;
}
//������ű�
double J_View_k(Fractal*julia) {
	double k;
	k = (*julia).View_Size / (*julia).Paint_Size;
	return k;
}
//ˢ��Julia��Ԥ��ͼ
int J_View_refresh(Fractal*julia) {
	IMAGE img;
	RECT viewzone;//�Ŵ�Ŀ�귶Χ
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
	if (((*julia).user.L_msg.mkCtrl != 0)) {//Ctrl��ѡ��������
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
//���Julia��Ԥ��ͼ
int J_View_clear(Fractal*julia) {
	RECT viewzone;
	viewzone = RectZone((*julia).x, (*julia).y, (*julia).View_Size, (*julia).View_Size);
	clearrectangle(viewzone.left, viewzone.top, viewzone.right, viewzone.bottom);
	rectangle(viewzone.left, viewzone.top, viewzone.right, viewzone.bottom);
	return 0;
}
//ȷ�����ź��x,y��Χ
int J_Enlarge_tempxy(Fractal*julia) {
	(*julia).temp_xy.xn = (*julia).xy.xn + ((*julia).xy.xm - (*julia).xy.xn)*(*julia).EnlargeZone.left / (*julia).Paint_Size;
	(*julia).temp_xy.xm = (*julia).xy.xn + ((*julia).xy.xm - (*julia).xy.xn)*(*julia).EnlargeZone.right / (*julia).Paint_Size;
	(*julia).temp_xy.yn = (*julia).xy.yn + ((*julia).xy.ym - (*julia).xy.yn)*((*julia).Paint_Size - (*julia).EnlargeZone.bottom) / (*julia).Paint_Size;
	(*julia).temp_xy.ym = (*julia).xy.yn + ((*julia).xy.ym - (*julia).xy.yn)*((*julia).Paint_Size - (*julia).EnlargeZone.top) / (*julia).Paint_Size;
	return 0;
}
//�������ź�����귶Χ
int J_Paint_enlarge(Fractal*julia) {
	(*julia).xy = (*julia).temp_xy;
	J_Button_renew(julia);
	return 0;
}
//Julia��ˢ�°�ť
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
/////////////////��ť�¼�///////////////////
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
//����x�����ֵ
int J_Button_xm(Fractal*julia) {
	int i;
	char s[20];
	char r[25];
	InputBox(s, 20, "������x�����ֵ");
	sscanf_s(s, "%lf", &((*julia).xy.xm));
	i = Button_clear((*julia).pB, (*julia).ButtonCount, xM);
	sprintf_s(r, 25, "xm = %lf", (*julia).xy.xm);
	Button_textout(r, &((*julia).pB[i]));
	J_View_clear(julia);
	(*julia).isEnlarge = 0;
	return -1;
}
//����x����Сֵ
int J_Button_xn(Fractal*julia) {
	int i;
	char s[20];
	char r[25];
	InputBox(s, 20, "������x����Сֵ");
	sscanf_s(s, "%lf", &((*julia).xy.xn));
	i = Button_clear((*julia).pB, (*julia).ButtonCount, xN);
	sprintf_s(r, 25, "xn = %lf", (*julia).xy.xn);
	Button_textout(r, &((*julia).pB[i]));
	J_View_clear(julia);
	(*julia).isEnlarge = 0;
	return -1;
}
//����y�����ֵ
int J_Button_ym(Fractal*julia) {
	int i;
	char s[20];
	char r[25];
	InputBox(s, 20, "������y�����ֵ");
	sscanf_s(s, "%lf", &((*julia).xy.ym));
	i = Button_clear((*julia).pB, (*julia).ButtonCount, yM);
	sprintf_s(r, 25, "ym = %lf", (*julia).xy.ym);
	Button_textout(r, &((*julia).pB[i]));
	J_View_clear(julia);
	(*julia).isEnlarge = 0;
	return -1;
}
//����y����Сֵ
int J_Button_yn(Fractal*julia) {
	int i;
	char s[20];
	char r[25];
	InputBox(s, 20, "������y����Сֵ");
	sscanf_s(s, "%lf", &((*julia).xy.yn));
	i = Button_clear((*julia).pB, (*julia).ButtonCount, yN);
	sprintf_s(r, 25, "yn = %lf", (*julia).xy.yn);
	Button_textout(r, &((*julia).pB[i]));
	J_View_clear(julia);
	(*julia).isEnlarge = 0;
	return -1;
}
//���븴��
int J_Button_ab(Fractal*julia) {
	int i;
	char sa[20];
	char sb[20];
	char r[50];
	InputBox(sa, 20, "������a");
	sscanf_s(sa, "%lf", &((*julia).a));
	InputBox(sb, 20, "������b");
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
//�����ť
int J_Button_clear(Fractal*julia) {
	(*julia).isEnlarge = 0;
	return SendDB("Julia", "��ȷ��Ҫ�����", 2, -1);
}
//����
int J_Button_save(Fractal*julia) {
	IMAGE img;
	getimage(&img, 0, 0, (*julia).Paint_Size, (*julia).Paint_Size);
	saveimage("Julia.bmp", &img);
	SendMB("Julia", "����ɹ���");
	return -1;
}
//���ذ�ť
int J_Button_back(Fractal*julia) {
	return SendDB("Julia", "��ȷ��Ҫ������", 1, -1);
}
//�˳���ť
int J_Button_quit(Fractal*julia) {
	return SendDB("Julia", "��ȷ��Ҫ�˳���", 0, -1);
}
/////////////////��ť�¼�///////////////////
//Fractal�������Ƿ�Ϸ�
int J_CheckIndex(Fractal*julia, double*dx, double*dy) {
	*dx = ((*julia).xy.xm - (*julia).xy.xn) / (*julia).Paint_Size;
	*dy = ((*julia).xy.ym - (*julia).xy.yn) / (*julia).Paint_Size;
	if (*dx <= 0 || *dy <= 0)return 0;
	return 1;
}
//Julia��������
int J_Iterator(long double a, long double b, long double x, long double y, int ColorCount) {
	int time;
	long double za, zb;//������ʵ�鲿
	long double z;//z��ģ
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
//Julia����ͼ-����
int J_Analyser(Fractal*julia, int*paint) {
	double dx, dy;
	int i, j;
	if (J_CheckIndex(julia, &dx, &dy) == 0) { 
		SendMB("��ͼʧ��", "���귶Χ��С");
		return 0;
	}
	double*x = (double*)malloc((*julia).Paint_Size * sizeof(double));
	double*y = (double*)malloc((*julia).Paint_Size * sizeof(double));
	if (x == NULL || y == NULL) {
		SendMB("��ͼʧ��", "����ʧ��");
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
//Julia����ͼ-��ʾ
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
		SendMB("��ͼʧ��", "��ͼ��Ϣ����ʧ��");
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
//Julia����ϸ�µĻ���
int J_Paint2(Fractal*julia) {
	if ((*julia).isEnlarge != 0)J_Paint_enlarge(julia);
	float*paint = (float*)malloc((*julia).Paint_Size*(*julia).Paint_Size * sizeof(int));
	if (paint == NULL) {
		SendMB("��ͼʧ��", "��ͼ��Ϣ����ʧ��");
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
//Julia����ϸ�µĻ���-����
int J_Analyser2(Fractal*julia, float*paint) {
	double dx, dy;
	int i, j;
	if (J_CheckIndex(julia, &dx, &dy) == 0) {
		SendMB("��ͼʧ��", "���귶Χ��С");
		return 0;
	}
	double*x = (double*)malloc((*julia).Paint_Size * sizeof(double));
	double*y = (double*)malloc((*julia).Paint_Size * sizeof(double));
	if (x == NULL || y == NULL) {
		SendMB("��ͼʧ��", "����ʧ��");
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
//Julia����ϸ�µĵ�����
float J_Iterator2(long double a, long double b, long double x, long double y, int ColorCount) {
	float time;
	long double za, zb;//������ʵ�鲿
	long double z;//z��ģ
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
//Julia����ϸ�µĻ���-��ʾ
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
