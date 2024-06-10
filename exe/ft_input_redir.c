/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:03:04 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/10 19:17:17 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// have I to add +1 for the null terminated?
static void	ft_write_heredoc(int fd, char *hd_stop, t_minishell *data)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (!input)
			ft_exitf("readline issue", 1, NULL, data);
		if (ft_strcmp(input, hd_stop) == 0)
			break ;
		write(fd, input, ft_strlen(input));
		free(input);
	}
	write(fd, "\n\0", 2);
}

// check heredocs file permissions on line 47
int	ft_iterate_heredocs(t_commands *c_cmd, t_minishell *data)
{
	int	i;
	int	fd;

	if (!c_cmd->hd_stop)
		return (0);
	i = 0;
	while (c_cmd->hd_stop[i])
	{
		if (i != 0)
			close(fd);
		unlink("heredoc");
		fd = open("heredoc", O_WRONLY | O_APPEND | O_CREAT, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (fd == -1)
			ft_exitf("open issue", 1, NULL, data);
		ft_write_heredoc(fd, c_cmd->hd_stop[i], data);
		i++;
	}
	close(fd);
	return (1);
}

void	ft_input_redir(t_minishell *data, t_commands *c_cmd, int *pipefd)
{
	int		fd;
	bool	here_open;

	here_open = ft_iterate_heredocs(c_cmd, data);
	fd = open("heredoc", O_RDONLY);
	if (c_cmd->infile)
	{
		if (here_open != 0)
			close(fd);
		fd = open(c_cmd->infile, O_RDONLY);
		if (fd == -1)
			ft_exitf("open issue", 1, NULL, data);
	}
	else if (!c_cmd->hd_stop)
	{
		close(fd);
		unlink("heredoc");
		if (dup2(pipefd[0], 0) == -1)
			ft_exitf("dup2 issue", 1, NULL, data);
		return ;
	}
	if (dup2(fd, 0) == -1)
		ft_exitf("dup2 issue", 1, NULL, data);
	close(fd);
	unlink("heredoc");
}
