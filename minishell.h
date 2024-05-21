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
