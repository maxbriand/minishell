#include "minishell.h"


void	define_p_cmd(char *arg, t_commands *p_cmd, t_pars *p)
{
	int	fdout;
	//need to look at quote here ?? or define before  ?
	if (p->next_can_be_opt && is_option(arg, p_cmd, p) == true)
			return ;
	if (is_operator(arg, p_cmd, p) == true)
		return ;
	if (p->next_is_hd_stop)
	{
		p_cmd->hd_stop = ft_addback(p_cmd->hd_stop, arg);
		p->next_is_hd_stop = false;
		return ;
	}
	if (p->next_is_infile)
	{
		if (p_cmd->infile)
			free(p_cmd->infile);
		p_cmd->infile = ft_strdup(arg);
		if (!p_cmd->infile)
			exit (1); //mayday error ?
		p->next_is_infile = false;
		return ;
	}
	if (p->next_is_outfile)
	{
		if (p_cmd->outfile)
			free(p_cmd->outfile);
		p_cmd->outfile = ft_strdup(arg);
		if (!p_cmd->outfile)
			exit (1); //mayday error ?
		fdout = open(p_cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		close(fdout);
		p->next_is_outfile = false;
		return ;
	}
	if(p->next_can_be_arg)
	{
		if (p_cmd->arg)
		{
			p_cmd->arg = ft_strjoin(p_cmd->arg, " ");
			p_cmd->arg = ft_strjoin(p_cmd->arg, arg);
		}
		else
			p_cmd->arg = ft_strdup(arg);
	}
	if (p_cmd->cmd == NULL)
	{
		arg_is_cmd(arg, p_cmd, p);
	}

	//after finding something else if already set to "true"
}
