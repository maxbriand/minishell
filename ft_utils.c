/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:40:36 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/03 17:40:37 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_only_space(char *str)
{
	int	i;

	i = 0;
	if (str[0] == ' ')
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}