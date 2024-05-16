#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() 
{
    char *input;

    while (1) 
    {
        input = readline("Enter command: ");
        if (!input) {
            break;
        }
        if (*input) {
            add_history(input);
        }
        pid_t   pid;
        int     pipefd[2];
        pipe(pipefd);
        pid = fork();
        if (pid == 0)
        {
            close(pipefd[0]);
            close(pipefd[1]);
            free(input);
            return (0);
        }
        close(pipefd[0]);
        close(pipefd[1]);
        free(input);
        wait(NULL);
        return (0);
        printf("You entered: %s\n", input);
    }
    return 0;
}
