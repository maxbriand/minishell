/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:36:53 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/05 09:27:39 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_define_outfile_error(t_commands *p_cmd, t_utils *utils)
{
	if (p_cmd->msg_error == NULL)
	{
		if (access(p_cmd->outfile, F_OK) != 0)
			p_cmd->msg_error = ft_better_strdup_free
				("minishell: %s: No such file or directory",
					p_cmd->outfile, utils);
		else
			p_cmd->msg_error = ft_better_strdup_free
				("minishell: %s: Permission denied", p_cmd->outfile, utils);
		p_cmd->err_is_outfile = true;
		p_cmd->exit_code = 1;
	}
	else
		free(p_cmd->outfile);
	p_cmd->outfile = NULL;
}

void	ft_define_infile_error(t_commands *p_cmd, t_utils *utils)
{
	if (access(p_cmd->infile, F_OK) == 0)
	{
		if (access(p_cmd->infile, R_OK) != 0 && p_cmd->msg_error == NULL)
		{
			p_cmd->err_is_infile = true;
			p_cmd->msg_error = ft_better_strdup_free
				("minishell: %s: Permission denied", p_cmd->infile, utils);
			p_cmd->exit_code = 1;
		}
	}
	else
	{
		if (p_cmd->msg_error == NULL)
		{
			p_cmd->err_is_infile = true;
			p_cmd->msg_error = ft_better_strdup_free
				("minishell: %s: No such file or directory",
					p_cmd->infile, utils);
			p_cmd->exit_code = 1;
		}
		else
			free(p_cmd->infile);
		p_cmd->infile = NULL;
	}
}
