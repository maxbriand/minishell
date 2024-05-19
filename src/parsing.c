#include "../parsing.h"

//main's of the parsing. if return null, no command need to be done
void	ft_parsing(char *input, t_minishell *mini)
{
	t_pars		*p;
	t_commands	*buf;
	int			i;

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



	buf = mini->p_cmd;
	while (buf )
	{
		if (buf != mini->p_cmd)
			mini->p_cmd->in_pipe = true;
		define_first_pcmd(p->spl_cmd[0], buf, p);
		i= 1;
		while (p->spl_cmd[i])
		{
			define_p_cmd(p->spl_cmd[i], buf, p);
			i++;
		}



		//COMMENT THE NEXT BLOCK IF YOU DONT WANT PRINTF OF p_cmd
		printf("\n%d = in pipe\n", buf->in_pipe);
		printf("%s = cmd\n", buf->cmd);
		printf("%d = builtins\n", buf->b_builtins);
		printf("%s = option\n", buf->option);
		printf("%s = arg\n", buf->arg);
		printf("%d = append-out\n", buf->append_output);
		int y = 0;
		if (buf->hd_stop != NULL)
		{
			while (buf->hd_stop[y])
			{
				printf("%s = hd_stop n%d\n", buf->hd_stop[y], y);
				y++;
			}
		}
		printf("%s = outfile\n", buf->stdoutput);
		printf("%s = infile\n\n", buf->stdinfile);
		//END OF PRINTF



		p = p->next;
		buf = buf->next;
	}
	//for the moment I get a struct wich has been
	//segmented with pipe to finally get segmented command

//test for see if i get as i need the arg
	// int i = 0;
	// printf("\n%s = arg\n", mini->p_cmd->cmd);
	// printf("%d = is next can be machin\n", p->next_can_be_opt);
	// printf("%d = builtins\n", mini->p_cmd->b_builtins);



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
