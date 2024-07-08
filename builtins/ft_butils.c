/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_butils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:49:24 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/09 00:49:17 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lfor_var(char **arr, char *var)
{
	int	i;
	int	lvar;

	if (ft_strchr(var, '=') != 0)
		lvar = ft_strchr(var, '=') - var;
	else
		lvar = ft_strlen(var);
	i = 0;
	while (arr[i])
	{
		if (ft_strncmp(arr[i], var, lvar) == 0)
		{
			if (arr[i][lvar] == '=' || arr[i][lvar] == '\0')
				return (i);
		}
		i++;
	}
	return (-1);
}

char	*ft_get_env_var(char **env, char *var)
{
	int	len;

	while (*env)
	{
		len = (int)(ft_strchr(*env, '=') - *env);
		if (ft_strncmp(*env, var, len) == 0 && (int) ft_strlen(var) == len)
			return (ft_strchr(*env, '=') + 1);
		env++;
	}
	return (NULL);
}
