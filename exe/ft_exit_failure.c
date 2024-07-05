/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_failure.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:10:40 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/05 18:52:52 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (c_cmd)
	{
		if (c_cmd->exit_code != 0)
			data->exit_code = c_cmd->exit_code;
	}
	ft_free_data(data);
	if (ec != -1)
		data->exit_code = ec;
	if (data->exit_code == 0)
		data->exit_code = 1;
	store_ec = data->exit_code;
	ft_free_data_exit(data);
	exit(store_ec);
}
