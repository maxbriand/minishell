/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:40:28 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/03 19:45:05 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//free s1 but not s2, and accept if s1 or s2 is empty, EXIT AND FREE utils
char	*ft_strjoin_free_s1(char *s1, char *s2, t_utils *utils)
{
	char	*result;
	int		i;

	result = NULL;
	if (s1)
	{
		result = ft_strdup(s1);
		if (!result)
			ft_ultimate_free_exit(utils, NULL, NULL);
		free(s1);
	}
	i = 0;
	if (s2)
	{
		while (s2[i])
		{
			result = ft_charaddback(&result, s2[i], utils);
			i++;
		}
	}
	return (result);
}

//free s2 but not s1, and accept if s1 or s2 is empty, EXIT AND FREE utils
char	*ft_strjoin_free_s2(char *s1, char *s2, t_utils *utils)
{
	char	*result;
	int		i;

	result = NULL;
	if (s1)
	{
		result = ft_strdup(s1);
		if (!result)
			ft_ultimate_free_exit(utils, NULL, NULL);
	}
	i = 0;
	if (s2)
	{
		while (s2[i])
		{
			result = ft_charaddback(&result, s2[i], utils);
			i++;
		}
		free(s2);
	}
	return (result);
}

//free s1 AND s2, and accept if s1 or s2 is empty, EXIT AND FREE utils
char	*ft_strjoin_free(char *s1, char *s2, t_utils *utils)
{
	char	*result;
	int		i;

	result = NULL;
	if (s1)
	{
		result = ft_strdup(s1);
		if (!result)
			ft_ultimate_free_exit(utils, NULL, NULL);
		free(s1);
		s1 = NULL;
	}
	i = 0;
	if (s2)
	{
		while (s2[i])
		{
			result = ft_charaddback(&result, s2[i], utils);
			i++;
		}
		free(s2);
		s2 = NULL;
	}
	return (result);
}
