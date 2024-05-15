/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 23:22:30 by mbriand           #+#    #+#             */
/*   Updated: 2024/05/15 21:33:37 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

//need to be rename
//a split but when char priority is found, seach for the next char priority and then split, and continue with char c.
static int	count_cut(char *str, char c, char quote, char d_quote)
{
	int		i;
	int		nb_cut;
	bool	on_quote;
	bool	on_dquote;

	i = 0;
	nb_cut = 0;
	on_dquote = false;
	on_quote = false;
	while (str[i])
	{
		//I cut between space when it's not under quote
		if (on_quote == false && on_dquote == false && str[i] == c)
		{
			nb_cut++;
			while (str[i] == c)
				i++;
		}
		//define if we are in a type of quote or not
		if (str[i] == quote && on_quote == false && on_dquote == false)
			on_quote = true;
		else if (str[i] == quote && on_quote == true && on_dquote == false)
			on_quote = false;
		if (str[i] == d_quote && on_quote == false && on_dquote == false)
			on_dquote = true;
		else if (str[i] == d_quote && on_quote == false && on_dquote == true)
			on_dquote = false;
		i++;
	}
	return (nb_cut);
}


char	**ft_split_parsing(char *str, char c, char quote, char d_quote)
{
	int	nb_cut;

	nb_cut = count_cut(str, c, quote, d_quote)

}
