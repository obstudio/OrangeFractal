#include"stdafx.h"
#include"structures.h"
#include"functions.h"
using namespace std;
/////////////////Buttonͨ��/////////////////////
//ȷ����ť����
int Button_rows(Button*button, int ButtonCount) {
	int rowCount = 1;//����
	int i;
	for (i = 0; i < ButtonCount; ++i) {
		if (button[i].i > rowCount)rowCount = button[i].i;
	}
	return rowCount;
}
//ȷ��һ���ڰ�ť����
int Button_inArow(Button*button, int ButtonCount, int row) {
	int count = 1;//ͬ�и��� 
	int i;
	for (i = 0; i < ButtonCount; ++i) {
		if ((button[i].i == row) && (count < button[i].j))count = button[i].j;
	}
	return count;
}
//��ʾ��ť��
/*cOlorbar,xM,xN,yM,yN,aB,pAint,cLear,sAve,bAck,qUit*/
int Button_showbuttons(Button*button, int ButtonCount) {
	int i;
	settextcolor(WHITE);
	for (i = 0; i < ButtonCount; ++i) {
		rectangle(button[i].x - button[i].width / 2, button[i].y - button[i].height / 2, button[i].x + button[i].width / 2, button[i].y + button[i].height / 2);
		switch (button[i].type) {
		case cOlorbar:Button_textout(_T("��ɫ������"), &button[i]); break;
		case xM:Button_textout(_T("xm = 0.0"), &button[i]); break;
		case xN:Button_textout(_T("xn = 0.0"), &button[i]); break;
		case yM:Button_textout(_T("ym = 0.0"), &button[i]); break;
		case yN:Button_textout(_T("yn = 0.0"), &button[i]); break;
		case aB:Button_textout(_T("c = 0.0 + 0.0 * i"), &button[i]); break;
		case pAint:Button_textout(_T("��ʼ��ͼ"), &button[i]); break;
		case cLear:Button_textout(_T("���"), &button[i]); break;
		case sAve:Button_textout(_T("����"), &button[i]); break;
		case bAck:Button_textout(_T("����"), &button[i]); break;
		case qUit:Button_textout(_T("�˳�"), &button[i]); break;
		default:
			break;
		}
	}
	return 0;
}
//�����ť����
int Button_textout(LPCTSTR str, Button*button) {
	RECT rect = { (*button).x - (*button).width / 2, (*button).y - (*button).height * 2 / 7, (*button).x + (*button).width / 2, (*button).y + (*button).height / 2 };
	drawtext(str, &rect, DT_CENTER | DT_VCENTER);
	return 0;
}

//�жϰ�ť����
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
//��հ�ť����
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

//�����а�ť��״̬�ָ�Ϊδ����
int Button_Reset(Button*button, int ButtonCount) {
	int i;
	for (i = 0; i < ButtonCount; ++i) {
		(*button).IsTriggerd = 0;
	}
	return 0;
}
//�ҵ���������ť�ı��
int Button_Find(Button*button, int ButtonCount) {
	int i;
	for (i = 0; i < ButtonCount; ++i) {
		if (button[i].IsTriggerd != 0)return i;
	}
	return -1;
}

/////////////////ColorBarͨ��/////////////////////
//��ʾ���н�����
int ColorBar_show(Button*button, int ButtonCount, RGB*ColorBar, int ColorCount) {
	int i;//ѭ���±�
	for (i = 0; i < ButtonCount; ++i) {//�������а�ť
		if (button[i].type == cOlorbar) //���Ϊ������
			ColorBar_paint(&button[i], ColorBar, ColorCount);
	}
	return 0;
}
//��ʾһ��������
int ColorBar_paint(Button*button, RGB*ColorBar, int ColorCount) {
	int i, d;//�������ϵĵ�λ�ú�������ɫ���϶�Ӧ��λ��
	int R, G, B;//��ɫֵ
	int start_x, start_y, end_x, end_y;//Ϳɫ�����������
	float k;//����������ɫ������ű�
	start_x = (*button).x - (*button).width / 2 + 1;
	end_x = (*button).x + (*button).width / 2 - 1;
	start_y = (*button).y - (*button).height / 2 + 1;
	end_y = (*button).y + (*button).height / 2 - 1;//ȷ�������������
	k = 1.0*(ColorCount - 1) / (end_x - start_x);//ȷ�����ű�
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
//ȷ����ɫ���λ��
int ColorBar_GetPosition(User*user, Button*button, int ColorCount) {
	int position = 0;
	position = 1.0 * (ColorCount - 1)*((*user).F_msg.x + (*button).width / 2 - (*button).x) / (*button).width;
	if (position < 0)position = 0;
	if (position >= ColorCount)position = ColorCount - 1;
	return position;
}
//�õ�Ҫ�޸ĵĹؼ�ɫ��
int Juncture_Find(int position, Juncture*pJ, int* JunctureCount, int ColorCount) {
	int i = 0;
	int delta;//���
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
//�༭�ؼ�ɫ��
int Juncture_Edit(Juncture*pJ) {
	char r[4];
	char g[4];
	char b[4];
	InputBox(r, 4, "�������ɫֵ(0-255)");
	InputBox(g, 4, "��������ɫֵ(0-255)");
	InputBox(b, 4, "��������ɫֵ(0-255)");
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
//�ؼ�ɫ������
int Juncture_Sort(Juncture*pJ, int JunctureCount) {
	Juncture*temp = pJ;//�����ݴ���
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
//���������ڹؼ�ɫ������ɽ���
int Tween_Shaper(Juncture*pJ, RGB*ColorBar) {
	int start, end;//��ʼλ�ã���ֹλ��
	int sR, sG, sB, eR, eG, eB;//��ֹ����ɫֵ
	int i;
	start = pJ->position;//�õ���ʼλ��
	ColorBar[start] = pJ->rgb;//������ʼ�����ɫ
	sR = ColorBar[start].R;
	sG = ColorBar[start].G;
	sB = ColorBar[start].B;//��¼�����ɫֵ
	pJ++;//��һ���ؼ���
	end = pJ->position;//�õ���ֹλ��
	ColorBar[pJ->position] = pJ->rgb;//������ֹ�����ɫ
	eR = ColorBar[end].R;
	eG = ColorBar[end].G;
	eB = ColorBar[end].B;//��¼�յ���ɫֵ
	for (i = start; i < end; ++i) {//�������
		ColorBar[i].R = sR + (i - start)*(eR - sR) / (end - start);
		ColorBar[i].G = sG + (i - start)*(eG - sG) / (end - start);
		ColorBar[i].B = sB + (i - start)*(eB - sB) / (end - start);
	}
	return 0;
}
//ˢ����ɫ��
int ColorBar_Compiler(Juncture*pJ, int JunctureCount, RGB*ColorBar, int ColourCount) {
	int i;//ѭ���±�
	Juncture_Sort(pJ, JunctureCount);//�Թؼ�ɫ������
	for (i = 0; i < JunctureCount - 1; i++)	Tween_Shaper(&pJ[i], ColorBar);//ÿ������ɫ������ɽ���
	if (pJ[0].position > 0) {//���������޹ؼ�ɫ�㣬������ɫ
		for (i = 0; i < pJ[0].position; ++i)ColorBar[i] = pJ[0].rgb;
	}
	if (pJ[JunctureCount - 1].position <ColourCount - 1) {//������ұ��޹ؼ�ɫ�㣬������ɫ
		for (i = ColourCount - 1; i > pJ[JunctureCount - 1].position; --i)ColorBar[i] = pJ[JunctureCount - 1].rgb;
	}
	return 0;
}


/////////////////Userͨ��/////////////////////
//��ȡ�û�����
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
//�����û�����
int ResetUser(User*user) {
	MOUSEMSG init = { 0 };
	(*user).F_msg = (*user).L_msg = init;
	return 0;
}
//ȷ����������
RECT RectZone(int x, int y, int wid, int hei) {
	RECT rect = { 0,0,0,0 };
	rect.left = x - wid / 2;
	rect.right = x + wid / 2;
	rect.top = y - hei / 2;
	rect.bottom = y + hei / 2;
	return rect;
}
//ȷ�������Ƿ��ھ���������
int IsRectZone(RECT rect, User*user) {
	if ((*user).F_msg.x > rect.left && (*user).F_msg.x<rect.right && (*user).F_msg.y>rect.top && (*user).F_msg.y < rect.bottom)
		return 1;
	else
		return 0;
}
//////////////////Fractal����///////////////
int JuliaView(int wid, int hei);
/////////////////Others/////////////////////////
//����ͼƬ
IMAGE ResizePic(IMAGE*Old_img, int New_wid, int New_hei = 0) {
	int i, j;
	int t, xt, yt;
	int Old_wid = (*Old_img).getwidth();
	int Old_hei = (*Old_img).getheight();
	//��ֹԽ��
	if (New_wid<0 || New_hei<0) {
		New_wid = Old_wid;
		New_hei = Old_hei;
	}

	//������ֻ��һ��ʱ�������Զ�����
	if (New_hei == 0) {
		//�˴���Ҫע����*��/����Ȼ��Ŀ��ͼƬС��ԭͼʱ�����
		New_hei = New_wid * Old_hei / Old_wid;
	}
	IMAGE New_img(New_wid, New_hei);
	DWORD* oldDr = GetImageBuffer(Old_img);
	DWORD* newDr = GetImageBuffer(&New_img);
	//��ֵ ʹ��˫���Բ�ֵ�㷨
	for (i = 0; i<New_hei - 1; i++) {
		for (j = 0; j<New_wid - 1; j++) {
			t = i*New_wid + j;
			xt = j*Old_wid / New_wid;
			yt = i*Old_hei / New_hei;
			if (xt > Old_wid - 2)xt = Old_wid - 2;
			if (yt > Old_hei - 2)yt = Old_hei - 2;
			newDr[i*New_wid + j] = oldDr[xt + yt*Old_wid];
			//putimage(0,200,&newImg);//ʵ�����м���ͼƬ
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