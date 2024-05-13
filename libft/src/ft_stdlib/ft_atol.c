/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:04:34 by mbriand           #+#    #+#             */
/*   Updated: 2024/04/02 18:04:34 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *s)
{
	long		nbr;
	const char	*sign;
	int			digit;	

	nbr = 0;
	sign = s;
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
	{
		digit = *s - '0';
		if ((((LONG_MAX / 10 == nbr) && digit > LONG_MAX % 10)
				|| (LONG_MAX / 10 < nbr)) && *sign != '-')
			return (LONG_MAX);
		if ((((LONG_MIN / 10 == -nbr) && - digit < LONG_MIN % 10)
				|| (LONG_MIN / 10 > -nbr)) && *sign == '-')
			return (LONG_MIN);
		nbr *= 10;
		nbr += (*s) - 48;
		s++;
	}
	if (*sign == '-')
		nbr *= -1;
	return (nbr);
}
