/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:39:09 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/05 02:03:40 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_just_name_env(
		char *arg, int start, bool *on_quote, t_utils *utils)
{
	int		end;
	char	*result;

	if (arg[start] == '$')
		start++;
	end = start;
	while (arg[end])
	{
		if (!ft_isalpha(arg[end]) || (arg[end] != '\'' && on_quote[0])
			|| (arg[end] == '\"' && on_quote[1]))
			break ;
		end++;
	}
	result = ft_substr(arg, start, end - start);
	if (!result)
		ft_ultimate_free_exit(utils, NULL, NULL);
	return (result);
}

static bool	ft_create_result(
	bool *on_quote, char **result, char *arg, t_utils *utils)
{
	bool	res;

	res = false;
	if (on_quote[2] == true)
		*result = ft_charaddback(result, arg[utils->ap_j], utils);
	else
		res = true;
	utils->ap_j++;
	return (res);
}

static int	ft_in_if(
	char *arg, bool *on_quote, char **result, t_utils *utils)
{
	char	*var_env;
	int		j;

	j = 0;
	if (arg[j] == '$' && arg[j + 1] == '?')
	{
		*result = ft_strjoin_free(
				*result, ft_itoa(utils->mini->exit_code), utils);
		j += 2;
	}
	else
	{
		var_env = ft_catch_env(utils->mini->env,
				ft_just_name_env(arg, j, on_quote, utils), utils);
		*result = ft_strjoin_free(*result, var_env, utils);
		j++;
		while (arg[j] && (ft_isalnum(arg[j]) || arg[j] == '_'))
			j++;
	}
	return (j);
}

static char	*ft_apply_var_env(char *arg, int i, t_utils *utils, t_pars *p)
{
	bool	on_quote[3];
	char	*res;

	on_quote[0] = false;
	on_quote[1] = false;
	res = NULL;
	p->is_expand[i] = false;
	while (arg[utils->ap_j])
	{
		on_quote[2] = true;
		if (ft_define_on_quote(arg, utils->ap_j, on_quote) == true)
			on_quote[2] = false;
		if (arg[utils->ap_j] == '$'
			&& (ft_isalnum(arg[utils->ap_j + 1]) || arg[utils->ap_j + 1] == '?'
				|| ((arg[utils->ap_j + 1] == '\"'
						|| arg[utils->ap_j + 1] == '\'') && !on_quote[0]
					&& !on_quote[1])) && !on_quote[0] && !p->next_is_hd_stop)
		{
			p->is_expand[i] = true;
			utils->ap_j += ft_in_if(&arg[utils->ap_j], on_quote, &res, utils);
		}
		else
			p->was_quote = ft_create_result(on_quote, &res, arg, utils);
	}
	return (res);
}

int	ft_remove_quote_bslash(int i, t_utils *utils, t_pars *p)
{
	int		j;
	char	*buf;

	j = 0;
	buf = ft_apply_var_env(p->spl_cmd[i], i, utils, p);
	free(p->spl_cmd[i]);
	p->spl_cmd[i] = buf;
	buf = NULL;
	if (p->spl_cmd[i] == NULL)
	{
		p->spl_cmd[i] = malloc(sizeof(char) * 1);
		if (!p->spl_cmd[i])
			return (1);
		p->spl_cmd[i][0] = '\0';
		return (0);
	}
	while (p->spl_cmd[i][j])
	{
		buf = ft_charaddback(&buf, p->spl_cmd[i][j], utils);
		j++;
	}
	free(p->spl_cmd[i]);
	p->spl_cmd[i] = ft_better_strdup_free(buf, buf, utils);
	return (0);
}
