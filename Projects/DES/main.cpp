/******************************************************************************/
//	���̣�DES
//	���ܣ�DES�ӡ������ļ�
//  ���ߣ�jlcss|ExpNIS

/******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <afxwin.h>

#include "des.h"

#define DECRYPT_FILE "DES��������.txt"
#define ENCRYPT_FILE "DES��������.txt"
//! Լ���ļ����2M
#define MAX_FILE	1024*1024*2

/******************************************************************************/
//	���ƣ�usage
//	���ܣ�������Ϣ
//  ������Ӧ�ó�������
//	���أ���ʾ��Ϣ

/******************************************************************************/
void Usage( const char *appname )
{
	printf( "\n\tusage: des -e �����ļ� 64λ��Կ\n" );
	printf( "\tusage: des -d �����ļ� 64λ��Կ\n" );
}

/******************************************************************************/
//	���ƣ�FileIn
//	���ܣ���ȡ�����ļ����ڴ�
//  ������strFile:�ļ����ƣ�inBuff:ָ���ļ����ݻ�����
//	���أ�ʵ�ʶ�ȡ���ݴ�С(�ֽ�)

/******************************************************************************/
int FileIn( const char *strFile, unsigned char *&inBuff )
{
	int iFileLen=0;

	//! �������ļ�
	CFile file( strFile, CFile::modeRead );
	iFileLen = ( int )file.GetLength();
	if( iFileLen>MAX_FILE )
	{
		printf( "�ļ����Ȳ��ܴ��� %dM,!\n", MAX_FILE/(1024*1024) );
		goto out;
	}

	inBuff = new unsigned char[iFileLen+1];
	if( !inBuff )
		goto out;

	file.Read( inBuff, iFileLen );
	file.Close();
	inBuff[iFileLen] = 0;

out:
	return iFileLen;
}

/******************************************************************************/
//	���ƣ�FileOut
//	���ܣ���/���ܽ���������ǰĿ¼�����ļ���
//  ������strOutָ������ַ��������������Сlen��strFileΪ����ļ�
//	���أ���

/******************************************************************************/
void FileOut( const void *strOut, int len, const char *strFile )
{
	//! ������ļ�
	CFile outfile( strFile , CFile::modeCreate | CFile::modeWrite );
	outfile.Write( strOut , len );
	outfile.Close();
}

/******************************************************************************/
//	���ƣ�CheckParse
//	���ܣ�У��Ӧ�ó�����ڲ���
//  ������argc����main������argc������argvָ��main������argv����
//	���أ��������Ϸ�����true�����򷵻�false
//  ��ע���򵥵���ڲ���У��

/******************************************************************************/
bool CheckParse( int argc, char** argv )
{
	if( (argc != 4) || 
		(argv[1][1]!='e' && argv[1][1]!='d') ||
		(strlen( argv[3] ) >(64/8) ) )
	{
		Usage( argv[0] );
		return false;
	}

	return true;
}

//! ����������(Use MFC in a Shared DLL)
int main( int argc, char **argv )
{
	//! �ڴ˴���д����......

	return true;
}