#include<iostream>
#include"fuzzycontrol.h"
#include"fuzzypid.h"
using namespace std;

fuzzy a;
fuzzypid b;

void main()
{
	b.Fuzzy_Control_Matrix_Total();
	b.Fuzzy_Input(250,100,20,34);
	b.U_Calculate();
	b.U_Defuzzy();
	b.Input_Kp_Interval(0.120, 0.180);
	b.Input_Ki_Interval(0.0120, 0.0180);
	b.Input_Kd_Interval(0.00120, 0.00180);
	b.Cal_Kp_Ki_Kd(0.150, 0.0150, 0.00150);



	cout << "�ǶȲ�ֵ��" <<"      " <<b.error<< endl;
	cout << "���ٶȲ�ֵ��    " << b.dderror<< endl;
	cout << endl;
	cout << "E��Ӧ��ģ�����ϣ�" << endl;
	for (int i = 0; i < 13; i++)
		cout << b.e1[i] << "   ";
	cout << endl;
	cout << endl;
	cout << "EC��Ӧ��ģ�����ϣ�" << endl;
	for (int j = 0; j < 13; j++)
		cout << b.ec1[j] << "   ";
	cout << endl;
	cout << endl;
	cout << "�������Kp��Ki��Kd�������ģ�����ϣ�" << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			cout << b.U_Final[i][j] << "   ";
			if (j == 12)
				cout << endl;
		}
		cout << endl;
	}
	cout << endl;
	cout << "���ģ�������ģ������ľ�ȷ�������" << endl;
	cout << "U(Kp):" << b.u[0] << "       " << "U(Ki):" << b.u[1] << "       " << "U(Kd):" << b.u[2] << endl;
	cout << endl;
	cout << "Kp��Ki��Kd�ı仯��:" << endl;
	cout << "��Kp��" << b.Kp_ << "    " << "��Ki��" << b.Ki_ << "    " << "��Kd" << b.Kd_ << endl;
	cout << endl;
	cout << "Kp��Ki��Kd�ĳ�ʼֵ:" << endl;
	cout << "Kp��" << "0.150" << "            " << "Ki��" << "0.150" << "           " << "Kd��" << "0.00150" << endl;
	cout << "�����Kp��Ki��Kd��ֵ:" << endl;
	cout << "Kp��" << b.kp << "         " << "Ki��" << b.ki << "        " << "Kd��" << b.kd << endl;
	


	 
}

