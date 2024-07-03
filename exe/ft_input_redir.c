/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:03:04 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/03 02:54:57 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_input_redir(t_minishell *data, t_commands *c_cmd, int *pipefd)
{
	int		fd;

	fd = open(c_cmd->heredoc, O_RDONLY);
	if (c_cmd->infile)
	{
		if (c_cmd->heredoc)
			close(fd);
		fd = open(c_cmd->infile, O_RDONLY);
		if (fd == -1)
			ft_exitf("open issue", 1, NULL, data);
	}
	else if (!c_cmd->hd_stop)
	{
		close(fd);
		unlink(c_cmd->heredoc);
		if (dup2(pipefd[0], 0) == -1)
			ft_exitf("dup2 issue", 1, NULL, data);
		return ;
	}
	if (dup2(fd, 0) == -1)
		ft_exitf("dup2 issue", 1, NULL, data);
	close(fd);
	unlink(c_cmd->heredoc);
}
