#include "minishell.h"

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
		ft_input_redir(data, c_cmd, pipefd);
	close(pipefd[0]);

	if (c_cmd->outfile || c_cmd->next != NULL)
		ft_output_redir(data, c_cmd, pipefd);
	close(pipefd[1]);

	// write(2, "before exe of ", 14);
	// write(2, c_cmd->test, 1);
	// write(2, "\n", 1);

	if (c_cmd->b_builtins == 0)
		execve(path, c_cmd->arg_cmd, data->env);
	ft_exit_failure("execution issue\n", data);
	// else
	// 	ft_builtins_exe(data, c_cmd);
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
