/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_before_exe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 01:31:21 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/03 03:00:51 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_if_exitcode_2(t_minishell *data, t_commands *p_cmd)
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

int	ft_if_no_command(t_minishell *data, t_commands *p_cmd)
{
	if (!p_cmd->cmd)
	{
		if (p_cmd->hd_stop)
			unlink(p_cmd->heredoc);
		if (p_cmd->msg_error)
			ft_write_error(p_cmd->msg_error);
		return (1);
	}
	return (0);
}

void	ft_if_only_exit(t_minishell *data, t_commands *p_cmd)
{
	if (p_cmd->cmd)
	{
		if (ft_strcmp(p_cmd->cmd, "exit") == 0 && !p_cmd->arg \
				&& !p_cmd->option && !p_cmd->next)
		{
			ft_write_error("exit");
			exit (data->exit_code);
		}
	}
}

int	ft_before_cmd_exe(t_minishell *data, t_commands *p_cmd)
{
	if (!p_cmd)
		return (1);
	ft_if_only_exit(data, p_cmd);
	data->exit_code = p_cmd->exit_code;
	if (ft_if_no_command(data, p_cmd) || ft_if_exitcode_2(data, p_cmd))
		return (1);
	return (0);
}
