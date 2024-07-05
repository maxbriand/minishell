/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:03:04 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/05 22:19:06 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_input_redir(t_minishell *data, t_commands *c_cmd, int *pipefd)
{
	int		fd;

	if (c_cmd->infile)
	{
		fd = open(c_cmd->infile, O_RDONLY);
		if (fd == -1)
			ft_exitf("open issue", 1, NULL, data);
	}
	else if (!c_cmd->heredoc)
	{
		if (c_cmd->heredoc)
			unlink(c_cmd->heredoc);
		if (dup2(pipefd[0], 0) == -1)
			ft_exitf("dup2 issue", 1, NULL, data);
		return ;
	}
	else
		fd = open(c_cmd->heredoc, O_RDONLY);
	if (dup2(fd, 0) == -1)
		ft_exitf("dup2 issue", 1, NULL, data);
	close(fd);
	if (c_cmd->heredoc)
		unlink(c_cmd->heredoc);
}
