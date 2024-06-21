/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_define_pcmd_first.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:39:43 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/21 20:02:54 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_create_arg(int *i, char **expand, t_commands *p_cmd, t_pars *p)
{
	arg_is_cmd(expand[0], p_cmd, p);
	*i = 1;
	if (expand[*i])
	{
		while (is_option(expand[*i], p_cmd, p) == true)
			(*i)++;
		while (expand[*i])
		{
			p_cmd->arg = ft_addback(p_cmd->arg, expand[*i]);
			(*i)++;
		}
	}
}

//define if the first arg is a command, a redirection etc
void	define_first_pcmd(char *first_arg, t_commands *p_cmd, t_pars *p)
{
	char	**expand;
	int		i;

	if (first_arg[0] == '\0')
		return ;
	if (p->is_arg[0] == true)
	{
		if (arg_is_cmd(first_arg, p_cmd, p) == true)
			return ;
	}
	if (ft_is_operator(first_arg, p_cmd, p) == true)
		return ;
	if (p->is_expand[0] == true)
	{
		expand = ft_split(first_arg, ' ');
		if (!expand)
			p->malloc_error = true;
		ft_create_arg(&i, expand, p_cmd, p);
		free_array(expand);
		return ;
	}
	if (arg_is_cmd(first_arg, p_cmd, p) == true)
		return ;
}
