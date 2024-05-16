#include "minishell.h"


// if (ft_strncmp(input, "cd", 2) == 0)
// 	ft_cd(env);

// static void	ft_redefine_stdout(t_minishell *data, t_commands *p_cmd, int *pipefd)
// {

// 	// dup2 pipefd
// 	// if no output 
// 	// check append
// }

// static void	ft_redefine_stdin(t_minishell *data, t_commands *p_cmd, int *pipefd)
// {
// 	dup2(pipefd[0], 0);
// 	// if (p_cmd != NULL)
// 		// append input text
		


// 	//append if 2 stdin define

// 	//dup2 pipefd
// }


static void	ft_builtins_exe(t_minishell *data, t_commands *p_cmd)
{
	if (strcmp(p_cmd->cmd, "cd") == 0)
		ft_cd(p_cmd);
	if (strcmp(p_cmd->cmd, "echo") == 0)
		ft_echo();
	if (strcmp(p_cmd->cmd, "env") == 0)
		ft_env();
	if (strcmp(p_cmd->cmd, "exit") == 0)
		ft_exit();
	if (strcmp(p_cmd->cmd, "export") == 0)
		ft_export();
	if (strcmp(p_cmd->cmd, "pwd") == 0)
		ft_pwd();
	if (strcmp(p_cmd->cmd, "unset") == 0)
		ft_unset();
	// free
	exit(EXIT_SUCCESS);
}


static void	ft_child_exe(t_minishell *data, t_commands *p_cmd, int *pipefd)
{
	//check existing command
	// if (p_cmd->b_builtins == 0)
		//ft_check_path(); // add my pushed function not the pipex on my computer

	// stdin redirection
	// if (p_cmd->stdinput != NULL || p_cmd->heredoc == 1 ) // add || pipefd[0] is not enpty
	// 	ft_redefine_stdin(data, p_cmd, pipefd);
	close(pipefd[0]);

	// stdout redirection
	// if (p_cmd->stdoutput != NULL || p_cmd->next != NULL)
	// 	ft_redefine_stdout(data, p_cmd, pipefd);
	close(pipefd[1]);

	// exec command
	if (p_cmd->b_builtins == 0)
	{
		printf("exe none builtin command\n"); 
		//execve();
	}
	else
	{
		ft_builtins_exe(data, p_cmd);
	}
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
		i++;
	}
	close(pipefd[0]);
	close(pipefd[1]);
	while(wait(NULL) != -1);
	return (0);
}
