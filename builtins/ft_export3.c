/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:58:13 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/09 00:49:53 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_modify_line(t_minishell *data, char *var, int n)
{
	free(data->env[n]);
	data->env[n] = ft_strdup(var);
	if (!data->env[n])
		ft_exitf("malloc issue", 1, NULL, data);
}

static void	ft_add_line(t_minishell *data, char *var)
{
	char	**new_env;
	int		lnew_env;

	lnew_env = ft_arrlen(data->env) + 1 + 1;
	new_env = malloc(sizeof(char *) * lnew_env);
	if (!new_env)
		ft_exitf("malloc issue", 1, NULL, data);
	ft_arrcpy(new_env, data->env);
	new_env[lnew_env - 2] = ft_strdup(var);
	if (!new_env[lnew_env - 2])
		ft_exitf("malloc issue", 1, NULL, data);
	new_env[lnew_env - 1] = NULL;
	ft_arrfree(data->env);
	data->env = new_env;
}

void	ft_export_env(t_minishell *data, char *var)
{
	int	n;

	n = ft_lfor_var(data->env, var);
	if (n == -1)
		ft_add_line(data, var);
	else
		ft_modify_line(data, var, n);
}
