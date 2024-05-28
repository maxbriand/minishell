#include "minishell.h"

// static void	ft_cd_home(void)
// {
// 	chdir();


// }

void	ft_cd(t_minishell *data, t_commands *c_cmd)
{
	// if (c_cmd->option == NULL && c_cmd->arg == NULL)
	// 	ft_cd_home();
	ft_arrprintf(data->env);
	// chdir(c_cmd->arg);
	chdir("/nfs/homes/mbriand/minishell/builtins");
}
