/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:58:52 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/05 01:26:15 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child_exe(t_minishell *data, t_commands *c_cmd, int **pipefds, int c)
{
	char	*path;
	
	if (c_cmd->exit_code != 0 && c_cmd->err_is_infile == 1)
		ft_exit_failure(c_cmd->msg_error, c_cmd, data);
	ft_set_pipefd(data, c_cmd, pipefds, c);
	if (c_cmd->b_builtins == 0)
		path = ft_check_path(data, c_cmd);
	if (c_cmd->exit_code != 0 && c_cmd->err_is_outfile == 1)
		ft_exit_failure(c_cmd->msg_error, c_cmd, data);
	if (c_cmd->infile || c_cmd->hd_stop || c_cmd->in_pipe)
		ft_input_redir(data, c_cmd, c_cmd->pipefd0);
	if (c_cmd->outfile || c_cmd->next != NULL)
		ft_output_redir(data, c_cmd, c_cmd->pipefd1);
	ft_close_pipes(data, pipefds);
	if (c_cmd->b_builtins == 0)
	{
		execve(path, c_cmd->arg_cmd, data->env);
		c_cmd->exit_code = 127;
		ft_exit_failure(" command not found\n", c_cmd, data);
	}
	else
	{
		ft_builtins_exe(data, c_cmd);
		exit(data->exit_code);
	}
}

void	ft_exe(t_minishell *data, t_commands *p_cmd)
{
	int		c;
	pid_t	pid;

	// do I need to keep this line to handle empty cmd?
	if (p_cmd->cmd == NULL)
	{
		data->exit_code = p_cmd->exit_code;		
		return ;
	}
	data->pipe_nbr = ft_pipe_counter(p_cmd);
	if (data->pipe_nbr == 0 && p_cmd->b_builtins == 1)
	{
		if (p_cmd->exit_code != 0)
		{
			data->exit_code = p_cmd->exit_code;
			return ;
		}
		ft_builtins_exe(data, p_cmd);
		return ;
	}
	data->pipefds = ft_create_pipes(data->pipe_nbr, data);
	c = 0;
	while (p_cmd)
	{
		pid = fork();
		if (pid == -1)
			ft_exit_failure("fork creation issue", NULL, data);
		if (pid == 0)
				ft_child_exe(data, p_cmd, data->pipefds, c);
		p_cmd = p_cmd->next;
		c++;
	}
	ft_close_pipes(data, data->pipefds);
	while (wait(&(data->exit_code)) != -1);
	data->exit_code = WEXITSTATUS(data->exit_code);
}
