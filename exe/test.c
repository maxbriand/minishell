#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "minishell.h"

static void ft_exit_failuree(const char *msg) {
    perror(msg);
    // Perform any necessary cleanup
    exit(EXIT_FAILURE);
}

void ft_print_fd_content(int fd) {
    char buffer[1024];
    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0'; // Null-terminate the buffer
        dprintf(STDOUT_FILENO, "%s", buffer); // Print the buffer to stdout
    }

    if (bytes_read == -1) {
        ft_exit_failuree("read");
    }
}

