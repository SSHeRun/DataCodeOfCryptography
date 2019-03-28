/******************************************************************************/
//	���̣�AES
//	���ܣ�AES�ӡ������ļ�
//  ���ߣ�jlcss|ExpNIS

/******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <afxwin.h>

#include "aes.h"

#define DECRYPT_FILE "AES��������.txt"
#define ENCRYPT_FILE "AES��������.txt"
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
	printf( "\n\tusage: aes -e �����ļ� 128λ��Կ\n" );
	printf( "\tusage: aes -d �����ļ� 128λ��Կ\n" );
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
//	���أ����³ɹ�����ʵ��������ȣ����򷵻�0

/******************************************************************************/
int FileOut( const void *strOut, int len, const char *strFile )
{
	FILE *fp = NULL;
	int iWrite=0;

	if( strOut == NULL || len ==0 )
		goto out;

	//! ���ļ����
	if( (fp = fopen( strFile,"wb" )) == NULL ) // ������д
		goto out;

	iWrite = fwrite( strOut, 1, len, fp );
	fclose(fp);

out:
	return iWrite;
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
		(strlen( argv[3] ) >(128/8) ) )
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
	unsigned char mw[16]={0};//�������ĺ����ĳ���
	unsigned char key[16]={0};
	if(CheckParse(argc,argv)){
	//У����������Ƿ���ȷ
		//memcpy(key,argv[3],16);
		//������Կ
		ReadFileLenth=FileIn(argv[2],pBuffIn);
		//�����ļ�
		if(ReadFileLenth%16!=0){//����ļ��ĳ��Ȳ���16�ı���
			for(int i=0;i<=16;i++){
				if(*(pBuffIn+ReadFileLenth/16+i)==NULL){
					*(pBuffIn+ReadFileLenth/16+i)=0;//���벻��16�ֽڵ���ĩ�ļ�β
				}
			}
			ReadFileLenth=(ReadFileLenth/16+1)*16; 
		}
		if(argv[1][1]=='e'){
			for(int i=0;i<ReadFileLenth/16;i++){
				memcpy(mw,pBuffIn+i*16,16);
				aes_encrypt((unsigned char *)argv[3],(unsigned int *)mw);//����
				memcpy(pBuffOut+i*16,mw,16);
			}
			FileOut(pBuffOut,ReadFileLenth,DECRYPT_FILE);
		}else if(argv[1][1]=='d'){
			for(int i=0;i<ReadFileLenth/16;i++){
				memcpy(mw,pBuffIn+i*16,16);
				aes_decrypt((unsigned char *)argv[3],(unsigned int *)mw);//����
				memcpy(pBuffOut+i*16,mw,16);
			}
			FileOut(pBuffOut,ReadFileLenth,ENCRYPT_FILE);
		}else{
			printf("�����������\n");
		}
	}else{
		printf("�����������\n");
	}
	return 0;
}