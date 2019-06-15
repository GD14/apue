#include"rong.h"
#include<poll.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<errno.h>
#define MAXFD 	  1000
#define SERV_PORT 11022
#define LISTENQ	  500 

typedef struct sockaddr SA;

int main(){
	//listen socket fd
	int i,n;
	int listenfd,clientfd;
	socklen_t client_len;
	//poll fd array
	struct sockaddr_in listenSock;	

	struct sockaddr_in clientSock;	
	client_len=sizeof(clientSock);

	memset(&listenSock,0,sizeof(listenSock));

	listenfd=socket(AF_INET,SOCK_STREAM,0);
	listenSock.sin_family=AF_INET;
	listenSock.sin_addr.s_addr=htonl(INADDR_ANY);
	listenSock.sin_port=htons(SERV_PORT);

	if(bind(listenfd,(SA*)&listenSock,sizeof(listenSock))<0)
		err_sys("bind error\n");

	if(listen(listenfd,LISTENQ)<0)
		err_sys("listen error\n");



	int nready;
	char buf[MAXLINE];
	struct pollfd pfd[MAXFD];


	pfd[0].fd=listenfd;
	pfd[0].events=POLLIN;
	for(i=1;i<MAXFD;++i)
		pfd[i].fd=-1;
	int sockfd;
	int maxi=0;
	for(;;){
		if((nready=poll(pfd,maxi+1,-1))<0)
			err_sys("poll error\n");
		if(pfd[0].revents&POLLIN){
			clientfd=accept(listenfd,(SA*)&clientSock,&client_len);	
			for(i=1;i<MAXFD;++i)
				if(pfd[i].fd<0){
					pfd[i].fd=clientfd;	
					break;
				}
			if(i==MAXFD)
				err_sys("too many fd\n");	

			if(i>maxi) maxi=i;

			pfd[i].events=POLLIN;
			printf("new client[%d]\n",i);
			if(--nready<=0)
				continue;
		}
		for(i=1;i<=maxi;++i){
			if((sockfd=pfd[i].fd)==-1)
				continue;

			if(pfd[i].revents&POLLIN){
				if((n=read(sockfd,buf,MAXLINE))<0){
					if(errno==ECONNRESET){
						printf("client[%d] abort connect\n",i);	
						close(sockfd);
					}else
						err_sys("read error");
				}else if(n==0){
						printf("client[%d] close connect\n",i);	
						close(sockfd);
				}else {
					for(int j=1;j<=maxi;++j)
						if(j!=i&&(pfd[j].fd>0)){
							n=write(pfd[j].fd,buf,n);		
							buf[n]=0;
							printf("client[%d]:%s\n",i,buf);
						}
				}	
				if(--nready<=0)
					break;
			}
		}
	}
}
