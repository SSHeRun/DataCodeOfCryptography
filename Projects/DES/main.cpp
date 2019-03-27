/******************************************************************************/
//	工程：DES
//	功能：DES加、解密文件
//  作者：jlcss|ExpNIS

/******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <afxwin.h>

#include "des.h"

#define DECRYPT_FILE "DES加密密文.txt"
#define ENCRYPT_FILE "DES解密明文.txt"
//! 约束文件最大2M
#define MAX_FILE	1024

/******************************************************************************/
//	名称：usage
//	功能：帮助信息
//  参数：应用程序名称
//	返回：提示信息

/******************************************************************************/
void Usage( const char *appname )
{
	printf( "\n\tusage: des -e 明文文件 64位密钥\n" );
	printf( "\tusage: des -d 密文文件 64位密钥\n" );
}

/******************************************************************************/
//	名称：FileIn
//	功能：读取磁盘文件到内存
//  参数：strFile:文件名称；inBuff:指向文件内容缓冲区
//	返回：实际读取内容大小(字节)

/******************************************************************************/
int FileIn( const char *strFile, unsigned char *&inBuff )
{
	int iFileLen=0;

	//! 打开密文文件
	CFile file( strFile, CFile::modeRead );
	iFileLen = ( int )file.GetLength();
	if( iFileLen>MAX_FILE )
	{
		printf( "文件长度不能大于 %dM,!\n", MAX_FILE/(1024*1024) );
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
//	名称：FileOut
//	功能：加/解密结果输出到当前目录磁盘文件中
//  参数：strOut指向输出字符缓冲区，输出大小len，strFile为输出文件
//	返回：无

/******************************************************************************/
void FileOut( const void *strOut, int len, const char *strFile )
{
	//! 输出到文件
	CFile outfile( strFile , CFile::modeCreate | CFile::modeWrite );
	outfile.Write( strOut , len );
	outfile.Close();
}

/******************************************************************************/
//	名称：CheckParse
//	功能：校验应用程序入口参数
//  参数：argc等于main主函数argc参数，argv指向main主函数argv参数
//	返回：若参数合法返回true，否则返回false
//  备注：简单的入口参数校验

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

//! 程序主函数(Use MFC in a Shared DLL)
int main( int argc, char **argv )
{
	//! 在此处填写代码......
	
	int ReadFileLenth=0;//定义读入文件的长度
	unsigned char bufferIN[MAX_FILE] = {0};//定义输入缓冲大小
	unsigned char bufferOUT[MAX_FILE] = {0};//定义输出缓冲区大小
	unsigned char *pBuffIn = bufferIN;//定义输入缓冲区指针
	unsigned char *pBuffOut = bufferOUT;//定义输出缓冲区指针
	
	unsigned k1 = 0;//密钥低位
	unsigned k2 = 0;//密钥高位
	unsigned m1 = 0;//32位明文(左)
	unsigned m2 = 0;//32位明文(右)
	unsigned c1 = 0;//密文(左)
	unsigned c2 = 0;//密文(右)
	if(CheckParse(argc,argv)){
	//校验输出参数是否正确
		memcpy(&k1,argv[3],4);
		memcpy(&k2,argv[3]+4,4);
		//分割密钥为低位和高位
		ReadFileLenth=FileIn(argv[2],pBuffIn);
		//读入文件
		if(ReadFileLenth%8!=0){//如果文件的长度不是8的倍数
			for(int i=0;i<=8;i++){
				if(*(pBuffIn+ReadFileLenth/8+i)==NULL){
					*(pBuffIn+ReadFileLenth/8+i)=0;//补齐不足8字节的最末文件尾
				}
			}
			ReadFileLenth=(ReadFileLenth/8+1)*8; 
		}
		if(argv[1][1]=='e'){
			for(int i=0;i<ReadFileLenth/8;i++){
				memcpy(&m1,pBuffIn+i*8,4);
				memcpy(&m2,pBuffIn+i*8+4,4);
				des_encrypt(k1,k2,m1,m2,c1,c2);//加密
				memcpy(pBuffOut+i*8,&c1,4);
				memcpy(pBuffOut+i*8+4,&c2,4);
			}
			FileOut(pBuffOut,ReadFileLenth,DECRYPT_FILE);
		}else if(argv[1][1]=='d'){
			for(int i=0;i<ReadFileLenth/8;i++){
				memcpy(&c1,pBuffIn+i*8,4);
				memcpy(&c2,pBuffIn+i*8+4,4);
				des_decrypt(k1,k2,c1,c2,m1,m2);//解密
				memcpy(pBuffOut+i*8,&m1,4);
				memcpy(pBuffOut+i*8+4,&m2,4);
			}
			FileOut(pBuffOut,ReadFileLenth,ENCRYPT_FILE);
		}else{
			printf("参数输入错误\n");
		}
	}else{
		printf("参数输入错误\n");
	}
	return true;
}