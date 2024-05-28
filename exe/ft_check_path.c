#include "minishell.h"

static char	**ft_get_env_paths(t_minishell *data)
{
	char	**env_paths;
	char	**save_env_paths;
	int		i;
	
	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (!data->env[i])
		ft_exit_failure("Command file not found", data);
	env_paths = ft_split(data->env[i] + 5, ':');
	if (!env_paths)
		ft_exit_failure("Malloc issue during path searching", data);
	save_env_paths = env_paths;
	env_paths = ft_arrcat(env_paths, "/");
	ft_arrfree(save_env_paths);
	if (!env_paths)
		ft_exit_failure("Malloc issue during path searching", data);
	return (env_paths);
}

static char	**ft_get_path_list(t_minishell *data, t_commands *current_cmd)
{
	char	**save_path_list;
	char	**path_list;

	path_list = ft_get_env_paths(data);
	save_path_list = path_list;
	path_list = ft_arrcat(path_list, current_cmd->cmd);
	ft_arrfree(save_path_list);
	if (path_list == NULL)
		ft_exit_failure ("Malloc issue during path creation", data);
	return (path_list);
}

static char	*ft_is_already_path(char *full_cmd)
{
	char	*al_path;

	al_path = ft_strcut(full_cmd, ' ');
	if (access(al_path, R_OK) == 0)
		return (al_path);
	if (al_path != full_cmd)
		free(al_path);
	return (NULL);
}

char	*ft_check_path(t_minishell *data, t_commands *current_cmd)
{
	char	**paths;
	char	**save_paths;
	char	*store;
	char	*al_path;

	al_path = ft_is_already_path(current_cmd->cmd);
	if (al_path != NULL)
		return (al_path);
	paths = ft_get_path_list(data, current_cmd);
	save_paths = paths;
	while (*paths)
	{
		if (access(*paths, R_OK) == 0)
		{
			store = ft_strdup(*paths);
			ft_arrfree(save_paths);
			if (store == NULL)
				ft_exit_failure("strdup malloc issue", data);
			return (store);
		}
		paths++;
	}
	ft_arrfree(save_paths);
	ft_exit_failure("command not found", data);
	return (NULL);
}
