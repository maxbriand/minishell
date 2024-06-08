/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_exe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 00:04:09 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/09 00:09:08 by mbriand          ###   ########.fr       */
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
