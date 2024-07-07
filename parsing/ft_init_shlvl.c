/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_shlvl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:06:37 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/07 20:10:42 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_shlvl(t_minishell *data, t_utils *utils)
{
	int	i;
	int	shlvl;

	i = 0;
	while (ft_strncmp(data->env[i], "SHLVL", 5))
		i++;
	shlvl = ft_atoi(*(data->env + 6)) + 1;
	free(data->env[i]);
	utils->env_free = i;
	data->env[i] = ft_strjoin_free_s2("SHLVL=", ft_itoa(shlvl), utils);
	utils->env_free = 0;
}
