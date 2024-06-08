/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_pipefd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:30:49 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/08 17:30:50 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_pfd(t_minishell *data, t_commands *c_cmd, int **pipefds, int c)
{
	if (c == 0)
		c_cmd->pipefd0 = NULL;
	else
		c_cmd->pipefd0 = pipefds[c-1];
	if (c >= data->pipe_nbr)
		c_cmd->pipefd1 = NULL;
	else
		c_cmd->pipefd1 = pipefds[c];
}
