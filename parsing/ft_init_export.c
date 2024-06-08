/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 02:15:38 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/09 00:03:50 by gmersch          ###   ########.fr       */
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
			return false;
		i++;
	}
	return (s1 < s2);// NORM ????
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
			if (buf != i && ft_is_s1_before(env_buf[i], env_buf[buf]) == true && ft_strchr(env_buf[i], '='))
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
	int		current;
	int		buf;
	char	**result;

	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		exit (1);//mayday error ?
	result[count] = NULL;
	define_sort(env, count, result);
	return(result);
}

//need to change name to quote add
static char	**result_declare(char **result, char **res_ncmplt, int count)
{
	int		i;
	int		j;
	bool	is_quote;

	i = 0;
	while (res_ncmplt[i])
	{
		j = 0;
		//result[i] = ft_strdup("declare -x ");
		is_quote = false;
		while (res_ncmplt[i][j])
		{
			result[i] = ft_charaddback(&result[i], res_ncmplt[i][j]);
			if (res_ncmplt[i][j] == '=' && is_quote == false)
			{
				result[i] = ft_charaddback(&result[i], '\"');
				is_quote = true;
			}
			j++;
		}
		result[i] = ft_charaddback(&result[i], '\"');
		i++;
	}
	return (result);
}

char	**ft_init_export(t_minishell *mini)
{
	int		count;
	char	**result;
	char	**res_not_complete;
	int		j;
	int		i;

	i = 0;
	count = 0;
	while (mini->env[i])
	{
		if (ft_strchr(mini->env[i], '='))
			count++;
		i++;
	}
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		exit (1);//mayday error ?
	result[count] = NULL;
	res_not_complete = sort_export(count, mini->env);
	result = result_declare(result, res_not_complete, count);
	free_array(res_not_complete);
	return (result);
}
