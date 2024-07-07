/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 19:51:03 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/07 21:32:23 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_env(t_minishell *data, t_utils *utils, char **env)
{
	utils->mini = data;
	if (!data->env)
		data->env = ft_strdup_array(env, utils);
	if (!data->env)
		ft_ultimate_free_exit(utils, NULL, NULL, NULL);
}
