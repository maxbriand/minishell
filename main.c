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

static void	ft_printf_parsing(t_commands *p_cmd)
{
	int i;
	printf("\n\033[1;33mPARSING RESULT:\033[0m");
	while (p_cmd)
	{
		printf("\n\033[1;32mInput redirection:\033[0m");
		if (p_cmd->infile == NULL && !p_cmd->hd_stop && p_cmd->in_pipe == 0)
			printf("\033[1;31m(no redirection)\033[0m");
		printf("\n");
		printf("Infile: %s\n", p_cmd->infile);
		int y = 0;
		if (!p_cmd->hd_stop)
			printf("hd_stop: (null) \n");
		else
		{
			while (p_cmd->hd_stop[y] && p_cmd->hd_stop)
			{
				printf("hd_stop: %s n%d\n", p_cmd->hd_stop[y], y);
				y++;
			}
		}
		printf("In pipe: %d\n", p_cmd->in_pipe);
		printf("\n\033[1;32mOutput redirection:\033[0m");
		if (p_cmd->outfile == NULL)
			printf("\033[1;31m(no redirection)\033[0m");
		printf("\n");
		printf("Outfile: %s \n", p_cmd->outfile);
		printf("Append-out: %d\n", p_cmd->append_outfile);
		printf("\n\033[1;32mCommand:\033[0m\n");
		printf("Cmd: %s\n", p_cmd->cmd);
		printf("Option: %s\n", p_cmd->option);
		printf("Arg: ");
		sleep(1);
		ft_arrprintf(p_cmd->arg);
		printf("\n");
		y = 0;
		printf("cmd+arg+opt: ");
		if (!p_cmd->arg_cmd)
			printf("(null)");
		else
		{
			while (p_cmd->arg_cmd[y])
			{
				printf("%s ", p_cmd->arg_cmd[y]);
				y++;
			}
		}
		printf("\n");
		printf("Builtins: %d\n", p_cmd->b_builtins);
		printf("\n\033[1;32mError:\033[0m\n");
		printf("Msg error: %s", p_cmd->msg_error);
		printf("Code error: %d\n", p_cmd->exit_code);
		printf("Is Infile Error: %d\n", p_cmd->err_is_infile);
		printf("Is Outfile Error: %d\n", p_cmd->err_is_outfile);
		p_cmd = p_cmd->next;
	}
	printf("\n\033[1;32mOutput result: \033[0m\n");
	printf("\n");
}

t_minishell	*ft_init_mish(t_minishell *mish, t_commands *p_cmd, char **env)
{
	mish = malloc(sizeof(t_minishell));
	mish->exit_code = 0;
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
	t_minishell	*data;

	data = ft_init_mish(data, p_cmd, env);
	//data->p_cmd = ft_init_p_cmd_tests(data->p_cmd);
	errcode = 0;
	while (1)
	{
		cmd = readline("mish: ");
		if (!cmd)
			break;
		if (*cmd)
			add_history(cmd);
		ft_parsing(cmd, data);
		// ft_printf_parsing(data->p_cmd);
		ft_exe(data, data->p_cmd);
		//ft_printf("the current error code is %d\n", data->exit_code);
		// if (strcmp(data->p_cmd->cmd, "exit") == 0)
		// {
		// 	dup2(2, 1);
		// 	ft_printf("hey men");
		// 	break;
		// }
		free(cmd);
		//free_p_cmd(data->p_cmd);
	}
	// write(2, "hdsi", 4);
	// t_commands	*test = data->p_cmd;
	// sleep(1);
	// while (test)
	// {
	// 	// ft_printf("cmd: %s ff\n", test->cmd);
	// 	test = test->next;
	// }
	return (data->exit_code);
}
// if (ft_strcmp(cmd, "history -c") == 0)
// 	clear_history();
