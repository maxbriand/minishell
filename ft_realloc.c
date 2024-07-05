/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:40:10 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/05 07:52:51 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//add 1 element to a array. Free old array, so not needed to free it after
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
			{
				ft_free_array(new_array);
				return (NULL);
			}
			i++;
		}
		ft_free_array(old_array);
	}
	new_array[i] = ft_strdup(new_element);
	if (!new_array[i])
	{
		ft_free_array(new_array);
		return (NULL);
	}
	new_array[i + 1] = NULL;
	return (new_array);
}

//same has addback, but free new_element
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
			{
				ft_free_array(new_array);
				return (NULL);
			}
			i++;
		}
		ft_free_array(old_array);
	}
	new_array[i] = ft_strdup(new_element);
	if (!new_array[i])
	{
		ft_free_array(new_array);
		return (NULL);
	}
	free(new_element);
	return (new_array);
}

//add a char to a string, need to send a adress of the string to old array
//FREE AND EXIT
char	*ft_charaddback(
		char **old_array, char new_element, t_utils *utils)
{
	char	*new_array;
	int		i;
	int		len;

	len = ft_better_strlen(*old_array);
	if (new_element == '\0' && !*old_array)
		new_array = malloc(sizeof(char));
	else
		new_array = malloc(sizeof(char) * (len + 2));
	if (!new_array)
	{
		if (utils)
			ft_ultimate_free_exit(utils, NULL, *old_array, NULL);
		return (NULL);
	}
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
