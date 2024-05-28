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
