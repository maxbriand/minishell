#include "minishell.h"

// have to free the old env if it's a malloc env
void	ft_delete_argn(t_minishell *mish, int n)
{
	int		size_env;
	char	**new_env;

	size_env = ft_arrlen(mish->env);
	new_env = malloc(sizeof(char *) * size_env);
	ft_arrncpy(new_env, mish->env, n);
	ft_arrcpy(new_env + n, mish->env + (n + 1));
	new_env[size_env] = NULL;
	if (mish->env_malloc == 0)
		mish->env_malloc = 1;
	else
		ft_arrfree(mish->env);
	mish->env = new_env; 
}

void	ft_looking_for_argn(t_minishell *mish, char *arg)
{
	int	i;
	int argl;

	if (ft_strchr(arg, '='))
		return ;
	argl = ft_strlen(arg);
	i = 0;
	while (mish->env[i])
	{
		if (strncmp(mish->env[i], arg, argl) == 0)
		{
			if (mish->env[i][argl] == '=')
				ft_delete_argn(mish, i);
		}
		i++;
	}
}

void	ft_unset(t_minishell *mish, t_commands *p_cmd)
{
	int	i;
	
	if (!mish || !p_cmd || !p_cmd->arg)
		return ;
	i = 0;
	while (p_cmd->arg[i])
	{
		ft_looking_for_argn(mish, p_cmd->arg[i]);
		i++;
	}
}
