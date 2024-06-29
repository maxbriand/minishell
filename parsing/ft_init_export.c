/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 02:15:38 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/28 17:02:07 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_define_sort(char **env, int count, char **result)
{
	int		buf;
	int		i;
	int		current;
	char	**env_buf;

	current = 0;
	env_buf = ft_strdup_array(env);
	if (!env_buf || !env)
		return ;
	while (current < count)
	{
		buf = 0;
		i = 0;
		while (env_buf[i])
		{
			if (buf != i && ft_is_s1_before(env_buf[i], env_buf[buf]) == true
				&& ft_strchr(env_buf[i], '='))
				buf = i;
			i++;
		}
		result[current] = ft_strdup(env_buf[buf]);
		ft_remove_element(env_buf, buf);
		current++;
	}
	ft_free_array(env_buf);
}

static char	**ft_sort_export(int count, char **env)
{
	char	**result;

	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	result[count] = NULL;
	ft_define_sort(env, count, result);
	if (!env)
		return (NULL);
	return (result);
}

static void	ft_create_str(char **str, char **res_ncmplt, int *j, bool *is_quote)
{
	*str = ft_charaddback(str, (*res_ncmplt)[*j]);
	if (!*str)
	{
		ft_free_array(res_ncmplt);
		return ;
	}
	if ((*res_ncmplt)[*j] == '=' && *is_quote == false)
	{
		*str = ft_charaddback(str, '\"');
		if (!*str)
		{
			ft_free_array(res_ncmplt);
			return ;
		}
		*is_quote = true;
	}
	(*j)++;
}

static char	**ft_result_declare(char **res_ncmplt)
{
	int		i;
	int		j;
	bool	is_quote;
	char	**result;
	char	*str;

	i = 0;
	result = NULL;
	while (res_ncmplt[i])
	{
		j = 0;
		is_quote = false;
		str = NULL;
		while (res_ncmplt[i][j])
			ft_create_str(&str, &res_ncmplt[i], &j, &is_quote);
		if (!res_ncmplt[i])
			return (NULL);
		str = ft_charaddback(&str, '\"');
		if (!str)
			return (NULL);
		result = ft_addback(result, str);
		free(str);
		i++;
	}
	return (result);
}

char	**ft_init_export(t_minishell *mini)
{
	int		count;
	char	**result;
	char	**res_not_complete;
	int		i;

	i = 0;
	count = 0;
	while (mini->env[i])
	{
		if (ft_strchr(mini->env[i], '='))
			count++;
		i++;
	}
	res_not_complete = ft_sort_export(count, mini->env);
	if (!res_not_complete)
		ft_ultimate_free_exit(mini, NULL, NULL);
	result = ft_result_declare(res_not_complete);
	ft_free_array(res_not_complete);
	return (result);
}
