#include"fractal.h"
using namespace std;
/////////////////��������///////////////////////
int main();
/////////////////main����/////////////////////
int main(){
	int choice = 1;
	int wid = 1000;
	int hei = 680;
	initgraph(wid, hei);//ע�ᴰ��
	while (choice != 0) {//�����κ�������ֵ��Ϊ0��ʱ��,����ѡ�����,�����������
		choice = MainMenu();//choice = mainmenu(wid, hei);����������˵�����
//		_getch();
//		choice = 4;
		switch (choice) {
		case 1:	
			PlaySound("funky.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); ;
			choice = JuliaView(wid, hei);
			PlaySound(NULL, NULL, NULL);
			break;
		case 2:
			PlaySound("funky.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); ;
			choice = gJuliaView(wid, hei);
			PlaySound(NULL, NULL, NULL);
			break;
		case 3:
			PlaySound("funky.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); ;
			choice = MandelbrotView(wid, hei);
			PlaySound(NULL, NULL, NULL);
			break;
		case 4:
			PlaySound("funky.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); ;
			//choice = NewtonView(wid, hei);
			PlaySound(NULL, NULL, NULL);
			break;
		default:break;
		}
	}
	closegraph();
	return 0;
}
//////////////////��������///////////////////