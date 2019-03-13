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
    //小数点的位置 pos存放小数点后第一位。比如：3456.123 pos存放6
    int sign;   //数的正负 1为正数，-1为负数，
    int before; // 小数点前的位数
    int after;  //小数点后的位数
    int data[M];
	//    BigInt NormalAdd(const BigInt &a,const BigInt &b);
    BigInt NormalAdd(const BigInt &a);// 不考虑符号加法运算 return this+a
    BigInt NormalSubtract( const BigInt & a); //要求this>a进行减法 ,且不考虑符号
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