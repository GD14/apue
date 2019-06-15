#include"rong.h"

int main(){
	char buf[MAXLINE];
	char *ptr;
	if((ptr=getcwd(buf,MAXLINE))!=NULL)
		printf("%s\n",ptr);
	return 0;
}
