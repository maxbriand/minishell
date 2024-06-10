/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_define_pcmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:39:46 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/10 15:39:18 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	ft_define_pcmd_arg_cmd(char *arg, int i, t_commands *p_cmd, t_pars *p)
{
	char	**expand;

	if(p->next_can_be_arg)
	{
		p_cmd->arg = ft_addback(p_cmd->arg, arg);
		return ;
	}
	if (p->is_expand[i] == true && p_cmd->cmd == NULL)
	{
		expand = ft_split(arg, ' ');
		arg_is_cmd(expand[0], p_cmd, p);
		i = 1;
		if (expand[i])
		{
			while (is_option(expand[i], p_cmd, p) == true)
				i++;
			while (expand[i])
			{
				p_cmd->arg = ft_addback(p_cmd->arg, expand[i]);
				i++;
			}
		}
		free_array(expand);
		return ;
	}
	if (p_cmd->cmd == NULL)
		arg_is_cmd(arg, p_cmd, p);
}

static void	ft_define_next(char *arg, int i, t_commands *p_cmd, t_pars *p)
{
	char	**expand;

	if (p->next_is_infile || p->last_was_env)
	{
		p->last_was_env = false;
		if (p->is_expand[i])
		{
			expand = ft_split(arg, ' ');
			if (ft_strlen_array(expand) > 1  && p_cmd->msg_error == NULL)
			{
				p_cmd->msg_error = ft_better_strdup("minishell: %s: ambiguous redirect", arg);
				p_cmd->exit_code = 1;
				return ;
			}
			free_array(expand);
		}
		//if (p_cmd->infile)
			//free(p_cmd->infile);
		p_cmd->infile = ft_strdup(arg);
		if (!p_cmd->infile)
			exit (1); //mayday error ?
		define_infile_error(p_cmd);
		p->next_is_infile = false;
		return ;
	}
	ft_define_pcmd_arg_cmd(arg, i, p_cmd, p);
}

static void	ft_define_other(char *arg, int i, t_commands *p_cmd, t_pars *p)
{
	if (ft_is_operator(arg, p_cmd, p) == true)
		return ;
	if (p->next_is_hd_stop)
	{
		p_cmd->hd_stop = ft_addback(p_cmd->hd_stop, arg);
		p->next_is_hd_stop = false;
		return ;
	}
	if (p->next_is_outfile)
	{
		if (p_cmd->outfile)
			free(p_cmd->outfile);
		p_cmd->outfile = ft_strdup(arg);
		if (!p_cmd->outfile)
			exit (1); //mayday error ?
		p->next_is_outfile = false;
		return ;
	}
	ft_define_next(arg, i, p_cmd, p);
}

void	define_p_cmd(char *arg, int i, t_commands *p_cmd, t_pars *p)
{
	if (arg[0] == '\0')
		return ;
	if (p->next_is_arg)
	{
		if (!ft_is_operator(arg, p_cmd, p))
			p_cmd->arg = ft_addback(p_cmd->arg, arg);
		p->next_is_arg = false;
		return ;
	}
	if (p->is_arg[i] == true)
	{
		if (p_cmd->cmd == NULL)
		{
			arg_is_cmd(arg, p_cmd, p);
			return ;
		}
		p_cmd->arg = ft_addback(p_cmd->arg, arg);
		return ;
	}
	if (p->next_can_be_opt && is_option(arg, p_cmd, p) == true)
		return ;
	ft_define_other(arg, i, p_cmd, p);
}
