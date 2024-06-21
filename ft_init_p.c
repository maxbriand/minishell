/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:39:59 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/21 16:01:33 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	define_new_node(t_pars *n)
{
	n->last_was_echo = false;
	n->next_is_hd_stop = false;
	n->next_is_infile = false;
	n->next_is_outfile = false;
	n->next_can_be_opt = false;
	n->next_can_be_arg = false;
	n->next_is_arg = false;
	n->last_was_env = false;
	n->next = NULL;
	n->malloc_error = false;
}

static int	if_no_error(char *input_no_pipe, t_pars	*n)
{
	n->spl_cmd = ft_split_separator(input_no_pipe);
	if (!n->spl_cmd)
		return (1);
	if (n->spl_cmd[0])
	{
		n->is_arg = define_shure_arg(n->spl_cmd);
		n->is_expand = malloc(sizeof(bool) * ft_strlen_array(n->spl_cmd));
		if (!n->is_expand)
		{
			free(n->spl_cmd);
			return (1);
		}
	}
	else
	{
		n->is_arg = NULL;
		n->is_expand = NULL;
	}
	n->exit_code = 0;
	n->error_msg = NULL;
	return (0);
}

//create a new node for my struct t_pars. every node is a cmd separed by pipe
static t_pars	*new_node(char *input_no_pipe)
{
	t_pars	*n;

	n = malloc(sizeof(t_pars));
	if (!n)
		return (NULL);
	if (input_no_pipe == NULL || ft_strlen(input_no_pipe) == 0
		|| is_only_space(input_no_pipe) == 1)
	{
		n->exit_code = 2;
		n->error_msg = ft_strdup(
				"minishell: syntax error near unexpected token `|'");
		if (!n->error_msg)
			return (NULL);
		n->spl_cmd = NULL;
		n->is_arg = NULL;
		n->is_expand = NULL;
	}
	else if (if_no_error(input_no_pipe, n) != 0)
		return (NULL);
	define_new_node(n);
	return (n);
}

static int	iter_new_node(
	char *input, char **input_no_pipe, t_pars *buf, t_pars *head)
{
	int	i;

	i = 1;
	while (input_no_pipe[i])
	{
		buf->next = new_node(input_no_pipe[i]);
		if (buf->next != NULL)
			buf = buf->next;
		else
		{
			free_array(input_no_pipe);
			return (1);
		}
		i++;
	}
	pipe_unexpected(input, head);
	free_array(input_no_pipe);
	return (0);
}

//function for get a structure with segmented line of command
t_pars	*define_p(char *input)
{
	char	**input_no_pipe;
	t_pars	*head;
	t_pars	*buf;

	if (is_only_space(input) == 0)
	{
		input_no_pipe = ft_split_quote_ignore(input, '|');
		if (!input_no_pipe)
			return (NULL);
		head = new_node(input_no_pipe[0]);
		if (!head)
		{
			free_array(input_no_pipe);
			return (NULL);
		}
		buf = head;
		if (iter_new_node(input, input_no_pipe, buf, head))
			return (NULL);
		return (head);
	}
	return (0);
}
