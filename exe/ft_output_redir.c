/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:41:19 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/09 02:43:55 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_output_redir(t_minishell *data, t_commands *c_cmd, int *pipefd)
{
	int	fd;

	if (c_cmd->outfile && c_cmd->append_outfile == 1)
	{
		fd = open(c_cmd->outfile, O_WRONLY | O_APPEND);
		if (dup2(fd, 1) == -1)
			ft_exitf("dup2 issue", 1, NULL, data);
		close(fd);
	}
	else if (c_cmd->outfile)
	{
		fd = open(c_cmd->outfile, O_WRONLY | O_TRUNC);
		if (dup2(fd, 1) == -1)
			ft_exitf("dup2 issue", 1, NULL, data);
		close(fd);
	}
	else
	{
		dup2(pipefd[1], 1);
	}
}
