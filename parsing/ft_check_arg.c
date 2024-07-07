/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:39:22 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/07 21:28:33 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_opt_echo(char *arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

bool	ft_is_option(char *arg, t_commands *p_cmd, t_pars *p, t_utils *utils)
{
	if (arg[0] == '-')
	{
		if (p->last_was_echo && (p_cmd->arg && \
				((!ft_strncmp(arg, "-n", 2)) && !ft_opt_echo(arg))))
		{
			p_cmd->arg = ft_addback(p_cmd->arg, arg);
			if (!p_cmd->arg)
				ft_ultimate_free_exit(utils, NULL, NULL, NULL);
			return (true);
		}
		if (p_cmd->option)
		{
			p_cmd->option = ft_strjoin(p_cmd->option, arg + 1);
			if (!p_cmd->option)
				ft_ultimate_free_exit(utils, NULL, NULL, NULL);
		}
		else
		{
			p_cmd->option = ft_strdup(arg);
			if (!p_cmd->option)
				ft_ultimate_free_exit(utils, NULL, NULL, NULL);
		}
		return (true);
	}
	return (false);
}

bool	ft_arg_is_cmd(char *arg, t_commands *p_cmd, t_pars *p, t_utils *utils)
{
	p->next_can_be_opt = true;
	p->next_can_be_arg = true;
	if (p_cmd->msg_error == NULL)
		p_cmd->bf_cmd = false;
	p_cmd->cmd = ft_strdup(arg);
	if (!p_cmd->cmd)
		ft_ultimate_free_exit(utils, NULL, NULL, NULL);
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
