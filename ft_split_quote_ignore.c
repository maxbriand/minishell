/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote_ignore.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 23:22:30 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/05 02:50:18 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_split_here(char *str, int *i, t_utils *utils)
{
	char	*result;
	int		j;
	char	c;

	c = '|';
	if (*i - utils->last_split == 0)
		return (NULL);
	result = malloc(sizeof(char) * (*i - utils->last_split + 1));
	if (!result)
		ft_ultimate_free_exit(utils, NULL, NULL);
	j = 0;
	while (utils->last_split < *i)
	{
		result[j] = str[utils->last_split];
		j++;
		utils->last_split = utils->last_split + 1;
	}
	result[j] = '\0';
	while (str[*i] == c)
		*i = *i + 1;
	utils->last_split = *i;
	return (result);
}

static char	*ft_should_split(bool *on_quote, int *i, char *str, t_utils *utils)
{
	char	*result;

	result = NULL;
	if (on_quote[0] == false && on_quote[1] == false && str[*i] == '|')
	{
		result = ft_split_here(str, i, utils);
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
static int	ft_split_parsing(
			char *str, bool *on_quote, t_utils *utils)
{
	int		y;
	int		i;

	i = 0;
	y = 0;
	if (str[i] == '|')
	{
		utils->res_splt_q[0] = ft_split_here(str, &i, utils);
		if (!utils->res_splt_q[0])
			return (0); //maybe 0, and not 1
		y++;
	}
	while (str[i] == '|')
		i++;
	utils->last_split = i;
	while (str[i])
	{
		utils->res_splt_q[y] = ft_should_split(on_quote, &i, str, utils);
		if (utils->res_splt_q[y])
			y++;
	}
	utils->res_splt_q[y] = ft_split_here(str, &i, utils);
	if (!utils->res_splt_q[y])
		return (1); //maybe 0, and not 1
	return (0);
}

static int	ft_count_cut(char *str, char c, bool *on_quote)
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

//a split but when char priority is found, seach for the next char priority
//and then split, and continue with char c.
char	**ft_split_quote_ignore(char *str, char c, t_utils *utils)
{
	int		nb_cut;
	bool	on_quote[2];
	char	**res;

	res = NULL;
	on_quote[0] = false;
	on_quote[1] = false;
	nb_cut = ft_count_cut(str, c, on_quote);
	utils->res_splt_q = ft_calloc(nb_cut + 1, sizeof(char *));
	if (!utils->res_splt_q)
		ft_ultimate_free_exit(utils, NULL, NULL);
	on_quote[0] = false;
	on_quote[1] = false;
	if (ft_split_parsing(str, on_quote, utils) == 1)
		return (NULL);
	res = ft_strdup_array(utils->res_splt_q, utils);
	ft_free_array(utils->res_splt_q);
	utils->res_splt_q = NULL;
	return (res);
}
