#pragma once
#include"stdafx.h"
/*��κ�*/
enum button_type { jUlia, hElp, cOlorbar, xM, xN, yM, yN, aB, pAint, cLear, sAve, bAck, qUit,  tAn90 };
///////////////�ṹ�嶨��/////////////////////
struct XYRange {//���귶Χ
	double xn;
	double xm;
	double yn;
	double ym;
};
struct User {//�û�����
//���
	MOUSEMSG F_msg;//����ʱ�������Ϣ
	MOUSEMSG L_msg;//�ɿ�ʱ�������Ϣ
};
struct Button {
	int i; int j;//�дΡ��д�
	int x; int y;//λ��
	int width; int height;//���
	button_type type;//��ť����
	int IsTriggerd = 0;//�Ƿ񱻰���
};
struct RGB {//RGB��ɫ
	int R;
	int G;
	int B;
};
struct Juncture {
	int position;//�������ϵ�λ��
	RGB rgb;//��ɫֵ
};
struct Fractal {
	int Width; int Height;//�����ܿ���ܸ�
	int Paint_Size; int View_Size;//��ͼ����Ԥ������С
	int x; int y;//Ԥ����λ��
	int isEnlarge = 0;//���Ż��Ʊ�ǣ���ʼΪ��
	RECT EnlargeZone;//��������
	XYRange xy;//���귶Χ
	XYRange temp_xy;//�ݴ����귶Χ
	double a = 0; double b = 0; double c = 0; double d = 0;//���ֲ���
	RGB*ColorBar;//������
	int ColorCount;//��ɫ������ɫ���ֱ��ʣ�
	Juncture* pJ;//�ؼ�ɫ��
	int JunctureCount;//ɫ����
	Button* pB;//��ť��
	int ButtonCount;//��ť��
	User user;//����
};
