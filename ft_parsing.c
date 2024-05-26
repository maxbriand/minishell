#include "minishell.h"

//main's of the parsing. if return null, no command need to be done
void	ft_parsing(char *input, t_minishell *mini)
{
	t_pars		*p;
	t_commands	*buf;
	int			i;

	if (ft_strlen(input) == 0)
		return ;
	if (is_error_quote(input) == true)
		return ;
	p = define_p(input, mini);
	if (!p)
		return ;
	define_cmd(mini, p);
	buf = mini->p_cmd;
	while (buf)
	{
		if (buf != mini->p_cmd)
			buf->in_pipe = true;
		define_first_pcmd(p->spl_cmd[0], buf, p);
		i= 1;
		while (p->spl_cmd[i])
		{
			define_p_cmd(p->spl_cmd[i], buf, p);
			i++;
		}
		if (buf->arg_cmd == NULL && buf->cmd)
			cmd_arg_join(buf);



		//COMMENT THE NEXT BLOCK IF YOU DONT WANT PRINTF OF p_cmd
		printf("\n%d = in pipe\n", buf->in_pipe);
		printf("%s = cmd\n", buf->cmd);
		printf("%d = builtins\n", buf->b_builtins);
		printf("%s = option\n", buf->option);
		printf("%s = arg\n", buf->arg);
		printf("%d = append-out\n", buf->append_outfile);
		int y = 0;
		if (buf->hd_stop != NULL)
		{
			while (buf->hd_stop[y])
			{
				printf("%s = hd_stop n%d\n", buf->hd_stop[y], y);
				y++;
			}
		}
		printf("%s = outfile\n", buf->outfile);
		printf("%s = infile\n", buf->infile);
		y = 0;
		if (buf->arg_cmd)
		{
			while (buf->arg_cmd[y])
			{
				printf("%s = cmd+arg+opt[%d]\n", buf->arg_cmd[y], y);
				y++;
			}
		}

		//END OF PRINTF



		p = p->next;
		buf = buf->next;
	}
	free_p(p);
}
