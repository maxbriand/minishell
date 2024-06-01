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
	init_pcmd(mini, p);
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
		if (p->spl_cmd[0])
		{
			remove_quote_bslash(p->spl_cmd, 0, mini, p);
			//printf("%d = is_expand\n", p->is_expand[0]);
			if (p->spl_cmd[0][0] != '\0')
				define_first_pcmd(p->spl_cmd[0], buf, p);
			i = 1;
			while (p->spl_cmd[i])
			{
				remove_quote_bslash(p->spl_cmd, i, mini, p);
				//printf("%d = is_expand\n", p->is_expand[i]);
				define_p_cmd(p->spl_cmd[i], i, buf, p);
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
		}
		p = p->next;
		buf = buf->next;
	}
	free_p(p);
}
