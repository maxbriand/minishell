/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:55:09 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/08 17:55:05 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**ft_create_pipes(int pipenbr, t_minishell *data)
{
	int	**pipefds;
	int	i;

	pipefds = malloc(sizeof(int *) * pipenbr);
	if (!pipefds)
		ft_exitf("malloc issue", 1, NULL, data);
	i = 0;
	while (i < pipenbr)
	{
		pipefds[i] = malloc(sizeof(int) *2);
		if (pipe(pipefds[i]) == -1)
			ft_exitf("pipe issue", 1, NULL, data);
		i++;
	}
	return (pipefds);
}
