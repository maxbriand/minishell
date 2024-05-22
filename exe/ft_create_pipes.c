/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:55:09 by mbriand           #+#    #+#             */
/*   Updated: 2024/05/22 17:53:15 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**ft_create_pipes(int pipenbr, t_minishell *data)
{
	int	**pipefds;
	int	i;

	pipefds = malloc(sizeof(int *) * pipenbr);
	// add protection
	i = 0;
	while (i < pipenbr)
	{
		pipefds[i] = malloc(sizeof(int) *2);
		if (pipe(pipefds[i]) == -1)
			ft_exit_failure("pipe issue", data);
		i++;
	}
	return (pipefds);
}
