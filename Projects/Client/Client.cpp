// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>

int main(int argc, char* argv[])
{
WORD wVersion;
WSADATA wsaData;
char message[1024];
int err;
wVersion = MAKEWORD(1,1);

//��ʼ��Windows Sockets
err = WSAStartup(wVersion,&wsaData);
if(err != 0){
   return 0;
}

//������ʽ�׽���
SOCKET connectSocket = ::socket(AF_INET,SOCK_STREAM,0);

sockaddr_in servAddr;
servAddr.sin_family = AF_INET;
//���÷������������ĵ�ַ�Ͷ˿ںţ�����ķ������Ǳ��ص�
servAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
servAddr.sin_port=htons(5001);
printf("��ʼ���ӡ���\n");
if(connect(connectSocket,(struct sockaddr*)&servAddr,
   sizeof(servAddr)) == SOCKET_ERROR)
   printf("���Ӵ���\n");
else
{
	printf("������Ҫ���͵���Ϣ��");
	scanf("%[^\n]",message);
	printf("������Ϣ����\n");
   //���ӳɹ�����������˷�������
   ::send(connectSocket,message,strlen(message),MSG_DONTROUTE);
   //���շ��������ص���Ϣ
   char buf[1024];
   memset(buf,0,sizeof(char)*1024);
   int n = recv(connectSocket,buf,1024,MSG_PEEK);
   if(n>0)
   printf("�ͻ����յ���Ϣ��%s\n",buf);
}

//�ر��׽���
closesocket(connectSocket);
WSACleanup();
system("pause");
return 1;


}
