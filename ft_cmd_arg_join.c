#include "minishell.h"

void	cmd_arg_join(t_commands *cmd)
{
	int	i;

	cmd->arg_cmd = ft_addback(cmd->arg_cmd, cmd->cmd);
	if (cmd->option)
		cmd->arg_cmd = ft_addback(cmd->arg_cmd, cmd->option);
	i = 0;
	if (cmd->arg)
	{
		while (cmd->arg[i])
		{
			cmd->arg_cmd = ft_addback(cmd->arg_cmd, cmd->arg[i]);
			i++;
		}
	}
}
