// Crypto.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wincrypt.h>
#define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)
#define KEYLENGTH  0x00800000
void HandleError(char *s);

#define ENCRYPT_ALGORITHM CALG_RC4 
#define ENCRYPT_BLOCK_SIZE 8

 
bool EncryptFile(
				 PCHAR szSource, 
				 PCHAR szDestination, 
				 PCHAR szPassword);

int main(int argc, char* argv[])
{
	
    CHAR szSource[100]; 
    CHAR szDestination[100]; 
    CHAR szPassword[100]; 	
	
	printf("Encrypt a file. \n\n");
	printf("Enter the name of the file to be encrypted: ");//输入要加密的源文件名
	scanf("%s",szSource);
	printf("Enter the name of the output file: ");//加密后文件输出存放地址
	scanf("%s",szDestination);
	printf("Enter the password:");//加密密码
	scanf("%s",szPassword);
	
	//调用加密方法
	if(EncryptFile(szSource, szDestination, szPassword))
	{
		printf("Encryption of the file %s was a success. \n", szSource);
		printf("The encrypted data is in file %s.\n",szDestination);		
	}
	else
	{
		HandleError("Error encrypting file!"); 
	} 

	system("pause");
	return 0;
}

//加密方法
static bool EncryptFile(PCHAR szSource,PCHAR szDestination,PCHAR szPassword)						
{ 		
	//声明和初始化局部变量 
	FILE *hSource; 
	FILE *hDestination; 
	
	HCRYPTPROV hCryptProv; 
	HCRYPTKEY hKey; 
	HCRYPTHASH hHash; 
		
	PBYTE pbBuffer; 
	DWORD dwBlockLen; 
	DWORD dwBufferLen; 
	DWORD dwCount; 	
	
	// 打开源文件
	if(hSource = fopen(szSource,"rb"))
	{
		printf("The source plaintext/cryptotext file, %s, is open. \n", szSource);	
	}
	else
	{ 
		HandleError("Error opening source plaintext file!");
	} 
	
	//打开目的文件
	if(hDestination = fopen(szDestination,"wb"))
	{
		printf("Destination file %s is open. \n", szDestination);
	}
	else
	{
		HandleError("Error opening destination ciphertext file!"); 
	}

	//以下获得一个CSP句柄
	if(CryptAcquireContext(
				&hCryptProv, 
				NULL,				//NULL表示使用默认密钥容器，默认密钥容器名为用户登陆名
				NULL, 
				PROV_RSA_FULL, 
				0))
	{
		printf("A cryptographic provider has been acquired. \n");
	}
	else
	{   //创建密钥容器
		if(CryptAcquireContext(
				&hCryptProv, 
				NULL, 
				NULL, 
				PROV_RSA_FULL, 
				CRYPT_NEWKEYSET))
		{
			//创建密钥容器成功，并得到CSP句柄
			printf("A new key container has been created.\n");
		}
		else
		{
			HandleError("Could not create a new key container.\n");
		}		
	}

	// 创建一个会话密钥（session key）
	// 会话密钥也叫对称密钥，用于对称加密算法。 
	if(CryptCreateHash(
		hCryptProv, 
		CALG_MD5, 
		0, 
		0, 
		&hHash))
    {
        printf("A hash object has been created. \n");
    }
    else
    { 
		HandleError("Error during CryptCreateHash!\n");
    }
	// 用输入的密码产生一个散列
	if(CryptHashData(hHash,(BYTE *)szPassword,strlen(szPassword), 0))
	{
		printf("The password has been added to the hash. \n");
	}
	else
	{
		HandleError("Error during CryptHashData. \n"); 
	}
	// 通过散列生成会话密钥 
	if(CryptDeriveKey(hCryptProv,ENCRYPT_ALGORITHM, hHash, KEYLENGTH,&hKey))
	{
		printf("An encryption key is derived from the password hash. \n"); 
	}
	else
	{
		HandleError("Error during CryptDeriveKey!\n"); 
	}
	
	//删除散列表	
	CryptDestroyHash(hHash); 
	hHash = NULL; 	
	
	// 因为加密算法是按ENCRYPT_BLOCK_SIZE 大小的块加密的，所以被加密的
	// 数据长度必须是ENCRYPT_BLOCK_SIZE 的整数倍。下面计算一次加密的
	// 数据长度。
	dwBlockLen = 1000 - 1000 % ENCRYPT_BLOCK_SIZE; 	
	
	//如果使用块编码，则需要额外空间 	
	if(ENCRYPT_BLOCK_SIZE > 1) 
		dwBufferLen = dwBlockLen + ENCRYPT_BLOCK_SIZE; 
	else 
		dwBufferLen = dwBlockLen; 	
	
	// 分配内存 
	if(pbBuffer = (BYTE *)malloc(dwBufferLen))
	{
		printf("Memory has been allocated for the buffer. \n");
	}
	else
	{ 
		HandleError("Out of memory. \n"); 
	}
	
	//加密源文件，并将数据写入目标文件
	do 
	{ 		
		// 从源文件中读出dwBlockLen个字节 
		dwCount = fread(pbBuffer, 1, dwBlockLen, hSource); 
		if(ferror(hSource))
		{ 
			HandleError("Error reading plaintext!\n");
		}		
		
		// 加密数据
		if(!CryptEncrypt(
					hKey,			//密钥
					0,				//如果数据同时进行散列和加密，这里传入一个散列对象
					feof(hSource),	//如果是最后一个被加密的块，输入TRUE.如果不是输.
									//入FALSE这里通过判断是否到文件尾来决定是否为最后一块。
					0,				//保留
					pbBuffer,		//输入被加密数据，输出加密后的数据
					&dwCount,		//输入被加密数据实际长度，输出加密后数据长度
					dwBufferLen))	//pbBuffer的大小。
		{ 
			HandleError("Error during CryptEncrypt. \n"); 
		} 			
		
		// 将加密过的数据写入目标文件 		
		fwrite(pbBuffer, 1, dwCount, hDestination); 
		if(ferror(hDestination))
		{ 
			HandleError("Error writing ciphertext.");
		}		
	}while(!feof(hSource)); 

    //关闭文件、释放内存	
	if(hSource) 
		fclose(hSource); 
	if(hDestination) 
		fclose(hDestination); 	
	
	if(pbBuffer) 
		free(pbBuffer);	
	
	if(hKey) 
		CryptDestroyKey(hKey); 	
	
	if(hHash) 
		CryptDestroyHash(hHash); 	
	
	if(hCryptProv) 
		CryptReleaseContext(hCryptProv, 0);
	return(TRUE); 	
} 

//异常处理方法
void HandleError(char *s)
{
    fprintf(stderr,"An error occurred in running the program. \n");
    fprintf(stderr,"%s\n",s);
    fprintf(stderr, "Error number %x.\n", GetLastError());
    fprintf(stderr, "Program terminating. \n");
    exit(1);
} 