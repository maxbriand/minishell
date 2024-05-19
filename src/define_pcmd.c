#include "../parsing.h"


void	define_p_cmd(char *arg, t_commands *p_cmd, t_pars *p)
{
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
		if (p_cmd->stdinfile)
			free(p_cmd->stdinfile);
		p_cmd->stdinfile = ft_strdup(arg);
		if (!p_cmd->stdinfile)
			exit (1); //mayday error ?
		p->next_is_infile = false;
		return ;
	}
	if (p->next_is_outfile)
	{
		if (p_cmd->stdoutput)
			free(p_cmd->stdoutput);
		p_cmd->stdoutput = ft_strdup(arg);
		if (!p_cmd->stdoutput)
			exit (1); //mayday error ?
		p->next_is_outfile = false;
		return ;
	}
	if(p->next_can_be_arg)
	{
		p->next_can_be_arg = false;
		p_cmd->arg = ft_strdup(arg);
	}
	if (p_cmd->cmd == NULL)
	{
		arg_cmd(arg, p_cmd, p);
	}

	//note: need to set cmd->is_arg_can_be_opt to "false"
	//after finding something else if already set to "true"
}
