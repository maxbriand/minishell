/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:57:33 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/04 05:19:08 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_utils	*ft_init_utils(void)
{
	t_utils	*utils;

	utils = malloc(sizeof(t_utils));
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
	return (utils);
}