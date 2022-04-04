#include"fuzzycontrol.h"

fuzzy::fuzzy(){}
 

fuzzy::~fuzzy() {}



float fuzzy::min(float a, float b)
{
	if (a < b)
		return a;
	else
		return b;
}

float fuzzy::max(float a, float b)
{
	if (a > b)
		return a;
	else
		return b;
}


//ģ������ļ���
//a Eģ�����ϣ�������
//b ECģ�����ϣ�������
//c Uģ�����ϣ�������
void fuzzy::Fuzzy_Control_Matrix_cal(int a,int b,int c)
{
	//��ÿ��ģ������Ri = ��Ai x Bi�� x Ci
	//���ȼ���E �� EC��ģ����ϵ����,����E��EC��ģ����ϵ����ת��Ϊ�ɲ�����һ�μ������ʽ
	//E�ɽ��ƿ���14x1��������
	//EC�ɿ���1x13��������
	int k = 0;
	for (int j=0; j<14; j++)
	{
		for (int i = 0; i < 13; i++)
		{
			FC_Matrix[j][i] = min(E[a][j],EC[b][i]);
			FC_Matrix_Use[k] = FC_Matrix[j][i];
			k++;
		}
	}
	for (int i = 0; i < 14 * 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			FC_Matrix_Final[i][j] = min(FC_Matrix_Use[i],U[c][j]);
		}
	}
	 
 
}
 
 
//ģ������
void fuzzy::Set_Rules()
{

}