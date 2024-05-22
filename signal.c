#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int pipefd[2]; // Array to hold the two ends of the pipe
    pid_t cpid;
    char buf;

    // Create the pipe
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    cpid = fork();
    if (cpid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0)
    {
        printf("in child: the value of pipefd[0] is %d\n", pipefd[0]);
        printf("in child: the value of pipefd[1] is %d\n", pipefd[1]);
        // Child process
        close(pipefd[1]); // Close unused write end

        printf("Child process reading from pipe:\n");
        while (read(pipefd[0], &buf, 1) > 0)
            write(STDOUT_FILENO, &buf, 1);

        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[0]);
        _exit(EXIT_SUCCESS);
    }
    else
    {
        // Parent process
        sleep(5);
        printf("in parent: the value of pipefd[0] is %d\n", pipefd[0]);
        printf("in parent: the value of pipefd[1] is %d\n", pipefd[1]);
        close(pipefd[0]); // Close unused read end
        char message[] = "Hello from parent!";
        write(pipefd[1], message, strlen(message));
        close(pipefd[1]); // Reader will see EOF
        wait(NULL); // Wait for child
        exit(EXIT_SUCCESS);
    }
}

