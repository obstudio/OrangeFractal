#include"stdafx.h"
#include"structures.h"
#include"functions.h"
using namespace std;
/////////////////Button通用/////////////////////
//确定按钮行数
int Button_rows(Button*button, int ButtonCount) {
	int rowCount = 1;//行数
	int i;
	for (i = 0; i < ButtonCount; ++i) {
		if (button[i].i > rowCount)rowCount = button[i].i;
	}
	return rowCount;
}
//确定一行内按钮个数
int Button_inArow(Button*button, int ButtonCount, int row) {
	int count = 1;//同行个数 
	int i;
	for (i = 0; i < ButtonCount; ++i) {
		if ((button[i].i == row) && (count < button[i].j))count = button[i].j;
	}
	return count;
}
//显示按钮集
/*cOlorbar,xM,xN,yM,yN,aB,pAint,cLear,sAve,bAck,qUit*/
int Button_showbuttons(Button*button, int ButtonCount) {
	int i;
	settextcolor(WHITE);
	for (i = 0; i < ButtonCount; ++i) {
		rectangle(button[i].x - button[i].width / 2, button[i].y - button[i].height / 2, button[i].x + button[i].width / 2, button[i].y + button[i].height / 2);
		switch (button[i].type) {
		case cOlorbar:Button_textout(_T("颜色渐变条"), &button[i]); break;
		case xM:Button_textout(_T("xm = 0.0"), &button[i]); break;
		case xN:Button_textout(_T("xn = 0.0"), &button[i]); break;
		case yM:Button_textout(_T("ym = 0.0"), &button[i]); break;
		case yN:Button_textout(_T("yn = 0.0"), &button[i]); break;
		case aB:Button_textout(_T("c = 0.0 + 0.0 * i"), &button[i]); break;
		case pAint:Button_textout(_T("开始绘图"), &button[i]); break;
		case cLear:Button_textout(_T("清除"), &button[i]); break;
		case sAve:Button_textout(_T("保存"), &button[i]); break;
		case bAck:Button_textout(_T("返回"), &button[i]); break;
		case qUit:Button_textout(_T("退出"), &button[i]); break;
		default:
			break;
		}
	}
	return 0;
}
//输出按钮文字
int Button_textout(LPCTSTR str, Button*button) {
	RECT rect = { (*button).x - (*button).width / 2, (*button).y - (*button).height * 2 / 7, (*button).x + (*button).width / 2, (*button).y + (*button).height / 2 };
	drawtext(str, &rect, DT_CENTER | DT_VCENTER);
	return 0;
}

//判断按钮类型
button_type Button_Judge(Button*button, int ButtonCount, User*user) {
	int i;
	RECT rect;
	for (i = 0; i < ButtonCount; ++i) {
		rect = RectZone(button[i].x, button[i].y, button[i].width, button[i].height);
		if (IsRectZone(rect, user)) {
			button[i].IsTriggerd = 1;
			return button[i].type;
		}
	}
	return tAn90;
}
//清空按钮内容
int Button_clear(Button*button, int ButtonCount, button_type type) {
	int i;
	RECT rect;
	for (i = 0; i < ButtonCount; ++i) {
		if (button[i].type == type&&button[i].IsTriggerd == 1) {
			rect = RectZone(button[i].x, button[i].y, button[i].width, button[i].height);
			clearrectangle(rect.left + 1, rect.top + 1, rect.right - 1, rect.bottom - 1);
			return i;
		}
	}
	return 0;
}

//将所有按钮的状态恢复为未触发
int Button_Reset(Button*button, int ButtonCount) {
	int i;
	for (i = 0; i < ButtonCount; ++i) {
		(*button).IsTriggerd = 0;
	}
	return 0;
}
//找到被触发按钮的编号
int Button_Find(Button*button, int ButtonCount) {
	int i;
	for (i = 0; i < ButtonCount; ++i) {
		if (button[i].IsTriggerd != 0)return i;
	}
	return -1;
}

/////////////////ColorBar通用/////////////////////
//显示所有渐变条
int ColorBar_show(Button*button, int ButtonCount, RGB*ColorBar, int ColorCount) {
	int i;//循环下标
	for (i = 0; i < ButtonCount; ++i) {//遍历所有按钮
		if (button[i].type == cOlorbar) //如果为渐变条
			ColorBar_paint(&button[i], ColorBar, ColorCount);
	}
	return 0;
}
//显示一个渐变条
int ColorBar_paint(Button*button, RGB*ColorBar, int ColorCount) {
	int i, d;//渐变条上的点位置和它在颜色表上对应的位置
	int R, G, B;//颜色值
	int start_x, start_y, end_x, end_y;//涂色矩形区域参数
	float k;//渐变条到颜色表的缩放比
	start_x = (*button).x - (*button).width / 2 + 1;
	end_x = (*button).x + (*button).width / 2 - 1;
	start_y = (*button).y - (*button).height / 2 + 1;
	end_y = (*button).y + (*button).height / 2 - 1;//确定矩形区域参数
	k = 1.0*(ColorCount - 1) / (end_x - start_x);//确定缩放比
	for (i = 0; i <= end_x - start_x; ++i) {
		d = i*k;
		R = ColorBar[d].R;
		G = ColorBar[d].G;
		B = ColorBar[d].B;
		setlinecolor(RGB(R, G, B));
		line(i + start_x, start_y, i + start_x, end_y);
	}
	setlinecolor(WHITE);
	return 0;
}
//确定颜色点的位置
int ColorBar_GetPosition(User*user, Button*button, int ColorCount) {
	int position = 0;
	position = 1.0 * (ColorCount - 1)*((*user).F_msg.x + (*button).width / 2 - (*button).x) / (*button).width;
	if (position < 0)position = 0;
	if (position >= ColorCount)position = ColorCount - 1;
	return position;
}
//得到要修改的关键色点
int Juncture_Find(int position, Juncture*pJ, int* JunctureCount, int ColorCount) {
	int i = 0;
	int delta;//误差
	delta = ColorCount*1.0 / 50;
	for (i = 0; i < *JunctureCount; ++i) {
		if ((position - pJ[i].position)*(position - pJ[i].position) < delta*delta)
			return i;
	}
	i = *JunctureCount;
	(*JunctureCount)++;
	pJ[i].position = position;
	return i;
}
//编辑关键色点
int Juncture_Edit(Juncture*pJ) {
	char r[4];
	char g[4];
	char b[4];
	InputBox(r, 4, "请输入红色值(0-255)");
	InputBox(g, 4, "请输入绿色值(0-255)");
	InputBox(b, 4, "请输入蓝色值(0-255)");
	sscanf_s(r, "%d", &((*pJ).rgb.R));
	sscanf_s(g, "%d", &((*pJ).rgb.G));
	sscanf_s(b, "%d", &((*pJ).rgb.B));
	if ((*pJ).rgb.R < 0)(*pJ).rgb.R = 0;
	if ((*pJ).rgb.G < 0)(*pJ).rgb.G = 0;
	if ((*pJ).rgb.B < 0)(*pJ).rgb.B = 0;
	if ((*pJ).rgb.R > 255)(*pJ).rgb.R = 255;
	if ((*pJ).rgb.G > 255)(*pJ).rgb.G = 255;
	if ((*pJ).rgb.B > 255)(*pJ).rgb.B = 255;
	return 0;
}
//关键色点排序
int Juncture_Sort(Juncture*pJ, int JunctureCount) {
	Juncture*temp = pJ;//交换暂存器
	int i, j, exchange;
	for (i = 0; i < JunctureCount; ++i) {
		exchange = 0;
		for (j = 0; j < JunctureCount - 1; ++j) {
			if (pJ[j].position > pJ[j + 1].position) {
				*temp = pJ[j];
				pJ[j] = pJ[j + 1];
				pJ[j + 1] = *temp;
				exchange++;
			}
		}
		if (exchange == 0)
			return 0;
	}
	return 0;
}
//在两个相邻关键色点间生成渐变
int Tween_Shaper(Juncture*pJ, RGB*ColorBar) {
	int start, end;//起始位置，终止位置
	int sR, sG, sB, eR, eG, eB;//起止点颜色值
	int i;
	start = pJ->position;//得到起始位置
	ColorBar[start] = pJ->rgb;//更改起始点的颜色
	sR = ColorBar[start].R;
	sG = ColorBar[start].G;
	sB = ColorBar[start].B;//记录起点颜色值
	pJ++;//下一个关键点
	end = pJ->position;//得到终止位置
	ColorBar[pJ->position] = pJ->rgb;//更改终止点的颜色
	eR = ColorBar[end].R;
	eG = ColorBar[end].G;
	eB = ColorBar[end].B;//记录终点颜色值
	for (i = start; i < end; ++i) {//渐变计算
		ColorBar[i].R = sR + (i - start)*(eR - sR) / (end - start);
		ColorBar[i].G = sG + (i - start)*(eG - sG) / (end - start);
		ColorBar[i].B = sB + (i - start)*(eB - sB) / (end - start);
	}
	return 0;
}
//刷新颜色表
int ColorBar_Compiler(Juncture*pJ, int JunctureCount, RGB*ColorBar, int ColourCount) {
	int i;//循环下标
	Juncture_Sort(pJ, JunctureCount);//对关键色点排序
	for (i = 0; i < JunctureCount - 1; i++)	Tween_Shaper(&pJ[i], ColorBar);//每个相邻色点间生成渐变
	if (pJ[0].position > 0) {//如果最左边无关键色点，补齐颜色
		for (i = 0; i < pJ[0].position; ++i)ColorBar[i] = pJ[0].rgb;
	}
	if (pJ[JunctureCount - 1].position <ColourCount - 1) {//如果最右边无关键色点，补齐颜色
		for (i = ColourCount - 1; i > pJ[JunctureCount - 1].position; --i)ColorBar[i] = pJ[JunctureCount - 1].rgb;
	}
	return 0;
}


/////////////////User通用/////////////////////
//读取用户操作
int GetUser(User*user) {
	(*user).F_msg = (*user).L_msg = GetMouseMsg();
	while (!(*user).F_msg.mkLButton) {
		(*user).F_msg = GetMouseMsg();
	}
	(*user).L_msg = GetMouseMsg();
	while ((*user).L_msg.mkLButton) {
		(*user).L_msg = GetMouseMsg();
	}
	FlushMouseMsgBuffer();
	return 0;
}
//重置用户操作
int ResetUser(User*user) {
	MOUSEMSG init = { 0 };
	(*user).F_msg = (*user).L_msg = init;
	return 0;
}
//确定矩形区域
RECT RectZone(int x, int y, int wid, int hei) {
	RECT rect = { 0,0,0,0 };
	rect.left = x - wid / 2;
	rect.right = x + wid / 2;
	rect.top = y - hei / 2;
	rect.bottom = y + hei / 2;
	return rect;
}
//确定操作是否在矩形区域内
int IsRectZone(RECT rect, User*user) {
	if ((*user).F_msg.x > rect.left && (*user).F_msg.x<rect.right && (*user).F_msg.y>rect.top && (*user).F_msg.y < rect.bottom)
		return 1;
	else
		return 0;
}
//////////////////Fractal窗口///////////////
int JuliaView(int wid, int hei);
/////////////////Others/////////////////////////
//缩放图片
IMAGE ResizePic(IMAGE*Old_img, int New_wid, int New_hei = 0) {
	int i, j;
	int t, xt, yt;
	int Old_wid = (*Old_img).getwidth();
	int Old_hei = (*Old_img).getheight();
	//防止越界
	if (New_wid<0 || New_hei<0) {
		New_wid = Old_wid;
		New_hei = Old_hei;
	}

	//当参数只有一个时按比例自动缩放
	if (New_hei == 0) {
		//此处需要注意先*再/。不然当目标图片小于原图时会出错
		New_hei = New_wid * Old_hei / Old_wid;
	}
	IMAGE New_img(New_wid, New_hei);
	DWORD* oldDr = GetImageBuffer(Old_img);
	DWORD* newDr = GetImageBuffer(&New_img);
	//赋值 使用双线性插值算法
	for (i = 0; i<New_hei - 1; i++) {
		for (j = 0; j<New_wid - 1; j++) {
			t = i*New_wid + j;
			xt = j*Old_wid / New_wid;
			yt = i*Old_hei / New_hei;
			if (xt > Old_wid - 2)xt = Old_wid - 2;
			if (yt > Old_hei - 2)yt = Old_hei - 2;
			newDr[i*New_wid + j] = oldDr[xt + yt*Old_wid];
			//putimage(0,200,&newImg);//实现逐行加载图片
			byte r = (GetRValue(oldDr[xt + yt*Old_wid]) +
				GetRValue(oldDr[xt + yt*Old_wid + 1]) +
				GetRValue(oldDr[xt + (yt + 1)*Old_wid])
				+ GetRValue(oldDr[xt + (yt + 1)*Old_wid + 1])) / 4;
			byte g = (GetGValue(oldDr[xt + yt*Old_wid]) +
				GetGValue(oldDr[xt + yt*Old_wid] + 1) +
				GetGValue(oldDr[xt + (yt + 1)*Old_wid])
				+ GetGValue(oldDr[xt + (yt + 1)*Old_wid]) + 1) / 4;
			byte b = (GetBValue(oldDr[xt + yt*Old_wid]) +
				GetBValue(oldDr[xt + yt*Old_wid] + 1) +
				GetBValue(oldDr[xt + (yt + 1)*Old_wid])
				+ GetBValue(oldDr[xt + (yt + 1)*Old_wid + 1])) / 4;
			newDr[i*New_wid + j] = RGB(r, g, b);
		}
	}
	return New_img;
}
int SendMB(LPCSTR title,LPCTSTR message) {
	HWND hWnd;
	hWnd = GetHWnd();
	MessageBox(hWnd, message, title, MB_OK);
	return 0;
}
int SendDB(LPCSTR title, LPCTSTR message, int a, int b) {
	HWND hWnd;
	hWnd = GetHWnd();
	if (MessageBox(hWnd, message, title, MB_YESNO | MB_ICONQUESTION) == IDYES)
		return a;
	else
		return b;
}