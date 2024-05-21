/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:36:56 by mbriand           #+#    #+#             */
/*   Updated: 2024/05/20 18:30:59 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_sc(char **str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_cmd_counter(t_commands *p_cmd)
{
	int c; 
	
	c = 0;
	while(p_cmd)
	{
		p_cmd = p_cmd->next;
		c++;
	}
	return (c);
}
