#include "../parsing.h"

void	cmd_arg_join(t_commands *cmd)
{
	cmd->arg_cmd = ft_addback(cmd->arg_cmd, cmd->cmd);
	if (cmd->option)
		cmd->arg_cmd = ft_addback(cmd->arg_cmd, cmd->option);
	if (cmd->arg)
		cmd->arg_cmd = ft_addback(cmd->arg_cmd, cmd->arg);
}