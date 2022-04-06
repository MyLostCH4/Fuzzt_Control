#pragma once
#ifndef FUZZYPID_H
#define FUZZYPID_H
//Ϊ������ģ���ȼ�֮�佨����Ӧ��ϵ

#define ENL 0
#define ENM 1
#define ENS 2
#define EZO 3
#define EPS 4
#define EPM 5
#define EPL 6

#define ECNL 0
#define ECNM 1
#define ECNS 2
#define ECZO 3
#define ECPS 4
#define ECPM 5
#define ECPL 6

#define UNL 0
#define UNM 1
#define UNS 2
#define UZO 3
#define UPS 4
#define UPM 5
#define UPL 6
class fuzzypid
{
public:

	fuzzypid();
	~fuzzypid();


	//����a��b֮����ֵС���Ǹ�
	float min(float a, float b);


	//����a��b֮����ֵ����Ǹ�
	float max(float a, float b);


	//�������뽫С����Ϊ����
	int round_float(float number);


	//fuzzy matrixģ����ϵ�������
	void Fuzzy_Control_Matrix_cal(int a, int b, int c);


	//��������ģ������Ĳ�����������ģ���������һ��
	void Fuzzy_Control_Matrix_Total();


	//��������ģ��������
	void Fuzzy_Input(float target_e, float current_value_e, float target_ec, float current_value_ec);


	//���������ģ������
	void U_Calculate();


	//�������ģ�������ģ����
	void U_Defuzzy();


	//��������˦�Kp �� ��Ki �� ��Kd֮���Kp��Ki��Kd
	void Cal_Kp_Ki_Kd(float Kp,float Ki,float Kd);

	//����Kp��Ki��Kd�ı仯����
	void Input_Kp_Interval(float a, float b) { Kp_max =  b - a; }

	void Input_Ki_Interval(float a, float b) { Ki_max = b - a; }
	
	void Input_Kd_Interval(float a, float b) { Kd_max = b - a; }



	//E��EC��ɵ�ģ����ϵ����(������ģ������ʱʹ��)
	float FC_Matrix[13][13];
	float FC_Matrix_Use[13 * 13];
	float FC_Matrix_Final[13*13][13];
	

	//����ľ�ȷ�Ƕ����ͽ��ٶ����
	float error;
	float dderror;


	//�����ӳ�䵽�涨����
	float e;
	float ec;


	//��ȷ���ģ���������õ���ģ������
	float e1[13];
	float ec1[13];
	float u1[13];

	//e1��ec1��ɵ�ģ����ϵ���󣬼����������ʱʹ��
	float fc_matrix[13][13];
	float fc_matrix_use[13 * 13];


	//Kp ��Ki��Kd�����ģ������
	float U_Final[3][13];


	//���Kp��Ki��Kdģ������ľ�ȷ��
	float u[3];


	//�����������ģ�������������������ֵ������ֵ��
	float u_max = (1 * 6 + 0.8 * 5 + 0.4 * 4 + 0.1 * 3) / (1 + 0.8 + 0.4 + 0.1);

	//Kp Ki Kd����Ӧ����ģ����ϵ����
	float Final[3][13 * 13][13];


	//Kp��Ki��Kd�ı仯��
	float Kp_;
	float Ki_;
	float Kd_;

	//Kp��Ki��Kd�ı仯��Χ
	float Kp_max;
	float Ki_max;
	float Kd_max;

	//�����Kp��Ki��Kd��ֵ
	float kp;
	float ki;
	float kd;



	//���Ա�����������֤�㷨
	float y[3] = { 1,2,3 };
	float k[3] = { 4,3,1 };
	float p[3] = { 4,6,7 };
	float v[3][3];
	float vv[9];
	float vvv[3 * 3][3];

	//���Ժ�����������֤�㷨
	void Fuzzy_Control_Matrix_cal_1();
 
private:
	//�Ƕ��������
	float E[7][13] =
	{
		//-6    -5    -4    -3     -2    -1     0     1     2     3     4     5     6
		{ 1.0,  0.8,  0.4,  0.1,    0,    0,    0,    0,    0,    0,    0,    0,    0},//ENL

		{ 0.2,  0.7,  1.0,  0.7,  0.2,    0,    0,    0,    0,    0,    0,    0,    0},//ENM

		{   0,    0,  0.2,  0.6,  1.0,  0.9,    0,    0,    0,    0,    0,    0,    0},//ENS

		{   0,    0,    0,    0,    0,  0.5,  1.0,  0.5,    0,    0,    0,    0,    0},//EZO

		{   0,    0,    0,    0,    0,    0,    0,  0.9,  1.0,  0.7,  0.2,    0,    0},//EPS

		{   0,    0,    0,    0,    0,    0,    0,    0,  0.2,  0.7,  1.0,  0.7,  0.2},//EPM

		{   0,    0,    0,    0,    0,    0,    0,    0,    0,  0.1,  0.4,  0.8,  1.0} //EPL
	};
	//���ٶ��������
	float EC[7][13] =
	{
		//-6    -5    -4    -3     -2    -1     0     1     2     3     4     5     6
		{ 1.0,  0.8,  0.4,  0.1,    0,    0,    0,    0,    0,    0,    0,    0,    0},//ECNL

		{ 0.2,  0.7,  1.0,  0.7,  0.2,    0,    0,    0,    0,    0,    0,    0,    0},//ECNM

		{   0,    0,  0.2,  0.6,  1.0,  0.9,    0,    0,    0,    0,    0,    0,    0},//ECNS

		{   0,    0,    0,    0,    0,  0.5,  1.0,  0.5,    0,    0,    0,    0,    0},//ECZO

		{   0,    0,    0,    0,    0,    0,    0,  0.9,  1.0,  0.7,  0.2,    0,    0},//ECPS

		{   0,    0,    0,    0,    0,    0,    0,    0,  0.2,  0.7,  1.0,  0.7,  0.2},//ECPM

		{   0,    0,    0,    0,    0,    0,    0,    0,    0,  0.1,  0.4,  0.8,  1.0} //ECPL
	};
	//���������
	float U[7][13] =
	{
		//-6    -5    -4    -3     -2    -1     0     1     2     3     4     5     6
		{ 1.0,  0.8,  0.4,  0.1,    0,    0,    0,    0,    0,    0,    0,    0,    0},//UNL

		{ 0.2,  0.7,  1.0,  0.7,  0.2,    0,    0,    0,    0,    0,    0,    0,    0},//UNM

		{   0,    0,  0.2,  0.6,  1.0,  0.9,    0,    0,    0,    0,    0,    0,    0},//UNS

		{   0,    0,    0,    0,    0,  0.5,  1.0,  0.5,    0,    0,    0,    0,    0},//UZO

		{   0,    0,    0,    0,    0,    0,    0,  0.9,  1.0,  0.7,  0.2,    0,    0},//UPO

		{   0,    0,    0,    0,    0,    0,    0,    0,  0.2,  0.7,  1.0,  0.7,  0.2},//UPS

		{   0,    0,    0,    0,    0,    0,    0,    0,    0,  0.1,  0.4,  0.8,  1.0} //UPM
	};

	//ģ�����򣬴����ھ����У�����λ����ֵΪ666�����ʾ�����ܳ��ֵ������������
	float rules[3][7][7] =
	{
		//Kp��Ӧ��ģ������
		{
			//ENL   ENM   ENS   EZO   EPS   EPM   EPL
			{ 666,  666,  UPL,  UPL,  UPL,  UNM,  UNL},//ECNL

			{ UPM,  UPS,  UPS,  UPM,  UPM,  UNM,  UNL},//ECNM

			{ UPL,  UPM,  UPS,  UPS,  UPS,  UNM,  UNL},//ECNS

			{ UPL,  UPM,  UPS,  UZO,  UNS,  UNM,  UNL},//ECZO

			{ UPL,  UPM,  UNS,  UNS,  UNS,  UNM,  UNL},//ECPS

			{ UPL,  UPM,  UNM,  UNS,  UNS,  UNS,  UNM},//ECPM

			{ UPL,  UPM,  UNL,  UNL,  UNL,  666,  666} //ECPL
		},
		//Ki��Ӧ��ģ������
		{
			//ENL   ENM   ENS   EZO   EPS   EPM   EPL
			{ 666,  666,  UPL,  UPL,  UPL,  UNM,  UNL},//ECNL

			{ UPM,  UPS,  UPS,  UPM,  UPM,  UNM,  UNL},//ECNM

			{ UPL,  UPM,  UPS,  UPS,  UPS,  UNM,  UNL},//ECNS

			{ UPL,  UPM,  UPS,  UZO,  UNS,  UNM,  UNL},//ECZO

			{ UPL,  UPM,  UNS,  UNS,  UNS,  UNM,  UNL},//ECPS

			{ UPL,  UPM,  UNM,  UNS,  UNS,  UNS,  UNM},//ECPM

			{ UPL,  UPM,  UNL,  UNL,  UNL,  666,  666} //ECPL
		},
		//Kd��Ӧ��ģ������
		{
			//ENL   ENM   ENS   EZO   EPS   EPM   EPL
			{ 666,  666,  UPL,  UPL,  UPL,  UNM,  UNL},//ECNL

			{ UPM,  UPS,  UPS,  UPM,  UPM,  UNM,  UNL},//ECNM

			{ UPL,  UPM,  UPS,  UPS,  UPS,  UNM,  UNL},//ECNS

			{ UPL,  UPM,  UPS,  UZO,  UNS,  UNM,  UNL},//ECZO

			{ UPL,  UPM,  UNS,  UNS,  UNS,  UNM,  UNL},//ECPS

			{ UPL,  UPM,  UNM,  UNS,  UNS,  UNS,  UNM},//ECPM

			{ UPL,  UPM,  UNL,  UNL,  UNL,  666,  666} //ECPL
		}

	};
	//���Ծ���
	float ru[7][7] =
	{
		//ENL   ENM   ENS   EZO   EPS   EPM   EPL
		{ 666,  666,  UPL,  UPL,  UPL,  UNM,  UNL},//ECNL

		{ UPM,  UPS,  UPS,  UPM,  UPM,  UNM,  UNL},//ECNM

		{ UPL,  UPM,  UPS,  UPS,  UPS,  UNM,  UNL},//ECNS

		{ UPL,  UPM,  UPS,  UZO,  UNS,  UNM,  UNL},//ECZO

		{ UPL,  UPM,  UNS,  UNS,  UNS,  UNM,  UNL},//ECPS

		{ UPL,  UPM,  UNM,  UNS,  UNS,  UNS,  UNM},//ECPM

		{ UPL,  UPM,  UNL,  UNL,  UNL,  666,  666} //ECPL
	};
};



#endif // !FUZZYPID_H
