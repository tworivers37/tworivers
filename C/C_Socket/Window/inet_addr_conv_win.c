#include<stdio.h>
#include<WinSock2.h>
#include<string.h>

void ErrorHandling(char*message);

void main(){
	WSADATA wsaData;
	
	char *addr="123.123.123.123";
	unsigned long conv_addr;

	struct sockaddr_in sAddr;
	char *strPtr;
	char strArr[20];

	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0) ErrorHandling("WSAStartup error");

	conv_addr=inet_addr(addr);

	if(conv_addr==INADDR_NONE) printf("Error occured \n");
	else printf("Network ordered integer addr : %#lx\n",conv_addr);

	sAddr.sin_addr.s_addr=htonl(0x1020304);
	strPtr=inet_ntoa(sAddr.sin_addr);
	strcpy(strArr,strPtr);
	printf("Dotted-Decimal notation3 %s \n",strArr);

	WSACleanup();
}
void ErrorHandling(char*message){
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}