/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:34:20 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/28 23:07:35 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	ft_is_n_option(char *option)
// {
// 	int	i;
	
// 	if (*option == '-')
// 		option++;
// 	i = 0;
// 	while (option[i])
// 	{
		
// 	}
// }

void	ft_echo(t_commands *c_cmd)
{
	if (c_cmd->option == NULL)
	{
		ft_arrprintf(c_cmd->arg);
		ft_printf("\n");
	}
	else if (ft_strcmp(c_cmd->option, "-n") == 0)
	{
		ft_arrprintf(c_cmd->arg);
	}
}
