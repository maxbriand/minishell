#include "minishell.h"

/*
Parsing have to return:


*/

int	main(int ac, char **av, char **env)
{
	char	*input;
	
	while (1)
	{
		input = readline("minishell> ");
		add_history(input);
		// input go through the parsing
			//ft_parsing
		
		if (ft_strncmp(input, "cd", 2) == 0)
			ft_cd(env);
		
		// execution
		if (ft_strcmp(input, "history -c") == 0)
			clear_history();
	
		if (ft_strcmp(input, "exit") == 0)
			break;
	}
	return (0);
}
