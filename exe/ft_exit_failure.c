/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_failure.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:10:40 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/10 18:17:59 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// delete heredoc if user close minishell
void	ft_free_str(char *str)
{
	if (!str)
		return ;
	free(str);
}

void	ft_free_p_cmd(t_commands *p_cmd)
{
	t_commands *old_p_cmd;

	while (p_cmd)
	{
		ft_free_str(p_cmd->infile);
		ft_free_str(p_cmd->outfile);
		ft_free_str(p_cmd->cmd);
		ft_free_str(p_cmd->option);
		ft_free_str(p_cmd->msg_error);
		ft_arrfree(p_cmd->hd_stop);
		ft_arrfree(p_cmd->arg);
		ft_arrfree(p_cmd->arg_cmd);
		old_p_cmd = p_cmd;
		p_cmd = p_cmd->next;
		free (old_p_cmd);
	}
}

void	ft_free_pipefds(int **pipefds, int pipenbr)
{
	int	i;

	i = 0;
	if (!pipefds)
		return ;
	while (i < pipenbr)
	{
		free(pipefds[i]);
		i++;
	}
	free (pipefds);
}

// use close pipe 
void	ft_free_data(t_minishell *data)
{
	ft_free_p_cmd(data->p_cmd);
	data->p_cmd = NULL;
	ft_free_pipefds(data->pipefds, data->pipe_nbr);
}

int	ft_write_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (0);
}

void	ft_free_data_exit(t_minishell *data)
{
	ft_arrfree(data->export);
	data->export = NULL;
	ft_arrfree(data->env);
	data->env = NULL;
	free(data);
}

void	ft_exitf(char *msg, int ec, t_commands *c_cmd, t_minishell *data)
{
	int	store_ec;

	ft_write_error(msg);
	if (!data)
		exit (1);
	ft_free_data(data);
	if (!c_cmd)
	{
		if (c_cmd->exit_code != 0)
			data->exit_code = c_cmd->exit_code;
	}
	if (ec != -1)
		data->exit_code = ec;
	if (data->exit_code == 0)
		data->exit_code = 1;
	store_ec = data->exit_code;
	ft_free_data_exit(data);
	exit(store_ec);
}
