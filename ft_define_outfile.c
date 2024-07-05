/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_define_outfile.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:39:34 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/05 16:55:24 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_define_outfile(t_utils *utils, char *arg, t_pars *p)
{
	if (p->next_is_outfile)
	{
		if (utils->buf_pcmd->outfile)
			free(utils->buf_pcmd->outfile);
		utils->buf_pcmd->outfile = ft_strdup(arg);
		if (!utils->buf_pcmd->outfile)
			ft_ultimate_free_exit(utils, NULL, NULL, NULL);
		if (ft_strncmp(utils->buf_pcmd->outfile, "<", 1)
			|| ft_strncmp(utils->buf_pcmd->outfile, ">", 1))
			ft_set_error_op(utils->buf_pcmd, utils);
		p->next_is_outfile = false;
		return ;
	}
}
