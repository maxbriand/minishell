/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:39:09 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/10 17:24:01 by gmersch          ###   ########.fr       */
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

static void create_result(bool *on_quote, char **result, char *arg, int *j)
{
	on_quote[3] = false;
	if (on_quote[2] == true)
		*result = ft_charaddback(result, arg[*j]);
	(*j)++;
}

static int	inside_if(char *arg,  bool *on_quote, char **result, t_minishell *mini)
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
		var_env = catch_env(mini->env, just_name_env(arg, j, on_quote));
		*result = ft_strjoin_free(*result, var_env);
		j++;
		while (arg[j] && (ft_isalnum(arg[j]) || arg[j] == '_')) //mayday need really only isalnum ????
			j++;
	}
	return (j);
}

static char	*apply_var_env(char *arg, int i, t_minishell *mini, t_pars *p)
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
		if (ft_define_on_quote(arg, j, on_quote) == true)
			on_quote[2] = false;
		else
			on_quote[2] = true;
		if (arg[j] == '$' && (ft_isalnum(arg[j + 1]) || arg[j + 1] == '?' || ((arg[j + 1] == '\"' || arg[j + 1] == '\'') && (!on_quote[0] && !on_quote[1]))) && !on_quote[0] && p->next_is_hd_stop == false)
		{
			p->is_expand[i] = true; // maydayyy expoand in quote
			j += inside_if(&arg[j], on_quote, &result, mini);
		}
		else
			create_result(on_quote, &result, arg, &j);
	}
	free(arg);
	return (result);
}

//pas backslash mais dollar
void	remove_quote_bslash(char **str, int i, t_minishell *mini, t_pars *p)
{
	int		j;
	char	*buf;

	buf = NULL;
	j = 0;
	str[i] = apply_var_env(str[i], 0, mini, p);//je dois faire par rapoirt auchar
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

//char	*just_name_env(char *arg, int start, bool *on_quote)
// {
// 	int	end;
// 	char *result;

// 	if (arg[start] == '$')
// 		start++;
// 	end = start;
// 	while (arg[end])
// 	{
// 		if ((!ft_isalpha(arg[end]) && arg[end] != '_') || (arg[end] != '\'' && on_quote[0]) || (arg[end] == '\"' && on_quote[1]))
// 			break ;
// 		end++;
// 	}
// 	result = ft_substr(arg, start, end - start);
// 	return (result);
// }

// static char	*create_result(bool *on_quote, char **result, char *arg, bool *is_expand)
// {
// 	*is_expand = false;
// 	if (on_quote[2] == true)
// 		*result = ft_charaddback(result, *arg);
// 	(*arg)++;
// 	return (arg);
// }

// static int	inside_if(char *arg,  bool *on_quote, char **result, t_minishell *mini)
// {
// 	char	*var_env;
// 	int		j;

// 	on_quote[3] = true;
// 	j = 0;
// 	if (arg[j] == '$' && arg[j + 1] == '?')
// 	{
// 		*result = ft_strjoin_free(*result, ft_itoa(mini->exit_code));
// 		j += 2;
// 	}
// 	else
// 	{
// 		var_env = catch_env(mini->env, just_name_env(arg, j, on_quote));
// 		*result = ft_strjoin_free(*result, var_env);
// 		j++;
// 		while (arg[j] && (ft_isalnum(arg[j]) || arg[j] == '_')) //mayday need really only isalnum ????
// 			j++;
// 	}
// 	return (j);
// }

// static char	*apply_var_env(char *arg, int i, t_minishell *mini, t_pars *p)
// {
// 	bool	on_quote[3];
// 	char	*result;
// 	int		j;
// 	bool	is_expand;

// 	on_quote[0] = false;
// 	on_quote[1] = false;
// 	result = NULL;
// 	is_expand = false;
// 	j = 0;
// 	while (arg[j])
// 	{
// 		if (ft_define_on_quote(arg, j, on_quote) == true)
// 			on_quote[2] = false;
// 		else
// 			on_quote[2] = true;
// 		if (arg[j] == '$' && (ft_isalnum(arg[j + 1]) || arg[j + 1] == '?' || ((arg[j + 1] == '\"' || arg[j + 1] == '\'') && (!on_quote[0] && !on_quote[1]))) && !on_quote[0] && p->next_is_hd_stop == false)
// 		{
// 			is_expand = true;
// 			j = inside_if(&arg[j], on_quote, &result, mini);
// 		}
// 		else
// 			j += create_result(on_quote, &result, &arg[j], &is_expand) - (arg + j);
// 			//j += create_result(on_quote, &result, &arg[j], &is_expand) - *arg + j;
// 	}
// 	p->is_expand[i] = is_expand;
// 	//free(arg);
// 	return (result);
// }

// //pas backslash mais dollar
// void	remove_quote_bslash(char **str, int i, t_minishell *mini, t_pars *p)
// {
// 	int		j;
// 	char	*buf;

// 	buf = NULL;
// 	j = 0;
// 	str[i] = apply_var_env(str[i], 0, mini, p);//je dois faire par rapoirt auchar
// 	if (str[i] == NULL)
// 	{
// 		str[i] = malloc(sizeof(char) * 1);
// 		if (!str[i])
// 			exit (1); //mayday error
// 		str[i][0] = '\0';
// 	}
// 	else
// 	{
// 		while (str[i][j]) // are we shure that str(i(j existe ?
// 		{
// 			buf = ft_charaddback(&buf, str[i][j]);
// 			j++;
// 		}
// 		free(str[i]);
// 		str[i] = ft_strdup(buf);
// 		free(buf);
// 	}
// }

