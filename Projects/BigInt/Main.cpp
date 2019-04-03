// BigInt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include "BigInt.h"

int main(int argc, char* argv[])
{

	char op;
	cout<<"which operation you want to choose?('+','-','*')"<<endl;
	op=getchar();
	
	string str1,str2;
	cout<<"please input two big number"<<endl;
	cin>>str1;
	getchar();
	cin>>str2;
	cout<<"a="<<str1<<"  "<<"b="<<str2<<endl;


	BigInt a( str1 );
	BigInt b( str2 );
	BigInt c;
	switch(op){
	case '+':
		c = a + b;
		std::cout <<"a+b="<<c<< std::endl;
		break;
	case '-':
		c = a - b;
		std::cout <<"a-b="<<c<< std::endl;
		break;
	case '*':
		c = a * b;
		std::cout <<"a*b="<<c<< std::endl;
		break;
	default:
		std::cout <<"can't run!"<< std::endl;
	}

	//BigInt a( "1234567890" );
	//BigInt b( "1000000000" );

	//std::cout << c << std::endl;
	system( "pause" );

	return 0;
}
