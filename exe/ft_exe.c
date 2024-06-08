/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:58:52 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/08 19:20:54 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child_exe(t_minishell *data, t_commands *c_cmd, int **pipefds, int c)
{
	char	*path;
	
	if (c_cmd->exit_code != 0 && c_cmd->bf_cmd == true)
		ft_exitf(c_cmd->msg_error, c_cmd->exit_code, c_cmd, data);
	ft_set_pfd(data, c_cmd, pipefds, c);
	if (c_cmd->b_builtins == 0)
		path = ft_check_path(data, c_cmd);
	if (c_cmd->exit_code != 0 && c_cmd->bf_cmd == false)
		ft_exitf(c_cmd->msg_error, c_cmd->exit_code, c_cmd, data);
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

int	ft_check_ec_2(t_minishell *data, t_commands *p_cmd)
{
	while (p_cmd)
	{
		if (p_cmd->exit_code == 2)
		{
			data->exit_code = 2;
			ft_write_error(p_cmd->msg_error);
			return (1);
		}
		p_cmd = p_cmd->next;	
	}
	return (0);
}

void	ft_exe(t_minishell *data, t_commands *p_cmd)
{
	int		c;
	pid_t	pid;

	if (!p_cmd)
		return;
	if (!p_cmd->cmd)
	{
		data->exit_code = p_cmd->exit_code;		
		if (p_cmd->msg_error)
			ft_write_error(p_cmd->msg_error);
		return ;
	}
	// looking for exit_code 2 -> problem because the exit code persists
	if (ft_check_ec_2(data, p_cmd) == 1)
		return;
	data->pipe_nbr = ft_pipe_counter(p_cmd);
	if (data->pipe_nbr == 0 && p_cmd->b_builtins == 1)
	{
		if (p_cmd->exit_code != 0)
		{
			data->exit_code = p_cmd->exit_code;
			return ;
		}
		ft_builtins_exe(data, p_cmd);
		data->exit_code = 0;
		return ;
	}
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
