#include "../parsing.h"

//main's of the parsing. if return null, no command need to be done
void	ft_parsing(char *input, t_minishell *mini)
{
	t_pars	*p;

	if (ft_strlen(input) == 0)
		return ;
	p = define_p(input);
	if (!p)
		return ;
	//cree tout les maillons de cmd
	//ceci est temporaire:
	define_cmd(mini, p);
	//printf("%s\n", mini->p_cmd->arg);



	//I NEED TO DEFINE ALL ARG FROM 'p_cmd' BEFORE TESTING,
	// SO LEAKS OR CRASH IS NORMAL ACTUALLY




	define_first_arg(p->spl_cmd[0], mini, p);
	//for the moment I get a struct wich has been
	//segmented with pipe to finally get segmented command

//test for see if i get as i need the arg
	int i = 0;
	printf("\n%s = arg\n", mini->p_cmd->cmd);
	printf("%d = is next can be machin\n", p->next_can_be_opt);



	//test pour voir si je recupere bien tout split sur les |
	// int i;
	// int f;
	// f = 0;
	// t_pars *buf;
	// buf = p;
	// while(p)
	// {
	// 	i = 0;
	// 	printf("\n\nMaillon %d:\n", f);
	// 	while (p->spl_cmd[i])
	// 	{
	// 		printf(" Argument %d = %s\n", i, p->spl_cmd[i]);
	// 		i++;
	// 	}
	// 	p = p->next;
	// 	f++;
	// 	if (p)
	// 		printf("\n\n");
	// }
	// p = buf;
	free_p(p);
}
