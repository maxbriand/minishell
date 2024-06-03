/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_separator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 23:22:30 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/03 17:51:16 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_sep(char c, char *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (sep[i] == c)
			return (true);
		i++;
	}
	return (false);
}
//je doos gerer les <> sepqremenbt poiur les sepqrqrteur
//if celui davant n'est pas un sep et que i est plus grqnd aue 1 ou 0jsp,
//alors on cute sur les <>
static int	count_cut(char *str, bool *on_quote, char *sep)
{
	int		i;
	int		nb_cut;

	i = 0;
	nb_cut = 0;
	while (is_sep(str[i], sep) == true)
		i++;
	while (str[i])
	{
		if (i > 0 && on_quote[0] == false && on_quote[1] == false
			&& (is_sep(str[i], sep) == true || str[i] == '<' || str[i] == '>'))
		{
			if (((str[i] == '<') || (str[i] == '>')) && is_sep(str[i - 1], sep) == false)
			{
				nb_cut++;
				while (str[i] == '<' || str[i] == '>')
					i++;
			}
			else
			{
				if (str[i] == '<' || str[i] == '>')
				{
					while (str[i] == '<' || str[i] == '>')
						i++;
				}
				else
				{
					if (is_sep(str[i], sep))
					{
						nb_cut++;
						while (is_sep(str[i], sep))
							i++;
					}
					else
						i++;
				}
			}
		}
		else
		{
			ft_define_on_quote(str, i, on_quote);
			//if (str[i] == '<' || str[i] == '>')
			//{
			//	while (str[i] == '<' || str[i] == '>')
			//		i++;
			//}
			//else
			i++;
		}
		//printf("%d = i\n", i);
		//printf("%d = count\n", nb_cut);
	}
	if (is_sep(str[i - 1], sep) == false)
		nb_cut++;
	//printf("%d = count FINAL\n", nb_cut);
	return (nb_cut);
}

static char	*split_here(char *str, int *i, int *last_split, bool *on_quote)
{
	char	*result;
	int		j;
	int		len;
	char	*sep;

	len = *i - *last_split;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		exit (1);//mayday error
	sep = ft_strdup(" ");
	sep = ft_charaddback(&sep, '\t');
	j = 0;
	while (*last_split < *i)
	{
		result[j] = str[*last_split];
		j++;
		*last_split = *last_split + 1;
	}
	result[j] = '\0';
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
	return (result);
}

//need to initialize the two booleen on false or valgrind error
static void	ft_split_parsing(char *str, char *sep, char **result)
{
	int		y;
	int		i;
	int		last_split;
	bool	on_quote[2];

	y = 0;
	i = 0;
	on_quote[0] = false;
	on_quote[1] = false;
	while (is_sep(str[i], sep))
		i++;
	last_split = i;
	while (str[i])
	{
		if (i > 0 && on_quote[0] == false && on_quote[1] == false && (is_sep(str[i], sep)
		|| ((str[i] == '<' || str[i] == '>') && (str[i - 1] != '<' && str[i - 1] != '>' && is_sep(str[i - 1], sep) == 0))))
		{

			result[y] = split_here(str, &i, &last_split, on_quote);
			if (str[i] == '\0')
				return ;
			y++;
		}
		else
		{
			ft_define_on_quote(str, i, on_quote);
			i++;
		}
		//printf("\n%d = onquote\n", on_quote[0]);
		//printf("%d = ondquote\n", on_quote[1]);
	}
	if (is_sep(str[i - 1], sep) == false)
		result[y] = split_here(str, &i, &last_split, on_quote);
}

//a split but when char priority is found, seach for the next char priority
//and then split, and continue with char c.
char	**ft_split_separator(char *str)
{
	int		nb_cut;
	char	**result;
	char	*sep;
	bool	on_quote[2];

	sep = ft_strdup(" ");
	sep = ft_charaddback(&sep, '\t');
	on_quote[0] = false;
	on_quote[1] = false;
	nb_cut = count_cut(str, on_quote, sep);
	//printf("%d = count\n", nb_cut);
	result = ft_calloc(nb_cut + 1, sizeof(char *));
	if (!result)
		exit(1); //mayday error !
	ft_split_parsing(str, sep, result);
	free(sep);
	return (result);
}
