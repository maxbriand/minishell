/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:40:28 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/09 00:46:01 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free_s1(char *s1, char *s2, t_utils *utils)
{
	char	*result;
	int		i;

	result = NULL;
	if (s1)
	{
		result = ft_strdup(s1);
		if (!result)
			ft_ultimate_free_exit(utils, NULL, NULL, NULL);
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

char	*ft_strjoin_free_s2(char *s1, char *s2, t_utils *utils)
{
	char	*result;
	int		i;

	result = NULL;
	if (s1)
	{
		result = ft_strdup(s1);
		if (!result)
			ft_ultimate_free_exit(utils, NULL, s2, NULL);
	}
	i = 0;
	if (s2)
	{
		utils->s2 = s2;
		while (s2[i])
		{
			result = ft_charaddback(&result, s2[i], utils);
			i++;
		}
		free(s2);
		utils->s2 = NULL;
	}
	return (result);
}

char	*ft_strjoin_free(char *s1, char *s2, t_utils *utils)
{
	char	*result;
	int		i;

	result = NULL;
	if (s1)
	{
		result = ft_strdup(s1);
		if (!result)
			ft_ultimate_free_exit(utils, NULL, NULL, NULL);
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
