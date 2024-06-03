/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_element.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:40:13 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/03 17:40:14 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//mettre un \0
void	free_tab_hole(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab[i]);
	i++;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
//remove an element from a char **
// char	**ft_remove_element(char **old_array, int id_rm)
// {
// 	char	**new_array;
// 	int		i;
// 	int		j;
// 	int		len;
// 	bool	is_hole;

// 	if (id_rm < 0 || old_array == NULL)
// 		return (NULL);
// 	len = ft_strlen_array(old_array);
// 	printf("%d = len\n", len);
// 	if (len == 1)
// 	{
// 		free(old_array[0]);
// 		return ();
// 	}
// 	new_array = malloc(sizeof(char *) * (len + 1));
// 	if (!new_array)
// 		exit (1);//mayday error
// 	i = 0;
// 	while (i < id_rm)
// 	{
// 		new_array[i] = ft_strdup(old_array[i]);
// 		if (!new_array[i])
// 		{
// 			while (i-- >= 0)
// 				free(new_array[i]);
// 			free(new_array);
// 			exit (1); //mayday error ?
// 		}
// 		i++;
// 	}
// 	while (old_array[i + 1])
// 	{
// 		new_array[i] = ft_strdup(old_array[i + 1]);
// 		if (!new_array[i + 1])
// 		{

// 			while (i-- >= 0)
// 				free(new_array[i]);
// 			free(new_array);
// 			exit (1); //mayday error ?
// 		}
// 		i++;
// 	}
// 	new_array[i] = NULL;
// 	free_tab_hole(old_array);
// 	old_array = NULL;
// 	return (new_array);
// }
