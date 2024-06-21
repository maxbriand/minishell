/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote_ignore.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 23:22:30 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/21 19:58:23 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_cut(char *str, char c, bool *on_quote)
{
	int		i;
	int		nb_cut;

	i = 0;
	nb_cut = 0;
	if (str[i] == c)
		nb_cut++;
	while (str[i] == c)
		i++;
	while (str[i])
	{
		if (on_quote[0] == false && on_quote[1] == false && str[i] == c)
		{
			nb_cut++;
			while (str[i] == c)
				i++;
		}
		else
		{
			ft_define_on_quote(str, i, on_quote);
			i++;
		}
	}
	nb_cut++;
	return (nb_cut);
}

static char	*split_here(char *str, int *i, int *last_split, char c)
{
	char	*result;
	int		j;

	if (*i - *last_split == 0)
		return (NULL);
	result = malloc(sizeof(char) * (*i - *last_split + 1));
	if (!result)
		return (NULL);
	j = 0;
	while (*last_split < *i)
	{
		result[j] = str[*last_split];
		j++;
		*last_split = *last_split + 1;
	}
	result[j] = '\0';
	while (str[*i] == c)
		*i = *i + 1;
	*last_split = *i;
	return (result);
}

static char	*ft_should_split(bool *on_quote, int *i, char *str, int *last_split)
{
	char	*result;

	result = NULL;
	if (on_quote[0] == false && on_quote[1] == false && str[*i] == '|')
	{
		result = split_here(str, i, last_split, '|');
		if (!result)
			return (NULL);
	}
	else
	{
		ft_define_on_quote(str, *i, on_quote);
		(*i)++;
	}
	return (result);
}

//need to initialize the two booleen on false or valgrind error
static int	ft_split_parsing(char *str, bool *on_quote, char **result, int i)
{
	int		y;
	int		last_split;

	y = 0;
	last_split = 0;
	if (str[i] == '|')
	{
		result[0] = split_here(str, &i, &last_split, '|');
		if (!result[0])
			return (0);
		y++;
	}
	while (str[i] == '|')
		i++;
	last_split = i;
	while (str[i])
	{
		result[y] = ft_should_split(on_quote, &i, str, &last_split);
		if (result[y])
			y++;
	}
	result[y] = split_here(str, &i, &last_split, '|');
	if (!result[0])
		return (1);
	return (0);
}

//a split but when char priority is found, seach for the next char priority
//and then split, and continue with char c.
char	**ft_split_quote_ignore(char *str, char c)
{
	int		nb_cut;
	char	**result;
	bool	on_quote[2];

	on_quote[0] = false;
	on_quote[1] = false;
	nb_cut = count_cut(str, c, on_quote);
	result = ft_calloc(nb_cut + 1, sizeof(char *));
	if (!result)
		return (NULL);
	on_quote[0] = false;
	on_quote[1] = false;
	if (ft_split_parsing(str, on_quote, result, 0) == 1)
		return (NULL);
	return (result);
}
