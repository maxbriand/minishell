/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:39:22 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/03 18:50:40 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_option(char *arg, t_commands *p_cmd)
{
	if (arg[0] == '-')
	{
		if (p_cmd->option)
		{
			p_cmd->option = ft_strjoin(p_cmd->option, arg + 1);
			if (!p_cmd->option)
				exit (1);//mayday return error ?
		}
		else
		{
			p_cmd->option = ft_strdup(arg);
			if (!p_cmd->option)
				exit (1); //mayday return error ?
		}
		return (true);
	}
	return (false);
}

bool	arg_is_cmd(char *arg, t_commands *p_cmd, t_pars *p)
{
	p->next_can_be_opt = true;
	p->next_can_be_arg = true;
	p_cmd->cmd = ft_strdup(arg);
	if (!p_cmd->cmd)
		exit (1);//Error message ?
	if (strcmp(arg, "echo") == 0 || strcmp(arg, "cd") == 0
		|| strcmp(arg, "pwd") == 0 || strcmp(arg, "export") == 0
		|| strcmp(arg, "unset") == 0 || strcmp(arg, "env") == 0
		|| strcmp(arg, "exit") == 0)
	{
		p_cmd->b_builtins = true;
		if (strcmp(arg, "env") == 0)
			p->next_is_infile = true;
		return (true);
	}
	return (true);
}
