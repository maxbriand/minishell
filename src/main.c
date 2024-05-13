#include "../minishell.h"
//NOT THE REAL MAIN, THIS ONE IS JUST FOR TESTING MY PARS
int main (int ac, char **av, char **env)
{
	char	*input;
	t_minishell	*mini;

	while (1)
	{
		input = readline("minishell> ");
		add_history(input);

		if (ft_strcmp(input, "history -c") == 0)
			clear_history();

		if (ft_strcmp(input, "exit") == 0)
			break;
		mini = parsing(input);
	}
	return (0);
}
