/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:39:59 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/04 06:27:39 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_define_new_node(t_pars *n)
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
	n->was_quote = false;
}

static void	ft_if_no_error(char *input_no_pipe, t_pars	*n, t_utils *utils)
{
	n->spl_cmd = ft_split_separator(input_no_pipe, utils);
	if (!n->spl_cmd)
		ft_ultimate_free_exit(utils, &input_no_pipe, NULL);
	if (n->spl_cmd[0])
	{
		n->is_arg = ft_define_shure_arg(n->spl_cmd, utils);
		n->is_expand = malloc(sizeof(bool) * ft_strlen_array(n->spl_cmd));
		if (!n->is_expand)
		{
			free(input_no_pipe);
			ft_ultimate_free_exit(utils, n->spl_cmd, NULL);
		}
	}
	else
	{
		n->is_arg = NULL;
		n->is_expand = NULL;
	}
	n->exit_code = 0;
	n->error_msg = NULL;
}

//create a new node for my struct t_pars. every node is a cmd separed by pipe
static t_pars	*ft_new_node(char *input_no_pipe, t_utils *utils)
{
	t_pars	*n;

	n = malloc(sizeof(t_pars));
	if (!n)
		ft_ultimate_free_exit(utils, &input_no_pipe, NULL);
	if (input_no_pipe == NULL || ft_strlen(input_no_pipe) == 0
		|| ft_is_only_space(input_no_pipe) == 1)
	{
		n->exit_code = 2;
		n->error_msg = ft_strdup(
				"minishell: syntax error near unexpected token `|'");
		if (!n->error_msg)
			ft_ultimate_free_exit(utils, &input_no_pipe, NULL);
		n->spl_cmd = NULL;
		n->is_arg = NULL;
		n->is_expand = NULL;
	}
	ft_if_no_error(input_no_pipe, n, utils);
	ft_define_new_node(n);
	return (n);
}

static int	ft_iter_new_node(
	char *input, char **input_no_pipe, t_pars *head, t_utils *utils)
{
	int		i;
	t_pars	*buf;

	buf = head;
	i = 1;
	while (input_no_pipe[i])
	{
		buf->next = ft_new_node(input_no_pipe[i], utils);
		if (buf->next != NULL)
			buf = buf->next;
		else
			ft_ultimate_free_exit(utils, input_no_pipe, NULL);
		i++;
	}
	ft_pipe_unexpected(input, head, utils);
	ft_free_array(input_no_pipe);
	return (0);
}

//function for get a structure with segmented line of command
t_pars	*ft_define_p(char *input, t_utils *utils)
{
	char	**input_no_pipe;
	t_pars	*head;

	if (ft_is_only_space(input) == 0)
	{
		input_no_pipe = ft_split_quote_ignore(input, '|', utils);
		head = ft_new_node(input_no_pipe[0], utils);
		utils->p = head;
		if (!head)
			ft_ultimate_free_exit(utils, input_no_pipe, NULL);
		if (ft_iter_new_node(input, input_no_pipe, head, utils))
			return (NULL);
		return (head);
	}
	return (0);
}
