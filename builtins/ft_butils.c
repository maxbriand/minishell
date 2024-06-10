/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_butils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:49:24 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/10 18:58:57 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// return index from 0 to the var in env or export
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

// Find the variable in env
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
