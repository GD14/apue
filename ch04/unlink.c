#include "rong.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>

int main(){
	if(open("tempfile",O_RDWR)<0)
		err_sys("open error");
	
	if(unlink("tempfile")<0){
		char *ptr=strerror(errno);	
		printf("reason:%s\n",ptr);
		err_sys("unlink error\n");
	}

	printf("file unlinked\n");
	
	sleep(15);

	printf("done\n");

	exit(0);
}
