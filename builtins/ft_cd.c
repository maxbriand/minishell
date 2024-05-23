#include "minishell.h"

int	ft_cd(t_minishell *mish, t_commands *p_cmd)
{
	if(chdir(p_cmd->arg)== 0)
	{
		ft_printf("the program move the current dir\n");
		return (0);
	}
	else
	{
		ft_printf("an error occurs\n");
		return (-1);
	}
	exit(EXIT_SUCCESS);
}
