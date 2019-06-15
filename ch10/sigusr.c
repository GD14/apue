#include "rong.h"
#include <sys/signal.h>
static void sig_usr(int);

int main()
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR)
        err_sys("can't catch SIGUSR1");


    if (signal(SIGUSR2,sig_usr)==SIG_ERR)
        err_sys("can't catch SIGUSR2");
    
    for(;;)
        pause();
}

static void sig_usr(int signo){
    if(signo== SIGUSR1)
        printf("receive SIGUSR1\n");
    else
    if(signo==SIGUSR2)
        printf("receive SIGUSR2\n");
    else 
        err_sys("received signal %d\n",signo);
}