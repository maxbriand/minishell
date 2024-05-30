#include "minishell.h"

//printf("%s = msg_err\n", buf->msg_error);
		// printf("%d = err_is_infile\n", buf->err_is_infile);
		// printf("%d = err_is_outfile\n", buf->err_is_outfile);
		// printf("%d = code_err\n", buf->code_error);

static void	ft_printf_parsing(t_commands *p_cmd)
{
	printf("\n\033[1;33mPARSING RESULT:\033[0m");
	if (p_cmd)
	{
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
					printf("hd_stop: %s = n%d\n", p_cmd->hd_stop[y], y);
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
			y = 0;
			if (p_cmd->arg)
			{
				while (p_cmd->arg[y])
				{
					printf("Arg[%d]: %s\n", y, p_cmd->arg[y]);
					y++;
				}
			}
			else
				printf("Arg: NULL\n");
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
			printf("Msg error: %s\n", p_cmd->msg_error);
			printf("Code error: %d\n", p_cmd->code_error);
			printf("Is Infile Error: %d\n", p_cmd->err_is_infile);
			printf("Is Outfile Error: %d\n", p_cmd->err_is_outfile);
			p_cmd = p_cmd->next;
		}
		printf("\n\033[1;32mOutput result: \033[0m\n");
		printf("\n\n");
	}
}


//NOT THE REAL MAIN, THIS ONE IS JUST FOR TESTING MY PARS
int main (int ac, char **av, char **env)
{
	char	*input;
	t_minishell	*mini;

	//I absolutly need to have path->env define in mini before going to my parsing
	//Same for mini->env
	mini = malloc(sizeof(t_minishell));
	mini->env = env;
	//mini->path_env = catch_path(env);

	(void)ac;
	(void)av;
	while (1)
	{
		input = readline("\n\nminishell> ");
		add_history(input);

		if (ft_strcmp(input, "history -c") == 0)
			clear_history();

		if (ft_strcmp(input, "exit") == 0)
			break;

		//here
		ft_parsing(input, mini);
		ft_printf_parsing(mini->p_cmd);
		//DONT FORGET TO FREE MINI AND ALL P_CMD OR LEAAAKKS
		//free p_cmd
	}
	return (0);
}
