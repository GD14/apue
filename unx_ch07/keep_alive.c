#include "rong.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <errno.h>

typedef struct sockaddr SA; 

#define PORT 9999
#define LISTENQ 50
#define MAX_EVENTS 50
int main(){
    int sockfd;
    char buf[MAXLINE];


    //create tcp socket
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        err_sys("socket error\n");
    }
    //set the sockaddr
    struct sockaddr_in servaddr;
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(PORT);

    socklen_t sock_len;
    sock_len=sizeof(servaddr);

    //bind the socket addr
    if(bind(sockfd,(SA*)&servaddr,sock_len)<0)
        err_sys("bind error\n");


    if(listen(sockfd,LISTENQ)<0)
        err_sys("listen\n");


    int epollfd,n,nfds,clientfd;
    struct epoll_event ev,events[MAX_EVENTS];
    struct sockaddr_in clientaddr;
    socklen_t client_len;
	

    //create a epoll instance
    epollfd=epoll_create1(0);
    if(epollfd<0)
        err_sys("epoll_create\n");

    ev.events=EPOLLIN;
    ev.data.fd=sockfd;
    if(epoll_ctl(epollfd,EPOLL_CTL_ADD,sockfd,&ev)==-1){
        err_sys("epoll_ctl:sockfd");
    }

    for(;;){
        nfds=epoll_wait(epollfd,events,MAX_EVENTS,-1);
        if(nfds==-1)
            err_sys("epoll_wait\n");
        
        for(int i=0;i<nfds;++i)
            if(events[i].data.fd==sockfd){
                clientfd=accept(sockfd,(SA*)&clientaddr,&client_len);
                if(clientfd==-1)
                    err_sys("accept\n");
                ev.events=EPOLLIN;
                ev.data.fd=clientfd;
                if(epoll_ctl(epollfd,EPOLL_CTL_ADD,clientfd,&ev)==-1)
                    err_sys("epoll_ctl:clientfd");
            }else{
                if((n=read(events[i].data.fd,buf,MAXLINE))<0){
                    if(errno==ETIMEDOUT)
                        printf("time out\n");
                }else if(n==0){
                    printf("close\n");
                }else{
                    printf("%s\n",buf);
                }                
            }
    }
    
    return 0;
}
