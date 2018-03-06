#include"CheatHead.h"

void Llkcheat::workMain()
{
	if (en_fail == init())
	{
		return;
	}
	getChess();	//��ȡ������Ϣ
	InMap();	//������Ϣ¼��list��map

	cout << "Load succeed! Press any key to clear the block! " << endl;
	getchar();
	valueClear();
}


Status Llkcheat::init()	//�����ʼ��,������ȡ���ھ�� ����id ���̾���Ȳ���
{
	hWin = FindWindow(nullptr, "QQ��Ϸ - ��������ɫ��");	//��ȡ��Ϸ���ھ��
	if (!hWin)
	{
		cout << "��Ϸ���ھ����ȡʧ��!" << endl;
		return en_fail;
	}
	GetWindowThreadProcessId(hWin, &pid);	//��ȡ����id
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);	//��ȡ���̾��
	if (!hProcess)
	{
		cout << "���̾����ȡʧ��!" << endl;
		return en_fail;
	}
	cout << "��Ϸ���ھ�� " << hWin << endl;
	cout << "���̾�� " << hProcess << endl;
	return en_success;
}

Status Llkcheat::getChess()		//��ȡ������Ϣ
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

void Llkcheat::showMap()			//�������map�и�list����Ϣ
{
	cout << "Map size is " << arrMap.size();

	//����Map
	map<valueType, list<elem>>::iterator iter;
	for (iter = arrMap.begin(); iter != arrMap.end(); iter++)
	{
		cout << "List Type is " << iter->first << endl;
		showList(iter->second);
	}
}

void Llkcheat::showList(list<elem> &eList)
{
	//����List
	list<elem>::iterator iter;
	for (iter = eList.begin(); iter != eList.end(); iter++)
	{
		cout << "--Elem is : " << iter->type << "  " << iter->x << "  " << iter->y << endl;
	}
}

void Llkcheat::InMap()			//������Ϣ¼��list��map
{
	int i;
	for (i = 0; i < CHESS_SIZE; i++)
	{
		if (0 == value[i])		//�հ�Ԫ��ֱ������
		{
			continue;
		}
		else
		{
			map<valueType, list<elem> >::iterator m_it;
			elem tempElem = typeInElem(value[i], i);
			list<elem> tempList;

			m_it = arrMap.find(value[i]);

			//elem temp(value[i], i % 9, i / 9);	//����������

			if (m_it == arrMap.end())		//δ���ҵ���Ӧtypeʱ����list��¼��map
			{
				//list<elem> eList;				//����������
				tempList = elemInList(tempElem);
				arrMap[value[i]] = tempList;
			}
			else
			{
				arrMap[value[i]].push_front(tempElem);	//���ҵ���Ӧ��¼��ֱ�ӽ�elem������Ӧ��list��
			}
		}
	}
}

list<elem> Llkcheat::elemInList(elem data)	//��elem������list��
{
	list<elem> eList;
	eList.push_front(data);
	return eList;
}

elem Llkcheat::typeInElem(valueType type, int i)	//������Ԫ��������elem��
{
	elem temp(type, i % 19, i / 19);	//��ȡ����Ԫ��
	return temp;
}

void Llkcheat::mapClick()								//����map��list�����ݽ��е��
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

void Llkcheat::listClick(list<elem> &eList)				//���ݴ���list���е������
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

Status Llkcheat::elemClick(elem &firElem, elem &secElem)	//���ݴ�������Elem��������Ϣ�������������ӵ������,˳��:�ȵ��firElem��Ӧ��Ԫ��,����secElem��Ӧ��Ԫ��
{
	if (firElem.type != secElem.type)	//�����󷽿�Ԫ�����Ͳ�ͬʱ�˳�������en_fail,��������ʧ��
	{
		return en_fail;
	}

	int x, y;
	RECT r1;
	GetWindowRect(hWin, &r1);
	//cout << "x=" << x << "  y=" << y << endl;

	//���ǰ��ʼ����������ѡ��
	SetCursorPos(r1.left + 8, r1.top + 166);	//�������λ��
	//������¼�
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

	//firElem���
	Sleep(10);
	x = r1.left + 25 + firElem.x * 31;
	y = r1.top + 195 + firElem.y * 35;
	//�������λ��
	SetCursorPos(x, y);
	//������¼�
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

	
	//secElem���
	Sleep(10);
	x = r1.left + 25 + secElem.x * 31;
	y = r1.top + 195 + secElem.y * 35;
	//�������λ��
	SetCursorPos(x, y);
	//������¼�
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

	return en_success;
}

void Llkcheat::valueClear()								//������Ԫ�������ܺ���,ѭ��
{
	int i = 0;
	while (arrMap.size() != 0)
	{
		arrMap.clear();	//ԭmap���
		memset(value, 0, sizeof(char)*CHESS_SIZE);//��value������ϢΪ0
		getChess();		//����value������Ϣ
		InMap();		//¼��map��Ϣ
		mapClick();		//����mapͨ���������������������
		i++;
		if (10 == i)	//�жϴ���,���ڴ���arrMap.size()����Ϊ0������ѭ���������ÿѭ��10����ͣһ��
		{
			cout << "continue" << endl;
			getchar();
			i = 0;
		}
	}
}