#include "minishell.h"
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

		//DONT FORGET TO FREE MINI AND ALL P_CMD OR LEAAAKKS
		//free p_cmd
	}
	return (0);
}
