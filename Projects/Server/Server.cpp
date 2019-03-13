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

//初始化Windows Sockets
err = WSAStartup(wVersion,&wsaData);

if(err != 0){
   return 0;
}

//建立流式套接字
SOCKET listenSocket = socket(AF_INET,SOCK_STREAM,0);

sockaddr_in addr;
int nSockErr;
addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
addr.sin_family = AF_INET;
//设定监听端口5001
addr.sin_port=htons(5001);

//绑定套接字
if(bind(listenSocket,(struct sockaddr*)&addr,
   sizeof(addr)) == SOCKET_ERROR)
   nSockErr = WSAGetLastError();

//将套接字设置成监听状态
if(listen(listenSocket,5) == SOCKET_ERROR)
   nSockErr = WSAGetLastError();
printf("等待客户端连接...\n");

//等待客户的链接请求

SOCKET connectSocket = accept(listenSocket,NULL,NULL);
printf("建立连接\n");
if(connectSocket == INVALID_SOCKET)
{
   printf("接受错误...\n");
   nSockErr = WSAGetLastError();
}
else
{
   //有客户链接请求被成功接收
   char buf[1024];
   memset(buf,0,sizeof(char)*1024);
   //接收客户端传输过来的数据
   int n = recv(connectSocket,buf,1024,MSG_PEEK);
   if(n>0)
   printf("服务器收到信息：%s\n",buf);
   printf("请输入要发给客户端的消息：");
   scanf("%[^\n]",message);
   printf("发送消息……\n");
   ::send(connectSocket,message,strlen(message),MSG_DONTROUTE);
}

//关闭套接字
::closesocket(listenSocket);
::closesocket(connectSocket);
::WSACleanup();
system("pause");
return 1;

}

