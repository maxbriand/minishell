
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
	char	**hd_stop;
	char	*infile; // last infile -> only if this infile it's the last input redirection / after heredoc
	bool	in_pipe; //pipe before the command or not (0 or 1)
	char	*outfile; // last outfile -> last fd
	bool	append_outfile;
	char	*cmd;
	char	*option;
	char	*arg;
	char	**arg_cmd; // cmd + option + arg
	struct s_commands	*next;
	// int		out_pipe; => don't because the last cmd have null on next
}	t_commands;


// +1 for the boolean ONLY is the other one is 0 / false
typedef struct s_minishell
{
	t_commands	*p_cmd;
	char		**env;
	int			open_quote;
	int			open_dquote;
}	t_minishell;

// Error
void	ft_exit_failure(char *msg, t_minishell *data);
int		ft_write_error(char *msg);

// Exe
int		ft_exe(t_minishell *data, t_commands *p_cmd);
char	*ft_check_path(t_minishell *data, t_commands *current_cmd);
int		ft_sc(char **str);

// Builtins
int		ft_cd(t_commands *p_cmd);
void	ft_exit(void);
void	ft_echo(void);
void	ft_env(void);
void	ft_export(void);
void	ft_pwd(void);
void	ft_unset(void);

#endif
