#include "minishell.h"

/*
Parsing have to return:


*/

int	main(int ac, char **av, char **env)
{
	char 		*cmd;
	t_commands	*p_cmd;

	p_cmd = malloc(sizeof(t_commands));
	p_cmd->b_builtins = 1;
	p_cmd->append_output = 0;
	p_cmd->stdinput = NULL;
	p_cmd->stdoutput = NULL;
	p_cmd->cmd = ft_strdup("cd");
	p_cmd->option = NULL;
	p_cmd->arg = NULL;
	p_cmd->next = NULL;
	p_cmd->heredoc = 0;

	while (1)
	{
		cmd = readline("minishell: ");
		
		add_history(cmd);
		// cmd go through the parsing
			//ft_parsing


		// ft_parsing();
		//ft_exe(NULL, p_cmd);

		if (ft_strcmp(cmd, "env") == 0)
		{
			while (*env)
			{
				ft_printf("%s\n", *env);
				env++;
			}

		}

		// execution
		if (ft_strcmp(cmd, "history -c") == 0)
			clear_history();

		if (ft_strcmp(cmd, "exit") == 0)
			break;
	
		free(cmd);

	}
	return (0);
}
