#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

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
	char	**arg;
	char	**arg_cmd; // cmd + option + arg
	struct s_commands	*next;
	int		*pipefd0;
	int		*pipefd1;
	bool	err_is_infile;
	bool	err_is_outfile;
	bool	bf_cmd;
	int		exit_code;
	char	*msg_error;
}	t_commands;

typedef struct s_minishell
{
	t_commands	*p_cmd;
	int			pipe_nbr;
	char		**export;
	char		**env;
	char		**path_env;
	int			open_quote;
	int			open_dquote;
	int			**pipefds;
	int			exit_code;
}	t_minishell;

#include "parsing.h"


#endif
