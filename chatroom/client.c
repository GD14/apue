#include "rong.h"
#include <poll.h>
#include <arpa/inet.h>
#include <sys/socket.h>
typedef struct sockaddr SA;
#define SERV_PORT 	9999 
#define MAXFD 		100	


#define CLEAR_LINE() printf("\033[K")

int main(int argc,char *argv[]){

	int n;
	int clientfd;	

	struct sockaddr_in servaddr;

	if(argc!=2){
		err_sys("usage:client ip\n");	
	}
	clientfd=socket(AF_INET,SOCK_STREAM,0);

	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(SERV_PORT);;
	if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr)<0)
		err_sys("inet_pton error %s\n",argv[1]);

	if(connect(clientfd,(SA*)&servaddr,sizeof(servaddr))<0)
		err_sys("connect error\n");

	struct pollfd pfd[MAXFD];

	pfd[0].fd=STDIN_FILENO;
	pfd[0].events=POLLIN;

	pfd[1].fd=clientfd;
	pfd[1].events=POLLIN;

	char buf[MAXLINE];
	int maxi=2;
	for(;;){
		if(poll(pfd,maxi+1,-1)<0)	
			err_sys("poll error\n");
	 	if(pfd[0].revents&POLLIN){
			if((n=read(STDIN_FILENO,buf,MAXLINE))<0){
				err_sys("read error\n");	
			}else if(n==0){
				close(clientfd);	
				break;
			}			
			if((n=write(clientfd,buf,n))<0){
				err_sys("write error\n");
			}
		}

		if(pfd[1].revents&POLLIN){
			if((n=read(pfd[1].fd,buf,MAXLINE))<0){
				err_sys("read server error\n");	
			}else if(n==0){
				printf("server closed\n");
				break;		
			}	
			CLEAR_LINE();	
			if((n=write(STDIN_FILENO,buf,n))<0){
				err_sys("write error\n");
			}
		}
			printf("YOU:\n");
	}
	return 0;
}
