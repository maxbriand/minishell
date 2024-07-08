/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:10:36 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/08 22:13:41 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_error(t_utils *utils, char *input, t_pars **p)
{
	if (ft_strlen(input) == 0 || ft_is_error_quote(input) == true)
	{
		ft_free_utils(&utils);		
		return (1);
	}
	*p = ft_define_p(utils, input);
	if (!*p)
	{
		ft_free_utils(&utils);
		return (1);
	}
	utils->p = *p;
	return (0);
}