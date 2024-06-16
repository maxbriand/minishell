/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:39:51 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/16 18:36:43 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//1 = / error
//JE LUTILISE PAS
bool	error_p(int nb, char *cmd)
{
	if (nb == 1)
	{
		ft_printf("minishell: %s: No such file or directory", cmd);
		return (true);
	}
	return (false);
	//if (nb == 2)
}
