#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <process.h>

#define BUF_SIZE 100
#define MAX_CLNT 256

unsigned WINAPI HandleClnt(void *arg);
void SendMsg(char * msg,int len);
void ErrorHandling(char * msg);

int clntcnt = 0;
SOCKET clntSocks[MAX_CLNT];
HANDLE hMutex;

int main(int argc,char *argv[])
{
	WSADATA wsaData;
	SOCKET hServSock,hClntSock;
	SOCKADDR_IN servAdr,clntAdr;
	int clntAdrSz;
	HANDLE hThread;
	//if(argc =! 2)
	//{
	//	printf("Usage : %s <port> \n",argv[0]);
	//	exit(1);
	//}
	if(WSAStartup(MAKEWORD(2,2),&wsaData) != 0)
		ErrorHandling("WSAStartup() error !\n");
	hMutex = CreateMutex(NULL,FALSE,NULL);
	hServSock = socket(PF_INET,SOCK_STREAM,0);
	memset(&servAdr,0,sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(9190);

	if(bind(hServSock,(SOCKADDR*)&servAdr,sizeof(servAdr)) == SOCKET_ERROR)
		ErrorHandling("bind() error");
	if(listen(hServSock,5) == SOCKET_ERROR)
		ErrorHandling("listen() error");

	while(1)
	{
		clntAdrSz = sizeof(clntAdr);
		printf("11111111111111111111\n");
		hClntSock = accept(hServSock,(SOCKADDR*)&clntAdr,&clntAdrSz);
		printf("22222222222222222222\n");
		WaitForSingleObject(hMutex,INFINITE);
		clntSocks[clntcnt++] = hClntSock;
		ReleaseMutex(hMutex);

		hThread = (HANDLE)_beginthreadex(NULL,0,HandleClnt,(void *)&hClntSock,0,NULL);
		printf("connectd clint IP : %s \n",inet_ntoa(clntAdr.sin_addr));
	}
	closesocket(hServSock);
	WSACleanup();
	system("pause");
	return 0;
}

unsigned WINAPI HandleClnt(void *arg)
{
	SOCKET hClntSock = *(SOCKET*)arg;
	int strlen = 0,i;
	char msg[BUF_SIZE];

	while((strlen = recv(hClntSock,msg,sizeof(msg),0)) != 0)
		SendMsg(msg,strlen);
	WaitForSingleObject(hMutex,INFINITE);
	for( i = 0;i < clntcnt;i++)
	{
		if(hClntSock == clntSocks[i])
		{
			while(i++<clntcnt-1)
				clntSocks[i] = clntSocks[i + 1];
			break;
		}
	}
	clntcnt--;
	ReleaseMutex(hMutex);
	closesocket(hClntSock);
	return 0;
}
void SendMsg(char *msg,int len)
{
	int i;
	WaitForSingleObject(hMutex,INFINITE);
	for( i = 0; i < clntcnt;i++)
		send(clntSocks[i],msg,len,0);
	ReleaseMutex(hMutex);
}
void ErrorHandling(char *msg)
{
	fputs(msg,stderr);
	fputc('\n',stderr);
	exit(1);
}