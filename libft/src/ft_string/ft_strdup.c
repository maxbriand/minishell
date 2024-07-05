/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 23:25:27 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/05 09:08:09 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Take only src and create dst
char	*ft_strdup(const char *s)
{
	char	*sdup;

	sdup = malloc(ft_strlen(s) + 1);
	if (sdup == NULL)
		return (NULL);
	ft_strlcpy(sdup, s, ft_strlen(s) + 1);
	return (sdup);
}
