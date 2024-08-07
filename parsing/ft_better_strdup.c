/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_better_strdup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:39:16 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/09 00:43:43 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_better_strdup(char *s, char *arg, t_utils *utils)
{
	char	*sdup;
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1] == 's' && arg)
		{
			sdup = ft_strjoin_free_s1(ft_substr(s, 0, i), arg, utils);
			i += 2;
			sdup = ft_strjoin_free(sdup, ft_substr(s, i, ft_strlen(s)), utils);
			return (sdup);
		}
		i++;
	}
	return (NULL);
}

char	*ft_better_strdup_free(char *s, char *arg, t_utils *utils)
{
	char	*sdup;
	int		i;

	i = 0;
	sdup = NULL;
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1] == 's' && arg)
		{
			sdup = ft_strjoin_free(ft_substr(s, 0, i), arg, utils);
			i += 2;
			sdup = ft_strjoin_free(sdup, ft_substr(s, i, ft_strlen(s)), utils);
			return (sdup);
		}
		i++;
	}
	if (arg)
	{
		sdup = ft_strdup(arg);
		free(arg);
	}
	if (!sdup)
		ft_ultimate_free_exit(utils, NULL, NULL, NULL);
	return (sdup);
}

char	**ft_strdup_array(char **array, t_utils *utils)
{
	char	**result;
	int		i;

	if (!array)
		return (NULL);
	i = 0;
	result = malloc(sizeof(char *) * (ft_strlen_array(array) + 1));
	if (!result)
		ft_ultimate_free_exit(utils, NULL, NULL, NULL);
	while (array[i])
	{
		result[i] = ft_strdup(array[i]);
		if (!result[i])
			ft_ultimate_free_exit(utils, result, NULL, NULL);
		i++;
	}
	result[i] = NULL;
	return (result);
}
