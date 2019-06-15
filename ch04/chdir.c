#include "rong.h"


int main(){
	if(chdir("/tmp")<0)
		err_sys("chdir failed\n");
	printf("chdir to /tmp successed\n");
	exit(0);
}
