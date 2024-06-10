/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 22:43:10 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/10 17:37:58 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_export(char **env, int n, t_minishell *data)
{
	int		size_env;
	char	**new_env;

	size_env = ft_arrlen(env);
	new_env = malloc(sizeof(char *) * size_env);
	if (!new_env)
		ft_exitf("malloc issue", 1, NULL, data);
	ft_arrncpy(new_env, env, n);
	ft_arrcpy(new_env + n, env + (n + 1));
	new_env[size_env - 1] = NULL;
	ft_arrfree(data->export);
	data->export = new_env;
}

// have to free the old env if it's a malloc env
void	ft_unset_env(char **env, int n, t_minishell *data)
{
	int		size_env;
	char	**new_env;

	size_env = ft_arrlen(env);
	new_env = malloc(sizeof(char *) * size_env);
	if (!new_env)
		ft_exitf("malloc issue", 1, NULL, data);
	ft_arrncpy(new_env, env, n);
	ft_arrcpy(new_env + n, env + (n + 1));
	new_env[size_env - 1] = NULL;
	ft_arrfree(data->env);
	data->env = new_env;
}

static int	ft_check_unset_error(t_minishell *data, t_commands *c_cmd)
{
	if (!data || !c_cmd)
		return (1);
	if (c_cmd->option)
	{
		data->exit_code = 2;
		ft_write_error("unset: invalid option");
		return (1);
	}
	if (!c_cmd->arg)
		return (1);
	return (0);
}

void	ft_unset(t_minishell *data, t_commands *c_cmd)
{
	int	i;
	int	n;

	if (ft_check_unset_error(data, c_cmd) == 1)
		return ;
	i = 0;
	n = 0;
	while (c_cmd->arg[i])
	{
		if (ft_strchr(c_cmd->arg[i], '='))
		{
			i++;
			continue ;
		}
		n = ft_lfor_var(data->export, c_cmd->arg[i]);
		if (n != -1)
			ft_unset_export(data->export, n, data);
		n = ft_lfor_var(data->env, c_cmd->arg[i]);
		if (n != -1)
			ft_unset_env(data->env, n, data);
		i++;
	}
}
