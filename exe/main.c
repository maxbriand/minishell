#include "minishell.h"

/*
Parsing have to return:


*/

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_commands	*p_input;
	
	p_input = malloc(sizeof(t_commands *));
	p_input->b_builtins = 1;
	p_input->append_output = 0;
	p_input->input = NULL;
	p_input->output = NULL;
	p_input->cmd = ft_strdup("cd");
	p_input->option = NULL;
	p_input->arg = NULL;
	p_input->next = NULL;
	p_input->heredoc = 0;

	while (1)
	{
		input = readline("minishell> ");
		add_history(input);
		// input go through the parsing
			//ft_parsing

		// ft_parsing();
		ft_exe(NULL, p_input);

		// execution
		if (ft_strcmp(input, "history -c") == 0)
			clear_history();

		if (ft_strcmp(input, "exit") == 0)
			break;
	}
	return (0);
}
