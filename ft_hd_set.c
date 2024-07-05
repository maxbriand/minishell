/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hd_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 22:57:29 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/05 09:30:36 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_hd_set(
	t_minishell *mini, t_commands *buf, t_commands *p_cmd, t_utils *utils)
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
		buf->heredoc = ft_strjoin_free_s2("heredoc", ft_itoa(i), utils);
		i = ft_strlen_array(buf->hd_stop);
		mini->count_hd = mini->count_hd + i;
	}
}
