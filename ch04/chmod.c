#include "rong.h"
#include <sys/stat.h>
#include <fcntl.h>

int main(){

	struct stat	statbuf;
	
	if(stat("foo",&statbuf)<0)
		err_sys("stat error for foo\n");

	if(chmod("foo",(statbuf.st_mode&~S_IXGRP)|S_ISGID)<0)
		err_sys("chmod error for foo\n");
	
	if(chmod("bar",S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)<0)
		err_sys("chmod error for foo\n");

	exit(0);
}
