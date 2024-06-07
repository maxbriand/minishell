/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:59:21 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/06 20:28:05 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_export_parsing(char	*arg)
{
	if (ft_isdigit(*arg) == 1 || *arg == '=')
		return (1);
	while (*arg && *arg != '=')
	{
		if (ft_isalnum(*arg) != 1 && *arg != '_')
			return (1);
		arg++;
	}
	return (0);
}

static void	ft_ite_arg(t_minishell *data, t_commands *c_cmd)
{
	int	i;
	
	i = 0;
	while (c_cmd->arg[i])
	{
		if (ft_export_parsing(c_cmd->arg[i]) == 1)
		{
			ft_write_error(" not a valid identifier");
			data->exit_code = 1;
			i++;
			continue ;
		}
		if (ft_strchr(c_cmd->arg[i], '=') != 0)
			ft_export_env(data, c_cmd->arg[i]);
		ft_export_export(data, c_cmd->arg[i]);
		i++;
	}
}

void	ft_export(t_minishell *data, t_commands *c_cmd)
{
	int	i;
	
	if (!data->export)
		return ;
	i = 0;
	if (!c_cmd->arg)
	{
		while (data->export[i])
		{
			ft_printf("declare -x %s\n", data->export[i]);
			i++;
		}
		return ;
	}
	else
	{
		ft_ite_arg(data, c_cmd);
	}
}
