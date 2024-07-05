/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_separator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 23:22:30 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/05 10:04:19 by gmersch          ###   ########.fr       */
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

static char	*ft_split_here(char **str, int **ij, bool *on_quote, t_utils *utils)
{
	char	*result;
	int		j;
	int		len;

	len = *ij[0] - utils->last_split_sep;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		ft_ultimate_free_exit(utils, str, (char *)utils->buf_p, NULL);
	j = 0;
	while (utils->last_split_sep < *ij[0])
	{
		result[j] = str[*ij[1]][utils->last_split_sep];
		j++;
		utils->last_split_sep += 1;
	}
	result[j] = '\0';
	ft_splt_exec(&(*ij[0]), str[*ij[1]], on_quote, utils);
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
	char **str, int j, bool *on_quote, t_utils *utils)
{
	int		i;
	int		*ij[2];

	ij[0] = &i;
	ij[1] = &j;
	i = 0;
	ft_define_int(&i, &utils->last_split_sep, str[j], utils->sep);
	while (str[j][i])
	{
		if (ft_find_split(&i, on_quote, utils->sep, str[j]))
		{
			utils->res_splt_s = ft_addback_free(utils->res_splt_s,
					ft_split_here(str, ij, on_quote, utils));
			if (!utils->res_splt_s)
				ft_ultimate_free_exit(utils, str, (char *)utils->buf_p, NULL);
		}
	}
	if (ft_is_sep(str[j][i - 1], utils->sep) == false)
	{
		utils->res_splt_s = ft_addback_free(utils->res_splt_s,
				ft_split_here(str, ij, on_quote, utils));
		if (!utils->res_splt_s)
			ft_ultimate_free_exit(utils, str, (char *)utils->buf_p, NULL);
	}
	return (ft_strdup_array(utils->res_splt_s, utils));
}

char	**ft_split_separator(char **str, int i, t_utils *utils)
{
	char	**result;
	bool	on_quote[2];

	utils->sep = ft_strjoin(" ", "\t");
	if (!utils->sep)
		ft_ultimate_free_exit(utils, str, (char *)utils->buf_p, NULL);
	on_quote[0] = false;
	on_quote[1] = false;
	utils->res_splt_s = NULL;
	result = ft_split_parsing(str, i, on_quote, utils);
	ft_free_array(utils->res_splt_s);
	utils->res_splt_s = NULL;
	free(utils->sep);
	utils->sep = NULL;
	return (result);
}
