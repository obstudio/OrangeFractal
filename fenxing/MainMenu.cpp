#include"MainMenu.h"
using namespace std;
//MainMenu����
int MainMenu() {
	int cont ;
	init();//��ʼ��
	cont = exam();//���й���	
	cleardevice();//����
	return cont;
}
	void init()
	{	
		//�������
		outtextxy(300, 100, "Orange Fractal");
		outtextxy(200, 300, "Julia");
		outtextxy(200, 400, "z=z^2+c");
		outtextxy(400, 300, "Gjulia");
		outtextxy(400, 400, "z=z^3+c");
		outtextxy(600, 300, "Mandeblort");
		outtextxy(600, 400, "z=c^2+z");
		outtextxy(800, 550, "Help");
		outtextxy(800, 630, "Exit");
	//	outtextxy(50, 550, "������������");
	//	outtextxy(50, 600, "��Բ��    ����");
	//	outtextxy(50, 650, "������    ����");
		//����ť��
		setcolor(WHITE);
		//�����в���������ΰ�ť���귶Χ
		rectangle(200, 300, 300, 400);
		rectangle(400, 300, 500, 400);
		rectangle(600, 300, 700, 400);
		rectangle(780, 540, 850, 580);
		rectangle(780, 620, 850, 660);

	}



	int exam()
	{
		MOUSEMSG m;
		while (true)
		{
			do { m = GetMouseMsg(); } while (!m.mkLButton);//��ȡһ�������Ϣ
			if (m.x > 200 && m.y > 300 && m.y < 400 && m.x < 300)
			{
				return 1;

			}
			if (m.x > 400 && m.y > 300 && m.y < 400 && m.x < 500)
			{
				return 2;

			}
			if (m.x > 600 && m.y > 300 && m.y < 400 && m.x < 700)
			{
				return 3;

			}

			if (m.x > 780 && m.y > 540 && m.y < 580 && m.x < 850)
			{
				WinExec("Help.txt", SW_SHOW);
			}
			if (m.x > 780 && m.y > 620 && m.y < 660 && m.x < 850)
			{
				return 0;
			}
		}
		Sleep(2);
	}
