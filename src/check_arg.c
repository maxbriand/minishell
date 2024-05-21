#include "../parsing.h"

bool	is_error_quote(char *str)
{
	int	i;
	int	nb_quote;
	int	nb_dquote;

	i = 0;
	nb_quote = 0;
	nb_dquote = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			nb_quote++;
		else if (str[i] == '\"')
			nb_dquote++;
		i++;
	}
	if (nb_quote % 2 == 1 || nb_dquote % 2 == 1)
	{
		printf("minishell: Error syntax: Quote not closed\n");//mayday exit error ?
		return (true);
	}
	return (false);
}

static bool	is_operator_not_append(char *arg, t_commands *cmd, t_pars *p)
{
	if (ft_strncmp(arg, "<", 1) == 0)
	{
		if (ft_strlen(arg) > 1)
			cmd->infile = ft_strdup(arg + 1);
		else
			p->next_is_infile = true;
		return (true);
	}
	else if (ft_strncmp(arg, ">", 1) == 0)
	{
		cmd->append_outfile = false;
		if (ft_strlen(arg) > 1)
			cmd->outfile = ft_strdup(arg + 1);
		else
			p->next_is_outfile = true;
		return (true);
	}
	return (false);
}

bool	is_operator(char *arg, t_commands *cmd, t_pars *p)
{
	if (ft_strncmp(arg, "<<", 2) == 0)
	{
		if (ft_strlen(arg) > 2)
			cmd->infile = ft_strdup(arg + 2);
		else
			p->next_is_hd_stop = true;
		return (true);
	}
	else if (ft_strncmp(arg, ">>", 2) == 0)
	{
		cmd->append_outfile = true;
		if (ft_strlen(arg) > 2)
			cmd->outfile = ft_strdup(arg + 2);
		else
			p->next_is_outfile = true;
		return (true);
	}
	else if (is_operator_not_append(arg, cmd, p) == true)
		return (true);
	return (false);
//Seul les bg ultime lirons ce message
}

bool	is_option(char *arg, t_commands *cmd, t_pars *p)
{
	if (arg[0] == '-')
	{
		if (cmd->option)
		{
			cmd->option = ft_strjoin(cmd->option, arg + 1);
			if (!cmd->option)
				exit (1);//mayday return error ?
		}
		else
		{
			cmd->option = ft_strdup(arg);
			if (!cmd->option)
				exit (1); //mayday return error ?
		}
		return (true);
	}
	return (false);
}

bool	arg_cmd(char *arg, t_commands *cmd, t_pars *p)
{
	p->next_can_be_opt = true;
	p->next_can_be_arg = true;
	cmd->cmd = ft_strdup(arg);
	if (!cmd->cmd)
		exit (1);//Error message ?
	return (true);
}
