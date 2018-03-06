#pragma once

#include<Windows.h>
#include<iostream>
#include<map>
#include<list>
using namespace std;

#define CHESS_SIZE 19*11	//�궨������С

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
	HWND hWin;				//�洢���ھ��
	DWORD pid;				//�洢����id
	DWORD chessAddr;		//�洢�����������׵�ַ
	DWORD num;				//�洢����Ԫ�ظ���
	HANDLE hProcess;		//�洢���̾��
	valueType value[CHESS_SIZE] = { 0 };			//��¼������������Ϣ
	map<valueType, list<elem>> arrMap;				//�洢����������Ԫ�ع�ϵmap,ÿ��valueTypeֵ��Ӧһ��list,list�ڼ�¼����ͬvalueTypeֵԪ�ص�����


	void workMain();		//����������

	Status init();			//�����ʼ��,������ȡ���ھ�� ����id ���̾���Ȳ���
	Status getChess();		//��ȡ������Ϣ
	Status elemClick(elem &firElem, elem &secElem);	//���ݴ�������Elem��������Ϣ�������������ӵ������,˳��:�ȵ��firElem��Ӧ��Ԫ��,����secElem��Ӧ��Ԫ��
	void InMap();			//������Ϣ¼��list��map
	void showMap();			//�������map�и�list����Ϣ
	void showList(list<elem> &eList);				//�������list�и�elem����Ϣ
	void valueClear();								//������Ԫ�������ܺ���
	void mapClick();								//����map��list�����ݽ��е��
	void listClick(list<elem> &eList);				//���ݴ���list���е������
	elem typeInElem(valueType type, int i);			//��������Ϣ������elem��
	list<elem> elemInList(elem data);				//��elem������list��

	Llkcheat()
	{
		pid = 0;
		chessAddr = 0x189F78;//��CE�õ��ľ����ַ,��ͬ���л������ܲ�ͬ
		num = CHESS_SIZE;
	}
};
