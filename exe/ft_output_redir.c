/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:41:19 by mbriand           #+#    #+#             */
/*   Updated: 2024/05/29 18:10:12 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_output_redir(t_minishell *data, t_commands *p_cmd, int *pipefd)
{
	int	fd;

	if (p_cmd->outfile && p_cmd->append_outfile == 1)
	{
		fd = open(p_cmd->outfile, O_WRONLY | O_APPEND);
		if (dup2(fd, 1) == -1)
			ft_exit_failure("dup2 issue", NULL, data);
		// write(2, "append of ", 10 );
		// write(2, "\n", 1);
		close(fd);
	}
	else if (p_cmd->outfile)
	{
		fd = open(p_cmd->outfile, O_WRONLY | O_TRUNC);
		if (dup2(fd, 1) == -1)
			ft_exit_failure("dup2 issue", NULL, data);
		close(fd);
	}
	else
	{
		dup2(pipefd[1], 1);
	}
}
