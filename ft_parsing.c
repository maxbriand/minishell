#include "minishell.h"

//main's of the parsing. if return null, no command need to be done
void	ft_parsing(char *input, t_minishell *mini)
{
	t_pars		*p;
	t_commands	*buf;
	int			i;
	int			fdout;

	if (ft_strlen(input) == 0)
		return ;
	if (is_error_quote(input) == true)
		return ;
	p = define_p(input, mini);
	if (!p)
		return ;
	define_cmd(mini, p);
	buf = mini->p_cmd;

//THIS BLOCK IS FOR PRINTF ALL CUT MADE WITH SPLIT
//COMMENT THIS FOR NO PRINTF
	//  int f;
	// f = 0;
	// t_pars *buf2;
	// buf2 = p;
	// while(p)
	// {
	// 	i = 0;
	// 	printf("\n\nMaillon %d:\n", f);
	// 	while (p->spl_cmd[i])
	// 	{
	// 		printf(" Argument %d = %s.\n", i, p->spl_cmd[i]);
	// 		printf(" is_arg shure %d = %d.\n", i, p->is_arg[i]);
	// 		i++;
	// 	}
	// 	p = p->next;
	// 	f++;
	// 	if (p)
	// 		printf("\n\n");
	// }
	// p = buf2;
//END OF PRINTF



	while (buf)
	{
		if (buf != mini->p_cmd)
			buf->in_pipe = true;
		define_first_pcmd(p->spl_cmd[0], buf, p);
		i = 1;
		while (p->spl_cmd[i])
		{
			define_p_cmd(p->spl_cmd[i], p->is_arg[i], buf, p);
			i++;
		}
		if (buf->arg_cmd == NULL && buf->cmd)
			cmd_arg_join(buf);
		if (buf->outfile && buf->err_is_infile == false)
		{
			fdout = open(buf->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fdout <= 0)
				define_outfile_error(buf);
			else
				close(fdout);
		}



		//COMMENT THE NEXT BLOCK IF YOU DONT WANT PRINTF OF p_cmd
		// printf("\n\n%d = in pipe\n", buf->in_pipe);
		// printf("%s = cmd\n", buf->cmd);
		// printf("%d = builtins\n", buf->b_builtins);
		// printf("%s = option\n", buf->option);
		// printf("%s = arg\n", buf->arg);
		// int y = 0;
		// if (buf->arg_cmd)
		// {
		// 	while (buf->arg_cmd[y])
		// 	{
		// 		printf("%s = cmd+arg+opt[%d]\n", buf->arg_cmd[y], y);
		// 		y++;
		// 	}
		// }
		// printf("\n\n");
		// printf("%s = msg_err\n", buf->msg_error);
		// printf("%d = err_is_infile\n", buf->err_is_infile);
		// printf("%d = err_is_outfile\n", buf->err_is_outfile);
		// printf("%d = code_err\n", buf->code_error);

		// y = 0;
		// if (buf->hd_stop != NULL)
		// {
		// 	while (buf->hd_stop[y])
		// 	{
		// 		printf("%s = hd_stop n%d\n", buf->hd_stop[y], y);
		// 		y++;
		// 	}
		// }
		// printf("%d = append-out\n", buf->append_outfile);
		// printf("%s = outfile\n", buf->outfile);
		// printf("%s = infile\n", buf->infile);

		//END OF PRINTF



		p = p->next;
		buf = buf->next;
	}
	//test for see if i get as i need the arg
	// int i = 0;
	// printf("\n%s = arg\n", mini->p_cmd->cmd);
	// printf("%d = is next can be machin\n", p->next_can_be_opt);
	// printf("%d = builtins\n", mini->p_cmd->b_builtins);



	//test pour voir si je recupere bien tout split sur les |

	free_p(p);
}
