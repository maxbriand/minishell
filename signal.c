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

int main() {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    char stop_word[] = "STOP\n";  // Define the stop word or sequence

    printf("Enter text (type 'STOP' to finish):\n");

    while ((bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[bytes_read] = '\0';  // Null-terminate the string
        if (strcmp(buffer, stop_word) == 0) {
            break;  // Stop reading if stop word is entered
        }
        printf("Received: %s", buffer);
    }

    return 0;
}
