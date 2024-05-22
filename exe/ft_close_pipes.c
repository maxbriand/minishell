/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:09:18 by mbriand           #+#    #+#             */
/*   Updated: 2024/05/22 15:54:25 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_pipes(t_minishell *data, int **pipefds)
{
	int	i;

	i = 0;
	while (i < data->pipe_nbr)
	{
		free(pipefds[i]);
		i++;
	}
	free (pipefds);
}
