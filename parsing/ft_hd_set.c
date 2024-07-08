/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hd_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 22:57:29 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/08 21:25:38 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static bool	ft_check_error(t_minishell *mini)
{
	t_commands	*buf;
	bool		error;

	error = false;
	buf = mini->p_cmd;
	while (buf)
	{
		if (buf->exit_code == 2)
			error = true;
		buf = buf->next;
	}	
	return (error);
}

void	ft_hd_set(
	t_minishell *mini, t_commands *buf, t_commands *p_cmd, t_utils *utils)
{
	int			i;
	t_commands	*head;
	bool		error;

	error = ft_check_error(mini);
	if (buf->hd_stop && !error)
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
