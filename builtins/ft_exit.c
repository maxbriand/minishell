#include "minishell.h"

static int	ft_strcheck(char *str)
{
	while (*str)
	{
		if (ft_isdigit(*str) == 1)
			return (1);
		str++;
	}
	return (0);
}

static int	ft_arrcheck(t_commands *c_cmd)
{
	int	i;

	i = 0;
	while (c_cmd->arg[i])
	{
		if (ft_strcheck(c_cmd->arg[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_exit_parsing(t_minishell *data, t_commands *c_cmd)
{
	// non numeric argument
	if (ft_arrcheck(c_cmd) != 0)
	{
		ft_write_error("exit");
		ft_write_error(" numeric argument required");
		data->exit_code = 2;
		exit(2);
	}
	// too many arguments
	if (ft_arrlen(c_cmd->arg) > 1)
	{
		ft_write_error("exit");
		ft_write_error(" too many arguments");
		data->exit_code = 1;
		return (1);
	}
	return (0);
}

void	ft_exit(t_minishell *data, t_commands *c_cmd)
{
	if (c_cmd->arg == NULL)
		exit(data->exit_code);
	if (ft_exit_parsing(data, c_cmd) != 0)
		return ;
}
