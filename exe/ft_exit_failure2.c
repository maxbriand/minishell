/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_failure2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 01:30:03 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/09 00:48:59 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_str(char *str)
{
	if (!str)
		return ;
	free(str);
}

void	ft_free_p_cmd(t_commands *p_cmd)
{
	t_commands	*old_p_cmd;

	while (p_cmd)
	{
		ft_free_str(p_cmd->heredoc);
		ft_free_str(p_cmd->infile);
		ft_free_str(p_cmd->outfile);
		ft_free_str(p_cmd->cmd);
		ft_free_str(p_cmd->option);
		ft_free_str(p_cmd->msg_error);
		ft_arrfree(p_cmd->hd_stop);
		ft_arrfree(p_cmd->arg);
		ft_arrfree(p_cmd->arg_cmd);
		old_p_cmd = p_cmd;
		p_cmd = p_cmd->next;
		free (old_p_cmd);
	}
}
