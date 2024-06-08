/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:39:56 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/09 00:12:39 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check if there is consecutive pipe
int	pipe_unexpected(char *input, t_pars *p)
{
	int		i;
	int		j;
	bool	on_quote[2];
	t_pars	*buf;

	on_quote[0] = false;
	on_quote[1] = false;
	i = 0;
	buf = p;
	while (input[i])
	{
		ft_define_on_quote(input, i, on_quote);
		if (input[i] == '|' && !on_quote[0] && !on_quote[1])
		{
			buf = buf->next;
			if (!buf)
				break ;
			j = i + 1;
			while (input[j] == ' ')
				j++;
			if ((input[j] == '|' || input[j] == '\0') && (!buf->error_msg))
			{
				buf->error_msg = ft_strdup("minishell: syntax error near unexpected token `|'");
				buf->exit_code = 2;
				return (1);
			}
		}
		if (input[i] == '|' && input[i + 1] == '|' && !on_quote[0] && !on_quote[1] && (!buf->error_msg))
		{
			buf->error_msg = ft_strdup("minishell: syntax error near unexpected token `||'");
			buf->exit_code = 2;
			return (1);
		}
		if (input[i] == '|' && i == 0 && (!buf->error_msg))
		{
			p->error_msg = ft_strdup("minishell: syntax error near unexpected token `|'");
			p->exit_code = 2;
			return (1);
		}
		i++;
	}
	return (0);
}

void	error_next_file(t_commands *p_cmd)
{
	if (p_cmd->exit_code == 0)
	{
		p_cmd->exit_code = 2;
		p_cmd->msg_error = ft_strdup("syntax error near unexpected token `newline'");
	}
}

void	error_and_exit(char *error)
{
	ft_putstr_fd(error, 1);
	exit (1);
}

void	ft_better_putstr_fd(char *str, char *arg, int error)
{
	int	i;

	if (!str || !arg)
		return ;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] == 's')
		{
			ft_putstr_fd(arg, error);
			i += 2;
		}
		else
		{
			write(error, &str[i], 1);
			i++;
		}
	}
}

void	ft_is_expand(char *arg, int i, t_commands *p_cmd)
{
	char **expand;

	expand = ft_split(arg + i, ' ');
	if (ft_strlen_array(expand) > 1  && p_cmd->msg_error == NULL)
	{
		p_cmd->msg_error = ft_better_strdup("minishell: %s: ambiguous redirect", arg + i);
		p_cmd->exit_code = 1;
		p_cmd->err_is_infile = 1;
	}
	free_array(expand);
}

void	set_error_op(t_commands *p_cmd)
{
	p_cmd->msg_error = ft_strdup("minishell: syntax error near unexpected operator");
	p_cmd->exit_code = 2;
}
