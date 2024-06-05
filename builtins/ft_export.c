#include "minishell.h"

static int	ft_env_var_parsing(char	*arg)
{
	if (ft_isdigit(*arg) == 1 || *arg == '=')
		return (1);
	while (*arg && *arg != '=')
	{
		if (ft_isalnum(*arg) != 1)
			return (1);
		arg++;
	}
	return (0);
}

void	ft_add_env_var(t_minishell *data, t_commands *c_cmd)
{
	int	i;
	
	i = 0;
	while (c_cmd->arg[i])
	{
		if (ft_env_var_parsing(c_cmd->arg[i]) == 1)
		{
			ft_write_error(" not a valid identifier");
			data->exit_code = 1;
			i++;
			continue ;
		}
		// add the argument in env and export
		i++;
	}
}

void	ft_export(t_minishell *data, t_commands *c_cmd)
{
	int	i;
	
	if (!data->export)
		return ;
	i = 0;
	if (!c_cmd->arg)
	{
		while (data->export[i])
		{
			ft_printf("%s\n", data->export[i]);
			i++;
		}
		return ;
	}
	else
	{
		ft_add_env_var(data, c_cmd);
	}
}
