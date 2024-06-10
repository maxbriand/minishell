#include "minishell.h"

static void	ft_exe_env(t_minishell *data)
{
	int	i;

	if (!data->env)
		return ;
	i = 0;
	while (data->env[i])
	{
		ft_printf("%s\n", data->env[i]);
		i++;
	}
}

static int	ft_check_env_error(t_minishell *data, t_commands *c_cmd)
{
	if (c_cmd->option != NULL)
	{
		data->exit_code = 125;
		ft_write_error("env: invalid option");
		return (1);
	}
	if (c_cmd->arg != NULL)
	{
		data->exit_code = 127;
		ft_write_error("env: No such file or directory");
		return (1);
	}
	return (0);
}

void	ft_env(t_minishell *data, t_commands *c_cmd)
{
	if (ft_check_env_error(data, c_cmd) == 1)
		return ;
	ft_exe_env(data);
}
