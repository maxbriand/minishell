#include "minishell.h"

int g_sig = 0;

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

static void	ft_printf_parsing(t_minishell *data, t_commands *p_cmd)
{
	int i;
	ft_printf("\n\033[1;33mPARSING RESULT:\033[0m");
	while (p_cmd)
	{
		ft_printf("\n\033[1;32mInput redirection:\033[0m");
		if (p_cmd->infile == NULL && !p_cmd->hd_stop && p_cmd->in_pipe == 0)
			ft_printf("\033[1;31m(no redirection)\033[0m");
		ft_printf("\n");
		ft_printf("Infile: %s\n", p_cmd->infile);
		int y = 0;
		if (!p_cmd->hd_stop)
			ft_printf("hd_stop: (null) \n");
		else
		{
			while (p_cmd->hd_stop[y] && p_cmd->hd_stop)
			{
				ft_printf("hd_stop: %s n%d\n", p_cmd->hd_stop[y], y);
				y++;
			}
		}
		ft_printf("In pipe: %d\n", p_cmd->in_pipe);
		ft_printf("\n\033[1;32mOutput redirection:\033[0m");
		if (p_cmd->outfile == NULL)
			ft_printf("\033[1;31m(no redirection)\033[0m");
		ft_printf("\n");
		ft_printf("Outfile: %s \n", p_cmd->outfile);
		ft_printf("Append-out: %d\n", p_cmd->append_outfile);
		ft_printf("\n\033[1;32mCommand:\033[0m\n");
		ft_printf("Cmd: %s\n", p_cmd->cmd);
		ft_printf("Option: %s\n", p_cmd->option);
		ft_printf("Arg: ");
		ft_arrprintf(p_cmd->arg);
		ft_printf("\n");
		ft_printf("Nbr of arg: %d\n", ft_arrlen(p_cmd->arg));
		y = 0;
		ft_printf("cmd+arg+opt: ");
		if (!p_cmd->arg_cmd)
			ft_printf("(null)");
		else
		{
			while (p_cmd->arg_cmd[y])
			{
				ft_printf("%s ", p_cmd->arg_cmd[y]);
				y++;
			}
		}
		ft_printf("\n");
		ft_printf("Builtins: %d\n", p_cmd->b_builtins);
		ft_printf("\n\033[1;32mError:\033[0m\n");
		if (!p_cmd->msg_error)
			ft_printf("Msg error: %s\n", p_cmd->msg_error);
		else
			ft_printf("Msg error: %s\n", p_cmd->msg_error);
		ft_printf("Code error: %d\n", p_cmd->exit_code);
		ft_printf("Is Infile Error: %d\n", p_cmd->err_is_infile);
		ft_printf("Is Outfile Error: %d\n", p_cmd->err_is_outfile);
		p_cmd = p_cmd->next;
	}
	ft_printf("\n\033[1;32mOutput result: \033[0m\n");

	// ft_printf("This is the env variable pt: %p and fst element %s\n", data->env, *data->env);
}

t_minishell	*ft_init_mish(t_minishell *data, t_commands *p_cmd, char **env)
{
	data = malloc(sizeof(t_minishell));
	data->exit_code = 0;
	data->p_cmd = p_cmd;
	data->env = env;
	data->open_dquote = 0;
	data->open_quote = 0;
	data->export = NULL;
	return (data);
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
	ft_set_newterm(data);
	ft_signals(data);
	//data->p_cmd = ft_init_p_cmd_tests(data->p_cmd);
	errcode = 0;
	while (1)
	{
		cmd = readline("mish: ");
		if (g_sig == 2)
			data->exit_code = 130;
		g_sig = 0;
		if (!cmd)
			break;
		if (*cmd)
			add_history(cmd);
		ft_parsing(cmd, data);
		if (strcmp(cmd, "env") == 0)

		// HAVE TO DELETE that
			ft_env(data, data->p_cmd);


		// ft_printf_parsing(data, data->p_cmd);
		ft_exe(data, data->p_cmd);
		free(cmd);
		// free_p_cmd(data->p_cmd);
	}
	return (data->exit_code);
}
