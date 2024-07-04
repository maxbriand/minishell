/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 02:15:38 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/04 06:04:53 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_define_sort(
		char **env, int count, char **result, t_utils *utils)
{
	int		buf;
	int		i;
	int		current;
	char	**env_b;

	current = 0;
	env_b = ft_strdup_array(env, utils);
	if (!env_b || !env)
		return ;
	while (current < count)
	{
		buf = 0;
		i = 0;
		while (env_b[i])
		{
			if (buf != i && ft_is_s1_before(env_b[i], env_b[buf]) == true
				&& ft_strchr(env_b[i], '='))
				buf = i;
			i++;
		}
		result[current] = ft_better_strdup(env_b[buf], env_b[buf], utils);
		ft_remove_element(env_b, buf);
		current++;
	}
	ft_free_array(env_b);
}

static char	**ft_sort_export(int count, char **env, t_utils *utils)
{
	char	**result;

	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	result[count] = NULL;
	ft_define_sort(env, count, result, utils);
	if (!env)
		return (NULL);
	return (result);
}

static void	ft_create_str(
	t_utils *utils, char **res_ncmplt, int *j, bool *is_quote)
{
	utils->exp_str = ft_charaddback(&utils->exp_str, (*res_ncmplt)[*j], NULL);
	if (!utils->exp_str)
	{
		ft_free_array(res_ncmplt);
		ft_ultimate_free_exit(utils, NULL, NULL);
	}
	if ((*res_ncmplt)[*j] == '=' && *is_quote == false)
	{
		utils->exp_str = ft_charaddback(&utils->exp_str, '\"', NULL);
		if (!utils->exp_str)
		{
			ft_free_array(res_ncmplt);
			ft_ultimate_free_exit(utils, NULL, NULL);
		}
		*is_quote = true;
	}
	(*j)++;
}

static char	**ft_result_declare(char **res_ncmplt, t_utils *utils)
{
	int		i;
	int		j;
	bool	is_quote;
	char	**result;

	i = 0;
	result = NULL;
	while (res_ncmplt[i])
	{
		j = 0;
		is_quote = false;
		utils->exp_str = NULL;
		while (res_ncmplt[i][j])
			ft_create_str(utils, &res_ncmplt[i], &j, &is_quote);
		if (!res_ncmplt[i])
			return (NULL);
		utils->exp_str = ft_charaddback(&utils->exp_str, '\"', utils);
		result = ft_addback_free(result, utils->exp_str);
		if (!result)
			ft_ultimate_free_exit(utils, NULL, NULL);
		i++;
	}
	return (result);
}

char	**ft_init_export(t_minishell *mini, t_utils *utils)
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
	res_not_complete = ft_sort_export(count, mini->env, utils);
	if (!res_not_complete)
		ft_ultimate_free_exit(utils, NULL, NULL);
	result = ft_result_declare(res_not_complete, utils);
	ft_free_array(res_not_complete);
	return (result);
}
