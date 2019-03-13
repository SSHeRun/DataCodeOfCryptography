#ifndef BIG_INT_H
#define BIG_INT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include<iostream>
#include<string>
#include<cstring>
#include<sstream>
using namespace std;
const int M=400;
const int BASE=10;

class BigInt;

BigInt operator+(const BigInt &a,const BigInt &b);
BigInt operator*(const BigInt &a,const BigInt &b);
BigInt operator-(const BigInt &a,const BigInt &b);
//BigInt operator/(const BigInt &a,const BigInt &b);
std::ostream& operator<<(std::ostream &os,BigInt &a);
//power(BigInt &BASE,BigInt &n);

//****************************************
class BigInt
{
    friend BigInt operator+(const BigInt &a,const BigInt &b);
    friend BigInt operator*(const BigInt &a,const BigInt &b);
	friend BigInt operator-(const BigInt &a,const BigInt &b);
    //friend BigInt operator/(const BigInt &a,const BigInt &b);
    friend std::ostream& operator<<(std::ostream &os,BigInt &a);
    //friend power(BigInt &BASE,BigInt &n);
private:
    static int pos;    
    //С�����λ�� pos���С������һλ�����磺3456.123 pos���6
    int sign;   //�������� 1Ϊ������-1Ϊ������
    int before; // С����ǰ��λ��
    int after;  //С������λ��
    int data[M];
	//    BigInt NormalAdd(const BigInt &a,const BigInt &b);
    BigInt NormalAdd(const BigInt &a);// �����Ƿ��żӷ����� return this+a
    BigInt NormalSubtract( const BigInt & a); //Ҫ��this>a���м��� ,�Ҳ����Ƿ���
public:
    BigInt();
    BigInt( string str);
    static void SetPos(int m){pos=m;}
    int AbsCompare(const BigInt &a);
    int Compare(const BigInt &a); // this>a return 1 ;this<a return -1;this ==a reuturn 0;
    BigInt Add( BigInt &a);
    BigInt Subtract(BigInt &a);
    BigInt Mul(const BigInt &a);
};

BigInt operator+(const BigInt &a,const BigInt &b);
BigInt operator*(const BigInt &a,const BigInt &b);
BigInt operator-(const BigInt &a,const BigInt &b);
//BigInt operator/(const BigInt &a,const BigInt &b);
std::ostream& operator<<(std::ostream &os,BigInt &a);
//power(BigInt &BASE,BigInt &n);

#endif