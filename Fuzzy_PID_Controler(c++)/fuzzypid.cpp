#include "fuzzypid.h"

fuzzypid::fuzzypid() {}

fuzzypid::~fuzzypid() {}


//ȡ������֮����ֵ��С����
float fuzzypid::min(float a, float b)
{
	if (a < b)
		return a;
	else
		return b;
}

//ȡ������֮����ֵ�ϴ����
float fuzzypid::max(float a, float b)
{
	if (a > b)
		return a;
	else
		return b;
}
//��������ȡ��
int fuzzypid::round_float(float number)
{
	return (number > 0.0) ? (number + 0.5) : (number - 0.5);
}


//���㵥ģ����������ģ������
void fuzzypid::Fuzzy_Control_Matrix_cal(int a, int b, int c)
{
	int k = 0;
	//E��ECģ����ϵ����
	for (int j = 0; j < 13; j++)
	{
		for (int i = 0; i < 13; i++)
		{
			FC_Matrix[j][i] = min(E[a][j], EC[b][i]);
			FC_Matrix_Use[k] = FC_Matrix[j][i];
			k++;
		}
	}

	//E��EC��Uģ����ϵ����
	for (int i = 0; i < 13 * 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			FC_Matrix_Final[i][j] = min(FC_Matrix_Use[i], U[c][j]);
		}
	}
}


//���Ժ�����������֤�㷨
void fuzzypid::Fuzzy_Control_Matrix_cal_1()
{
	int h = 0;
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
		{
		   v[j][i] = min(y[j],k[i]);
		   vv[h] = v[j][i];
		   h++;
		}
	}
	for(int i=0;i<3*3;i++)
		for (int j = 0; j < 3; j++)
		{
			vvv[i][j] = min(vv[i],p[j]);
		}
}


//��������ģ��������Kp��Ki��Kd����E��EC��U����ģ����ϵ����
void fuzzypid::Fuzzy_Control_Matrix_Total()
{
	//�ֱ����Kp Ki Kd����ģ����ϵ����
	for (int m = 0; m < 3; m++)
	{

		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (rules[m][i][j] != 666)
					Fuzzy_Control_Matrix_cal(i, j, rules[m][i][j]);
				if (rules[m][i][j] == 666)
					continue;
				for (int a = 0; a < 13 * 13; a++)
					for (int b = 0; b < 13; b++)
					{
						Final[m][a][b] = max(Final[m][a][b], FC_Matrix_Final[a][b]);
					}
			}
		}
	}
}


//������������ģ��������
void fuzzypid::Fuzzy_Input(float target_e, float current_value_e, float target_ec, float current_value_ec)
{
	error = current_value_e - target_e;
	dderror = current_value_ec - target_ec;
	e = error / 10;
	ec = dderror / 20;

	//�ҵ�e��Ӧ��ģ�����ϵ�״̬
	if (e <= -5)
		for (int i = 0; i < 13; i++)
			e1[i] = E[ENL][i];
	if (e > -5 && e <= -3)
		for (int i = 0; i < 13; i++)
			e1[i] = E[ENM][i];
	if (e > -3 && e <= -1)
		for (int i = 0; i < 13; i++)
			e1[i] = E[ENS][i];
	if (e > -1 && e <= 1)
		for (int i = 0; i < 13; i++)
			e1[i] = E[EZO][i];
	if (e > 1 && e <= 3)
		for (int i = 0; i < 13; i++)
			e1[i] = E[EPS][i];
	if (e > 3 && e <= 5)
		for (int i = 0; i < 13; i++)
			e1[i] = E[EPM][i];
	if (e > 5)
		for (int i = 0; i < 13; i++)
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


//���������U��ģ����ϵ����
void fuzzypid::U_Calculate()
{
	//����E��EC��ģ����ϵ����
	int k = 0;
	for (int j = 0; j < 13; j++)
	{
		for (int i = 0; i < 13; i++)
		{
			fc_matrix[j][i] = min(e1[j],ec1[i]);
			fc_matrix_use[k] = fc_matrix[j][i];
			k++;
		}
	}

	//�� E��ECȷ����ģ����ϵ���� �� ��ģ����ϵ���� ����������U��ģ����ϵ����
	for (int m = 0; m < 3; m++)
	{
		float zuida;
		float use[13*13];
		for (int w = 0; w < 13; w++)
		{
			for (int f = 0; f < 13 * 13; f++)
				use[f] = min(fc_matrix_use[f], Final[m][f][w]);
			zuida = use[0];
			for (int f = 0; f < 13 * 13; f++)
			{
				if (use[f] >= zuida)
					zuida = use[f];
			}
			U_Final[m][w] = zuida;
	    }
	}
}


//��ģ������������Ȩƽ����
void fuzzypid::U_Defuzzy()
{
	int a = 0;
	float u_total[3] = {0,0,0};

	for (int m = 0; m < 3; m++)
	{
		for (int i = -6; i <= 6; i++)
		{
			u[m] = u[m] + i * U_Final[m][a];
			a++;
		}
		for (int i = 0; i < 13; i++)
		{
			u_total[m] = u_total[m] + U_Final[m][i];
		}
		u[m] = u[m] / u_total[m];
	}
}


//����E��EC����Kp��Ki��Kd��ֵ
void fuzzypid::Cal_Kp_Ki_Kd(float Kp, float Ki, float Kd)
{
	Kp_ = (u[0] / u_max) * (Kp_max / 2);
	Ki_ = (u[1] / u_max) * (Ki_max / 2);
	Kd_ = (u[2] / u_max) * (Kd_max / 2);

	kp = Kp + Kp_;
	ki = Ki + Ki_;
	kd = Kd + Kd_;
}
