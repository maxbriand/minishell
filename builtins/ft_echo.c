#include "minishell.h"

void	ft_echo(t_minishell *mish, t_commands *p_cmd)
{
	ft_arrprintf(p_cmd->arg);
	ft_printf("\n");
	// update exit code
}
