#include"rong.h"
#include<string.h>
#include<stdio.h>
#include<signal.h>
static void sig_pipe(int);
//kill the child process,will turn the kill child to defunct status
//because parent procees no set SIGCHID to waitpid
int main(){
	int n,fd1[2],fd2[2];
	char line[MAXLINE];

	if(signal(SIGPIPE,sig_pipe)==SIG_ERR)
		err_sys("signale eror\n");
	pid_t pid;
	if(pipe(fd1)<0||pipe(fd2)<0)
		err_sys("pipe error\n");
	
	if((pid=fork())<0){
		err_sys("fork error\n");	
	}else if(pid>0){
		close(fd1[0]);	
		close(fd2[1]);
		while(fgets(line,MAXLINE,stdin)!=NULL){
			n=strlen(line);
			if(write(fd1[1],line,n)!=n){
				err_sys("write error\n");
			}
			if((n=read(fd2[0],line,MAXLINE))<0)
				err_sys("read error\n");
			if(n==0){
				err_ret("child closed pipe\n");	
				break;
			}

			line[n]=0;
			if(fputs(line,stdout)==EOF)
				err_sys("fputs error");
		}

		if(ferror(stdin))
			err_sys("fgets error on stdin");
		exit(0);
	}else{
		close(fd1[1]);
		close(fd2[0]);
		if(fd1[0]!=STDIN_FILENO){
			if(dup2(fd1[0],STDIN_FILENO)<0)
				err_sys("dup2 error\n");
			close(fd1[0]);
		}
		if(fd2[1]!=STDOUT_FILENO){
			if(dup2(fd2[1],STDOUT_FILENO)<0)
				err_sys("dup2 error\n");
			close(fd2[1]);
		}
		if(execl("./add2.sh","add2.sh",(char*)0)<0)
			err_sys("execl error\n");
	}

	return 0;
}

static void sig_pipe(int signo){
	printf("cought SIGPIPE\n");
	exit(1);
}
