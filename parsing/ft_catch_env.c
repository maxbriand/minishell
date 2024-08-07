/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_catch_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:39:19 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/05 06:12:46 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_catch_env(char **envp, char *str, t_utils *utils)
{
	int		y;
	char	*path;

	y = 0;
	path = NULL;
	if (!str)
		ft_ultimate_free_exit(utils, NULL, NULL, NULL);
	while (envp[y] != NULL)
	{
		if (ft_strncmp(envp[y], str, ft_strlen(str)) == 0
			&& envp[y][ft_strlen(str)] == '=')
		{
			path = ft_strdup(&envp[y][ft_strlen(str) + 1]);
			if (!path)
				ft_ultimate_free_exit(utils, NULL, NULL, NULL);
			free(str);
			return (path);
		}
		y++;
	}
	free(str);
	return (path);
}
