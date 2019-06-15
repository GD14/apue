#include "rong.h"
#include <fcntl.h>


int main(int argc,char*argv[]){


	if(argc != 2)
		err_sys("usage: access <pathname>");	

	if(access(argv[1],R_OK)<0)
		err_ret("access error %s\n",argv[1]);	
	else printf("read access ok\n");


	if(open(argv[1],O_RDONLY)<0)
		err_sys("open error%s\n",argv[1]);
	else
		printf("open for reading ok\n");
	
	return 0;
}
