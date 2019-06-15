#include"rong.h"
#include<fcntl.h>


#define RWRWRW  0666
int main(){
	umask(0);
	if(creat("foo",RWRWRW)<0)
		err_sys("create error for foo\n");

	umask(S_IRGRP |S_IWGRP|S_IROTH|S_IWOTH);
	
	if(creat("bar",RWRWRW)<0)
		err_sys("create error for bar\n");

	exit(0);
}
