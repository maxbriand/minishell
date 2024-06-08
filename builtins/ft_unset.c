/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 22:43:10 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/08 17:54:55 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_unset_export(char **env, int n, t_minishell *data)
// {
// 	int		size_env;
// 	char	**new_env;

// 	size_env = ft_arrlen(env);
// 	new_env = malloc(sizeof(char *) * size_env);
// 	ft_arrncpy(new_env, env, n);
// 	ft_arrcpy(new_env + n, env + (n + 1));
// 	new_env[size_env] = NULL;
// 	if (data->env_malloc == 0)
// 		data->env_malloc = 1;
// 	else
// 		ft_arrfree(data->env);
// 	data->env = new_env; 
// }

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
	new_env[size_env] = NULL;
	if (data->env_malloc == 0)
		data->env_malloc = 1;
	else
		ft_arrfree(data->env);
	data->env = new_env; 
}

void	ft_unset(t_minishell *data, t_commands *p_cmd)
{
	int	i;
	int	n;
	
	if (!data || !p_cmd || !p_cmd->arg)
		return ;
	i = 0;
	n = 0;
	while (p_cmd->arg[i])
	{
		// if there are "=", don't continue
		if (ft_strchr(p_cmd->arg[i], '='))
			continue ;
		// if the var is in env, unset 
		n = ft_lfor_var(data->env, p_cmd->arg[i]);
		if (n != -1)
			ft_unset_env(data->env, n, data);
		// if the var is in export, unset 
		// n = ft_lfor_var(data->export, p_cmd->arg[i]);
		// if (n != -1)
		// 	ft_unset_export(data->export, n, data);			
		i++;
	}
}
