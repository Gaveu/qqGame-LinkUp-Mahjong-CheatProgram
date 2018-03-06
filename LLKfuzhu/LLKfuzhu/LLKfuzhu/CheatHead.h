#pragma once

#include<Windows.h>
#include<iostream>
#include<map>
#include<list>
using namespace std;

#define CHESS_SIZE 19*11	//宏定义矩阵大小

typedef enum{en_fail,en_success,en_error} Status;
typedef char valueType;

class elem
{
public:
	valueType type;
	int x;
	int y;

	elem(valueType inType, char inX, char inY)
	{
		type = inType;
		x = inX;
		y = inY;
	}
};

class Llkcheat
{
public:
	HWND hWin;				//存储窗口句柄
	DWORD pid;				//存储进程id
	DWORD chessAddr;		//存储连连看矩阵首地址
	DWORD num;				//存储矩阵元素个数
	HANDLE hProcess;		//存储进程句柄
	valueType value[CHESS_SIZE] = { 0 };			//记录连连看矩阵信息
	map<valueType, list<elem>> arrMap;				//存储连连看矩阵元素关系map,每个valueType值对应一个list,list内记录各相同valueType值元素的坐标


	void workMain();		//运行主函数

	Status init();			//程序初始化,包含获取窗口句柄 进程id 进程句柄等操作
	Status getChess();		//获取矩阵信息
	Status elemClick(elem &firElem, elem &secElem);	//根据传入两个Elem的坐标信息进行连连看连接点击尝试,顺序:先点击firElem对应的元素,后点击secElem对应的元素
	void InMap();			//矩阵信息录入list与map
	void showMap();			//遍历输出map中各list的信息
	void showList(list<elem> &eList);				//遍历输出list中各elem的信息
	void valueClear();								//连连看元素消除总函数
	void mapClick();								//根据map及list的数据进行点击
	void listClick(list<elem> &eList);				//根据传入list进行点击操作
	elem typeInElem(valueType type, int i);			//将坐标信息填入新elem中
	list<elem> elemInList(elem data);				//将elem填入新list中

	Llkcheat()
	{
		pid = 0;
		chessAddr = 0x189F78;//由CE得到的矩阵地址,不同运行环境可能不同
		num = CHESS_SIZE;
	}
};
