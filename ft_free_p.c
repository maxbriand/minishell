/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:45:10 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/05 13:46:57 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_p(t_pars *p)
{
	t_pars	*p_buf;

	while (p)
	{
		p_buf = p;
		if (p_buf->spl_cmd)
			ft_free_array(p_buf->spl_cmd);
		p_buf->spl_cmd = NULL;
		if (p_buf->is_arg)
			free(p_buf->is_arg);
		if (p_buf->is_expand)
			free(p_buf->is_expand);
		if (p_buf->error_msg)
			free(p_buf->error_msg);
		p = p->next;
		p_buf->spl_cmd = NULL;
		p_buf->is_arg = NULL;
		p_buf->is_expand = NULL;
		p_buf->error_msg = NULL;
		free(p_buf);
	}
}
