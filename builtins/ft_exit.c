#include "minishell.h"

void	ft_exit(t_minishell *mish, t_commands *p_cmd)
{
	//write(2, "exe", 3);
	exit(mish->exit_code);
	//printf("%d", mish->exit_code);
}
