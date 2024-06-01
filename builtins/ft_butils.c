/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_butils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:49:24 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/01 17:24:26 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Find the variable in env
char	*ft_get_env_var(char **env, char *var)
{
	int	len;
	
	while (*env)
	{
		len = (int) (ft_strchr(*env, '=') - *env);
		if (ft_strncmp(*env, var, len) == 0 && ft_strlen(var) == len)
			return (ft_strchr(*env, '=') + 1);
		env++;
	}
	return (NULL);
}
