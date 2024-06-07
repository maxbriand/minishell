/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:39:51 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/07 20:30:33 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//1 = / error
//JE LUTILISE PAS
bool	error_p(int nb, char *cmd)
{
	if (nb == 1)
	{
		printf("minishell: %s: No such file or directory", cmd);
		return (true);
	}
	return (false);
	//if (nb == 2)
}
