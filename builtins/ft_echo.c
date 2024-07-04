/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:34:20 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/04 01:01:10 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_n_option(char *option)
{
	int	i;

	if (*option == '-')
		option++;
	i = 0;
	while (option[i])
	{
		if (option[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_commands *c_cmd)
{
	if (!c_cmd->option)
	{
		ft_arrprintf(c_cmd->arg);
		ft_printf("\n");
	}
	else if (ft_is_n_option(c_cmd->option))
	{
		ft_arrprintf(c_cmd->arg);
	}
}
