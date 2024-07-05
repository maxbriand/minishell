/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:57:33 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/05 07:48:00 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_utils	*ft_init_utils(void)
{
	t_utils	*utils;

	utils = malloc(sizeof(t_utils));
	if (!utils)
		ft_ultimate_free_exit(NULL, NULL, NULL, NULL);
	utils->mini = NULL;
	utils->p = NULL;
	utils->ap_j = 0;
	utils->buf_pcmd = NULL;
	utils->buf_p = NULL;
	utils->exp_str = NULL;
	utils->res_splt_q = NULL;
	utils->last_split = 0;
	utils->res_splt_s = NULL;
	utils->last_split_sep = 0;
	utils->sep = NULL;
	utils->env_free = 0;
	utils->s2 = NULL;
	return (utils);
}

void	ft_redefine_utils(t_utils *utils)
{
	utils->ap_j = 0;
	if (utils->exp_str)
		free(utils->exp_str);
	utils->exp_str = NULL;
	if (utils->res_splt_q)
		ft_free_array(utils->res_splt_q);
	utils->res_splt_q = NULL;
	utils->last_split = 0;
	if (utils->res_splt_s)
		ft_free_array(utils->res_splt_s);
	utils->res_splt_s = NULL;
	utils->last_split_sep = 0;
	if (utils->sep)
		free(utils->sep);
	utils->env_free = 0;
	utils->sep = NULL;
	utils->s2 = NULL;
}