#include"MainMenu.h"
using namespace std;
//MainMenu窗口
int MainMenu() {
	int cont ;
	init();//初始化
	cont = exam();//运行过程	
	cleardevice();//结束
	return cont;
}
	void init()
	{	
		//文字输出
		outtextxy(300, 100, "Orange Fractal");
		outtextxy(200, 300, "Julia");
		outtextxy(200, 400, "z=z^2+c");
		outtextxy(400, 300, "Gjulia");
		outtextxy(400, 400, "z=z^3+c");
		outtextxy(600, 300, "Mandeblort");
		outtextxy(600, 400, "z=c^2+z");
		outtextxy(800, 550, "Help");
		outtextxy(800, 630, "Exit");
	//	outtextxy(50, 550, "制作者名单：");
	//	outtextxy(50, 600, "橘圆亮    周宇");
	//	outtextxy(50, 650, "朱秋熹    唐昕炜");
		//画按钮区
		setcolor(WHITE);
		//括号中参数代表矩形按钮坐标范围
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
			do { m = GetMouseMsg(); } while (!m.mkLButton);//获取一条鼠标消息
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
