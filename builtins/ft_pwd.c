/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:52:20 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/10 17:52:28 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pwd(t_minishell *data, int i)
{
	char	*buf;
	char	*err_buf;
	size_t	size;

	buf = NULL;
	err_buf = NULL;
	size = 0;
	while (err_buf == NULL)
	{
		buf = malloc(sizeof(char) * size);
		if (!buf)
			ft_exitf("malloc issue", 1, NULL, data);
		err_buf = getcwd(buf, size);
		if (err_buf == NULL)
			free(buf);
		size++;
	}
	ft_printf("%s\n", buf);
	if (i == 0)
		free(buf);
	else
		return (buf);
	return (NULL);
}
