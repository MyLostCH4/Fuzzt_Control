#include"fuzzycontrol.h"

fuzzy::fuzzy(){}
 

fuzzy::~fuzzy() {}


//ȡ������֮����ֵ��С����
float fuzzy::min(float a, float b)
{
	if (a < b)
		return a;
	else
		return b;
}

//ȡ������֮����ֵ�ϴ����
float fuzzy::max(float a, float b)
{
	if (a > b)
		return a;
	else
		return b;
}
//��������ȡ��
int fuzzy::round_float(float number)
{
	return (number > 0.0) ? (number + 0.5) : (number - 0.5);
}


//��������ģ��������
//������ĽǶ�ƫ��ͽ��ٶ�ƫ��ת��Ϊ��Ӧ��ģ������
void fuzzy::Fuzzy_Input(float target_e, float current_value_e,float target_ec,float current_value_ec)
{
	error = current_value_e - target_e;
	dderror = current_value_ec - target_ec;
	e = error/10;
	ec = dderror/20;
	//�ҵ�e��Ӧ��ģ�����ϵ�״̬
	if (e <= -5)
		for (int i = 0; i < 14; i++)
			e1[i] = E[ENL][i];
	if (e>-5&&e<=-3 )
		for (int i = 0; i < 14; i++)
			e1[i] = E[ENM][i];
	if (e > -3 && e <=-1)
		for (int i = 0; i < 14; i++)
			e1[i] = E[ENS][i];
	if (e > -1 && e <= 0)
		for (int i = 0; i < 14; i++)
			e1[i] = E[ENO][i];
	if (e > 0 && e <= 1)
		for (int i = 0; i < 14; i++)
			e1[i] = E[EPO][i];
	if (e > 1 && e <= 3)
		for (int i = 0; i < 14; i++)
			e1[i] = E[EPS][i];
	if (e > 3 && e <= 5)
		for (int i = 0; i < 14; i++)
			e1[i] = E[EPM][i];
	if (e > 5)
		for (int i = 0; i < 14; i++)
			e1[i] = E[EPL][i];

	//�ҵ�ec��Ӧ��ģ�����ϵ�״̬
	if (ec <= -5)
		for (int i = 0; i < 13; i++)
			ec1[i] = EC[ECNL][i];
	if (ec > -5 && ec <= -3)
		for (int i = 0; i < 13; i++)
			ec1[i] = EC[ECNM][i];
	if (ec > -3 && ec <= -1)
		for (int i = 0; i < 13; i++)
			ec1[i] = EC[ECNS][i];
	if (ec > -1 && ec <= 1)
		for (int i = 0; i < 13; i++)
			ec1[i] = EC[ECZO][i];
	if (ec > 1 && ec <= 3)
		for (int i = 0; i < 13; i++)
			ec1[i] = EC[ECPS][i];
	if (ec > 3 && ec <= 5)
		for (int i = 0; i < 13; i++)
			ec1[i] = EC[ECPM][i];
	if (ec > 5)
		for (int i = 0; i < 13; i++)
			ec1[i] = EC[ECPL][i]; 

}

//��������ģ����ϵ����������ģ����ϵ����
void fuzzy::U_Calculate()
{
	//����E��EC��ģ����ϵ����
	int q = 0;
	for (int j = 0; j < 14; j++)
	{
		for (int i = 0; i < 13; i++)
		{

			FC_Matrix_1[j][i] = min(e1[j], ec1[i]);
			FC_Matrix_Use_1[q] = FC_Matrix_1[j][i];
			q++;
		}
	}

	float zuida;
	for (int w = 0; w < 13; w++)
	{
		for (int f = 0; f < 14 * 13; f++)
			use[f] = min(FC_Matrix_Use_1[f], FC_Matrix_Total[f][w]);
		zuida = use[0];
		for (int f = 0; f < 14 * 13; f++)
		{
			if (use[f] >= zuida)
				zuida = use[f];
		}
		U_Final[w] = zuida;
	}
	//���Գ���
	/*
	for (int f = 0; f < 14 * 13; f++)
		use[f] = min(FC_Matrix_Use_1[f], FC_Matrix_Total[f][1]);
	zuida = use[0];
	for (int f = 0; f < 14 * 13; f++)
	{
		if (use[f] >= zuida)
			zuida = use[f];
	}
	U_Final[1] = zuida;
	*/
}
void fuzzy::U_Defuzzy()
{
	int a = 0;
	for (int i = -6; i <= 6; i++)
	{
		u = u + i * U_Final[a];
		a++;
	}
	for (int i = 0; i < 13; i++)
	{
		u_total = u_total + U_Final[i];
	}
	u = u / u_total;
}
//ģ������ļ���
//a Eģ�����ϣ�������
//b ECģ�����ϣ�������
//c Uģ�����ϣ�������
//��ÿ��ģ������Ri = ��Ai x Bi�� x Ci
//���ȼ���E �� EC��ģ����ϵ����,����E��EC��ģ����ϵ����ת��Ϊ�ɲ�����һ�μ������ʽ
//E�ɽ��ƿ���14x1��������
//EC�ɿ���1x13��������
void fuzzy::Fuzzy_Control_Matrix_cal(int a,int b,int c)
{
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

void fuzzy::Fuzzy_Control_Matrix_Total()
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if(rules[i][j]!=666)
				Fuzzy_Control_Matrix_cal(i, j, rules[i][j]);
			if (rules[i][j] == 666)
				continue;
			for(int a=0; a<14*13; a++)
				for (int b = 0; b < 13; b++)
				{
					FC_Matrix_Total[a][b] = max(FC_Matrix_Total[a][b],FC_Matrix_Final[a][b]);
				}


			/*
			for (int a = 0; a < 14 * 13; a++)
			{
				for (int b = 0; b < 13; b++)
				{
					FC_Matrix_Final_Last[a][b] = FC_Matrix_Final[a][b];
				}
			}
			if (rules[i][j] == 666)
				continue;
			if(rules[i][j]!=666)
				Fuzzy_Control_Matrix_cal(i,j,rules[i][j]);
			for (int c = 0; c < 14 * 13; c++)
			{
				for (int d = 0; d < 13; d++)
				{
					FC_Matrix_Total[c][d] = max(FC_Matrix_Final_Last[c][d], FC_Matrix_Final[c][d]);
				}
			}
			*/
		}
	}
}
 
//ģ������
void fuzzy::Set_Rules()
{

}