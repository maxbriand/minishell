/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_1builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 01:52:05 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/09 03:08:23 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_1b_output_redir(t_minishell *data, t_commands *c_cmd)
{
	int	fd;
	int	old_fd1;

	c_cmd->old_fd1 = dup(1);
	if (c_cmd->outfile && c_cmd->append_outfile == 1)
	{
		fd = open(c_cmd->outfile, O_WRONLY | O_APPEND);
		if (dup2(fd, 1) == -1)
			ft_exitf("dup2 issue", 1, NULL, data);
		close(fd);
	}
	else
	{
		fd = open(c_cmd->outfile, O_WRONLY | O_TRUNC);
		if (dup2(fd, 1) == -1)
			ft_exitf("dup2 issue", 1, NULL, data);
		close(fd);
	}
}

// static void	ft_1b_input_redir(t_minishell *data, t_commands *p_cmd)
// {

	
// }

static int	ft_if_already_error(t_minishell *data, t_commands *p_cmd)
{
	if (p_cmd->exit_code != 0)
	{
		data->exit_code = p_cmd->exit_code;
		ft_write_error(p_cmd->msg_error);
		return (1);
	}
	return (0);
}

static void	ft_reset_fd(t_minishell *data, t_commands *c_cmd)
{
	if (c_cmd->outfile)
	{
		close(1);
		dup2(c_cmd->old_fd1, 1);
		close(c_cmd->old_fd1);
	}
	// add for infile
}


int	ft_exe_1_builtin(t_minishell *data, t_commands *p_cmd)
{
	data->pipe_nbr = ft_pipe_counter(p_cmd);
	if (data->pipe_nbr == 0 && p_cmd->b_builtins == 1)
	{
		if (ft_if_already_error(data, p_cmd) == 1)
			return (1);
		// if (p_cmd->infile || p_cmd->hd_stop)
		// 	ft_1b_input_redir(data, p_cmd);
		if (p_cmd->outfile)
			ft_1b_output_redir(data, p_cmd);
		ft_builtins_exe(data, p_cmd);
		ft_reset_fd(data, p_cmd);
		return (1);
	}
	return (0);
}
