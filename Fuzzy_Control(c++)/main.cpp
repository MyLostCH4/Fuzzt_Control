#include<iostream>
#include"fuzzycontrol.h"
using namespace std;

fuzzy a;

void main()
{

	a.Fuzzy_Control_Matrix_Total();
	
	a.Fuzzy_Input(0, 1, 0, 0);

	a.U_Calculate();

	a.U_Defuzzy();

	

	cout << "E��Ӧ��ģ�����ϣ�" << endl;
	for (int i = 0; i < 14; i++)
		cout << a.e1[i] << " ";
	cout << endl;
	cout << "EC��Ӧ��ģ�����ϣ�" << endl;
	for (int i = 0; i < 13; i++)
		cout << a.ec1[i] << " ";
	cout << endl;
	cout << "E��EC��ȷ����ģ����ϵ����:" << endl;
	for (int i = 0; i < 14; i++)
		for (int j = 0; j < 13; j++)
		{
			cout << a.FC_Matrix_1[i][j] << "  ";
			if (j == 12)
				cout << endl;
		}

	cout << "�������ģ�����ϣ�" << endl;
	for (int i = 0; i < 13; i++)
		cout << a.U_Final[i] << " ";
	cout << endl;
	
	cout << "�����ģ�������ģ������ľ�ȷ�������" << endl;
	cout << a.u << endl;
	/*
	cout << "�ܵ�ģ����ϵ����:" << endl;
	for (int i = 0; i < 14 * 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			if (j < 12)
				cout << a.FC_Matrix_Total[i][j] << "    ";
			if (j == 12)
				cout << a.FC_Matrix_Total[i][j] << endl;
		}
	}
	*/
	 
}

