/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:40:28 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/21 17:15:55 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//free s1 but not s2, and accept if s1 or s2 is empty
char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;
	int		i;

	result = NULL;
	if (s1)
	{
		result = ft_strdup(s1);
		free(s1);
	}
	i = 0;
	if (s2)
	{
		while (s2[i])
		{
			result = ft_charaddback(&result, s2[i]);
			i++;
		}
		free(s2);
	}
	return (result);
}
