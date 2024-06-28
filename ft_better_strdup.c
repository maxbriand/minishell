/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_better_strdup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:39:16 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/28 15:56:03 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//use %s somewere inside the char *s like printf to add something in the string
char	*ft_better_strdup(char *s, char *arg)
{
	char	*sdup;
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1] == 's')
		{
			sdup = ft_substr(s, 0, i);
			sdup = ft_strjoin(sdup, arg);
			i += 2;
			sdup = ft_strjoin(sdup, ft_substr(s, i, ft_strlen(s)));
			return (sdup);
		}
		i++;
	}
	return (NULL);
}

//free the arg send as a parameter
char	*ft_better_strdup_free(char *s, char *arg)
{
	char	*sdup;
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1] == 's')
		{
			sdup = ft_substr(s, 0, i);
			sdup = ft_strjoin_free(sdup, arg);
			i += 2;
			sdup = ft_strjoin_free(sdup, ft_substr(s, i, ft_strlen(s)));
			return (sdup);
		}
		i++;
	}
	sdup = ft_strdup(arg);
	free(arg);
	return (sdup);
}

char	**ft_strdup_array(char **array)
{
	char	**result;
	int		i;

	if (!array)
		return (NULL);
	i = 0;
	result = malloc(sizeof(char *) * (ft_strlen_array(array) + 1));
	if (!result)
	{
		array = NULL;
		return (NULL);
	}
	while (array[i])
	{
		result[i] = ft_strdup(array[i]);
		if (!result[i])
		{
			free_array(result);
			result = NULL;
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}
