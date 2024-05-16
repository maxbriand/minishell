
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

typedef struct s_commands
{
	bool	b_builtins;
	char	**hd_stop;
	char	**stdinput;// standard input // append everytime
	char	**stdoutput;// standard output
	int		*append_output; // 0 - 1 for &gt;&gt; or &gt;
	char	*cmd;
	char	*option;
	char	*arg;
	char	**arg_cmd; // cmd + option + arg
	struct s_commands	*next;
}	t_commands;


// +1 for the boolean ONLY is the other one is 0 / false
typedef struct s_minishell
{
	t_commands	*commands;
	char		**env;
	int			open_quote;
	int			open_dquote;
}	t_minishell;

// Error
void	ft_exit_failure(char *msg, t_minishell *data);
int		ft_write_error(char *msg);

// Exe
int	ft_exe(t_minishell *data, t_commands *p_cmd);

// Builtins
int		ft_cd(t_commands *p_cmd);
void	ft_exit(void);
void	ft_echo(void);
void	ft_env(void);
void	ft_export(void);
void	ft_pwd(void);
void	ft_unset(void);

#endif
