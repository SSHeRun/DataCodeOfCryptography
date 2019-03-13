// Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>

int main(int argc, char* argv[])
{
WORD wVersion;
WSADATA wsaData;
int err;
char message[1024];
wVersion = MAKEWORD(1,1);

//��ʼ��Windows Sockets
err = WSAStartup(wVersion,&wsaData);

if(err != 0){
   return 0;
}

//������ʽ�׽���
SOCKET listenSocket = socket(AF_INET,SOCK_STREAM,0);

sockaddr_in addr;
int nSockErr;
addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
addr.sin_family = AF_INET;
//�趨�����˿�5001
addr.sin_port=htons(5001);

//���׽���
if(bind(listenSocket,(struct sockaddr*)&addr,
   sizeof(addr)) == SOCKET_ERROR)
   nSockErr = WSAGetLastError();

//���׽������óɼ���״̬
if(listen(listenSocket,5) == SOCKET_ERROR)
   nSockErr = WSAGetLastError();
printf("�ȴ��ͻ�������...\n");

//�ȴ��ͻ�����������

SOCKET connectSocket = accept(listenSocket,NULL,NULL);
printf("��������\n");
if(connectSocket == INVALID_SOCKET)
{
   printf("���ܴ���...\n");
   nSockErr = WSAGetLastError();
}
else
{
   //�пͻ��������󱻳ɹ�����
   char buf[1024];
   memset(buf,0,sizeof(char)*1024);
   //���տͻ��˴������������
   int n = recv(connectSocket,buf,1024,MSG_PEEK);
   if(n>0)
   printf("�������յ���Ϣ��%s\n",buf);
   printf("������Ҫ�����ͻ��˵���Ϣ��");
   scanf("%[^\n]",message);
   printf("������Ϣ����\n");
   ::send(connectSocket,message,strlen(message),MSG_DONTROUTE);
}

//�ر��׽���
::closesocket(listenSocket);
::closesocket(connectSocket);
::WSACleanup();
system("pause");
return 1;

}

