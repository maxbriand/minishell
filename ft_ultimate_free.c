/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:40:34 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/10 20:21:22 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

void	free_p(t_pars *p)
{
	t_pars	*p_buf;

	while(p)
	{
		p_buf = p;
		if (p_buf->spl_cmd)
			free_array(p_buf->spl_cmd);
		if (p_buf->is_arg)
			free(p_buf->is_arg);
		if (p_buf->is_expand)
			free(p_buf->is_expand);
		if (p_buf->error_msg)
			free(p_buf->error_msg);
		p = p->next;
		free(p_buf);
	}
}

void	free_p_cmd(t_commands *p_cmd)
{
	t_commands	*buf;

	while (p_cmd)
	{
		buf = p_cmd;
		p_cmd = p_cmd->next;
		if (buf->arg)
			free(buf->arg);
		if (buf->arg_cmd)
			free_array(buf->arg_cmd);
		if (buf->cmd)
			free(buf->cmd);
		if (buf->hd_stop)
			free_array(buf->hd_stop);
		if (buf->infile)
			free(buf->infile);
		if (buf->option)
			free(buf->option);
		if (buf->outfile)
			free(buf->outfile);
		if (buf->msg_error)
			free(buf->msg_error);
		free(buf);
	}
	p_cmd = NULL;
}

void	ultimate_free_exit(t_minishell *mini, t_pars *p, void *str, void **array)
{
	if (p)
		free_p(p);
	if (str)
		free(str);
	if (mini)
		free_mini(mini);
	if (array)
		free_array((char **)array);
	exit (1);
}

void	free_mini(t_minishell *mini)
{
	if (mini)
	{
		if (mini->env)
			free_array(mini->env);
		if (mini->export)
			free_array(mini->export);
		if (mini->p_cmd)
			free_p_cmd(mini->p_cmd);
	}
}
