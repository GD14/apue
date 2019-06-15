#include "rong.h"

static pit_t *childpid=NULL;


static int maxfd;


FILE * popen(const char *cmdstring,
			const char*type){
	int i;
	int pfd[2];
	pid_t pid;
	FILE *fp;

	if((type[0]!='r'&&type[0]!='w')||type[1]!=0){
		errno=EINVAL;	
		return NULL;
	}

	if(childpid==NULL){
		maxfd=open_max();
		if((childpid = calloc(maxfd,sizeof(pid)))==NULL)
			return NULL;
	}

	if (pipe(pfd)<0)
		return NULL;

}

int main(){


	return 0;
}
