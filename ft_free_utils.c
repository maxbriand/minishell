/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 04:25:38 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/05 02:15:52 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_utils(t_utils *utils)
{
	if (utils->exp_str)
		free(utils->exp_str);
	if (utils->res_splt_q)
		ft_free_array(utils->res_splt_q);
	utils->res_splt_q = NULL;
	if (utils->res_splt_s)
		ft_free_array(utils->res_splt_s);
	utils->res_splt_s = NULL;
	if (utils->sep)
		free(utils->sep);
	free (utils);
}