/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_in_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 01:57:08 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/09 00:35:09 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_builtin_path(t_minishell *data, t_commands *c_cmd)
{
	ft_builtins_exe(data, c_cmd);
	ft_free_data(data);
	ft_free_data_exit(data);
	exit(EXIT_SUCCESS);
}

static void	ft_if_only_hd(t_minishell *data, t_commands *c_cmd, int **pipefds)
{
	(void) data;
	if (!c_cmd->cmd)
	{
		ft_close_pipes(data, pipefds);
		unlink(c_cmd->heredoc);
		ft_free_data(data);
		ft_free_data_exit(data);
		exit(EXIT_SUCCESS);
	}
}

void	ft_child_exe(t_minishell *data, t_commands *c_cmd, int **pipefds, int c)
{
	char	*path;

	ft_if_only_hd(data, c_cmd, pipefds);
	if (c_cmd->exit_code != 0)
		ft_exitf(c_cmd->msg_error, c_cmd->exit_code, c_cmd, data);
	ft_set_pfd(data, c_cmd, pipefds, c);
	if (c_cmd->b_builtins == 0)
		path = ft_check_path(data, c_cmd);
	if (c_cmd->infile || c_cmd->hd_stop || c_cmd->in_pipe)
		ft_input_redir(data, c_cmd, c_cmd->pipefd0);
	if (c_cmd->outfile || c_cmd->next != NULL)
		ft_output_redir(data, c_cmd, c_cmd->pipefd1);
	ft_close_pipes(data, pipefds);
	if (c_cmd->b_builtins == 0)
	{
		if (ft_strncmp(c_cmd->cmd, "minishell", ft_strlen(c_cmd->cmd)))
			execve(path, c_cmd->arg_cmd, data->env);
		ft_exitf(" commanda not found\n", 127, c_cmd, data);
	}
	else
	{
		ft_builtin_path(data, c_cmd);
	}
}

void	ft_exe_in_fork(t_minishell *data, t_commands *p_cmd)
{
	int		c;
	pid_t	pid;
	pid_t	current_pid;

	data->pipefds = ft_create_pipes(data->pipe_nbr, data);
	c = 0;
	while (p_cmd)
	{
		pid = fork();
		if (pid == -1)
			ft_exitf("fork creation issue", 1, p_cmd, data);
		if (pid == 0)
			ft_child_exe(data, p_cmd, data->pipefds, c);
		p_cmd = p_cmd->next;
		c++;
	}
	ft_close_pipes(data, data->pipefds);
	while (1)
	{
		current_pid = wait(&(data->wait_code));
		if (current_pid == -1)
			break ;
		if (current_pid == pid)
			data->exit_code = WEXITSTATUS(data->wait_code);
	}
}
