#include "minishell.h"

int g_sig = 0;

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
		ft_printf("\n\033[1;32mCommand:\033[0m");
		if (p_cmd->cmd == NULL)
			ft_printf("\033[1;31m(no command)\033[0m\n");
		else
			ft_printf("\n");
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
		ft_printf("Msg error: %s\n", p_cmd->msg_error);
		ft_printf("Code error: %d\n", p_cmd->exit_code);
		ft_printf("Is Infile Error: %d\n", p_cmd->err_is_infile);
		ft_printf("Is Outfile Error: %d\n", p_cmd->err_is_outfile);
		p_cmd = p_cmd->next;
	}
	ft_printf("\n\033[1;32mOutput result: \033[0m\n");
}

t_minishell	*ft_init_mish(t_minishell *data, char **env)
{
	data = malloc(sizeof(t_minishell));
	if (!data)
		ft_exitf("malloc issue", 1, NULL, data);
	data->env = env;
	data->p_cmd = NULL;
	data->open_dquote = 0;
	data->open_quote = 0;
	data->export = NULL;
	return (data);
}

int	main(int ac, char **av, char **env)
{
	char 		*cmd;
	t_minishell	*data;

	data = ft_init_mish(data, env);
	while (1)
	{
		ft_signals(0);
		cmd = readline("mish: ");
		if (g_sig == 2)
			data->exit_code = 130;
		if (g_sig == 3)
			data->exit_code = 131;
		g_sig = 0;
		if (!cmd)
			break;
		if (*cmd)
			add_history(cmd);
		ft_parsing(cmd, data);
		// ft_printf_parsing(data, data->p_cmd);
		ft_signals(1);
		ft_exe(data, data->p_cmd);
		free(cmd);
		// free_p_cmd(data->p_cmd);
	}
	ft_printf("exit\n");
	return (data->exit_code);
}
