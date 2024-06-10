#include "minishell.h"

void	ft_echo(t_commands *c_cmd)
{
	if (c_cmd->option == NULL)
	{
		ft_arrprintf(c_cmd->arg);
		ft_printf("\n");
	}
	else if (ft_strcmp(c_cmd->option, "-n") == 0)
	{
		ft_arrprintf(c_cmd->arg);
	}
}
