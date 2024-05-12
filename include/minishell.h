
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

typedef struct s_commands
{
	bool	b_builtins;
	bool	append_output; // 0 - 1 for >> or >
	bool	heredoc;
	char	*input;// standard input // append everytime
	char	*output;// standard output
	char	*cmd;
	char	*option;
	char	*arg;
	struct s_commands	*next;
}	t_commands;

// +1 for the boolean ONLY is the other one is 0 / false
typedef struct s_minishell
{
	t_commands	*commands;
	int			open_quote;
	int			open_dquote;
}	t_minishell;


// Exe
void	ft_exe(t_minishell *datas, t_commands *p_input);

// Builtins
void	ft_cd(char **env);


#endif
