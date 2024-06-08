/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote_ignore.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 23:22:30 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/08 23:19:30 by gmersch          ###   ########.fr       */
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
		exit (1);//mayday eerror
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

//need to initialize the two booleen on false or valgrind error
static void	ft_split_parsing(char *str, bool *on_quote, char **result, char c)
{
	int		y;
	int		i;
	int		last_split;

	y = 0;
	i = 0;
	last_split = 0;
	if (str[i] == c)
	{
		result[0] = split_here(str, &i, &last_split, c);
		y++;
	}
	while (str[i] == c)
		i++;
	last_split = i;
	while (str[i])
	{
		if (on_quote[0] == false && on_quote[1] == false && str[i] == c)
		{
			result[y] = split_here(str, &i, &last_split, c);
			y++;
		}
		else
		{
			ft_define_on_quote(str, i, on_quote);
			i++;
		}
	}
	result[y] = split_here(str, &i, &last_split, c);
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
		exit(1); //mayday error !
	on_quote[0] = false;
	on_quote[1] = false;
	ft_split_parsing(str, on_quote, result, c);
	//if (result[0] == NULL)
	//	return (NULL); why did i put this protection ?? useful ??
	return (result);
}
