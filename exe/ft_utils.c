/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:36:56 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/09 18:18:20 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_a_directory(char *cmd)
{
	DIR	*dir;

	dir = opendir(cmd);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

int	ft_pipe_counter(t_commands *p_cmd)
{
	int c; 
	
	c = 0;
	while (p_cmd->next != NULL)
	{
		p_cmd = p_cmd->next;
		c++;
	}
	return (c);
}
