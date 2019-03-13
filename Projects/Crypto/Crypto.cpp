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
	printf("Enter the name of the file to be encrypted: ");//����Ҫ���ܵ�Դ�ļ���
	scanf("%s",szSource);
	printf("Enter the name of the output file: ");//���ܺ��ļ������ŵ�ַ
	scanf("%s",szDestination);
	printf("Enter the password:");//��������
	scanf("%s",szPassword);
	
	//���ü��ܷ���
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

//���ܷ���
static bool EncryptFile(PCHAR szSource,PCHAR szDestination,PCHAR szPassword)						
{ 		
	//�����ͳ�ʼ���ֲ����� 
	FILE *hSource; 
	FILE *hDestination; 
	
	HCRYPTPROV hCryptProv; 
	HCRYPTKEY hKey; 
	HCRYPTHASH hHash; 
		
	PBYTE pbBuffer; 
	DWORD dwBlockLen; 
	DWORD dwBufferLen; 
	DWORD dwCount; 	
	
	// ��Դ�ļ�
	if(hSource = fopen(szSource,"rb"))
	{
		printf("The source plaintext/cryptotext file, %s, is open. \n", szSource);	
	}
	else
	{ 
		HandleError("Error opening source plaintext file!");
	} 
	
	//��Ŀ���ļ�
	if(hDestination = fopen(szDestination,"wb"))
	{
		printf("Destination file %s is open. \n", szDestination);
	}
	else
	{
		HandleError("Error opening destination ciphertext file!"); 
	}

	//���»��һ��CSP���
	if(CryptAcquireContext(
				&hCryptProv, 
				NULL,				//NULL��ʾʹ��Ĭ����Կ������Ĭ����Կ������Ϊ�û���½��
				NULL, 
				PROV_RSA_FULL, 
				0))
	{
		printf("A cryptographic provider has been acquired. \n");
	}
	else
	{   //������Կ����
		if(CryptAcquireContext(
				&hCryptProv, 
				NULL, 
				NULL, 
				PROV_RSA_FULL, 
				CRYPT_NEWKEYSET))
		{
			//������Կ�����ɹ������õ�CSP���
			printf("A new key container has been created.\n");
		}
		else
		{
			HandleError("Could not create a new key container.\n");
		}		
	}

	// ����һ���Ự��Կ��session key��
	// �Ự��ԿҲ�жԳ���Կ�����ڶԳƼ����㷨�� 
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
	// ��������������һ��ɢ��
	if(CryptHashData(hHash,(BYTE *)szPassword,strlen(szPassword), 0))
	{
		printf("The password has been added to the hash. \n");
	}
	else
	{
		HandleError("Error during CryptHashData. \n"); 
	}
	// ͨ��ɢ�����ɻỰ��Կ 
	if(CryptDeriveKey(hCryptProv,ENCRYPT_ALGORITHM, hHash, KEYLENGTH,&hKey))
	{
		printf("An encryption key is derived from the password hash. \n"); 
	}
	else
	{
		HandleError("Error during CryptDeriveKey!\n"); 
	}
	
	//ɾ��ɢ�б�	
	CryptDestroyHash(hHash); 
	hHash = NULL; 	
	
	// ��Ϊ�����㷨�ǰ�ENCRYPT_BLOCK_SIZE ��С�Ŀ���ܵģ����Ա����ܵ�
	// ���ݳ��ȱ�����ENCRYPT_BLOCK_SIZE �����������������һ�μ��ܵ�
	// ���ݳ��ȡ�
	dwBlockLen = 1000 - 1000 % ENCRYPT_BLOCK_SIZE; 	
	
	//���ʹ�ÿ���룬����Ҫ����ռ� 	
	if(ENCRYPT_BLOCK_SIZE > 1) 
		dwBufferLen = dwBlockLen + ENCRYPT_BLOCK_SIZE; 
	else 
		dwBufferLen = dwBlockLen; 	
	
	// �����ڴ� 
	if(pbBuffer = (BYTE *)malloc(dwBufferLen))
	{
		printf("Memory has been allocated for the buffer. \n");
	}
	else
	{ 
		HandleError("Out of memory. \n"); 
	}
	
	//����Դ�ļ�����������д��Ŀ���ļ�
	do 
	{ 		
		// ��Դ�ļ��ж���dwBlockLen���ֽ� 
		dwCount = fread(pbBuffer, 1, dwBlockLen, hSource); 
		if(ferror(hSource))
		{ 
			HandleError("Error reading plaintext!\n");
		}		
		
		// ��������
		if(!CryptEncrypt(
					hKey,			//��Կ
					0,				//�������ͬʱ����ɢ�кͼ��ܣ����ﴫ��һ��ɢ�ж���
					feof(hSource),	//��������һ�������ܵĿ飬����TRUE.���������.
									//��FALSE����ͨ���ж��Ƿ��ļ�β�������Ƿ�Ϊ���һ�顣
					0,				//����
					pbBuffer,		//���뱻�������ݣ�������ܺ������
					&dwCount,		//���뱻��������ʵ�ʳ��ȣ�������ܺ����ݳ���
					dwBufferLen))	//pbBuffer�Ĵ�С��
		{ 
			HandleError("Error during CryptEncrypt. \n"); 
		} 			
		
		// �����ܹ�������д��Ŀ���ļ� 		
		fwrite(pbBuffer, 1, dwCount, hDestination); 
		if(ferror(hDestination))
		{ 
			HandleError("Error writing ciphertext.");
		}		
	}while(!feof(hSource)); 

    //�ر��ļ����ͷ��ڴ�	
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

//�쳣������
void HandleError(char *s)
{
    fprintf(stderr,"An error occurred in running the program. \n");
    fprintf(stderr,"%s\n",s);
    fprintf(stderr, "Error number %x.\n", GetLastError());
    fprintf(stderr, "Program terminating. \n");
    exit(1);
} 