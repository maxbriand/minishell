#include "minishell.h"

static void	ft_cd_home(t_minishell *data, t_commands *c_cmd)
{
	if (chdir(ft_get_env_var(data->env, "HOME")) == -1)
		ft_write_error("chdir issue");

}

void	ft_cd(t_minishell *data, t_commands *c_cmd)
{	
	if (c_cmd->option == NULL && c_cmd->arg == NULL)
		ft_cd_home(data, c_cmd);
	if (c_cmd->option == NULL && c_cmd->arg != NULL)
	{
		if(chdir(c_cmd->arg) == -1)
			ft_write_error("minishell: No such file or directory");
	}
}
