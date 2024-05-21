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

int main(void) 
{
    int test_fd[6][2];

    test_fd[3][0] = 4;
    printf("%d\n", test_fd[3][1]);
    return 0;
}
