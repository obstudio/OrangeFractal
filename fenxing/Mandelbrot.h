#pragma once
#include"stdafx.h"
#include"structures.h"
#include"functions.h"
/////////////////��������///////////////////////
int MandelbrotView(int wid, int hei);//Mandelbrot�����ƴ���
int M_Initialize(Fractal*mandelbrot, int wid, int hei);//Mandelbrot�������ʼ��
int M_Init_stats(Fractal*mandelbrot, int wid, int hei);//Mandelbrot��-��ʼ������
int M_Init_buttons(Fractal*mandelbrot);//Mandelbrot����ť��ʼ���趨
int M_Init_btsp(Fractal*mandelbrot);//Mandelbrot��ȷ����ť����λ��
							   //////////���ְ�ť��ֵ�趨///////////
int M_Init_colorbar(Button*button);
int M_Init_xm(Button*button);
int M_Init_xn(Button*button);
int M_Init_ym(Button*button);
int M_Init_yn(Button*button);
int M_Init_ab(Button*button);
int M_Init_paint(Button*button);
int M_Init_clear(Button*button);
int M_Init_save(Button*button);
int M_Init_back(Button*button);
int M_Init_quit(Button*button);
//////////���ְ�ť��ֵ�趨/////////////
int M_Init_graph(Fractal*mandelbrot);//Mandelbrot����ʼ������
int M_Button_renew(Fractal*mandelbrot);//Fractalˢ�°�ť
int M_Process(Fractal*mandelbrot);//Mandelbrot�����ƹ���
int M_Botton_Management(button_type xxx, Fractal*mandelbrot);//Mandelbrot����ť����
int M_IsPaintZone(Fractal*mandelbrot);//Mandelbrot���в����Ƿ��ڻ�ͼ����
int M_PaintZone(Fractal*mandelbrot);//Fractal��ͼ������
int M_Enlarge(Fractal*mandelbrot);//Mandelbrot���Ŵ����
double M_View_k(Fractal*mandelbrot);//������ű�
int M_View_refresh(Fractal*mandelbrot);//ˢ��Mandelbrot��Ԥ��ͼ
int M_View_clear(Fractal*mandelbrot);//���Mandelbrot��Ԥ��ͼ
int M_Enlarge_tempxy(Fractal*mandelbrot);//ȷ�����ź��x,y��Χ
int M_Paint_enlarge(Fractal*mandelbrot);//�������ź�����귶Χ
								   /////////////////Fractal��ť�¼�///////////////////
int M_Button_colorbar(Fractal*mandelbrot);
int M_Button_xm(Fractal*mandelbrot);
int M_Button_xn(Fractal*mandelbrot);
int M_Button_ym(Fractal*mandelbrot);
int M_Button_yn(Fractal*mandelbrot);
int M_Button_ab(Fractal*mandelbrot);
int M_Button_paint(Fractal*mandelbrot);
int M_Button_clear(Fractal*mandelbrot);
int M_Button_save(Fractal*mandelbrot);
int M_Button_back(Fractal*mandelbrot);
int M_Button_quit(Fractal*mandelbrot);
/////////////////Fractal��ť�¼�///////////////////
int M_Paint(Fractal*mandelbrot);//Mandelbrot�����ƹ���-��ͼ
int M_Analyser(Fractal*mandelbrot, int*paint);//Mandelbrot����ͼ-����
int M_Iterator(long double a, long double b, long double x, long double y, int ColorCount);//Mandelbrot��������
int M_CheckIndex(Fractal*mandelbrot, double*dx, double*dy);//Fractal�������Ƿ�Ϸ�
int M_Show(Fractal*mandelbrot, int*paint);//Mandelbrot����ͼ-��ʾ
int M_Paint2(Fractal*mandelbrot);//Mandelbrot����ϸ�µĻ���
int M_Analyser2(Fractal*mandelbrot, float*paint);//Mandelbrot����ϸ�µĻ���-����
float M_Iterator2(long double a, long double b, long double x, long double y, int ColorCount);//Mandelbrot����ϸ�µĵ�����
int M_Show2(Fractal*mandelbrot, float*paint);//Mandelbrot����ϸ�µĻ���-��ʾ
int M_Finish(Fractal*mandelbrot);//Mandelbrot������-����
int M_Freer(Fractal*mandelbrot);//Mandelbrot������-�ͷ�
