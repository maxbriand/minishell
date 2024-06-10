/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:40:10 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/10 18:35:37 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//to add to the libft later
#include "minishell.h"


static char	*strdup_protect(char *new_element)
{
	char *new_array;

	new_array = ft_strdup(new_element);
	if (!new_array)
		exit (1); //error to write?
	return (new_array);
}


//add 1 element to a array. Free the old array, so it's not needed to free it after
char	**ft_addback(char **old_array, char *new_element)
{
	char	**new_array;
	int		i;

	i = 0;
	if (old_array)
	{
		while (old_array[i])
			i++;
	}
	new_array = malloc(sizeof(char *) * (i + 2));
	if (!new_array)
		exit (1); //error to write?
	if (old_array)
	{
		i = 0;
		while (old_array[i])
		{
			new_array[i] = strdup_protect(old_array[i]);
			i++;
		}
		free_array(old_array);
	}
	new_array[i] = strdup_protect(new_element);
	new_array[i + 1] = NULL;
	return (new_array);
}

//not use ??
int	*ft_addback_int(int *old_array, int	new_element)
{
	int	*new_array;
	int	i;

	i = 0;
	if (old_array)
	{
		while (old_array[i] != -1)
			i++;
	}
	new_array = malloc(sizeof(int) * (i + 2));
	if (!new_array)
		exit (1); //error to write?
	if (old_array)
	{
		i = 0;
		while (old_array[i] != -1)
		{
			new_array[i] = old_array[i];
			i++;
		}
		free(old_array);
	}
	new_array[i] = new_element;
	new_array[i + 1] = -1;
	return (new_array);
	//coucou maxime va bosser au lieu de mater mon beau code
}

//add a char to a string, need to send a adress of the string to old array
char	*ft_charaddback(char **old_array, char new_element)
{
	char	*new_array;
	int		i;

	i = 0;
	if (*old_array)
	{
		while ((*old_array)[i])
			i++;
	}
	if (new_element == '\0' && !*old_array)
		new_array = malloc(sizeof(char));
	else
		new_array = malloc(sizeof(char) * (i + 2));
	if (!new_array)
		return (NULL); //error to write?
	if ((*old_array))
	{
		i = 0;
		while ((*old_array)[i])
		{
			new_array[i] = (*old_array)[i];
			i++;
		}
		free(*old_array);
	}
	new_array[i] = new_element;
	if (new_element != '\0')
		new_array[i + 1] = '\0';
	return (new_array);
}
