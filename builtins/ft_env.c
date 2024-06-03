#include "minishell.h"

void	ft_env(t_minishell *mish, t_commands *p_cmd)
{
	int	i;

	if (!mish->env)
		return ;
	i = 0;
	while (mish->env[i])
	{
		ft_printf("%s\n", mish->env[i]);
		i++;
	}
}
