/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:39:09 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/28 17:48:24 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_just_name_env(char *arg, int start, bool *on_quote)
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
	return (result);
}

static void	ft_create_result(bool *on_quote, char **result, char *arg, int *j)
{
	if (on_quote[2] == true)
		*result = ft_charaddback(result, arg[*j]);
	(*j)++;
}

static int	ft_in_if(
	char *arg, bool *on_quote, char **result, t_minishell *mini)
{
	char	*var_env;
	int		j;

	j = 0;
	if (arg[j] == '$' && arg[j + 1] == '?')
	{
		*result = ft_strjoin_free(*result, ft_itoa(mini->exit_code));
		j += 2;
	}
	else
	{
		var_env = ft_catch_env(mini->env, ft_just_name_env(arg, j, on_quote));
		*result = ft_strjoin_free(*result, var_env);
		j++;
		while (arg[j] && (ft_isalnum(arg[j]) || arg[j] == '_'))
			j++;
	}
	return (j);
}

static char	*ft_apply_var_env(char *arg, int i, t_minishell *mini, t_pars *p)
{
	bool	on_quote[3];
	char	*result;
	int		j;

	on_quote[0] = false;
	on_quote[1] = false;
	result = NULL;
	j = 0;
	p->is_expand[i] = false;
	while (arg[j])
	{
		on_quote[2] = true;
		if (ft_define_on_quote(arg, j, on_quote) == true)
			on_quote[2] = false;
		if (arg[j] == '$' && (ft_isalnum(arg[j + 1]) || arg[j + 1] == '?'
				|| ((arg[j + 1] == '\"' || arg[j + 1] == '\'') && !on_quote[0]
					&& !on_quote[1])) && !on_quote[0] && !p->next_is_hd_stop)
		{
			p->is_expand[i] = true;
			j += ft_in_if(&arg[j], on_quote, &result, mini);
		}
		else
			ft_create_result(on_quote, &result, arg, &j);
	}
	return (result);
}

int	ft_remove_quote_bslash(char **str, int i, t_minishell *mini, t_pars *p)
{
	int		j;
	char	*buf;

	j = 0;
	buf = ft_apply_var_env(str[i], 0, mini, p);
	free(str[i]);
	str[i] = buf;
	buf = NULL;
	if (str[i] == NULL)
	{
		str[i] = malloc(sizeof(char) * 1);
		if (!str[i])
			return (1);
		str[i][0] = '\0';
		return (0);
	}
	while (str[i][j])
	{
		buf = ft_charaddback(&buf, str[i][j]);
		j++;
	}
	free(str[i]);
	str[i] = ft_better_strdup_free(buf, buf);
	return (0);
}
