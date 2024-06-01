#include "minishell.h"

static bool	is_operator_not_append(char *arg, bool is_expand, t_commands *p_cmd, t_pars *p)
{
	int		fdout;
	char	**expand;

	if (ft_strncmp(arg, "<", 1) == 0)
	{
		if (ft_strlen(arg) > 1)
		{
			if (is_expand)
			{
				expand = ft_split(arg + 1, ' ');
				if (ft_strlen_array(expand) > 1  && p_cmd->msg_error == NULL)
				{
					p_cmd->msg_error = ft_better_strdup("minishell: %s: ambiguous redirect", arg + 1);
					p_cmd->exit_code = 1;
					p_cmd->err_is_infile = 1;
				}
				free_array(expand);
			}
			if (arg[1] != '>')
			{
				p_cmd->infile = ft_strdup(arg + 1);
				define_infile_error(p_cmd);
			}
			else
			{
				p_cmd->msg_error = ft_strdup("minishell: syntax error near unexpected operator");
				p_cmd->exit_code = 2;
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
			if (is_expand)
			{
				expand = ft_split(arg + 1, ' ');
				if (ft_strlen_array(expand) > 1  && p_cmd->msg_error == NULL)
				{
					p_cmd->msg_error = ft_better_strdup("minishell: %s: ambiguous redirect", arg + 1);
					p_cmd->exit_code = 1;
					p_cmd->err_is_outfile = 1;
				}
				free_array(expand);
			}
			if (arg[1] != '<' && p_cmd->err_is_infile == false)
			{
				p_cmd->outfile = ft_strdup(arg + 1);
				if (!p_cmd->outfile)
					exit(1);//mayday error ?
			}
			else
			{
				p_cmd->msg_error = ft_strdup("minishell: syntax error near unexpected operator");
				p_cmd->exit_code = 2;
			}
		}
		else
			p->next_is_outfile = true;
		return (true);
	}
	return (false);
}

bool	is_operator(char *arg, bool is_expand, t_commands *p_cmd, t_pars *p)
{
	int		fdout;
	char	**expand;

	if (ft_strncmp(arg, "<<", 2) == 0)
	{
		if (ft_strlen(arg) > 2)
		{
			if (is_expand)
			{
				expand = ft_split(arg + 2, ' ');
				if (ft_strlen_array(expand) > 1  && p_cmd->msg_error == NULL)
				{
					p_cmd->msg_error = ft_better_strdup("minishell: %s: ambiguous redirect", arg + 2);
					p_cmd->exit_code = 1;
					p_cmd->err_is_infile = 1;
				}
				free_array(expand);
			}
			if (arg[2] != '<' && arg[2] != '>')
				p_cmd->hd_stop = ft_addback(p_cmd->hd_stop, arg + 2);
			else
			{
				p_cmd->msg_error = ft_strdup("minishell: syntax error near unexpected operator");
				p_cmd->exit_code = 2;
			}
		}
		else
			p->next_is_hd_stop = true;
		return (true);
	}
	else if (ft_strncmp(arg, ">>", 2) == 0)
	{
		if (ft_strlen(arg) > 2)
		{
			if (is_expand)
			{
				expand = ft_split(arg + 2, ' ');
				if (ft_strlen_array(expand) > 1  && p_cmd->msg_error == NULL)
				{
					p_cmd->msg_error = ft_better_strdup("minishell: %s: ambiguous redirect", arg + 2);
					p_cmd->exit_code = 1;
					p_cmd->err_is_outfile = 1;
				}
				free_array(expand);
			}
			if (arg[2] != '<' && arg[2] != '>' && p_cmd->err_is_infile == false)
			{
				p_cmd->append_outfile = true;
				p_cmd->outfile = ft_strdup(arg + 2);
				if (!p_cmd->outfile)
					exit (1); //mayday error ?
			}
			else
			{
				p_cmd->msg_error = ft_strdup("minishell: syntax error near unexpected operator");
				p_cmd->exit_code = 2;
			}
		}
		else
		{
			p->next_is_outfile = true;
			p_cmd->append_outfile = true;
		}
		return (true);
	}
	return (is_operator_not_append(arg, is_expand, p_cmd, p));
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
	if (strcmp(arg, "echo") == 0 || strcmp(arg, "cd") == 0
		|| strcmp(arg, "pwd") == 0 || strcmp(arg, "export") == 0
		|| strcmp(arg, "unset") == 0 || strcmp(arg, "env") == 0
		|| strcmp(arg, "exit") == 0)
	{
		p_cmd->b_builtins = true;
		if (strcmp(arg, "env") == 0)
			p->next_is_infile = true;
		return (true);
	}
	return (true);
}
