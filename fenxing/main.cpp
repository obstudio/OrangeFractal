#include"fractal.h"
using namespace std;
/////////////////函数声明///////////////////////
int main();
/////////////////main函数/////////////////////
int main(){
	int choice = 1;
	int wid = 1000;
	int hei = 680;
	initgraph(wid, hei);//注册窗口
	while (choice != 0) {//当分形函数返回值不为0的时候,进入选择界面,否则结束程序
		choice = MainMenu();//choice = mainmenu(wid, hei);这里调用主菜单函数
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
//////////////////其他函数///////////////////