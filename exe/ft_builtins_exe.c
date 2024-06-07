/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_exe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:57:07 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/07 22:34:42 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtins_exe(t_minishell *data, t_commands *c_cmd)
{
	if (strcmp(c_cmd->cmd, "cd") == 0)
		ft_cd(data, c_cmd);
	else if (strcmp(c_cmd->cmd, "echo") == 0)
		ft_echo(data, c_cmd);
	else if (strcmp(c_cmd->cmd, "env") == 0)
		ft_env(data, c_cmd);
	else if (strcmp(c_cmd->cmd, "exit") == 0)
		ft_exit(data, c_cmd);
	else if (strcmp(c_cmd->cmd, "export") == 0)
		ft_export(data, c_cmd);
	else if (strcmp(c_cmd->cmd, "pwd") == 0)
		ft_pwd(data, c_cmd, 0);
	//else if (strcmp(c_cmd->cmd, "unset") == 0)
	//	ft_unset(data, c_cmd);
}
