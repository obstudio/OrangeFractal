#include"stdafx.h"
//输入一个无符号整数
int input_an_uint(unsigned int*p)
{
 *p = 0;//清空内容
 char c;//记录当前按键
 int len = 0;//长度
 unsigned int temp;//暂存器
 do
 {
	 c = _getch();//接受案件
	 if (isdigit(c) == 0) {//如果不是数
		 if (len > 0 && c == '\b') {//回退符
			 *p -= *p % 10;//取消最近一次输入
			 *p = *p / 10;
			 len -= 1;//长度-1
			 printf("\b \b");//光标回退
		 }
		 if (len > 0 && (c == '\r' || c == ' '))break;//在输入内容存在时,按回或空格结束输入
		 continue;//非法字符,不予理会
	 }
	 temp = *p * 10;//输入数字,用暂存器存储输入后的数
	 temp += c - '0';
	 if ((temp - c + '0')/10 != *p )continue;//如果溢出,不予理会
	 *p = temp;//如果不溢出,将值给目标变量
	 printf("%c", c);//显示输入的数字
	 len += 1;//长度加1
 } while (1);//死循环
 return len;//返回长度
}
//输入一个有符号整数
int input_a_sint(int*p) {
	*p = 0;//清空内容
	char c;//记录当前按键
	int len = 0;//数长度
	int temp;//暂存输入
	do
	{
		c = _getch();//读取按键
		if (len == 0&& c == '+') {//如果在第一个字符检测到正号
			printf("+");//显示正号
			do//内循环，输入正数
			{
				c = _getch();//继续对区按键
				if (isdigit(c) == 0) {//按键不是数字
					if (c == '\b') {//回退符
						if (len > 0) {//数长度大于0,
							*p -= *p % 10;//取消最近输入
							*p = *p / 10;
							len -= 1;//长度减1
							printf("\b \b");//光标回退
						}
						else {
							*p = 0;//删除正号
							printf("\b \b");
							break;//回到外循环
						}
					}
					if (len > 0 && (c == '\r' || c == ' '))goto quit;
					//在输入数长度大于0的情况下按回车或空格退出
					continue;//非法输入，不予理会
				}
				temp = *p * 10;//暂存键入结果
				temp += c - '0';
				if ((temp - c + '0') / 10 != *p)continue;//如果溢出，不予理会
				*p = temp;//如果没有溢出，就将结果赋给目标变量
				printf("%c", c);//显示键入的数字
				len += 1;//长度加1
			} while (1);//死循环
		}
		if (len == 0 &&c == '-') {//如果在第一个字符输入负号
			printf("-");//显示负号
			do//内循环，输入负数
			{
				c = _getch();//读取按键
				if (isdigit(c) == 0) {//如果不是数字
					if (c == '\b') {//回退符
						if (len > 0) {//在数长度大于0的情况下
							*p -= *p % 10;//取消最近输入
							*p = *p / 10;
							len -= 1;//长度减1
							printf("\b \b");//光标回退 
						}
						else {
							*p = 0;//清零
							printf("\b \b");//光标回退，删除正号
							break;//回到外循环
						}
					}
					if (len > 0 && (c == '\r' || c == ' ')) { *p = -*p; goto quit; }
					//在输入数长度大于0的情况下按回车或空格将输入变为负数并退出
					continue;//非法键入，不予理会
				}
				temp = *p * 10;//暂存输入
				temp += c - '0';
				if ((temp - c + '0') / 10 != *p)continue;//如果溢出，不予理会
				*p = temp;//没溢出，赋给目标变量
				printf("%c", c);//打印键入
				len += 1;//数长度加1
			} while (1);
		}
		if (isdigit(c) == 0) {//不为数字
			if (len > 0 && c == '\b') {//回退符
				*p -= *p % 10;//撤销最近输入
				*p = *p / 10;
				len -= 1;//长度减1
				printf("\b \b");//光标回退
			}
			if (len > 0 && (c == '\r' || c == ' '))break;
			//在输入数长度大于0的情况下按回车或空格退出
			continue;//非法键入，不予理会
		}
		temp = *p * 10;//暂存输入
		temp += c - '0';
		if ((temp - c + '0') / 10 != *p)continue;//如果溢出，不予理会
		*p = temp;//没溢出，赋给目标变量
		printf("%c", c);//打印输入数字
		len += 1;//长度加1
	} while (1);//死循环
	return 0;
	quit://退出部分
	return 0;
}
//输入一个小数
int input_a_double(double*p) {
	 *p = 0;//清空内容
	char c;//记录当前按键
	double decimal = 1;//记录小数位数
	int len = 0;//数长度
	do//输入循环
	{
		c = _getch();//读取按键
		if (len == 0 && c == '+') {//首字符输入正号
			printf("+");//打印正号
			do//循环，输入正数
			{
				c = _getch();//读取按键
				if (isdigit(c) == 0) {//如果不为数字
					if (c == '\b') {//回退符
						*p = 0;//清空输入
						decimal = 1;//重置小数位数
						while (len > 0) {//清空输入显示，重置长度
							printf("\b \b");
							len--;
						}
						break;//回到外循环
					}
					if (len > 0 && (c == '\r' || c == ' '))goto quit;
					//在输入数长度大于0的情况下按回车或空格退出
					if (len > 0 && c == '.') {//出现小数
						printf(".");//打印小数点
						do//小数部分输入循环
						{
							c = _getch();//读取按键
							if (isdigit(c) == 0) {//如果不为数字
								if (c == '\b') {//回退符
									*p = 0;//清空输入
									decimal = 1;//重置小数位数
									while (len > 0) {//清空输入显示，重置长度
										printf("\b \b");
										len--;
									}
									printf("\b \b");//由于小数点占一格，所以多清除一位
									break;//回到正数循环
								}
								if (decimal < 1 && (c == '\r' || c == ' '))goto quit;
								//在输入数长度大于0的情况下按回车或空格退出
								continue;//非法输入，不予理会
							}
							printf("%c", c);//显示输入
							decimal = decimal / 10;//小数位数加1
							*p += (c - '0') * decimal;//输入该位的数字
							len += 1;//长度加1
						} while (1);
					}
					continue;//非法输入，不予理会
				}
				if (len > 15)continue;//超过精度，不予理会
				*p *= 10;//记录输入
				*p += c - '0';
				len += 1;//长度加1
				printf("%c", c);//显示输入数字
			} while (1);//死循环
			printf("\b \b");//回外循环前去掉+号
		}
		if (len == 0 && c == '-') {//首字符为负号
			printf("-");//显示负号
			do//循环，输入负数
			{
				c = _getch();//读取按键
				if (isdigit(c) == 0) {//不为数字
					if (c == '\b') {//回退符
						*p = 0;//清空输入
						decimal = 1;//重置小数位数
						while (len > 0) {//清空显示并重置长度
							printf("\b \b");
							len--;
						}
						break;//回到外循环
					}
					if (len > 0 && (c == '\r' || c == ' ')) { *p = -*p; goto quit; }
					//在输入数长度大于0的情况下按回车或空格将输入变为负数并退出
					if (len > 0 && c == '.') {//小数点
						printf(".");//显示小数点
						do//小数部分循环
						{
							c = _getch();//读取按键
							if (isdigit(c) == 0) {//不为数字
								if (c == '\b') {//回退符
									*p = 0;//清空输入
									decimal = 1;//重置小数位数
									while (len > 0) {//清空输入并重置长度
										printf("\b \b");
										len--;
									}
									printf("\b \b");//删除小数点
									break;
								}
								if ((c == '\r'||c==' ')&&decimal < 1) { *p = -*p; goto quit; }
								//在输入数长度大于0的情况下按回车或空格将输入变为负数并退出
								continue;//非法输入，不予理会
							}
							if (len > 15)continue;//超过精度，不予理会
							decimal = decimal / 10;//没超精度，更新输入
							*p += (c - '0') * decimal;
							len += 1;//长度+1
							printf("%c", c);//显示输入
						} while (1);//死循环
					}
					continue;//非法输入，不予理会
				}
				if (len > 15)continue;//超过精度，不予理会
				*p *= 10;//没超精度，更新输入 
				*p += c - '0';
				len += 1;//长度+1
				printf("%c", c);//显示输入
			} while (1);//死循环
			printf("\b \b");//回外循环前删除负号
		}
		if (isdigit(c) == 0) {//不为数字
			if (c == '\b') {//回退符
				*p = 0;//清空输入
				while (len > 0) {//清空显示并重置长度 
					printf("\b \b");
					len--;
				}
				continue;//下一个
			}
			if (len > 0 && (c == '\r' || c == ' '))break;
		    //输入不为空时按回车或空格，退出
			if (len > 0 && c == '.') {//小数点
				printf(".");//显示小数点
				do//小数循环
				{
					c = _getch();//读取按键
					if (isdigit(c) == 0) {//不为数字
						if (c == '\b') {//回退符
							decimal = 1;//重置小数位数
							*p = 0;//清空输入
							while (len > 0) {//清空显示并重置长度
								printf("\b \b");
								len--;
							}
							printf("\b \b");//删除小数点
							break;//回外循环
						}
						if (decimal < 1 && (c == '\r' || c == ' '))goto quit;
						//输入不为空时按回车或空格，退出
						continue;//非法输入，不予理会
					}
					if (len > 15)continue;//超出精度，不予理会 
					decimal = decimal / 10;//没超精度，记下输入
					*p += (c - '0') * decimal;
					len += 1;//长度+1
					printf("%c", c);//显示输入
				} while (1);//死循环
			}
			continue;//非法输入，不予理会
		}
		if (len > 15)continue;//超出精度，不予理会
		*p *= 10;//没超精度，记下输入
		*p += c - '0';
		len += 1;//长度+1
		printf("%c", c);//显示输入
	} while (1);//死循环
	return 0;//结束输入
quit://结束输入（针对从多重循环内跳出的情况）
	return 0;
}
//输入一个选择
int input_a_choice(int*p,int lim) {
	char c;//记录最近按键
	int len = 0;//长度
	*p = 0;//清空输入
	int temp;//暂存器
	do
	{
		c = _getch();//读取按键
		if (isdigit(c) == 0) {//不为数字
			if (len > 0 &&c == '\b') {//为回退符
				*p -= *p % 10;//撤销最近输入
				*p = *p / 10;
				len -= 1;//长度减1
				printf("\b \b");//光标回退
			}
			if (len > 0 && (c == '\r' || c == ' '))break;
			//输入不为空时按回车或空格，退出
			continue;//非法输入，不予理会
		}
		temp = *p * 10;//暂存输入
		temp += c - '0';
		if ((temp - c + '0') / 10 != *p||temp>lim)continue;//超过限制，不予理会
		*p = temp;//没超限制，赋给目标变量
		printf("%c", c);//显示输入
		len += 1;//长度+1
	} while (1);//死循环
	return len;//返回长度
}