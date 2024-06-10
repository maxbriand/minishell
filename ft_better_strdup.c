/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_better_strdup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:39:16 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/10 20:11:39 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_better_strdup(char *s, char *arg)
{
	char	*sdup;
	int		i;

	i = 0;
	while(s[i])
	{
		if (s[i] == '%' && s[i + 1] == 's')
		{
			sdup = ft_substr(s, 0, i);
			sdup = ft_strjoin(sdup, arg);
			i+= 2;
			sdup = ft_strjoin(sdup, ft_substr(s, i, ft_strlen(s)));
			return (sdup);
		}
		i++;
	}
	return (NULL);
}

char	*ft_better_strdup_free(char *s, char *arg)
{
	char	*sdup;
	int		i;

	i = 0;
	while(s[i])
	{
		if (s[i] == '%' && s[i + 1] == 's')
		{
			sdup = ft_substr(s, 0, i);
			sdup = ft_strjoin_free(sdup, arg);
			i+= 2;
			sdup = ft_strjoin_free(sdup, ft_substr(s, i, ft_strlen(s)));
			return (sdup);
		}
		i++;
	}
	return (NULL);
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
		exit (1);//mayday error
	while(array[i])
	{
		result[i] = ft_strdup(array[i]);
		i++;
	}
	result[i] = NULL;
	return (result);
}
