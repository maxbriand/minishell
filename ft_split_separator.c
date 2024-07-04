/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_separator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 23:22:30 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/04 06:35:44 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_splt_exec(int *i, char *str, bool *on_quote, t_utils *utils)
{
	if (ft_is_sep(str[*i], utils->sep))
	{
		while (ft_is_sep(str[*i], utils->sep))
		{
			ft_define_on_quote(str, *i, on_quote);
			(*i)++;
		}
	}
	utils->last_split_sep = *i;
	if (str[*i] == '<' || str[*i] == '>')
	{
		ft_define_on_quote(str, *i, on_quote);
		*i = *i + 1;
	}
}

static char	*ft_split_here(char *str, int *i, bool *on_quote, t_utils *utils)
{
	char	*result;
	int		j;
	int		len;

	len = *i - utils->last_split_sep;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		ft_ultimate_free_exit(utils, NULL, NULL);
	j = 0;
	while (utils->last_split_sep < *i)
	{
		result[j] = str[utils->last_split_sep];
		j++;
		utils->last_split_sep += 1;
	}
	result[j] = '\0';
	ft_splt_exec(i, str, on_quote, utils);
	return (result);
}

static int	ft_find_split(int *i, bool *on_quote, char *sep, char *str)
{
	if (*i > 0 && on_quote[0] == false && on_quote[1] == false
		&& (ft_is_sep(str[*i], sep) || ((str[*i] == '<' || str[*i] == '>')
				&& (str[*i - 1] != '<' && str[*i - 1] != '>'
					&& ft_is_sep(str[*i - 1], sep) == 0))))
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
	char *str, bool *on_quote, t_utils *utils)
{
	int		i;
	char	*splt;
	char	**res;

	i = 0;
	utils->res_splt_s = NULL;
	ft_define_int(&i, &utils->last_split_sep, str, utils->sep);
	while (str[i])
	{
		if (ft_find_split(&i, on_quote, utils->sep, str))
		{
			splt = ft_split_here(str, &i, on_quote, utils);
			utils->res_splt_s = ft_addback_free(utils->res_splt_s, splt);
			if (!utils->res_splt_s)
				ft_ultimate_free_exit(utils, NULL, NULL);
		}
	}
	if (ft_is_sep(str[i - 1], utils->sep) == false)
	{
		splt = ft_split_here(str, &i, on_quote, utils);
		utils->res_splt_s = ft_addback_free(utils->res_splt_s, splt);
		if (!utils->res_splt_s)
			ft_ultimate_free_exit(utils, NULL, NULL);
	}
	res = ft_strdup_array(utils->res_splt_s, utils);
	return (res);
}

char	**ft_split_separator(char *str, t_utils *utils)
{
	char	**result;
	bool	on_quote[2];

	utils->sep = ft_strjoin(" ", "\t");
	if (!utils->sep)
		ft_ultimate_free_exit(utils, NULL, NULL);
	on_quote[0] = false;
	on_quote[1] = false;
	result = ft_split_parsing(str, on_quote, utils);
	free(utils->sep);
	utils->sep = NULL;
	return (result);
}
