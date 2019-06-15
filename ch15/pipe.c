#include "rong.h"

int main(){
	int fd[2];
	int pid;
	int n;
	char buf[MAXLINE];

	if(pipe(fd)<0)
		err_sys("pipe error\n");
	if((pid=fork())<0)
		err_sys("fork error\n");
	else if(pid==0){
		close(fd[0]);
		write(fd[1],"hello world\n",12);
	}else{
		close(fd[1]);
		n=read(fd[0],buf,MAXLINE);
		write(STDOUT_FILENO,buf,n);	
	}
	return 0;
}
