#pragma once
#include"stdafx.h"
#include"structures.h"
#include"functions.h"
/////////////////��������///////////////////////
int JuliaView(int wid, int hei);//Julia�����ƴ���
int J_Initialize(Fractal*julia, int wid, int hei);//Julia�������ʼ��
int J_Init_stats(Fractal*julia, int wid, int hei);//Julia��-��ʼ������
int J_Init_buttons(Fractal*julia);//Julia����ť��ʼ���趨
int J_Init_btsp(Fractal*julia);//Julia��ȷ����ť����λ��
//////////���ְ�ť��ֵ�趨///////////
int J_Init_colorbar(Button*button);
int J_Init_xm(Button*button);
int J_Init_xn(Button*button);
int J_Init_ym(Button*button);
int J_Init_yn(Button*button);
int J_Init_ab(Button*button);
int J_Init_paint(Button*button);
int J_Init_clear(Button*button);
int J_Init_save(Button*button);
int J_Init_back(Button*button);
int J_Init_quit(Button*button);
//////////���ְ�ť��ֵ�趨/////////////
int J_Init_graph(Fractal*julia);//Julia����ʼ������
int J_Button_renew(Fractal*julia);//Fractalˢ�°�ť
int J_Process(Fractal*julia);//Julia�����ƹ���
int J_Botton_Management(button_type xxx, Fractal*julia);//Julia����ť����
int J_IsPaintZone(Fractal*julia);//Julia���в����Ƿ��ڻ�ͼ����
int J_PaintZone(Fractal*julia);//Fractal��ͼ������
int J_Enlarge(Fractal*julia);//Julia���Ŵ����
double J_View_k(Fractal*julia);//������ű�
int J_View_refresh(Fractal*julia);//ˢ��Julia��Ԥ��ͼ
int J_View_clear(Fractal*julia);//���Julia��Ԥ��ͼ
int J_Enlarge_tempxy(Fractal*julia);//ȷ�����ź��x,y��Χ
int J_Paint_enlarge(Fractal*julia);//�������ź�����귶Χ
/////////////////Fractal��ť�¼�///////////////////
int J_Button_colorbar(Fractal*julia);
int J_Button_xm(Fractal*julia);
int J_Button_xn(Fractal*julia);
int J_Button_ym(Fractal*julia);
int J_Button_yn(Fractal*julia);
int J_Button_ab(Fractal*julia);
int J_Button_paint(Fractal*julia);
int J_Button_clear(Fractal*julia);
int J_Button_save(Fractal*julia);
int J_Button_back(Fractal*julia);
int J_Button_quit(Fractal*julia);
/////////////////Fractal��ť�¼�///////////////////
int J_Paint(Fractal*julia);//Julia�����ƹ���-��ͼ
int J_Analyser(Fractal*julia, int*paint);//Julia����ͼ-����
int J_Iterator(long double a, long double b, long double x, long double y, int ColorCount);//Julia��������
int J_CheckIndex(Fractal*julia, double*dx, double*dy);//Fractal�������Ƿ�Ϸ�
int J_Show(Fractal*julia, int*paint);//Julia����ͼ-��ʾ
int J_Paint2(Fractal*julia);//Julia����ϸ�µĻ���
int J_Analyser2(Fractal*julia, float*paint);//Julia����ϸ�µĻ���-����
float J_Iterator2(long double a, long double b, long double x, long double y, int ColorCount);//Julia����ϸ�µĵ�����
int J_Show2(Fractal*julia, float*paint);//Julia����ϸ�µĻ���-��ʾ
int J_Finish(Fractal*julia);//Julia������-����
int J_Freer(Fractal*julia);//Julia������-�ͷ�