/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:39:37 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/28 16:59:03 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_count_quote(bool *on_quote, char *str, int i, int nb_quote[2])
{
	if (!on_quote[0] && str[i] == '\'')
	{
		if (str[i] == '\'' && (!on_quote[0] && !on_quote[1]))
			nb_quote[0]++;
		ft_define_on_quote(str, i, on_quote);
	}
	else if (on_quote[0] && str[i] == '\'')
	{
		ft_define_on_quote(str, i, on_quote);
		if (str[i] == '\'' && (!on_quote[0] && !on_quote[1]))
			nb_quote[0]++;
	}
	else if (!on_quote[1] && str[i] == '\"')
	{
		if (str[i] == '\"' && (!on_quote[0] && !on_quote[1]))
			nb_quote[1]++;
		ft_define_on_quote(str, i, on_quote);
	}
	else if (on_quote[1] && str[i] == '\"')
	{
		ft_define_on_quote(str, i, on_quote);
		if (str[i] == '\"' && (!on_quote[0] && !on_quote[1]))
			nb_quote[1]++;
	}
}

bool	ft_is_error_quote(char *str)
{
	int		i;
	int		nb_quote[2];
	bool	on_quote[2];

	on_quote[0] = false;
	on_quote[1] = false;
	i = 0;
	nb_quote[0] = 0;
	nb_quote[1] = 0;
	while (str[i])
	{
		ft_count_quote(on_quote, str, i, nb_quote);
		i++;
	}
	if (nb_quote[0] % 2 == 1 || nb_quote[1] % 2 == 1)
	{
		//MAYDAY
		ft_printf("minishell: Error syntax: Quote not closed");
		return (true);
	}
	return (false);
}
