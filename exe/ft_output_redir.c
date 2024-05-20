/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:41:19 by mbriand           #+#    #+#             */
/*   Updated: 2024/05/20 16:05:24 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_output_redir(t_minishell *data, t_commands *p_cmd, int *pipefd)
{
	int	fd;

	if (p_cmd->outfile && p_cmd->append_outfile == 1)
	{
		fd = open(p_cmd->outfile, O_WRONLY, O_APPEND);
		if (dup2(fd, 1) == -1)
			ft_exit_failure("dup2 issue", data);
		close(fd);
	}
	else if (p_cmd->outfile)
	{
		fd = open(p_cmd->outfile, O_WRONLY);
		if (dup2(fd, 1) == -1)
			ft_exit_failure("dup2 issue", data);
		write(2, "outfile\n", 8);
		close(fd);
	}
	else
	{
		dup2(pipefd[1], 1);
		write(2, "pipefd[1]\n", 10);
	}
}
