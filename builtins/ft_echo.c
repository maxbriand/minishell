#include "minishell.h"

void	ft_echo(t_minishell *mish, t_commands *p_cmd)
{
	ft_printf("%s\n", p_cmd->arg);
}
