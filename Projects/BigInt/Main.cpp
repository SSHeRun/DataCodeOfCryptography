// BigInt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "BigInt.h"

int main(int argc, char* argv[])
{
	BigInt a( "1234567890" );
	BigInt b( "1000000000" );
	BigInt c = a * b;
	std::cout << c << std::endl;

	system( "pause" );

	return 0;
}
