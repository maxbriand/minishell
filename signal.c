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


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main() 
{
    char cwd[1024];

    // Get and print the current working directory
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working directory: %s\n", cwd);
    } else {
        perror("getcwd error");
        return 1;
    }

    // Change the working directory
    const char *new_directory = "/nfs/homes/mbriand/minishell/builtins"; // Replace with a valid directory path
    if (chdir(new_directory) != 0) {
        perror("chdir error");
        return 1;
    }

    // Get and print the new current working directory
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("New working directory: %s\n", cwd);
    } else {
        perror("getcwd error");
        return 1;
    }

    return 0;
}
