#include "minishell.h"

void	define_outfile_error(t_commands *p_cmd)
{
	if (p_cmd->msg_error == NULL)
	{
		p_cmd->msg_error = ft_better_strdup("minishell: %s: Permission denied\n", p_cmd->outfile);
		p_cmd->err_is_outfile = true;
		p_cmd->code_error = 1;
	}
	else
		free(p_cmd->outfile);
	p_cmd->outfile = NULL;
}

void	define_infile_error(t_commands *p_cmd)
{
	if (access(p_cmd->infile, F_OK) == 0)
	{
		if (access(p_cmd->infile, R_OK) != 0)
		{
			if (p_cmd->msg_error == NULL)
			{
				p_cmd->err_is_infile = true;
				p_cmd->msg_error = ft_better_strdup("minishell: %s: Permission denied\n", p_cmd->infile);
				p_cmd->code_error = 1;
			}
			else
				free(p_cmd->infile);
			p_cmd->infile = NULL;
		}
	}
	else
	{
		if (p_cmd->msg_error == NULL)
		{
			p_cmd->err_is_infile = true;
			p_cmd->msg_error = ft_better_strdup("minishell: %s: No such file or directory\n", p_cmd->infile);
			p_cmd->code_error = 1;
		}
		else
			free(p_cmd->infile);
		p_cmd->infile = NULL;
	}
}

void	define_p_cmd(char *arg, bool is_arg, t_commands *p_cmd, t_pars *p)
{
	int	fdout;
	//need to look at quote here ?? or define before  ?
	if (arg[0] == '\0')
		return ;
	if (is_arg == true)
	{
		p_cmd->arg = ft_addback(p_cmd->arg, arg);
		return ;
	}
	if (p->next_can_be_opt && is_option(arg, p_cmd) == true)
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
		define_infile_error(p_cmd);
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
		return ;
	}
	if(p->next_can_be_arg)
	{
		p_cmd->arg = ft_addback(p_cmd->arg, arg);
		return ;
	}
	if (p_cmd->cmd == NULL)
	{
		arg_is_cmd(arg, p_cmd, p);
	}

	//after finding something else if already set to "true"
}