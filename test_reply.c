#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "menu.h"

#define FONTSIZE 10
int PrintMenuOS()
{
    int i, j;
    char data_M[FONTSIZE][FONTSIZE] =
    {
        "          ",
        "  *    *  ",
        " ***  *** ",
        " * *  * * ",
        " * *  * * ",
        " *  **  * ",
        " *      * ",
        " *      * ",
        " *      * ",
        "          "
    };
    char data_e[FONTSIZE][FONTSIZE] =
    {
        "          ",
        "          ",
        "    **    ",
        "   *  *   ",
        "  *    *  ",
        "  ******  ",
        "  *       ",
        "   *      ",
        "    ***   ",
        "          "
    };
    char data_n[FONTSIZE][FONTSIZE] =
    {
        "          ",
        "          ",
        "    **    ",
        "   *  *   ",
        "  *    *  ",
        "  *    *  ",
        "  *    *  ",
        "  *    *  ",
        "  *    *  ",
        "          "
    };
    char data_u[FONTSIZE][FONTSIZE] =
    {
        "          ",
        "          ",
        "  *    *  ",
        "  *    *  ",
        "  *    *  ",
        "  *    *  ",
        "  *    *  ",
        "   *  **  ",
        "    **  * ",
        "          "
    };
    char data_O[FONTSIZE][FONTSIZE] =
    {
        "          ",
        "   ****   ",
        "  *    *  ",
        " *      * ",
        " *      * ",
        " *      * ",
        " *      * ",
        "  *    *  ",
        "   ****   ",
        "          "
    };
    char data_S[FONTSIZE][FONTSIZE] =
    {
        "          ",
        "    ****  ",
        "   **     ",
        "  **      ",
        "   ***    ",
        "     **   ",
        "      **  ",
        "     **   ",
        "  ****    ",
        "          "
    };

    for(i=0; i<FONTSIZE; i++)
    {
        for(j=0; j<FONTSIZE; j++)
        {
            printf("%c", data_M[i][j]);
        }
        for(j=0; j<FONTSIZE; j++)
        {
            printf("%c", data_e[i][j]);
        }
        for(j=0; j<FONTSIZE; j++)
        {
            printf("%c", data_n[i][j]);
        }
        for(j=0; j<FONTSIZE; j++)
        {
            printf("%c", data_u[i][j]);
        }
        for(j=0; j<FONTSIZE; j++)
        {
            printf("%c", data_O[i][j]);
        }
        for(j=0; j<FONTSIZE; j++)
        {
            printf("%c", data_S[i][j]);
        }
        printf("\n");
    }
    return 0;
}

int Quit(int argc, char *argv[])
{
    /* add XXX clean ops */
}

int Time(int argc, char *argv[])
{
    time_t tt;
    struct tm *t;
    tt = time(NULL);
    t = localtime(&tt);
    printf("time:%d:%d:%d:%d:%d:%d\n",t->tm_year+1900, t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
    return 0;
}

int TimeAsm(int argc, char *argv[])
{
    time_t tt;
    struct tm *t;
    asm volatile(
        "mov $0,%%ebx\n\t"
        "mov $0xd,%%eax\n\t" 
        "int $0x80\n\t" 
        "mov %%eax,%0\n\t"  
        : "=m" (tt) 
    );
    t = localtime(&tt);
    printf("time:%d:%d:%d:%d:%d:%d\n",t->tm_year+1900, t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
    return 0;
}

#include<stdio.h> 
#include<arpa/inet.h> /* internet socket */
#include<string.h>
//#define NDEBUG
#include<assert.h>

#define PORT                5001
#define IP_ADDR             "127.0.0.1"
#define MAX_BUF_LEN         1024
#define MAX_CONNECT_QUEUE   1024
int Replyhi()
{
        char szBuf[MAX_BUF_LEN] = "\0";
        char szReplyMsg[MAX_BUF_LEN] = "hi\0";
        int sockfd = -1;
        struct sockaddr_in serveraddr;
        struct sockaddr_in clientaddr;
        socklen_t addr_len = sizeof(struct sockaddr);
        serveraddr.sin_family = AF_INET;
        serveraddr.sin_port = htons(PORT);
        serveraddr.sin_addr.s_addr = inet_addr(IP_ADDR);
        memset(&serveraddr.sin_zero, 0, 8);
        sockfd = socket(PF_INET,SOCK_STREAM,0);
        int ret = bind( sockfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr)); 
        if(ret == -1)
        {
            fprintf(stderr,"Bind Error,%s:%d\n", __FILE__,__LINE__);
            close(sockfd);
            return -1; 
        }
        listen(sockfd,MAX_CONNECT_QUEUE); 

    while(1)
    {
        int newfd = accept( sockfd, (struct sockaddr *)&clientaddr, &addr_len);
        if(newfd == -1) 
        { 
            fprintf(stderr,"Accept Error,%s:%d\n", __FILE__,__LINE__); 
        } 
        ret = recv(newfd,szBuf,MAX_BUF_LEN,0); 
        if(ret > 0)
        {
            printf("recv \"%s\" from %s:%d\n", szBuf, (char*)inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));                \
        }
        ret = send(newfd,szReplyMsg,strlen(szReplyMsg),0);
        if(ret > 0) 
        { 
            printf("rely \"hi\" to %s:%d\n", (char*)inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));                \
        }
        close(newfd);
    }
    close(sockfd);
    return 0;
}

int StartReplyhi(int argc, char *argv[])
{
	int pid;
	/* fork another process */
	pid = fork();
	if (pid < 0)
	{
		/* error occurred */
		fprintf(stderr, "Fork Failed!");
		exit(-1);
	}
	else if (pid == 0)
	{
		/*	 child process 	*/
		Replyhi();
		printf("Reply hi TCP Service Started!\n");
	}
	else
	{
		/* 	parent process	 */
		printf("Please input hello...\n");
	}
}

int Hello(int argc, char *argv[])
{
        char szBuf[MAX_BUF_LEN] = "\0";
        char szMsg[MAX_BUF_LEN] = "hello\0";
        int sockfd = -1;
        struct sockaddr_in serveraddr;
        struct sockaddr_in clientaddr;
        socklen_t addr_len = sizeof(struct sockaddr);
        serveraddr.sin_family = AF_INET;
        serveraddr.sin_port = htons(PORT);
        serveraddr.sin_addr.s_addr = inet_addr(IP_ADDR);
        memset(&serveraddr.sin_zero, 0, 8);
        sockfd = socket(PF_INET,SOCK_STREAM,0);
        int ret = connect(sockfd,  (struct sockaddr *)&serveraddr,  sizeof(struct sockaddr));
        if(ret == -1) 
        {  
            fprintf(stderr,"Connect Error,%s:%d\n",  __FILE__,__LINE__);
            return -1; 
        }
        ret = send(sockfd,szMsg,strlen(szMsg),0);
        if(ret > 0) 
        { 
            printf("send \"hello\" to %s:%d\n", (char*)inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));                \
        }
        ret = recv(sockfd,szBuf,MAX_BUF_LEN,0); 
        if(ret > 0)
        {
            printf("recv \"%s\" from %s:%d\n", szBuf, (char*)inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));                \
        }

	close(sockfd); 
	return 0;
}

int main()
{
    PrintMenuOS();
    SetPrompt("MenuOS>>");
    MenuConfig("version","MenuOS V1.0(Based on Linux 3.18.6)",NULL);
    MenuConfig("quit","Quit from MenuOS",Quit);
    MenuConfig("time","Show System Time",Time);
    MenuConfig("time-asm","Show System Time(asm)",TimeAsm);
    MenuConfig("replyhi", "Reply hi TCP Service", StartReplyhi);
    MenuConfig("hello", "Hello TCP Client", Hello);
    ExecuteMenu();
}

