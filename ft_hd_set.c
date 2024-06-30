/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hd_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 22:57:29 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/30 22:58:20 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_hd_set(t_minishell *mini, t_commands *buf)
{
	int	i;

	if (buf->hd_stop)
	{
		i = 0;
		while (buf->hd_stop[i])
			i++;
		i--;
		mini->heredoc = ft_addback(mini->heredoc, buf->hd_stop[i]);
		if (!mini->heredoc)
			return (1);
		i++;
		mini->count_hd = mini->count_hd + i;
	}
	return (0);
}
