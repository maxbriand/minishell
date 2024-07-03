/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hd_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 22:57:29 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/03 15:51:14 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_hd_set(t_minishell *mini, t_commands *buf, t_commands *p_cmd)
{
	int			i;
	t_commands	*head;

	if (buf->hd_stop)
	{
		i = 0;
		head = p_cmd;
		while (head)
		{
			if (head->hd_stop)
				i++;
			head = head->next;
		}
		buf->heredoc = ft_strjoin("heredoc", ft_itoa(i));
		if (!buf->heredoc)
			return (1);
		i = ft_strlen_array(buf->hd_stop);
		mini->count_hd = mini->count_hd + i;
	}
	return (0);
}
