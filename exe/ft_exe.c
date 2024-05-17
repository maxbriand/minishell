#include "minishell.h"


// if (ft_strncmp(input, "cd", 2) == 0)
// 	ft_cd(env);

// static void	ft_redir_output(t_minishell *data, t_commands *p_cmd, int *pipefd)
// {

// 	// dup2 pipefd
// 	// if no output 
// 	// check append
// }

// have I to add +1 for the null terminated?
static void	ft_write_heredoc(int fd, char *hd_stop)
{
	char	*input;
	
	while (1)
	{
		input = readline(">");
		if (!input)
			break;
		if (strcmp(input, hd_stop))
			break;
		write(fd, input, strlen(input) + 1);
	}
}

static int	ft_iterate_heredocs(t_commands *cmd)
{
	int	i;
	int	fd;
	
	fd = open("heredoc", O_RDWR); // check heredoc file permissions
	i = 0;
	while (cmd->hd_stop[i])
	{
		ft_write_heredoc(fd, cmd->hd_stop[i]);
		ft_printf("%s\n", get_next_line(fd));
		i++;
	}
	return (fd);
}

static void	ft_redir_input(t_minishell *data, t_commands *c_cmd, int *pipefd)
{
	int	fd;
	
	if (c_cmd->infile != NULL)
	{
		fd = open(c_cmd->infile, O_RDONLY);
		if (fd == -1)
			ft_exit_failure("Open infile issue", data);
		dup2(fd, 0);
		close(fd);
		//fd = ft_iterate_heredocs(c_cmd);
		//close(fd);
		

		
		return ;
	}

	// // attribute fd;
	// if (c_cmd->hd_stop)
	// {
	// 	dup2();
	// }// be carefull, the string is perhaps no nul terminated
	// else
	// {
	// 	dup2(pipefd[0], 0);
	// }
}


static void	ft_builtins_exe(t_minishell *data, t_commands *c_cmd)
{
	if (strcmp(c_cmd->cmd, "cd") == 0)
		ft_cd(c_cmd);
	if (strcmp(c_cmd->cmd, "echo") == 0)
		ft_echo();
	if (strcmp(c_cmd->cmd, "env") == 0)
		ft_env();
	if (strcmp(c_cmd->cmd, "exit") == 0)
		ft_exit();
	if (strcmp(c_cmd->cmd, "export") == 0)
		ft_export();
	if (strcmp(c_cmd->cmd, "pwd") == 0)
		ft_pwd();
	if (strcmp(c_cmd->cmd, "unset") == 0)
		ft_unset();
	// free
	exit(EXIT_SUCCESS);
}

static void	ft_child_exe(t_minishell *data, t_commands *c_cmd, int *pipefd)
{
	char	*path;
	
	if (c_cmd->b_builtins == 0)
		path = ft_check_path(data, c_cmd);

	if (c_cmd->infile || c_cmd->hd_stop || c_cmd->in_pipe)
		ft_redir_input(data, c_cmd, pipefd);
	close(pipefd[0]);

	// stdout redirection
	// if (c_cmd->outfile || c_cmd->next != NULL)
	// 	ft_redefine_stdout(data, c_cmd, pipefd);
	close(pipefd[1]);

	// exec command
	if (c_cmd->b_builtins == 0)
		execve(path, c_cmd->arg_cmd, NULL);
	// else
	// 	ft_builtins_exe(data, c_cmd);
	ft_exit_failure("execution issue\n", data);
}

int	ft_exe(t_minishell *data, t_commands *p_cmd)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		ft_exit_failure("pipe creation issue", data);
	while (p_cmd)
	{
		pid = fork();
		if (pid == -1)
			ft_exit_failure("fork creation issue", data);
		if (pid == 0)
			ft_child_exe(data, p_cmd, pipefd);
		p_cmd = p_cmd->next;
	}
	close(pipefd[0]);
	close(pipefd[1]);	
	while(wait(NULL) != -1);
	return (0);
}
