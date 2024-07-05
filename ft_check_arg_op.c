/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg_op.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:51:41 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/05 09:55:25 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_op_infile(
	char *arg, t_commands *p_cmd, t_pars *p, t_utils *utils)
{
	if (ft_strlen(arg) > 1)
	{
		if (arg[1] != '<' && p_cmd->err_is_infile == false)
		{
			p_cmd->outfile = ft_strdup(arg + 1);
			if (!p_cmd->outfile)
				ft_ultimate_free_exit(utils, NULL, NULL, NULL);
		}
		else
			ft_set_error_op(p_cmd, utils);
	}
	else
		p->next_is_outfile = true;
}

static bool	ft_is_operator_not_append(
		char *arg, t_commands *p_cmd, t_pars *p, t_utils *utils)
{
	if (ft_strncmp(arg, "<", 1) == 0)
	{
		if (ft_strlen(arg) > 1)
		{
			if (arg[1] != '>')
			{
				p_cmd->infile = ft_strdup(arg + 1);
				if (!p_cmd->infile)
					ft_ultimate_free_exit(utils, NULL, NULL, NULL);
				ft_define_infile_error(p_cmd, utils);
			}
			else
				ft_set_error_op(p_cmd, utils);
		}
		else
			p->next_is_infile = true;
		return (true);
	}
	else if (ft_strncmp(arg, ">", 1) == 0)
	{
		ft_op_infile(arg, p_cmd, p, utils);
		return (true);
	}
	return (false);
}

static bool	ft_append_op_out(
	char *arg, t_commands *p_cmd, t_pars *p, t_utils *utils)
{
	if (ft_strlen(arg) > 2)
	{
		if (arg[2] != '<' && arg[2] != '>' && p_cmd->err_is_infile == false)
		{
			p_cmd->append_outfile = true;
			p_cmd->outfile = ft_strdup(arg + 2);
			if (!p_cmd->outfile)
				ft_ultimate_free_exit(utils, NULL, NULL, NULL);
		}
		else
			ft_set_error_op(p_cmd, utils);
	}
	else
	{
		p->next_is_outfile = true;
		p_cmd->append_outfile = true;
	}
	return (true);
}

bool	ft_is_operator(
		char *arg, t_commands *p_cmd, t_pars *p, t_utils *utils)
{
	if (ft_strncmp(arg, "<<", 2) == 0)
	{
		if (ft_strlen(arg) > 2)
		{
			if (arg[2] != '<' && arg[2] != '>')
			{
				if (p_cmd->exit_code != 2)
				{
					p_cmd->hd_stop = ft_addback(p_cmd->hd_stop, arg + 2);
					if (!p_cmd->hd_stop)
						ft_ultimate_free_exit(utils, NULL, NULL, NULL);
				}
				return (true);
			}
			else
				ft_set_error_op(p_cmd, utils);
		}
		else
			p->next_is_hd_stop = true;
		return (true);
	}
	else if (ft_strncmp(arg, ">>", 2) == 0)
		return (ft_append_op_out(arg, p_cmd, p, utils));
	return (ft_is_operator_not_append(arg, p_cmd, p, utils));
}
