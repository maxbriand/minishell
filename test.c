#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

typedef struct s_commands
{
	bool	b_builtins;
	bool	append_outfile; // 0 - 1 for >> or >
	char	**hd_stop;
	bool	in_pipe;
	char	*infile;// standard input // append everytime
	char	*outfile;// standard output // need to define the last outfile and
	//I open all the outfile and close instant after being create
	char	*cmd;
	char	*option;
	char	*arg;
	char	**arg_cmd; // cmd + option + arg
	struct s_commands	*next;
}	t_commands;

typedef struct s_minishell
{
	t_commands	*p_cmd;
	char		**env;
	char		**path_env;
	// +1 for the boolean ONLY is the other one is 0 / false
	int			open_quote;
	int			open_dquote;
}	t_minishell;

#include "parsing.h"


#endif




static void ft_exit_failuree(const char *msg) 
{
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

