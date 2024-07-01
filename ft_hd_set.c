/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hd_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 22:57:29 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/01 14:27:22 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_hd_set(t_minishell *mini, t_commands *buf)
{
	int	i;

	if (buf->hd_stop)
	{
		i = ft_strlen_array(mini->heredoc) + 1;
		mini->heredoc = ft_addback(
				mini->heredoc, ft_strjoin("heredoc", ft_itoa(i)));
		if (!mini->heredoc)
			return (1);
		i = ft_strlen_array(buf->hd_stop);
		mini->count_hd = mini->count_hd + i;
	}
	return (0);
}
