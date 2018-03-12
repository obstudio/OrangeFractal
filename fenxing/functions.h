#pragma once
#include"stdafx.h"
#include"structures.h"
/////////////////函数声明///////////////////////
/////////////////Button通用/////////////////////
int Button_rows(Button*button, int ButtonCount);//确定按钮行数
int Button_inArow(Button*button, int ButtonCount, int row);//确定一行内按钮个数
int Button_showbuttons(Button*button, int ButtonCount);//显示按钮集
int Button_textout(LPCTSTR str, Button*button);//输出按钮文字
int Button_clear(Button*button, int ButtonCount, button_type type);//清空按钮内容
button_type Button_Judge(Button*button, int ButtonCount, User*user);//判断按钮类型
int Button_Reset(Button*button, int ButtonCount);//将所有按钮的状态恢复为未触发
int Button_Find(Button*button, int ButtonCount);//找到被触发按钮的编号

/////////////////ColorBar通用/////////////////////
int ColorBar_show(Button*button, int ButtonCount, RGB*ColorBar, int ColorCount);//显示所有渐变条
int ColorBar_paint(Button*button, RGB*ColorBar, int ColorCount);//显示一个渐变条
int ColorBar_GetPosition(User*user, Button*button, int ColorCount);//确定颜色点的位置
int Juncture_Find(int position, Juncture*pJ, int* JunctureCount, int ColorCount);//得到要修改的关键色点
int Juncture_Edit(Juncture*pJ);//编辑关键色点
int Juncture_Sort(Juncture*pJ, int JunctureCount);//关键色点排序
int Tween_Shaper(Juncture*pJ, RGB*ColorBar);//在两个相邻关键色点间生成渐变
int ColorBar_Compiler(Juncture*pJ, int JunctureCount, RGB*ColorBar, int ColourCount);//刷新颜色表

/////////////////User通用/////////////////////
int GetUser(User*user);//读取用户操作
int ResetUser(User*user);//重置用户操作
int IsRectZone(RECT rect, User*user);//确定操作是否在矩形区域内
//////////////////Fractal窗口通用///////////////

/////////////////Others/////////////////////////
RECT RectZone(int x, int y, int wid, int hei);//确定矩形区域
IMAGE ResizePic(IMAGE*img, int New_wid, int New_hei);//缩放图片
int SendMB(LPCSTR title, LPCTSTR message);//发出弹窗消息
int SendDB(LPCSTR title, LPCTSTR message, int a, int b);//弹出判断框
