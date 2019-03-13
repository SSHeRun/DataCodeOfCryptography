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

//初始化Windows Sockets
err = WSAStartup(wVersion,&wsaData);
if(err != 0){
   return 0;
}

//创建流式套接字
SOCKET connectSocket = ::socket(AF_INET,SOCK_STREAM,0);

sockaddr_in servAddr;
servAddr.sin_family = AF_INET;
//设置服务器端主机的地址和端口号，这里的服务器是本地的
servAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
servAddr.sin_port=htons(5001);
printf("开始连接……\n");
if(connect(connectSocket,(struct sockaddr*)&servAddr,
   sizeof(servAddr)) == SOCKET_ERROR)
   printf("连接错误\n");
else
{
	printf("请输入要发送的消息：");
	scanf("%[^\n]",message);
	printf("发送消息……\n");
   //连接成功，向服务器端发送数据
   ::send(connectSocket,message,strlen(message),MSG_DONTROUTE);
   //接收服务器发回的消息
   char buf[1024];
   memset(buf,0,sizeof(char)*1024);
   int n = recv(connectSocket,buf,1024,MSG_PEEK);
   if(n>0)
   printf("客户端收到信息：%s\n",buf);
}

//关闭套接字
closesocket(connectSocket);
WSACleanup();
system("pause");
return 1;


}
