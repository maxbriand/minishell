#include "minishell.h"

void	ft_env(t_minishell *data, t_commands *p_cmd)
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
