#pragma once
#include"stdafx.h"
#include"structures.h"
#include"functions.h"
/*����*/
/////////////////��������///////////////////////
int gJuliaView(int wid, int hei);//Julia�����ƴ���
int gJ_Initialize(Fractal*gjulia, int wid, int hei);//Julia�������ʼ��
int gJ_Init_stats(Fractal*gjulia, int wid, int hei);//Julia��-��ʼ������
int gJ_Init_buttons(Fractal*gjulia);//Julia����ť��ʼ���趨
int gJ_Init_btsp(Fractal*gjulia);//Julia��ȷ����ť����λ��
							   //////////���ְ�ť��ֵ�趨///////////
int gJ_Init_colorbar(Button*button);
int gJ_Init_xm(Button*button);
int gJ_Init_xn(Button*button);
int gJ_Init_ym(Button*button);
int gJ_Init_yn(Button*button);
int gJ_Init_ab(Button*button);
int gJ_Init_paint(Button*button);
int gJ_Init_clear(Button*button);
int gJ_Init_save(Button*button);
int gJ_Init_back(Button*button);
int gJ_Init_quit(Button*button);
//////////���ְ�ť��ֵ�趨/////////////
int gJ_Init_graph(Fractal*gjulia);//Julia����ʼ������
int gJ_Button_renew(Fractal*gjulia);//Fractalˢ�°�ť
int gJ_Process(Fractal*gjulia);//Julia�����ƹ���
int gJ_Botton_Management(button_type xxx, Fractal*julia);//Julia����ť����
int gJ_IsPaintZone(Fractal*gjulia);//Julia���в����Ƿ��ڻ�ͼ����
int gJ_PaintZone(Fractal*gjulia);//Fractal��ͼ������
int gJ_Enlarge(Fractal*gjulia);//Julia���Ŵ����
double gJ_View_k(Fractal*gjulia);//������ű�
int gJ_View_refresh(Fractal*gjulia);//ˢ��Julia��Ԥ��ͼ
int gJ_View_clear(Fractal*gjulia);//���Julia��Ԥ��ͼ
int gJ_Enlarge_tempxy(Fractal*gjulia);//ȷ�����ź��x,y��Χ
int gJ_Paint_enlarge(Fractal*gjulia);//�������ź�����귶Χ
								   /////////////////Fractal��ť�¼�///////////////////
int gJ_Button_colorbar(Fractal*gjulia);
int gJ_Button_xm(Fractal*gjulia);
int gJ_Button_xn(Fractal*gjulia);
int gJ_Button_ym(Fractal*gjulia);
int gJ_Button_yn(Fractal*gjulia);
int gJ_Button_ab(Fractal*gjulia);
int gJ_Button_paint(Fractal*gjulia);
int gJ_Button_clear(Fractal*gjulia);
int gJ_Button_save(Fractal*gjulia);
int gJ_Button_back(Fractal*gjulia);
int gJ_Button_quit(Fractal*gjulia);
/////////////////Fractal��ť�¼�///////////////////
int gJ_Paint(Fractal*gjulia);//Julia�����ƹ���-��ͼ
int gJ_Analyser(Fractal*gjulia, int*paint);//Julia����ͼ-����
int gJ_Iterator(long double a, long double b, long double x, long double y, int ColorCount);//Julia��������
int gJ_CheckIndex(Fractal*gjulia, double*dx, double*dy);//Fractal�������Ƿ�Ϸ�
int gJ_Show(Fractal*gjulia, int*paint);//Julia����ͼ-��ʾ
int gJ_Paint2(Fractal*gjulia);//Julia����ϸ�µĻ���
int gJ_Analyser2(Fractal*gjulia, float*paint);//Julia����ϸ�µĻ���-����
float gJ_Iterator2(long double a, long double b, long double x, long double y, int ColorCount);//Julia����ϸ�µĵ�����
int gJ_Show2(Fractal*gjulia, float*paint);//Julia����ϸ�µĻ���-��ʾ
int gJ_Finish(Fractal*gjulia);//Julia������-����
int gJ_Freer(Fractal*gjulia);//Julia������-�ͷ�