#include "minishell.h"

static void	ft_builtins_exe(t_minishell *data, t_commands *c_cmd)
{
	if (strcmp(c_cmd->cmd, "cd") == 0)
		ft_cd(data, c_cmd);
	else if (strcmp(c_cmd->cmd, "echo") == 0)
		ft_echo(data, c_cmd);
	else if (strcmp(c_cmd->cmd, "env") == 0)
		ft_env(data, c_cmd);
	else if (strcmp(c_cmd->cmd, "exit") == 0)
		ft_exit(data, c_cmd);
	else if (strcmp(c_cmd->cmd, "export") == 0)
		ft_export(data, c_cmd);
	else if (strcmp(c_cmd->cmd, "pwd") == 0)
		ft_pwd(data, c_cmd);
	else if (strcmp(c_cmd->cmd, "unset") == 0)
		ft_unset(data, c_cmd);
	exit(EXIT_SUCCESS);
}

void	ft_child_exe(t_minishell *data, t_commands *c_cmd, int **pipefds, int c)
{
	char	*path;
	
	
	printf("the localization of ok is %p and the value is %d\n", &(data->ok), data->ok);
	data->ok = 3;
	printf("the localization of ok is %p and the value is %d\n", &(data->ok), data->ok);


	ft_set_pipefd(data, c_cmd, pipefds, c);
	if (c_cmd->b_builtins == 0)
		path = ft_check_path(data, c_cmd);
	if (c_cmd->infile || c_cmd->hd_stop || c_cmd->in_pipe)
		ft_input_redir(data, c_cmd, c_cmd->pipefd0);
	if (c_cmd->outfile || c_cmd->next != NULL)
		ft_output_redir(data, c_cmd, c_cmd->pipefd1);
	ft_close_pipes(data, pipefds);
	if (c_cmd->b_builtins == 0)
		execve(path, c_cmd->arg_cmd, data->env);
	else
		ft_builtins_exe(data, c_cmd);
	ft_exit_failure("execution issue\n", data);
}

void	ft_exe(t_minishell *data, t_commands *p_cmd)
{
	int		c;
	pid_t	pid;


	// test
	data->ok = 5;
	printf("the localization of ok is %p and the value is %d\n", &(data->ok), data->ok);


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


	// test
	printf("the localization of ok is %p and the value is %d\n", &(data->ok), data->ok);
}
