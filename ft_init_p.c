/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:39:59 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/05 09:33:10 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//create a new node for my struct t_pars. every node is a command separed by pipe
static t_pars	*new_node(char *input_no_pipe)
{
	t_pars	*node;

	node = malloc(sizeof(t_pars));
	if (!node)
		exit (1);//mayday error
	if (ft_strlen(input_no_pipe) == 0 || is_only_space(input_no_pipe) == 1)
	{
		node->exit_code = 2;
		node->error_msg = ft_strdup("minishell: syntax error near unexpected token `|'");
		node->spl_cmd = NULL;
		node->is_arg = NULL;
		node->is_expand = NULL;

	}
	else
	{
		node->spl_cmd = ft_split_separator(input_no_pipe);
		if (node->spl_cmd[0])
		{
			node->is_arg = define_shure_arg(node->spl_cmd);
			node->is_expand = malloc(sizeof(bool) * ft_strlen_array(node->spl_cmd));
		}
		else
		{
			node->is_arg = NULL;
			node->is_expand = NULL;
		}
		node->exit_code = 0;
		node->error_msg = NULL;
	}
	node->file_err[0] = false;
	node->file_err[1] = false;
	node->next_is_hd_stop = false;
	node->next_is_infile = false;
	node->next_is_outfile = false;
	node->next_can_be_opt = false;
	node->next_can_be_arg = false;
	node->next = NULL;
	return (node);
}

//function for get a structure with segmented line of command
t_pars	*define_p(char *input)
{
	int		i;
	char	**input_no_pipe;
	t_pars	*head;
	t_pars	*buf;
	//check pipe at start or double pipe in input: 0 if all good
	if (pipe_unexpected(input) == 0 && is_only_space(input) == 0)
	{
		input_no_pipe = ft_split_quote_ignore(input, '|');
		head = new_node(input_no_pipe[0]);
		if (!head)
		{
			free_array(input_no_pipe);
			return (NULL);
		}
		buf = head;
		i = 1;
		while (input_no_pipe[i])
		{
			buf->next = new_node(input_no_pipe[i]);
			if (buf->next != NULL)
				buf = buf->next;
			i++;
		}
		free_array(input_no_pipe);
		return (head);
	}
	return (0);
}

//ah ouais ca fouille dans le code je vois je vois
