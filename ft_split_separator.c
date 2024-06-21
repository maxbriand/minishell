/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_separator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 23:22:30 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/21 16:31:47 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	splt_exec(int *last_split, int *i, char *str, bool *on_quote)
{
	char	*sep;

	sep = ft_strdup(" ");
	if (!sep)
		return (1);
	sep = ft_charaddback(&sep, '\t');
	if (is_sep(str[*i], sep))
	{
		while (is_sep(str[*i], sep))
		{
			ft_define_on_quote(str, *i, on_quote);
			(*i)++;
		}
	}
	*last_split = *i;
	if (str[*i] == '<' || str[*i] == '>')
	{
		ft_define_on_quote(str, *i, on_quote);
		*i = *i + 1;
	}
	free(sep);
	return (0);
}

static char	*split_here(char *str, int *i, int *last_split, bool *on_quote)
{
	char	*result;
	int		j;
	int		len;

	len = *i - *last_split;
	result = malloc(sizeof(char) * (len + 1));
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
	if (splt_exec(last_split, i, str, on_quote))
		return (NULL);
	return (result);
}

static int	find_split(int *i, bool *on_quote, char *sep, char *str)
{
	if (*i > 0 && on_quote[0] == false && on_quote[1] == false
		&& (is_sep(str[*i], sep) || ((str[*i] == '<' || str[*i] == '>')
				&& (str[*i - 1] != '<' && str[*i - 1] != '>'
					&& is_sep(str[*i - 1], sep) == 0))))
		return (1);
	else
	{
		ft_define_on_quote(str, *i, on_quote);
		(*i)++;
	}
	return (0);
}

//need to initialize the two booleen on false or valgrind error
static char	**ft_split_parsing(
	char *str, char *sep, char **result, bool *on_quote)
{
	int		i;
	int		last_split;
	char	*splt;

	i = 0;
	result = NULL;
	ft_define_int(&i, &last_split, str, sep);
	while (str[i])
	{
		if (find_split(&i, on_quote, sep, str))
		{
			splt = split_here(str, &i, &last_split, on_quote);
			if (!splt)
				return (NULL);
			result = ft_addback_free(result, splt);
		}
	}
	if (is_sep(str[i - 1], sep) == false)
	{
		splt = split_here(str, &i, &last_split, on_quote);
		if (!splt)
			return (NULL);
		result = ft_addback_free(result, splt);
	}
	return (result);
}

char	**ft_split_separator(char *str)
{
	char	**result;
	char	*sep;
	bool	on_quote[2];

	sep = ft_strdup(" ");
	sep = ft_charaddback(&sep, '\t');
	on_quote[0] = false;
	on_quote[1] = false;
	result = ft_split_parsing(str, sep, NULL, on_quote);
	free(sep);
	return (result);
}
