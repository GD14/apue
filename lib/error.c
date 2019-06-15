#include"rong.h"
#include<stdarg.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


void err_sys(const char* format,...){
	char buffer[MAXLINE];
	va_list ap;
	va_start(ap,format);
	vsnprintf(buffer,MAXLINE,format,ap);	
	fflush(stdout);
	fputs(buffer,stderr);
	fflush(stderr);
	va_end(ap);
	exit(1);
}


void err_ret(const char *format,...){
	char buf[MAXLINE];
	va_list ap;
	va_start(ap,format);
	vsnprintf(buf,MAXLINE,format,ap);	
	fflush(stdout);
	fputs(buf,stderr);
	fflush(stderr);
	va_end(ap);
}

