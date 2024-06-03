/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:39:09 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/03 19:54:35 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*just_name_env(char *arg, int start, bool *on_quote)
{
	int	end;
	char *result;

	if (arg[start] == '$')
		start++;
	end = start;
	while (arg[end])
	{
		if (!ft_isalpha(arg[end]) || (arg[end] != '\'' && on_quote[0]) || (arg[end] == '\"' && on_quote[1]))
			break ;
		end++;
	}
	result = ft_substr(arg, start, end - start);
	return (result);
}

static char	*apply_var_env(char **arg, int i, t_minishell *mini, t_pars *p)
{
	char	*var_env;
	bool	on_quote[2];
	char	*result;
	bool	can_copy;
	int		j;

	on_quote[0] = false;
	on_quote[1] = false;
	result = NULL;
	j = 0;
	while (arg[i][j])
	{
		if (ft_define_on_quote(arg[i], j, on_quote) == true)
			can_copy = false;
		else
			can_copy = true;
		if (arg[i][j] == '$' && (ft_isalnum(arg[i][j + 1]) || arg[i][j + 1] == '\"' || arg[i][j + 1] == '\'') && !on_quote[0] && p->next_is_hd_stop == false)
		{
			p->is_expand[i] = true;
			if (arg[i][j] == '$' && arg[i][j + 1] == '?')
			{
				result = ft_strjoin_free(result, ft_itoa(mini->exit_code));
				j++;
			}
			else
			{
				var_env = catch_env(mini->env, just_name_env(arg[i], j, on_quote));
				result = ft_strjoin_free(result, var_env);
			}
			j++;
			while (arg[i][j] && (ft_isalnum(arg[i][j]) || arg[i][j] == '_'))
				j++;
		}
		else
		{
			p->is_expand[i] = false;
			if (can_copy == true)
				result = ft_charaddback(&result, arg[i][j]);
			j++;
		}
	}
	return (result);
}

//trying to norm but i didnt win this fight...
// static bool	is_dollar(char *arg, char **result, t_minishell *mini, char *name_env)
// {
// 	char	*var_env;

// 	if (arg[0] == '$' && arg[1] == '?')
// 	{
// 		*result = ft_strjoin_free(*result, ft_itoa(mini->exit_code));
// 		return (true);
// 	}
// 	else
// 	{
// 		var_env = catch_env(mini->env, name_env);
// 		*result = ft_strjoin_free(*result, var_env);
// 	}
// 	return (false);
// }

// static char	*apply_var_env(char **arg, int i, t_minishell *mini, t_pars *p)
// {
// 	bool	on_quote[2];
// 	char	*result;
// 	bool	can_copy;
// 	int		j;
// 	char	*name_env;

// 	on_quote[0] = false;
// 	on_quote[1] = false;
// 	result = NULL;
// 	j = 0;
// 	while (arg[i][j])
// 	{
// 		if (ft_define_on_quote(arg[i], j, on_quote) == true)
// 			can_copy = false;
// 		else
// 			can_copy = true;
// 		if (arg[i][j] == '$' && !on_quote[0] && p->next_is_hd_stop == false)
// 		{
// 			p->is_expand[i] = true;
// 			name_env = just_name_env(*arg, j, on_quote);
// 			if (is_dollar(&arg[i][j], &result, mini, name_env) == true) //
// 				j++;
// 			j++;
// 			while (*arg[j] && (ft_isalnum(*arg[j]) || *arg[j] == '_'))
// 				j++;
// 		}
// 		else
// 		{
// 			p->is_expand[i] = false;
// 			if (can_copy == true)
// 				result = ft_charaddback(&result, arg[i][j]);
// 			j++;
// 		}
// 	}
// 	return (result);
// }

//pas backslash mais dollar
void	remove_quote_bslash(char **str, int i, t_minishell *mini, t_pars *p)
{
	int		j;
	char	*buf;

	buf = NULL;
	j = 0;
	str[i] = apply_var_env(str, i, mini, p);//je dois faire par rapoirt auchar
	if (str[i] == NULL)
	{
		str[i] = malloc(sizeof(char) * 1);
		if (!str[i])
			exit (1); //mayday error
		str[i][0] = '\0';
	}
	else
	{
		while (str[i][j]) // are we shure that str(i(j existe ?
		{
			buf = ft_charaddback(&buf, str[i][j]);
			j++;
		}
		free(str[i]);
		str[i] = ft_strdup(buf);
		free(buf);
	}
}
