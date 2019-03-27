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
#define MAX_FILE	1024

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
	
	int ReadFileLenth=0;//��������ļ��ĳ���
	unsigned char bufferIN[MAX_FILE] = {0};//�������뻺���С
	unsigned char bufferOUT[MAX_FILE] = {0};//���������������С
	unsigned char *pBuffIn = bufferIN;//�������뻺����ָ��
	unsigned char *pBuffOut = bufferOUT;//�������������ָ��
	
	unsigned k1 = 0;//��Կ��λ
	unsigned k2 = 0;//��Կ��λ
	unsigned m1 = 0;//32λ����(��)
	unsigned m2 = 0;//32λ����(��)
	unsigned c1 = 0;//����(��)
	unsigned c2 = 0;//����(��)
	if(CheckParse(argc,argv)){
	//У����������Ƿ���ȷ
		memcpy(&k1,argv[3],4);
		memcpy(&k2,argv[3]+4,4);
		//�ָ���ԿΪ��λ�͸�λ
		ReadFileLenth=FileIn(argv[2],pBuffIn);
		//�����ļ�
		if(ReadFileLenth%8!=0){//����ļ��ĳ��Ȳ���8�ı���
			for(int i=0;i<=8;i++){
				if(*(pBuffIn+ReadFileLenth/8+i)==NULL){
					*(pBuffIn+ReadFileLenth/8+i)=0;//���벻��8�ֽڵ���ĩ�ļ�β
				}
			}
			ReadFileLenth=(ReadFileLenth/8+1)*8; 
		}
		if(argv[1][1]=='e'){
			for(int i=0;i<ReadFileLenth/8;i++){
				memcpy(&m1,pBuffIn+i*8,4);
				memcpy(&m2,pBuffIn+i*8+4,4);
				des_encrypt(k1,k2,m1,m2,c1,c2);//����
				memcpy(pBuffOut+i*8,&c1,4);
				memcpy(pBuffOut+i*8+4,&c2,4);
			}
			FileOut(pBuffOut,ReadFileLenth,DECRYPT_FILE);
		}else if(argv[1][1]=='d'){
			for(int i=0;i<ReadFileLenth/8;i++){
				memcpy(&c1,pBuffIn+i*8,4);
				memcpy(&c2,pBuffIn+i*8+4,4);
				des_decrypt(k1,k2,c1,c2,m1,m2);//����
				memcpy(pBuffOut+i*8,&m1,4);
				memcpy(pBuffOut+i*8+4,&m2,4);
			}
			FileOut(pBuffOut,ReadFileLenth,ENCRYPT_FILE);
		}else{
			printf("�����������\n");
		}
	}else{
		printf("�����������\n");
	}
	return true;
}