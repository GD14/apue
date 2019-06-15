#include	"rong.h"

#include 	<fcntl.h>

int main(int argc,char *argv[]){

	int val;
	if(argc!=2)
		err_sys("usage: fcntl <fd>");
	
	
	if((val=fcntl(atoi(argv[1]),F_GETFL,0))<0)
		err_sys("usage: fcntl <fd>");


	switch(val & O_ACCMODE){
		case O_RDONLY:
			printf("read only");
		break;
		case O_WRONLY:
			printf("wite only");
		break;
		case O_RDWR:
			printf("read write");
		break;
	}

	if(val & O_APPEND)
		printf(", append");
	if(val & O_NONBLOCK)
		printf(", nonblocking");
	if(val & O_SYNC)
		printf(", synchronous writes");
	exit(0);
}
