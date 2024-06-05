/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_element.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:40:13 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/05 08:32:28 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//mettre un \0
// void	free_tab_hole(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	while (tab[i])
// 	{
// 		free(tab[i]);
// 		i++;
// 	}
// 	free(tab[i]);
// 	i++;
// 	while (tab[i])
// 	{
// 		free(tab[i]);
// 		i++;
// 	}
// 	free(tab);
// }
//remove an element from a char **
void	ft_remove_element(char **array, int id_rm)
{
	int	len;
	int	i;

	len = ft_strlen_array(array);
	i = id_rm;
	free(array[id_rm]);
	while (i < (len - 1))
	{
		array[i] = array[i + 1];
		i++;
	}
	array[len - 1] = NULL;
}
