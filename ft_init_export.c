/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 02:15:38 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/15 16:17:07 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_is_s1_before(char *str1, char *str2)
{
	char	*alpha;
	int		s1;
	int		s2;
	int		i;

	alpha = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz";
	i = 0;
	while (str1[i] && str2[i])
	{
		s1 = ft_strchr(alpha, str1[i]) - alpha;
		s2 = ft_strchr(alpha, str2[i]) - alpha;
		if (s1 < s2)
			return (true);
		else if (s2 < s1)
			return (false);
		i++;
	}
	return (s1 < s2);
}

static void	define_sort(char **env, int count, char **result)
{
	int		buf;
	int		i;
	int		current;
	char	**env_buf;

	current = 0;
	i = 0;
	env_buf = ft_strdup_array(env);
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
	free_array(env_buf);
}

static char	**sort_export(int count, char **env)
{
	char	**result;

	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	result[count] = NULL;
	define_sort(env, count, result);
	return (result);
}

static void	create_str(char **str, char **res_ncmplt, int *j, bool *is_quote)
{
	*str = ft_charaddback(str, (*res_ncmplt)[*j]);
	if (!*str)
	{
		free_array(res_ncmplt);
		return ;
	}
	if ((*res_ncmplt)[*j] == '=' && *is_quote == false)
	{
		*str = ft_charaddback(str, '\"');
		if (!*str)
		{
			free_array(res_ncmplt);
			return ;
		}
		*is_quote = true;
	}
	(*j)++;
}

//need to change name to quote add
static char	**result_declare(char **res_ncmplt)
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
			create_str(&str, &res_ncmplt[i], &j, &is_quote);
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
	res_not_complete = sort_export(count, mini->env);
	if (!res_not_complete)
		ultimate_free_exit(mini, NULL, NULL, NULL);
	result = result_declare(res_not_complete);
	free_array(res_not_complete);
	return (result);
}
