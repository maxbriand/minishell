#include "minishell.h"

static bool	is_operator_not_append(char *arg, t_commands *p_cmd, t_pars *p)
{
	int	fdout;

	if (ft_strncmp(arg, "<", 1) == 0)
	{
		if (ft_strlen(arg) > 1)
		{
			if (arg[1] != '>')
			{
				p_cmd->infile = ft_strdup(arg + 1);
				define_infile_error(p_cmd);
			}
		}
		else
			p->next_is_infile = true;
		return (true);
	}
	else if (ft_strncmp(arg, ">", 1) == 0)
	{
		if (ft_strlen(arg) > 1)
		{
			if (arg[1] != '<')
			{
				p_cmd->outfile = ft_strdup(arg + 1);
				fdout = open(p_cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fdout <= 0)
					define_outfile_error(p_cmd);
				else
					close(fdout);
				}
		}
		else
			p->next_is_outfile = true;
		return (true);
	}
	return (false);
}

bool	is_operator(char *arg, t_commands *p_cmd, t_pars *p)
{
	int	fdout;

	if (ft_strncmp(arg, "<<", 2) == 0)
	{
		if (ft_strlen(arg) > 2)
		{
			if (arg[2] != '<' || arg[2] != '>')
				p_cmd->hd_stop = ft_addback(p_cmd->hd_stop, arg + 2);
		}
		else
			p->next_is_hd_stop = true;
		return (true);
	}
	else if (ft_strncmp(arg, ">>", 2) == 0)
	{
		if (ft_strlen(arg) > 2)
		{
			if (arg[2] != '<' || arg[2] != '>')
			{
				p_cmd->append_outfile = true;
				p_cmd->outfile = ft_strdup(arg + 2);
				fdout = open(p_cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fdout <= 0)
					define_outfile_error(p_cmd);
				else
					close(fdout);
			}
		}
		else
		{
			p->next_is_outfile = true;
			p_cmd->append_outfile = true;
		}
		return (true);
	}
	return (is_operator_not_append(arg, p_cmd, p));
//Seul les bg ultime lirons ce message
}

bool	is_option(char *arg, t_commands *p_cmd)
{
	if (arg[0] == '-')
	{
		if (p_cmd->option)
		{
			p_cmd->option = ft_strjoin(p_cmd->option, arg + 1);
			if (!p_cmd->option)
				exit (1);//mayday return error ?
		}
		else
		{
			p_cmd->option = ft_strdup(arg);
			if (!p_cmd->option)
				exit (1); //mayday return error ?
		}
		return (true);
	}
	return (false);
}

bool	arg_is_cmd(char *arg, t_commands *p_cmd, t_pars *p)
{
	p->next_can_be_opt = true;
	p->next_can_be_arg = true;
	p_cmd->cmd = ft_strdup(arg);
	if (!p_cmd->cmd)
		exit (1);//Error message ?
		// || (access(arg, F_OK) == 1
		// && (strcmp(arg + (ft_strlen(arg) - 5), "\\echo") == 0
		// || strcmp(arg + (ft_strlen(arg) - 3), "\\cd") == 0
		// || strcmp(arg + (ft_strlen(arg) - 4), "\\pwd") == 0
		// || strcmp(arg + (ft_strlen(arg) - 7), "\\export") == 0
		// || strcmp(arg + (ft_strlen(arg) - 6), "\\unset") == 0
		// || strcmp(arg + (ft_strlen(arg) - 4), "\\env") == 0)))
	if (strcmp(arg, "echo") == 0 || strcmp(arg, "cd") == 0
		|| strcmp(arg, "pwd") == 0 || strcmp(arg, "export") == 0
		|| strcmp(arg, "unset") == 0 || strcmp(arg, "env") == 0)
	{
		p_cmd->b_builtins = true;
		return (true);
	}
	return (true);
}
