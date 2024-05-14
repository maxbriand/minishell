#include "../parsing.h"

//main's of the parsing. if return null, no command need to be done
void	parsing(char *input, t_minishell *mini)
{
	t_pars	*node;

	if (ft_strlen(input) == 0)
		return ;
	node = define_p(input);
	if (!node)
		return ;
	//cree tout les maillons de cmd
	//ceci est temporaire:
	mini->p_cmd = malloc(sizeof(t_commands));
	mini->p_cmd->append_output = NULL;



	//I NEED TO DEFINE ALL ARG FROM 'p_cmd' BEFORE TESTING,
	// SO LEAKS OR CRASH IS NORMAL ACTUALLY




	define_first_arg(node->spl_cmd[0], mini->p_cmd, node);
	//for the moment I get a struct wich has been
	//segmented with pipe to finally get segmented command

	//test pour voir si je recupere bien tout split sur les |
	int i;
	t_pars *buf;
	buf = node;
	while(node)
	{
		i = 0;
		while (node->spl_cmd[i])
		{
			printf("%s\n", node->spl_cmd[i]);
			i++;
		}
		node = node->next;
		if (node)
			printf("\n\n");
	}
	node = buf;
	free_p(node);
}
