/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:40:34 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/05 21:52:16 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	other_free(t_commands *buf)
{
	if (buf->option)
		free(buf->option);
	if (buf->outfile)
		free(buf->outfile);
	if (buf->msg_error)
		free(buf->msg_error);
	if (buf->heredoc)
		free(buf->heredoc);
}

void	ft_free_pcmd(t_commands *p_cmd)
{
	t_commands	*buf;

	while (p_cmd)
	{
		buf = p_cmd;
		p_cmd = p_cmd->next;
		if (buf->arg)
			ft_free_array(buf->arg);
		buf->arg = NULL;
		if (buf->arg_cmd)
			ft_free_array(buf->arg_cmd);
		buf->arg_cmd = NULL;
		if (buf->cmd)
			free(buf->cmd);
		if (buf->hd_stop)
			ft_free_array(buf->hd_stop);
		buf->hd_stop = NULL;
		if (buf->infile)
			free(buf->infile);
		other_free(buf);
		free(buf);
	}
	p_cmd = NULL;
}

void	ft_ultimate_free_exit(
	t_utils *utils, char **array, char *str, char *msg)
{
	if (msg)
		ft_printf(msg);
	else
		ft_printf("malloc issue\n");
	if (str)
		free(str);
	str = NULL;
	if (array)
		ft_free_array(array);
	array = NULL;
	if (utils)
	{
		if (utils->p)
			ft_free_p(utils->p);
		if (utils->mini)
			ft_free_mini(utils->mini, utils);
		ft_free_utils(&utils);
	}
	exit (1);
}

static void	ft_free_mini_env(t_minishell *mini, t_utils *utils)
{
	int	i;

	i = 0;
	if (mini->env)
	{
		if (utils && utils->env_free)
		{
			while (i < utils->env_free)
			{
				free(mini->env[i]);
				i++;
			}
			i++;
			while (mini->env[i])
			{
				free(mini->env[i]);
				i++;
			}
			free(mini->env);
		}
		else
			ft_free_array(mini->env);
	}
}

void	ft_free_mini(t_minishell *mini, t_utils *utils)
{
	if (!mini)
		return ;
	ft_free_mini_env(mini, utils);
	mini->env = NULL;
	if (mini->export)
		ft_free_array(mini->export);
	mini->export = NULL;
	if (mini->p_cmd)
		ft_free_pcmd(mini->p_cmd);
	mini->p_cmd = NULL;
	mini->export = NULL;
	mini->env = NULL;
}
