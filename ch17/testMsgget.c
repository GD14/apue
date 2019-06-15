#include<stdio.h>
#include<unistd.h>
#include<sys/msg.h>
#include<sys/ipc.h>

int main(){
	key_t key=123456;
	int mid=msgget(key,IPC_CREAT|0666);
	printf("%d",mid);
	return 0;
}
