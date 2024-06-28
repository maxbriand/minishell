/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_arg_join.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:39:41 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/28 16:59:19 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmd_arg_join(t_commands *cmd)
{
	int	i;

	cmd->arg_cmd = ft_addback(cmd->arg_cmd, cmd->cmd);
	if (cmd->option)
		cmd->arg_cmd = ft_addback(cmd->arg_cmd, cmd->option);
	i = 0;
	if (cmd->arg)
	{
		while (cmd->arg[i])
		{
			cmd->arg_cmd = ft_addback(cmd->arg_cmd, cmd->arg[i]);
			i++;
		}
	}
}
