/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:40:10 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/09 00:45:37 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_addback(char **old_array, char *new_element)
{
	char	**new_array;
	int		i;
	int		len;

	len = ft_strlen_array(old_array);
	new_array = ft_calloc((len + 2), sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	if (old_array)
	{
		while (old_array[i])
		{
			new_array[i] = ft_strdup(old_array[i]);
			if (!new_array[i])
				return (ft_free_array(new_array));
			i++;
		}
		ft_free_array(old_array);
	}
	new_array[i] = ft_strdup(new_element);
	if (!new_array[i])
		return (ft_free_array(new_array));
	new_array[i + 1] = NULL;
	return (new_array);
}

char	**ft_addback_free(char **old_array, char *new_element)
{
	char	**new_array;
	int		i;
	int		len;

	len = ft_strlen_array(old_array);
	new_array = ft_calloc((len + 2), sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	if (old_array)
	{
		while (old_array[i])
		{
			new_array[i] = ft_strdup(old_array[i]);
			if (!new_array[i])
				return (ft_free_array(new_array));
			i++;
		}
		ft_free_array(old_array);
	}
	new_array[i] = ft_strdup(new_element);
	if (!new_array[i])
		return (ft_free_array(new_array));
	free(new_element);
	return (new_array);
}

char	*ft_charaddback(
		char **old_array, char new_element, t_utils *utils)
{
	char	*new_array;
	int		i;

	if (new_element == '\0' && !*old_array)
		new_array = malloc(sizeof(char));
	else
		new_array = malloc(sizeof(char) * (ft_better_strlen(*old_array) + 2));
	if (!new_array && utils)
		ft_ultimate_free_exit(utils, NULL, *old_array, NULL);
	else if (!new_array)
		return (NULL);
	i = 0;
	if ((*old_array))
	{
		while ((*old_array)[i])
		{
			new_array[i] = (*old_array)[i];
			i++;
		}
		free(*old_array);
	}
	new_array[i] = new_element;
	new_array[i + 1] = '\0';
	return (new_array);
}
