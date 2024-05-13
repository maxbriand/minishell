#include "../parsing.h"

//main's of the parsing. if return null, no command need to be done
t_minishell	*parsing(char *input)
{
	t_minishell	*mini;
	t_pars	*p;

	mini = malloc(sizeof(t_minishell));

	if (ft_strlen(input) == 0)
		return (NULL);
	p = define_p(input);
	if (!p)
		return (NULL);
	//cree tout les maillons de cmd
	//ceci est temporaire:
	mini->commands = malloc(sizeof(t_commands));


	define_first_arg(p->tab[0], mini->commands);
	//for the moment I get a struct wich has been
	//segmented with pipe to finally get segmented command


	//test pour voir si je recupere bien tout split sur les |
	int i;
	t_pars *buf;
	buf = p;
	while(p)
	{
		i = 0;
		while (p->tab[i])
		{
			printf("%s\n", p->tab[i]);
			i++;
		}
		p = p->next;
		if (p)
			printf("\n\n");
	}
	p = buf;
	free_p(p);
	return (mini);
}
