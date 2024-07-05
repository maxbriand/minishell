/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_define_pcmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:39:46 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/05 14:50:09 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_is_expand(char **expand, int i, t_utils *utils, t_pars *p)
{
	if (expand[i])
	{
		while (ft_is_option(expand[i], utils->buf_pcmd, p, utils) == true)
			i++;
		while (expand[i])
		{
			utils->buf_pcmd->arg = ft_addback(utils->buf_pcmd->arg, expand[i]);
			if (!utils->buf_pcmd->arg)
				ft_ultimate_free_exit(utils, NULL, NULL, NULL);
			i++;
		}
	}
	ft_free_array(expand);
}

static int	ft_define_arg_cmd(char *arg, int i, t_utils *utils, t_pars *p)
{
	char	**expand;

	if (p->next_is_infile || p->last_was_env)
		return (1);
	if (p->next_can_be_arg)
	{
		utils->buf_pcmd->arg = ft_addback(utils->buf_pcmd->arg, arg);
		if (!utils->buf_pcmd->arg)
			ft_ultimate_free_exit(utils, NULL, NULL, NULL);
		return (0);
	}
	if (p->is_expand[i] == true && utils->buf_pcmd->cmd == NULL)
	{
		expand = ft_split(arg, ' ');
		if (!expand)
			ft_ultimate_free_exit(utils, NULL, NULL, NULL);
		ft_arg_is_cmd(expand[0], utils->buf_pcmd, p, utils);
		i = 1;
		ft_is_expand(expand, i, utils, p);
		return (0);
	}
	if (utils->buf_pcmd->cmd == NULL)
		ft_arg_is_cmd(arg, utils->buf_pcmd, p, utils);
	return (0);
}

static void	ft_define_next(char *arg, int i, t_utils *utils, t_pars *p)
{
	char	**expand;

	if (ft_define_arg_cmd(arg, i, utils, p) == 0)
		return ;
	p->last_was_env = false;
	if (p->is_expand[i])
	{
		expand = ft_split(arg, ' ');
		if (!expand)
			ft_ultimate_free_exit(utils, NULL, NULL, NULL);
		if (ft_strlen_array(expand) > 1 && !utils->buf_pcmd->msg_error)
		{
			utils->buf_pcmd->msg_error = ft_better_strdup
				("minishell: %s: ambiguous redirect", arg, utils);
			utils->buf_pcmd->exit_code = 1;
		}
		ft_free_array(expand);
	}
	utils->buf_pcmd->infile = ft_strdup(arg);
	if (!utils->buf_pcmd->infile)
		ft_ultimate_free_exit(utils, NULL, NULL, NULL);
	ft_define_infile_error(utils->buf_pcmd, utils);
	p->next_is_infile = false;
}

static void	ft_define_other(char *arg, int i, t_utils *utils, t_pars *p)
{
	if (p->next_can_be_opt && ft_is_option(arg, utils->buf_pcmd, p, utils))
		return ;
	if (ft_is_operator(arg, utils->buf_pcmd, p, utils) == true)
		return ;
	if (p->next_is_hd_stop)
	{
		p->next_is_hd_stop = false;
		if (utils->buf_pcmd->exit_code == 2)
			return ;
		utils->buf_pcmd->hd_stop = ft_addback(utils->buf_pcmd->hd_stop, arg);
		if (!utils->buf_pcmd->hd_stop)
			ft_ultimate_free_exit(utils, NULL, NULL, NULL);
		return ;
	}
	if (p->next_is_outfile)
	{
		if (utils->buf_pcmd->outfile)
			free(utils->buf_pcmd->outfile);
		utils->buf_pcmd->outfile = ft_strdup(arg);
		if (!utils->buf_pcmd->outfile)
			ft_ultimate_free_exit(utils, NULL, NULL, NULL);
		p->next_is_outfile = false;
		return ;
	}
	ft_define_next(arg, i, utils, p);
}

void	ft_define_p_cmd(char *arg, int i, t_utils *utils, t_pars *p)
{
	if (p->next_is_arg)
	{
		if (!ft_is_operator(arg, utils->buf_pcmd, p, utils))
		{
			utils->buf_pcmd->arg = ft_addback(utils->buf_pcmd->arg, arg);
			if (!utils->buf_pcmd->arg)
				ft_ultimate_free_exit(utils, NULL, NULL, NULL);
		}
		p->next_is_arg = false;
		return ;
	}
	if (p->is_arg[i] == true)
	{
		if (utils->buf_pcmd->cmd == NULL)
		{
			ft_arg_is_cmd(arg, utils->buf_pcmd, p, utils);
			return ;
		}
		utils->buf_pcmd->arg = ft_addback(utils->buf_pcmd->arg, arg);
		if (!utils->buf_pcmd->arg)
			ft_ultimate_free_exit(utils, NULL, NULL, NULL);
		return ;
	}
	ft_define_other(arg, i, utils, p);
}
