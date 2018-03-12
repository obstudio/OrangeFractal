#pragma once
#include"stdafx.h"
#include"structures.h"
/////////////////��������///////////////////////
/////////////////Buttonͨ��/////////////////////
int Button_rows(Button*button, int ButtonCount);//ȷ����ť����
int Button_inArow(Button*button, int ButtonCount, int row);//ȷ��һ���ڰ�ť����
int Button_showbuttons(Button*button, int ButtonCount);//��ʾ��ť��
int Button_textout(LPCTSTR str, Button*button);//�����ť����
int Button_clear(Button*button, int ButtonCount, button_type type);//��հ�ť����
button_type Button_Judge(Button*button, int ButtonCount, User*user);//�жϰ�ť����
int Button_Reset(Button*button, int ButtonCount);//�����а�ť��״̬�ָ�Ϊδ����
int Button_Find(Button*button, int ButtonCount);//�ҵ���������ť�ı��

/////////////////ColorBarͨ��/////////////////////
int ColorBar_show(Button*button, int ButtonCount, RGB*ColorBar, int ColorCount);//��ʾ���н�����
int ColorBar_paint(Button*button, RGB*ColorBar, int ColorCount);//��ʾһ��������
int ColorBar_GetPosition(User*user, Button*button, int ColorCount);//ȷ����ɫ���λ��
int Juncture_Find(int position, Juncture*pJ, int* JunctureCount, int ColorCount);//�õ�Ҫ�޸ĵĹؼ�ɫ��
int Juncture_Edit(Juncture*pJ);//�༭�ؼ�ɫ��
int Juncture_Sort(Juncture*pJ, int JunctureCount);//�ؼ�ɫ������
int Tween_Shaper(Juncture*pJ, RGB*ColorBar);//���������ڹؼ�ɫ������ɽ���
int ColorBar_Compiler(Juncture*pJ, int JunctureCount, RGB*ColorBar, int ColourCount);//ˢ����ɫ��

/////////////////Userͨ��/////////////////////
int GetUser(User*user);//��ȡ�û�����
int ResetUser(User*user);//�����û�����
int IsRectZone(RECT rect, User*user);//ȷ�������Ƿ��ھ���������
//////////////////Fractal����ͨ��///////////////

/////////////////Others/////////////////////////
RECT RectZone(int x, int y, int wid, int hei);//ȷ����������
IMAGE ResizePic(IMAGE*img, int New_wid, int New_hei);//����ͼƬ
int SendMB(LPCSTR title, LPCTSTR message);//����������Ϣ
int SendDB(LPCSTR title, LPCTSTR message, int a, int b);//�����жϿ�
