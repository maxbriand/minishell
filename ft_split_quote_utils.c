/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:48:04 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/21 18:48:35 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_define_on_quote(char *str, int i, bool *on_quote)
{
	if (str[i] == '\'' && on_quote[0] == false && on_quote[1] == false)
	{
		on_quote[0] = true;
		return (true);
	}
	else if (str[i] == '\'' && on_quote[0] == true && on_quote[1] == false)
	{
		on_quote[0] = false;
		return (true);
	}
	if (str[i] == '\"' && on_quote[0] == false && on_quote[1] == false)
	{
		on_quote[1] = true;
		return (true);
	}
	else if (str[i] == '\"' && on_quote[0] == false && on_quote[1] == true)
	{
		on_quote[1] = false;
		return (true);
	}
	return (false);
}
