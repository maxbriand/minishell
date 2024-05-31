#include "minishell.h"

void	free_array(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_p(t_pars *p)
{
	t_pars	*p_buf;

	while(p)
	{
		p_buf = p;
		free_array(p->spl_cmd);
		free(p->is_arg);
		p = p->next;
		free(p_buf);
	}
	if (p)
		free(p);
}

void	free_p_cmd(t_commands *p_cmd)
{
	t_commands	*buf;

	while (p_cmd)
	{
		buf = p_cmd;
		p_cmd = p_cmd->next;
		if (buf->arg)
			free(buf->arg);
		if (buf->arg_cmd)
			free_array(buf->arg_cmd);
		if (buf->cmd)
			free(buf->cmd);
		if (buf->hd_stop)
			free_array(buf->hd_stop);
		if (buf->infile)
			free(buf->infile);
		if (buf->option)
			free(buf->option);
		if (buf->outfile)
			free(buf->outfile);
		if (buf->msg_error)
			free(buf->msg_error);
		free(buf);
	}
}
