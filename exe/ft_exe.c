/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:58:52 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/09 00:29:30 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exitcode_2(t_minishell *data, t_commands *p_cmd)
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

static int	ft_no_command(t_minishell *data, t_commands *p_cmd)
{
	if (!p_cmd->cmd)
	{
		if (p_cmd->msg_error)
			ft_write_error(p_cmd->msg_error);
		return (1);
	}
	return (0);
}

static void	ft_only_exit(t_minishell *data, t_commands *p_cmd)
{
	if (p_cmd->cmd)
	{
		if (ft_strcmp(p_cmd->cmd, "exit") == 0 && p_cmd->arg == NULL \
				&& p_cmd->option == NULL)
			exit (data->exit_code);
	}
	data->exit_code = p_cmd->exit_code;
}

static int	ft_one_builtin(t_minishell *data, t_commands *p_cmd)
{
	if (data->pipe_nbr == 0 && p_cmd->b_builtins == 1)
	{
		if (p_cmd->exit_code != 0)
		{
			data->exit_code = p_cmd->exit_code;
			ft_write_error(p_cmd->msg_error);
			return (1);
		}
		ft_builtins_exe(data, p_cmd);
		return (1);
	}
	return (0);
}

void	ft_exe(t_minishell *data, t_commands *p_cmd)
{
	int		c;
	pid_t	pid;

	if (!p_cmd)
		return;
	ft_only_exit(data, p_cmd);
	if (ft_no_command(data, p_cmd) || ft_exitcode_2(data, p_cmd))
		return ;
	data->pipe_nbr = ft_pipe_counter(p_cmd);
	if (ft_one_builtin(data, p_cmd))
		return ;
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
