#include "minishell.h"

// have I to add +1 for the null terminated?
static void	ft_write_heredoc(int fd, char *hd_stop, t_minishell *data)
{
	char	*input;
	
	while (1)
	{
		input = readline("> ");
		if (!input)
			ft_exit_failure("readline issue", data);
		if (strcmp(input, hd_stop) == 0)
			break;
		write(fd, input, strlen(input));
		free(input);
	}
	write(fd, "\n\0", 2);
}

static int	ft_iterate_heredocs(t_commands *c_cmd, t_minishell *data)
{
	int	i;
	int	fd;
	
	if (!c_cmd->hd_stop)
		return (-1);
	i = 0;
	while (c_cmd->hd_stop[i])
	{
		if (i != 0)
			close(fd);
		unlink("heredoc");
		fd = open("heredoc", O_WRONLY | O_APPEND | O_CREAT, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH); // check heredoc file permissions 
		if (fd == -1)
			ft_exit_failure("open issue", data);
		ft_write_heredoc(fd, c_cmd->hd_stop[i], data);
		i++;
	}
	close(fd);
	return (0);
}

void	ft_input_redir(t_minishell *data, t_commands *c_cmd, int *pipefd)
{
	int		fd;
	bool	here_open;
	
	here_open = ft_iterate_heredocs(c_cmd, data);
	fd = open("heredoc", O_RDONLY);
	if (c_cmd->infile)
	{
		if (here_open != -1)
			close(fd);
		fd = open(c_cmd->infile, O_RDONLY);
		if (fd == -1)
			ft_exit_failure("adup2 issue", data);
	}
	else if (!c_cmd->hd_stop)
	{
		close(fd);
		unlink("heredoc");
		if (dup2(pipefd[0], 0) == -1)
			ft_exit_failure("bdup2 issue", data);
		return ;
	}
	if (dup2(fd, 0) == -1)
		ft_exit_failure("edup2 issue", data);
	close(fd);
	unlink("heredoc");
}
