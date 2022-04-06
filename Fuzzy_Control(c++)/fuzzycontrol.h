//Ŀǰֻ֧��7��ģ���ȼ�������Ϊ[-6��6]
//                       ģ���ȼ�Ϊ��PB PM PS ZO NS NM NP
// 
//****************** ע�⣺ģ���ȼ�������Ŀǰ��֧���Զ���***********************
// 
//˫���룺�Ƕ�ƫ��E�ͽ��ٶ�ƫ��EC
//���������Kp ��Ki ��Kd
#pragma once
#ifndef FUZZYCONTROL_H
#define FUZZYCONTROL_H
//Ϊ������ģ���ȼ�֮�佨����Ӧ��ϵ

#define ENL 0
#define ENM 1
#define ENS 2
#define ENO 3
#define EPO 4
#define EPS 5
#define EPM 6
#define EPL 7

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

 
class fuzzy
{
 public:
	 fuzzy();
	 ~fuzzy();
	 //fuzzy matrixģ����ϵ�������
	 void Fuzzy_Control_Matrix_cal(int a,int b,int c);
	 void Set_Rules();


	 //����a��b֮����ֵС���Ǹ�
	 float min(float a,float b);
	 //����a��b֮����ֵ����Ǹ�
	 float max(float a,float b);
	 //�������뽫С����Ϊ����
	 int round_float(float number);

	 //��������ģ������Ĳ�����������ģ���������һ��
	 void Fuzzy_Control_Matrix_Total();

	
	 
	 //��������ģ��������
	 void Fuzzy_Input(float target_e, float current_value_e, float target_ec, float current_value_ec);
	 //���������ģ������
	 void U_Calculate();
	 //�������ģ�������ģ����
	 void U_Defuzzy();



	 //����ĳһ������E��EC��U��ɵ�ģ����ϵ����
	 float FC_Matrix_Final[14 * 13][13];


	 //�����̺�����ģ�������ģ������
	 float FC_Matrix_Total[14 * 13][13];

	 //�洢����������ֵU��ģ������
	 float U_Final[13];
	 //����E��EC��ɵ�ģ����ϵ����(������ģ������ʱʹ��)
	 float FC_Matrix[14][13];
	 float FC_Matrix_Use[14 * 13];

	 //����E��EC��ɵ�ģ����ϵ����(�������ģ������ʱʹ��)
	 float FC_Matrix_1[14][13];
	 float FC_Matrix_Use_1[14 * 13];



	 //�洢�ǶȲ�ֵE
	 float error;
	 //�������ٶȲ�ֵEC dderror
	 float dderror;

	 //ģ������E��EC
	 float e;
	 float ec;
	 float e1[14];
	 float ec1[13];
	 float u1[13];
	 //�������ģ������U�ľ�ȷ��
	 float u;
	 float u_total;

	 float use[13 * 14];
private:
	//�Ƕ��������[-6,6]����14����(��+0��-0������14��)

	 float E[8][14] = 
	{ 
    //-6    -5    -4    -3     -2    -1    -0    +0     1     2     3     4     5    6
	{ 1.0,  0.8,  0.4,  0.1,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},//NL
 
	{ 0.2,  0.7,  1.0,  0.7,  0.2,    0,    0,    0,    0,    0,    0,    0,    0,   0},//NM
 
	{   0,    0,  0.1,  0.5,  1.0,  0.8,  0.3,    0,    0,    0,    0,    0,    0,   0},//NS
 
	{   0,    0,    0,    0,  0.1,  0.6,  1.0,    0,    0,    0,    0,    0,    0,   0},//NO
 
	{   0,    0,    0,    0,    0,    0,    0,  1.0,  0.6,  0.1,    0,    0,    0,   0},//PO
 
	{   0,    0,    0,    0,    0,    0,    0,  0.3,  0.8,  1.0,  0.5,  0.1,    0,   0},//PS
 
	{   0,    0,    0,    0,    0,    0,    0,    0,    0,  0.2,  0.7,  1.0,  0.7, 0.2},//PM
 
	{   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  0.1,  0.4,  0.8, 1.0}	//PL
	};


	//���ٶ��������ͬ
    float EC[7][13] = 
	{
    //-6    -5    -4    -3     -2    -1     0     1     2     3     4     5     6
	{ 1.0,  0.8,  0.4,  0.1,    0,    0,    0,    0,    0,    0,    0,    0,    0},//NL

	{ 0.2,  0.7,  1.0,  0.7,  0.2,    0,    0,    0,    0,    0,    0,    0,    0},//NM

	{   0,    0,  0.2,  0.6,  1.0,  0.9,    0,    0,    0,    0,    0,    0,    0},//NS

	{   0,    0,    0,    0,    0,  0.5,  1.0,  0.5,    0,    0,    0,    0,    0},//ZO

	{   0,    0,    0,    0,    0,    0,    0,  0.9,  1.0,  0.7,  0.2,    0,    0},//PS

	{   0,    0,    0,    0,    0,    0,    0,    0,  0.2,  0.7,  1.0,  0.7,  0.2},//PM

	{   0,    0,    0,    0,    0,    0,    0,    0,    0,  0.1,  0.4,  0.8,  1.0} //PL
	};


	//���������ͬ
	float U[7][13] =  
	{
    //-6    -5    -4    -3     -2    -1     0     1     2     3     4     5     6
	{ 1.0,  0.8,  0.4,  0.1,    0,    0,    0,    0,    0,    0,    0,    0,    0},//NL

	{ 0.2,  0.7,  1.0,  0.7,  0.2,    0,    0,    0,    0,    0,    0,    0,    0},//NM

	{   0,    0,  0.2,  0.6,  1.0,  0.9,    0,    0,    0,    0,    0,    0,    0},//NS

	{   0,    0,    0,    0,    0,  0.5,  1.0,  0.5,    0,    0,    0,    0,    0},//ZO

	{   0,    0,    0,    0,    0,    0,    0,  0.9,  1.0,  0.7,  0.2,    0,    0},//PO

	{   0,    0,    0,    0,    0,    0,    0,    0,  0.2,  0.7,  1.0,  0.7,  0.2},//PS

	{   0,    0,    0,    0,    0,    0,    0,    0,    0,  0.1,  0.4,  0.8,  1.0} //PM
	};


	//ģ�����򣬴����ھ����У�����λ����ֵΪ666�����ʾ�����ܳ��ֵ������������
	float rules[7][8] =
	{
    //ENL   ENM   ENS   ENO   EPO   EPS   EPM   EPL
	{ 666,  666,  UPL,  UPL,  UPL,  UPL,  UNM,  UNL},//ECNL

	{ UPM,  UPS,  UPS,  UPM,  UPM,  UPM,  UNM,  UNL},//ECNM

	{ UPL,  UPM,  UPS,  UPS,  UPS,  UPS,  UNM,  UNL},//ECNS

	{ UPL,  UPM,  UPS,  UZO,  UZO,  UNS,  UNM,  UNL},//ECZO

	{ UPL,  UPM,  UNS,  UNS,  UNS,  UNS,  UNM,  UNL},//ECPS

	{ UPL,  UPM,  UNM,  UNM,  UNS,  UNS,  UNS,  UNM},//ECPM

	{ UPL,  UPM,  UNL,  UNL,  UNL,  UNL,  666,  666} //ECPL
	};



};


#endif // !FUZZYCONTROL_H

