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

int main() {
    char *currentDir;
    size_t size = 50; // Specify the size of the buffer.

    // Allocate memory for the buffer.
    currentDir = malloc(size);
    if (currentDir == NULL) {
        perror("Malloc failed");
        exit(EXIT_FAILURE);
    }

    // Get the current working directory.
    if (getcwd(currentDir, size) == NULL) 
    {
        perror("getcwd failed");
        free(currentDir);
        exit(EXIT_FAILURE);
    }

    // Print the current directory.
    printf("Current working directory: %s\n", currentDir);

    // Free the allocated memory.
    free(currentDir);

    return 0;
}


