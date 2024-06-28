/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:39:22 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/28 17:48:46 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_option(char *arg, t_commands *p_cmd, t_pars *p)
{
	if (arg[0] == '-')
	{
		if (p->last_was_echo == true && (p_cmd->arg
				|| (ft_strncmp(arg, "-e", 2) && ft_strncmp(arg, "-n", 2))))
		{
			p_cmd->arg = ft_addback(p_cmd->arg, arg);
			return (true);
		}
		if (p_cmd->option)
		{
			p_cmd->option = ft_strjoin(p_cmd->option, arg + 1);
			if (!p_cmd->option)
				p->malloc_error = true;
		}
		else
		{
			p_cmd->option = ft_strdup(arg);
			if (!p_cmd->option)
				p->malloc_error = true;
		}
		return (true);
	}
	return (false);
}

bool	ft_arg_is_cmd(char *arg, t_commands *p_cmd, t_pars *p)
{
	p->next_can_be_opt = true;
	p->next_can_be_arg = true;
	if (p_cmd->msg_error == NULL)
		p_cmd->bf_cmd = false;
	p_cmd->cmd = ft_strdup(arg);
	if (!p_cmd->cmd)
		p->malloc_error = true;
	if (ft_strcmp(arg, "echo") == 0 || ft_strcmp(arg, "cd") == 0
		|| ft_strcmp(arg, "pwd") == 0 || ft_strcmp(arg, "export") == 0
		|| ft_strcmp(arg, "unset") == 0 || ft_strcmp(arg, "env") == 0
		|| ft_strcmp(arg, "exit") == 0)
	{
		p_cmd->b_builtins = true;
		if (ft_strcmp(arg, "env") == 0)
			p->last_was_env = true;
		if (ft_strcmp(arg, "exit") == 0)
			p->next_is_arg = true;
		if (ft_strcmp(arg, "echo") == 0)
			p->last_was_echo = true;
		return (true);
	}
	return (true);
}
