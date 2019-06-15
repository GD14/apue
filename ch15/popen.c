#include"rong.h"
#include<stdio.h>
#define PAGER "${PAGER:-more}"

int main(int argc,char*argv[]){

	char line[MAXLINE];

	FILE *fpin,*fpout;

	if(argc!=2)
		err_sys("usage: a.out <pathmant>");

	if((fpin=fopen(argv[1],"r"))==NULL)
		err_sys("fopen error");

	if((fpout=popen(PAGER,"w"))==NULL)
		err_sys("fopen error");

	while(fgets(line,MAXLINE,fpin)!=NULL){
		if(fputs(line,fpout)==EOF)	
			err_sys("fput error");
	}

	if(ferror(fpin))
		err_sys("fgets error");

	if(pclose(fpout)==-1)
		err_sys("pclose error");
	exit(0);
}
