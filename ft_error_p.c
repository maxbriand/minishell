/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:39:51 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/07 21:45:01 by gmersch          ###   ########.fr       */
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
