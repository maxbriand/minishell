/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:40:34 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/03 16:26:32 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_p(t_pars *p)
{
	t_pars	*p_buf;

	while (p)
	{
		p_buf = p;
		if (p_buf->spl_cmd)
			ft_free_array(p_buf->spl_cmd);
		if (p_buf->is_arg)
			free(p_buf->is_arg);
		if (p_buf->is_expand)
			free(p_buf->is_expand);
		if (p_buf->error_msg)
			free(p_buf->error_msg);
		p = p->next;
		p_buf->spl_cmd = NULL;
		p_buf->is_arg = NULL;
		p_buf->is_expand = NULL;
		p_buf->error_msg = NULL;
		free(p_buf);
	}
}

static void	other_free(t_commands *buf)
{
	if (buf->msg_error)
		free(buf->msg_error);
	if (buf->heredoc)
		free(buf->heredoc);
}

static void	ft_free_pcmd(t_commands *p_cmd)
{
	t_commands	*buf;

	while (p_cmd)
	{
		buf = p_cmd;
		p_cmd = p_cmd->next;
		if (buf->arg)
			ft_free_array(buf->arg);
		if (buf->arg_cmd)
			ft_free_array(buf->arg_cmd);
		if (buf->cmd)
			free(buf->cmd);
		if (buf->hd_stop)
			ft_free_array(buf->hd_stop);
		if (buf->infile)
			free(buf->infile);
		if (buf->option)
			free(buf->option);
		if (buf->outfile)
			free(buf->outfile);
		other_free(buf);
		free(buf);
	}
	p_cmd = NULL;
}

void	ft_ultimate_free_exit(
	t_minishell *mini, t_pars *p, char **str, char *msg)
{
	if (msg)
		ft_printf(msg);
	if (p)
		ft_free_p(p);
	if (str)
		ft_free_array(str);
	if (mini)
		ft_free_mini(mini);
	exit (1);
}

void	ft_free_mini(t_minishell *mini)
{
	if (mini)
	{
		ft_free_array(mini->env);
		if (mini->export)
			ft_free_array(mini->export);
		if (mini->p_cmd)
			ft_free_pcmd(mini->p_cmd);
		mini->p_cmd = NULL;
		mini->export = NULL;
		mini->env = NULL;
	}
}
