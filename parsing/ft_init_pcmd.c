/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_pcmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:40:03 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/03 15:36:35 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_define_node(t_commands *node)
{
	node->b_builtins = false;
	node->append_outfile = NULL;
	node->hd_stop = NULL;
	node->in_pipe = false;
	node->infile = NULL;
	node->outfile = NULL;
	node->cmd = NULL;
	node->option = NULL;
	node->arg = NULL;
	node->arg_cmd = NULL;
	node->next = NULL;
	node->pipefd0 = NULL;
	node->pipefd1 = NULL;
	node->old_fd0 = 0;
	node->old_fd1 = 0;
	node->err_is_infile = false;
	node->err_is_outfile = false;
	node->exit_code = 0;
	node->msg_error = NULL;
	node->bf_cmd = true;
	node->heredoc = NULL;
}

static t_commands	*ft_node_create_pcmd(void)
{
	t_commands	*node;

	node = malloc(sizeof(t_commands));
	if (!node)
		return (NULL);
	ft_define_node(node);
	return (node);
}

static int	ft_iter_create_node(
	t_commands *next_node, t_commands *buf_cmd, t_pars *buf_p)
{
	while (buf_p)
	{
		next_node = ft_node_create_pcmd();
		if (!buf_cmd)
			return (1);
		if (buf_p->exit_code)
		{
			if (buf_p->error_msg)
			{
				next_node->msg_error = ft_strdup(buf_p->error_msg);
				if (!next_node->msg_error)
					return (1);
			}
			next_node->exit_code = buf_p->exit_code;
		}
		buf_cmd->next = next_node;
		buf_cmd = buf_cmd->next;
		buf_p = buf_p->next;
	}
	return (0);
}

int	ft_init_pcmd(t_minishell *mini, t_pars *p)
{
	t_pars		*buf_p;
	t_commands	*buf_cmd;
	t_commands	*next_node;

	next_node = NULL;
	buf_p = p;
	buf_cmd = ft_node_create_pcmd();
	if (!buf_cmd)
		return (1);
	if (buf_p->exit_code)
	{
		if (p->error_msg)
		{
			buf_cmd->msg_error = ft_strdup(p->error_msg);
			if (!buf_cmd->msg_error)
				return (1);
		}
		buf_cmd->exit_code = p->exit_code;
	}
	mini->p_cmd = buf_cmd;
	buf_p = buf_p->next;
	if (ft_iter_create_node(next_node, buf_cmd, buf_p))
		return (1);
	return (0);
}
