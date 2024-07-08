/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:38:21 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/08 16:51:05 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cd_home(t_minishell *data)
{
	if (!ft_get_env_var(data->env, "HOME"))
	{
		ft_write_error("minishell: cd: HOME not set");
		data->exit_code = 1;
		return ;
	}
	if (chdir(ft_get_env_var(data->env, "HOME")) == -1)
		ft_write_error("chdir issue");
}

void	ft_cd(t_minishell *data, t_commands *c_cmd)
{
	if (c_cmd->option == NULL && c_cmd->arg == NULL)
		ft_cd_home(data);
	if (c_cmd->option == NULL && c_cmd->arg != NULL)
	{
		if (ft_arrlen(c_cmd->arg) > 1)
		{
			ft_write_error("minishell: too many arguments");
			data->exit_code = 1;
		}
		else if (chdir(*(c_cmd->arg)) == -1)
		{
			ft_write_error("minishell: No such file or directory");
			data->exit_code = 1;
		}
	}
}
