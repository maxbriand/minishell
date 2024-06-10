/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:34:20 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/10 17:34:21 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
