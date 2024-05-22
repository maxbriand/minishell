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

void	ft_child_exe(t_minishell *data, t_commands *c_cmd, int **pipefds, int c)
{
	char	*path;

	ft_set_pipefd(data, c_cmd, pipefds, c);

	// if (c == 1)
	// 	sleep(5);
	// ft_printf("c_cmd is %d one, pipefd0 is %p and pipefd1 is %p\n", c, c_cmd->pipefd0, c_cmd->pipefd1);
	// sleep(1);
	// if (c == 0)
	// {
	// 	ft_printf("in c %d for pipefd0, pipefd1[1] is %d\n", c, c_cmd->pipefd1[1]);
	// 	sleep(1);
	// }
	// else
	// {
	// 	ft_printf("in c %d for pipefd1, pipefd0[0] is %d \n", c, c_cmd->pipefd0[0]);
	// 	sleep(1);
	// }

	if (c_cmd->b_builtins == 0)
		path = ft_check_path(data, c_cmd);

	if (c_cmd->infile || c_cmd->hd_stop || c_cmd->in_pipe)
		ft_input_redir(data, c_cmd, c_cmd->pipefd0);

	if (c_cmd->outfile || c_cmd->next != NULL)
		ft_output_redir(data, c_cmd, c_cmd->pipefd1);

	ft_close_pipes(data, pipefds);

	// write(2, "before exe of ", 14);
	// write(2, "\n", 1);

	// if (c_cmd->b_builtins == 0)
	execve(path, c_cmd->arg_cmd, data->env);
	ft_exit_failure("execution issue\n", data);
	// else
	// 	ft_builtins_exe(data, c_cmd);
}

void	ft_exe(t_minishell *data, t_commands *p_cmd)
{
	int		c;
	pid_t	pid;

	data->pipe_nbr = ft_pipe_counter(p_cmd);
	data->pipefds = ft_create_pipes(data->pipe_nbr, data);
	c = 0;
	while (p_cmd)
	{
		pid = fork();
		if (pid == -1)
			ft_exit_failure("fork creation issue", data);
		if (pid == 0)
				ft_child_exe(data, p_cmd, data->pipefds, c);
		p_cmd = p_cmd->next;
		c++;
	}
	ft_close_pipes(data, data->pipefds);
	while(wait(NULL) != -1);
}
