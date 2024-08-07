/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_heredocs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 01:13:34 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/09 00:48:40 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_write_heredoc(int fd, char *hd_stop)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			ft_write_error("warning: here-document is delimited by \
end-of-file");
			break ;
		}
		if (ft_strcmp(input, hd_stop) == 0)
			break ;
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
}

int	ft_iterate_heredocs(t_commands *c_cmd, t_minishell *data)
{
	int	i;
	int	fd;

	fd = 0;
	if (!c_cmd->hd_stop)
		return (0);
	i = 0;
	while (c_cmd->hd_stop[i] && c_cmd->heredoc)
	{
		if (i != 0)
			close(fd);
		fd = open(c_cmd->heredoc, O_WRONLY | O_APPEND | O_CREAT, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (fd == -1)
			ft_exitf("open issue", 1, NULL, data);
		ft_write_heredoc(fd, c_cmd->hd_stop[i]);
		i++;
	}
	if (fd)
		close(fd);
	return (1);
}

void	ft_create_heredocs(t_minishell *data, t_commands *p_cmd)
{
	if (!p_cmd)
		return ;
	while (p_cmd)
	{
		ft_iterate_heredocs(p_cmd, data);
		p_cmd = p_cmd->next;
	}
}
