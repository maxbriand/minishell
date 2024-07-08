/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:54:54 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/09 00:48:05 by gmersch          ###   ########.fr       */
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
# include <dirent.h>
# include "structs.h"
# include "parsing.h"

# ifndef GLOBAL
#  define GLOBAL

extern int	g_sig;
# endif

int		ft_pipe_counter(t_commands *p_cmd);
int		ft_is_a_directory(char *cmd);

void	ft_exitf(char *msg, int ec, t_commands *c_cmd, t_minishell *data);
int		ft_write_error(char *msg);
void	ft_free_data(t_minishell *data);
void	ft_free_data_exit(t_minishell *data);
void	ft_free_p_cmd(t_commands *p_cmd);
void	ft_free_str(char *str);

void	ft_create_heredocs(t_minishell *data, t_commands *p_cmd);
void	ft_exe(t_minishell *data, t_commands *p_cmd);
char	*ft_check_path(t_minishell *data, t_commands *current_cmd);
void	ft_input_redir(t_minishell *data, t_commands *c_cmd, int *pipefd);
int		ft_iterate_heredocs(t_commands *c_cmd, t_minishell *data);
void	ft_output_redir(t_minishell *data, t_commands *p_cmd, int *pipefd);
void	ft_builtins_exe(t_minishell *data, t_commands *c_cmd);

int		ft_before_cmd_exe(t_minishell *data, t_commands *p_cmd);
void	ft_if_only_exit(t_minishell *data, t_commands *p_cmd);
int		ft_if_no_command(t_commands *p_cmd);
int		ft_if_exitcode_2(t_minishell *data, t_commands *p_cmd);

int		ft_exe_1_builtin(t_minishell *data, t_commands *p_cmd);

void	ft_exe_in_fork(t_minishell *data, t_commands *p_cmd);

int		**ft_create_pipes(int pipenbr, t_minishell *data);
void	ft_set_pfd(t_minishell *data, t_commands *c_cmd, int **pipefds, int c);
void	ft_close_pipes(t_minishell *data, int **pipefds);

void	ft_cd(t_minishell *data, t_commands *p_cmd);
void	ft_exit(t_minishell *data, t_commands *p_cmd);
void	ft_echo(t_commands *p_cmd);
void	ft_env(t_minishell *data, t_commands *p_cmd);
void	ft_export(t_minishell *data, t_commands *p_cmd);
void	ft_export_export(t_minishell *data, char *var);
void	ft_export_env(t_minishell *data, char *var);
char	*ft_pwd(t_minishell *data, int i);
void	ft_unset(t_minishell *data, t_commands *p_cmd);

char	*ft_get_env_var(char **env, char *var);
int		ft_lfor_var(char **env, char *var);

void	ft_signals(int d);

#endif
