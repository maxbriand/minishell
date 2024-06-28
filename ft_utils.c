/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:40:36 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/28 16:56:42 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_only_space(char *str)
{
	int	i;

	i = 0;
	if (str[0] == ' ')
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

bool	ft_is_s1_before(char *str1, char *str2)
{
	char	*alpha;
	int		s1;
	int		s2;
	int		i;

	alpha = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz";
	i = 0;
	while (str1[i] && str2[i])
	{
		s1 = ft_strchr(alpha, str1[i]) - alpha;
		s2 = ft_strchr(alpha, str2[i]) - alpha;
		if (s1 < s2)
			return (true);
		else if (s2 < s1)
			return (false);
		i++;
	}
	return (s1 < s2);
}

size_t	ft_better_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}
