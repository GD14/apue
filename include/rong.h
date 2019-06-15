#ifndef RONG_H_
#define RONG_H_

#define MAXLINE 4096
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void err_ret(const char* format,...);

void err_sys(const char* format,...);

#endif

