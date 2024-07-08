/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:39:56 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/09 00:44:27 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_error(char *input, bool *on_quote, int i, t_utils *utils)
{
	if (input[i] == '|' && input[i + 1] == '|'
		&& !on_quote[0] && !on_quote[1] && (!utils->buf_p->error_msg))
	{
		utils->buf_p->error_msg = ft_strdup(
				"minishell: syntax error near unexpected token `||'");
		if (!utils->buf_p->error_msg)
			ft_ultimate_free_exit(utils, NULL, NULL, NULL);
		utils->buf_p->exit_code = 2;
		return (1);
	}
	if (input[i] == '|' && i == 0 && (!utils->buf_p->error_msg))
	{
		utils->buf_p->error_msg = ft_strdup(
				"minishell: syntax error near unexpected token `|'");
		if (!utils->buf_p->error_msg)
			ft_ultimate_free_exit(utils, NULL, NULL, NULL);
		utils->buf_p->exit_code = 2;
		return (1);
	}
	return (0);
}

static int	ft_is_pipe(char *input, int i, t_utils *utils)
{
	int	j;

	j = i + 1;
	while (input[j] == ' ')
		(j)++;
	if ((input[j] == '|' || input[j] == '\0') && (!utils->buf_p->error_msg))
	{
		utils->buf_p->error_msg = ft_strdup(
				"minishell: syntax error near unexpected token `|'");
		if (!utils->buf_p->error_msg)
			ft_ultimate_free_exit(utils, NULL, NULL, NULL);
		utils->buf_p->exit_code = 2;
		return (1);
	}
	return (0);
}

int	ft_pipe_unexpected(char *input, t_pars *p, t_utils *utils)
{
	int		i;
	bool	on_quote[2];

	on_quote[0] = false;
	on_quote[1] = false;
	i = 0;
	utils->buf_p = p;
	while (input[i])
	{
		ft_define_on_quote(input, i, on_quote);
		if (input[i] == '|' && !on_quote[0] && !on_quote[1])
		{
			utils->buf_p = utils->buf_p->next;
			if (!utils->buf_p)
				break ;
			if (ft_is_pipe(input, i, utils))
				return (1);
		}
		if (ft_check_error(input, on_quote, i, utils))
			return (1);
		i++;
	}
	return (0);
}

void	ft_error_next_file(t_commands *p_cmd, t_pars *p, t_utils *utils)
{
	if (p_cmd->exit_code == 0 && p->was_quote == false)
	{
		p_cmd->exit_code = 2;
		p_cmd->msg_error = ft_strdup(
				"syntax error near unexpected token `newline'");
		if (!p_cmd->msg_error)
			ft_ultimate_free_exit(utils, NULL, NULL, NULL);
	}
	else if (p_cmd->exit_code == 0 && p->was_quote)
	{
		p_cmd->exit_code = 1;
		p_cmd->msg_error = ft_strdup(
				"No such file or directory");
		if (!p_cmd->msg_error)
			ft_ultimate_free_exit(utils, NULL, NULL, NULL);
	}
}

void	ft_set_error_op(t_commands *p_cmd, t_utils *utils)
{
	if (p_cmd->msg_error == NULL)
	{
		p_cmd->msg_error = ft_strdup(
				"minishell: syntax error near unexpected operator");
		if (!p_cmd->msg_error)
			ft_ultimate_free_exit(utils, NULL, NULL, NULL);
		p_cmd->exit_code = 2;
	}
}
