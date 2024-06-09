/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_in_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 01:57:08 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/09 02:06:24 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_child_exe(t_minishell *data, t_commands *c_cmd, int **pipefds, int c)
{
	char	*path;
	
	// if (c_cmd->exit_code != 0 && c_cmd->bf_cmd == true)
	if (c_cmd->exit_code != 0)
		ft_exitf(c_cmd->msg_error, c_cmd->exit_code, c_cmd, data);
	ft_set_pfd(data, c_cmd, pipefds, c);
	if (c_cmd->b_builtins == 0)
		path = ft_check_path(data, c_cmd);
	// if (c_cmd->exit_code != 0 && c_cmd->bf_cmd == false)
	// 	ft_exitf(c_cmd->msg_error, c_cmd->exit_code, c_cmd, data);
	if (c_cmd->infile || c_cmd->hd_stop || c_cmd->in_pipe)
		ft_input_redir(data, c_cmd, c_cmd->pipefd0);
	if (c_cmd->outfile || c_cmd->next != NULL)
		ft_output_redir(data, c_cmd, c_cmd->pipefd1);
	ft_close_pipes(data, pipefds);
	if (c_cmd->b_builtins == 0)
	{
		execve(path, c_cmd->arg_cmd, data->env);
		ft_exitf(" command not found\n", 127, c_cmd, data);
	}
	else
	{
		ft_builtins_exe(data, c_cmd);
		exit(EXIT_SUCCESS);
	}
}

void	ft_exe_in_fork(t_minishell *data, t_commands *p_cmd)
{
	int		c;
	pid_t	pid;

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
	while (wait(&(data->exit_code)) != -1);
	data->exit_code = WEXITSTATUS(data->exit_code);
}