#pragma once
#pragma once
#include"stdafx.h"
#include"structures.h"
#include"functions.h"
/*����*/
/////////////////��������///////////////////////
int NewtonView(int wid, int hei);//newton�����ƴ���
int N_Initialize(Fractal*newton, int wid, int hei);//newton�������ʼ��
int N_Init_stats(Fractal*newton, int wid, int hei);//newton��-��ʼ������
int N_Init_buttons(Fractal*newton);//newton����ť��ʼ���趨
int N_Init_btsp(Fractal*newton);//newton��ȷ����ť����λ��
								//////////���ְ�ť��ֵ�趨///////////
int N_Init_colorbar(Button*button);
int N_Init_xm(Button*button);
int N_Init_xn(Button*button);
int N_Init_ym(Button*button);
int N_Init_yn(Button*button);
int N_Init_ab(Button*button);
int N_Init_paint(Button*button);
int N_Init_clear(Button*button);
int N_Init_save(Button*button);
int N_Init_back(Button*button);
int N_Init_quit(Button*button);
//////////���ְ�ť��ֵ�趨/////////////
int N_Init_graph(Fractal*newton);//newton����ʼ������
int N_Button_renew(Fractal*newton);//Fractalˢ�°�ť
int N_Process(Fractal*newton);//newton�����ƹ���
int N_Botton_Management(button_type xxx, Fractal*julia);//newton����ť����
int N_IsPaintZone(Fractal*newton);//newton���в����Ƿ��ڻ�ͼ����
int N_PaintZone(Fractal*newton);//Fractal��ͼ������
int N_Enlarge(Fractal*newton);//newton���Ŵ����
double N_View_k(Fractal*newton);//������ű�
int N_View_refresh(Fractal*newton);//ˢ��newton��Ԥ��ͼ
int N_View_clear(Fractal*newton);//���newton��Ԥ��ͼ
int N_Enlarge_tempxy(Fractal*newton);//ȷ�����ź��x,y��Χ
int N_Paint_enlarge(Fractal*newton);//�������ź�����귶Χ
									/////////////////Fractal��ť�¼�///////////////////
int N_Button_colorbar(Fractal*newton);
int N_Button_xm(Fractal*newton);
int N_Button_xn(Fractal*newton);
int N_Button_ym(Fractal*newton);
int N_Button_yn(Fractal*newton);
int N_Button_ab(Fractal*newton);
int N_Button_paint(Fractal*newton);
int N_Button_clear(Fractal*newton);
int N_Button_save(Fractal*newton);
int N_Button_back(Fractal*newton);
int N_Button_quit(Fractal*newton);
/////////////////Fractal��ť�¼�///////////////////
int N_Paint(Fractal*newton);//newton�����ƹ���-��ͼ
int N_Analyser(Fractal*newton, int*paint);//newton����ͼ-����
int N_Iterator(long double a, long double b, long double x, long double y, int ColorCount);//newton��������
int N_CheckIndex(Fractal*newton, double*dx, double*dy);//Fractal�������Ƿ�Ϸ�
int N_Show(Fractal*newton, int*paint);//newton����ͼ-��ʾ
int N_Paint2(Fractal*newton);//newton����ϸ�µĻ���
int N_Analyser2(Fractal*newton, float*paint);//newton����ϸ�µĻ���-����
float N_Iterator2(long double a, long double b, long double x, long double y, int ColorCount);//newton����ϸ�µĵ�����
int N_Show2(Fractal*newton, float*paint);//newton����ϸ�µĻ���-��ʾ
int N_Finish(Fractal*newton);//newton������-����
int N_Freer(Fractal*newton);//newton������-�ͷ�
