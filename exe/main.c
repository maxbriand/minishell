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
	// stdinput
	p_cmd->in_pipe = 0;
	p_cmd->infile = NULL;
	p_cmd->hd_stop = NULL;
	// p_cmd->hd_stop = malloc(sizeof(char *) * 2);
	// p_cmd->hd_stop[0] = ft_strdup("stop1");
	// p_cmd->hd_stop[1] = NULL;
	// p_cmd->hd_stop[1] = ft_strdup("stop2");
	// p_cmd->hd_stop[2] = ft_strdup("stop3");
	// p_cmd->hd_stop[3] = ft_strdup("stop4");
	// stdoutput
	p_cmd->append_outfile = 0;
	p_cmd->outfile = NULL;
	p_cmd->cmd = ft_strdup("ls");
	p_cmd->option = NULL;
	p_cmd->arg = NULL;
	p_cmd->arg_cmd = malloc(sizeof(char *) * 2);
	p_cmd->arg_cmd[0] = ft_strdup("ls");
	// p_cmd->arg_cmd[1] = ft_strdup("-l");
	p_cmd->arg_cmd[1] = NULL;
	p_cmd->next = NULL;

	p_cmd->next = malloc(sizeof(t_commands));
	p_cmd->next->in_pipe = 1;
	p_cmd->next->b_builtins = 0;
	p_cmd->next->hd_stop = NULL;
	p_cmd->next->infile = NULL;
	p_cmd->next->outfile = "out";
	p_cmd->next->append_outfile = 0;
	p_cmd->next->cmd = ft_strdup("cat");
	p_cmd->next->option = NULL;
	p_cmd->next->arg = NULL;
	p_cmd->next->arg_cmd = malloc(sizeof(char *) * 2);
	p_cmd->next->arg_cmd[0] = ft_strdup("cat");
	// p_cmd->next->arg_cmd[1] = ft_strdup("hello arrrrg");
	p_cmd->next->arg_cmd[1] = NULL;
	p_cmd->next->next = NULL;

	// p_cmd->next->next = malloc(sizeof(t_commands));
	// p_cmd->next->next->in_pipe = 1;
	// p_cmd->next->next->hd_stop = NULL;
	// p_cmd->next->next->b_builtins = 0;
	// p_cmd->next->next->append_outfile = 0;
	// p_cmd->next->next->infile = NULL;
	// p_cmd->next->next->outfile = NULL;
	// p_cmd->next->next->cmd = ft_strdup("cat");
	// p_cmd->next->next->option = NULL;
	// p_cmd->next->next->arg = NULL;
	// p_cmd->next->next->arg_cmd = malloc(sizeof(char *) * 2);
	// p_cmd->next->next->arg_cmd[0] = ft_strdup("cat");
	// p_cmd->next->next->arg_cmd[1] = NULL;
	// p_cmd->next->next->next = NULL;
	return(p_cmd);
}

t_minishell	*ft_init_mish(t_minishell *mish, t_commands *p_cmd, char **env)
{
	mish = malloc(sizeof(t_minishell));
	mish->p_cmd = p_cmd;
	mish->env = env;
	mish->open_dquote = 0;
	mish->open_quote = 0;
	return (mish);
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

	mish = ft_init_mish(mish, p_cmd, env);
	//mish->p_cmd = ft_init_p_cmd_tests(mish->p_cmd);
	errcode = 0;
	while (1)
	{
		cmd = readline("-> minishell: ");
		if (!cmd)
			break;
		if (*cmd)
			add_history(cmd);
		if (ft_strcmp(cmd, "history -c") == 0)
			clear_history();
		if (ft_strcmp(cmd, "exit") == 0)
			break;
		ft_parsing(cmd, mish);
		ft_exe(mish, mish->p_cmd);
		free(cmd);
	}
	//ft_free_tests(p_cmd, cmd);
	return (0);
}
