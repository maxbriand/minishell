/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:54:54 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/07 19:17:00 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <signal.h>
# include <termios.h>

typedef struct s_commands
{
	char				*infile; // last infile -> only if this infile it's the last input redirection / after heredoc
	char				**hd_stop;
	bool				in_pipe; //pipe before the command or not (0 or 1)
	char				*outfile; // last outfile -> last fd
	bool				append_outfile; // only need to know if the last outfile is an append
	char				*cmd;
	char				*option;
	char				**arg;
	char				**arg_cmd; // cmd + option + arg
	bool				b_builtins;
	struct s_commands	*next;
	int					*pipefd0;
	int					*pipefd1;
	bool				err_is_infile;
	bool				err_is_outfile;
	int					exit_code;
	char				*msg_error;
}	t_commands;

// +1 for the boolean ONLY is the other one is 0 / false
typedef struct s_minishell
{
	t_commands		*p_cmd;
	int				pipe_nbr;
	char			**env;
	char			**export;
	bool			env_malloc;
	char			**path_env;
	int				open_quote;
	int				open_dquote;
	int				**pipefds;
	int				exit_code;
}	t_minishell;

# ifndef GLOBAL
#  define GLOBAL
extern int g_sig;
# endif

# include "parsing.h"

void ft_print_fd_content(int fd);

// Utils
int	ft_pipe_counter(t_commands *p_cmd);

// Error
void	ft_exit_failure(char *msg, t_commands *c_cmd, t_minishell *data);
int		ft_write_error(char *msg);

// Exe
void	ft_exe(t_minishell *data, t_commands *p_cmd);
char	*ft_check_path(t_minishell *data, t_commands *current_cmd);
int		ft_sc(char **str);
void	ft_input_redir(t_minishell *data, t_commands *c_cmd, int *pipefd);
void	ft_output_redir(t_minishell *data, t_commands *p_cmd, int *pipefd);
void	ft_builtins_exe(t_minishell *data, t_commands *c_cmd);

// Exe - Pipes management
int		**ft_create_pipes(int pipenbr, t_minishell *data);
void	ft_set_pipefd(t_minishell *data, t_commands *c_cmd, int **pipefds, int c);
void	ft_close_pipes(t_minishell *data, int **pipefds);

// Builtins
void	ft_cd(t_minishell *mish, t_commands *p_cmd);
void	ft_exit(t_minishell *mish, t_commands *p_cmd);
void	ft_echo(t_minishell *mish, t_commands *p_cmd);
void	ft_env(t_minishell *mish, t_commands *p_cmd);
void	ft_export(t_minishell *mish, t_commands *p_cmd);
void	ft_export_export(t_minishell *data, char *var);
void	ft_export_env(t_minishell *data, char *var);
char	*ft_pwd(t_minishell *mish, t_commands *p_cmd, int i);
void	ft_unset(t_minishell *mish, t_commands *p_cmd);

// Builtins utils
char	*ft_get_env_var(char **env, char *var);
int		ft_lfor_var(char **env, char *var);

// Signals
void	ft_signals(int d);
void 	ft_set_newterm(t_minishell *data);

#endif
