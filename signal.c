#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// void sigint_handler(int signum) {
//     printf("Signal SIGINT reçu.\n");
//     exit(signum); // Sortir du programme avec le numéro de signal
// }


// int main(void)
// {
// 	struct sigaction sa;


// 	sigemptyset(&sa.sa_mask);
//     sa.sa_flags = 0;
//     sa.sa_handler = sigint_handler;

// 	sigaction(EOF, &sa, NULL);
//     while(1) {}

// 	return(0);
// }

#include <unistd.h>

int main(void)
{
    // char    *pathname = "/bin/ls";
    // char    *argv[] = {"ls", "-la", NULL};

    char    *pathname = "/bin/echo";
    char    *argv[] = {"echo", "indejcnje fjcendjsncjendjscs", NULL};



    execve(pathname, argv, NULL);

    return(0);
}

