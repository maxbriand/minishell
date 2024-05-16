#include "minishell.h"

static void	ft_free_tests(t_commands *p_cmd, char *cmd)
{
	free(p_cmd->next->cmd);
	free(p_cmd->next->arg);
	free(p_cmd->next);

	free(cmd);
	free(p_cmd->cmd);
	free(p_cmd->arg);
	free(p_cmd);
}

// Malloc unprotected
static t_commands	*ft_init_p_cmd_tests(t_commands *p_cmd)
{
	p_cmd = malloc(sizeof(t_commands));
	p_cmd->b_builtins = 0;
	p_cmd->append_output = 0;
	p_cmd->stdinput = NULL;
	p_cmd->stdoutput = NULL;
	p_cmd->cmd = ft_strdup("ls");
	p_cmd->option = NULL;
	p_cmd->arg = ft_strdup("exe");
	p_cmd->next = NULL;
	p_cmd->hd_stop = NULL;

	p_cmd->next = malloc(sizeof(t_commands));
	p_cmd->next->b_builtins = 0;
	p_cmd->next->append_output = 0;
	p_cmd->next->stdinput = NULL;
	p_cmd->next->stdoutput = NULL;
	p_cmd->next->cmd = ft_strdup("cat");
	p_cmd->next->option = NULL;
	p_cmd->next->arg = ft_strdup("exe");
	p_cmd->next->next = NULL;
	p_cmd->next->hd_stop = NULL;

	return(p_cmd);
}

/*
	p_cmd contains contains only good values 
	except a bad cmd / option / argument
*/
int	main(int ac, char **av, char **env)
{
	char 		*cmd;
	int			errcode;
	t_commands	*p_cmd;
	t_minishell	*mish;

	p_cmd = ft_init_p_cmd_tests(p_cmd);
	
	errcode = 0;
	while (1)
	{
		cmd = readline("-> minishell: ");
		if (!cmd)
			break;
		if (*cmd)
			add_history(cmd);

		//ft_parsing
			// use errcode like on exe

		// execution
		if (ft_strcmp(cmd, "history -c") == 0)
			clear_history();
		if (ft_strcmp(cmd, "exit") == 0)
			break;
		free(cmd);

		errcode = ft_exe(mish, p_cmd);
		if (errcode == -1)
			return (ft_write_error("parent issue in exe"));
	}
	ft_free_tests(p_cmd, cmd);
	return (0);
}
