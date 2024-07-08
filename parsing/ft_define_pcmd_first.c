/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_define_pcmd_first.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:39:43 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/09 00:44:15 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_create_arg(
	char **expand, t_commands *p_cmd, t_pars *p, t_utils *utils)
{
	int	i;

	ft_arg_is_cmd(expand[0], p_cmd, p, utils);
	i = 1;
	if (expand[i])
	{
		while (ft_is_option(expand[i], p_cmd, p, utils) == true)
			i++;
		while (expand[i])
		{
			p_cmd->arg = ft_addback(p_cmd->arg, expand[i]);
			if (!p_cmd->arg)
				ft_ultimate_free_exit(utils, NULL, NULL, NULL);
			i++;
		}
	}
}

void	ft_define_first_pcmd(
	char *first_arg, t_commands *p_cmd, t_pars *p, t_utils *utils)
{
	char	**expand;

	if (first_arg[0] == '\0')
		return ;
	if (p->is_arg[0] == true)
	{
		if (ft_arg_is_cmd(first_arg, p_cmd, p, utils) == true)
			return ;
	}
	if (ft_is_operator(first_arg, p_cmd, p, utils) == true)
		return ;
	if (p->is_expand[0] == true)
	{
		expand = ft_split(first_arg, ' ');
		if (!expand)
			ft_ultimate_free_exit(utils, NULL, NULL, NULL);
		ft_create_arg(expand, p_cmd, p, utils);
		ft_free_array(expand);
		return ;
	}
	if (ft_arg_is_cmd(first_arg, p_cmd, p, utils) == true)
		return ;
}
