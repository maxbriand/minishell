/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:20:18 by mbriand           #+#    #+#             */
/*   Updated: 2024/05/23 17:27:53 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arrprintf(char **arr_of_str)
{
	if (arr_of_str == NULL)
		return ;
	while (*arr_of_str)
	{
		ft_printf("%s\n", *arr_of_str);
		arr_of_str++;
	}
}
