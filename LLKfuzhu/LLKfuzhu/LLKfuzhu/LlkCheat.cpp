#include"CheatHead.h"

void Llkcheat::workMain()
{
	if (en_fail == init())
	{
		return;
	}
	getChess();	//获取矩阵信息
	InMap();	//矩阵信息录入list与map

	cout << "Load succeed! Press any key to clear the block! " << endl;
	getchar();
	valueClear();
}


Status Llkcheat::init()	//程序初始化,包含获取窗口句柄 进程id 进程句柄等操作
{
	hWin = FindWindow(nullptr, "QQ游戏 - 连连看角色版");	//获取游戏窗口句柄
	if (!hWin)
	{
		cout << "游戏窗口句柄获取失败!" << endl;
		return en_fail;
	}
	GetWindowThreadProcessId(hWin, &pid);	//获取进程id
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);	//获取进程句柄
	if (!hProcess)
	{
		cout << "进程句柄获取失败!" << endl;
		return en_fail;
	}
	cout << "游戏窗口句柄 " << hWin << endl;
	cout << "进程句柄 " << hProcess << endl;
	return en_success;
}

Status Llkcheat::getChess()		//获取矩阵信息
{
	SIZE_T readNum;

	readNum = 0;
	
	if (0 == ReadProcessMemory(hProcess, (LPVOID)chessAddr, value, CHESS_SIZE, &readNum))
	{
		return en_fail;
	}
	return en_success;
	/*
	int i, j;
	for (i = 0; i < 11; i++)
	{
	for (j = 0; j < 19; j++)
	{
	printf(" %x", value[i * 11 + j]);
	}
	printf("\n");
	}*/
}

void Llkcheat::showMap()			//遍历输出map中各list的信息
{
	cout << "Map size is " << arrMap.size();

	//遍历Map
	map<valueType, list<elem>>::iterator iter;
	for (iter = arrMap.begin(); iter != arrMap.end(); iter++)
	{
		cout << "List Type is " << iter->first << endl;
		showList(iter->second);
	}
}

void Llkcheat::showList(list<elem> &eList)
{
	//遍历List
	list<elem>::iterator iter;
	for (iter = eList.begin(); iter != eList.end(); iter++)
	{
		cout << "--Elem is : " << iter->type << "  " << iter->x << "  " << iter->y << endl;
	}
}

void Llkcheat::InMap()			//矩阵信息录入list与map
{
	int i;
	for (i = 0; i < CHESS_SIZE; i++)
	{
		if (0 == value[i])		//空白元素直接跳过
		{
			continue;
		}
		else
		{
			map<valueType, list<elem> >::iterator m_it;
			elem tempElem = typeInElem(value[i], i);
			list<elem> tempList;

			m_it = arrMap.find(value[i]);

			//elem temp(value[i], i % 9, i / 9);	//可能有问题

			if (m_it == arrMap.end())		//未查找到对应type时创建list并录入map
			{
				//list<elem> eList;				//可能有问题
				tempList = elemInList(tempElem);
				arrMap[value[i]] = tempList;
			}
			else
			{
				arrMap[value[i]].push_front(tempElem);	//查找到对应记录则直接将elem推入相应的list中
			}
		}
	}
}

list<elem> Llkcheat::elemInList(elem data)	//将elem填入新list中
{
	list<elem> eList;
	eList.push_front(data);
	return eList;
}

elem Llkcheat::typeInElem(valueType type, int i)	//将坐标元素填入新elem中
{
	elem temp(type, i % 19, i / 19);	//获取坐标元素
	return temp;
}

void Llkcheat::mapClick()								//根据map及list的数据进行点击
{
	if (arrMap.empty() == true)
	{
		return;
	}
	map<valueType, list<elem>>::iterator mLt;
	list<elem>::iterator lLt1, lLt2;
	for (mLt = arrMap.begin(); mLt != arrMap.end(); mLt++)
	{
		listClick(mLt->second);
	}
}

void Llkcheat::listClick(list<elem> &eList)				//根据传入list进行点击操作
{
	if (eList.empty() == true)
	{
		return;
	}
	list<elem>::iterator lLt1,lLt2;
	for (lLt1 = eList.begin(); lLt1 != eList.end(); lLt1++)
	{
		for (lLt2 = lLt1,lLt2++; lLt2 != eList.end(); lLt2++)
		{
			elemClick(*lLt1, *lLt2);
		}
	}
}

Status Llkcheat::elemClick(elem &firElem, elem &secElem)	//根据传入两个Elem的坐标信息进行连连看连接点击尝试,顺序:先点击firElem对应的元素,后点击secElem对应的元素
{
	if (firElem.type != secElem.type)	//两矩阵方块元素类型不同时退出并返回en_fail,方块消除失败
	{
		return en_fail;
	}

	int x, y;
	RECT r1;
	GetWindowRect(hWin, &r1);
	//cout << "x=" << x << "  y=" << y << endl;

	//点击前初始化消除方块选框
	SetCursorPos(r1.left + 8, r1.top + 166);	//设置鼠标位置
	//鼠标点击事件
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

	//firElem点击
	Sleep(10);
	x = r1.left + 25 + firElem.x * 31;
	y = r1.top + 195 + firElem.y * 35;
	//设置鼠标位置
	SetCursorPos(x, y);
	//鼠标点击事件
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

	
	//secElem点击
	Sleep(10);
	x = r1.left + 25 + secElem.x * 31;
	y = r1.top + 195 + secElem.y * 35;
	//设置鼠标位置
	SetCursorPos(x, y);
	//鼠标点击事件
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

	return en_success;
}

void Llkcheat::valueClear()								//连连看元素消除总函数,循环
{
	int i = 0;
	while (arrMap.size() != 0)
	{
		arrMap.clear();	//原map清空
		memset(value, 0, sizeof(char)*CHESS_SIZE);//置value数组信息为0
		getChess();		//重置value数组信息
		InMap();		//录入map信息
		mapClick();		//根据map通过引导鼠标点击以消除方块
		i++;
		if (10 == i)	//中断代码,用于处理arrMap.size()永不为0而无限循环的情况，每循环10次暂停一次
		{
			cout << "continue" << endl;
			getchar();
			i = 0;
		}
	}
}