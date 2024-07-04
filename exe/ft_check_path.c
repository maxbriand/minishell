/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:01:10 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/04 01:21:53 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		ft_exitf("Command file not found", -1, NULL, data);
	env_paths = ft_split(data->env[i] + 5, ':');
	if (!env_paths)
		ft_exitf("Malloc issue during path searching", -1, NULL, data);
	save_env_paths = env_paths;
	env_paths = ft_arrcat(env_paths, "/");
	ft_arrfree(save_env_paths);
	if (!env_paths)
		ft_exitf("Malloc issue during path searching", -1, NULL, data);
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
		ft_exitf ("Malloc issue during path creation", -1, NULL, data);
	return (path_list);
}

static char	*ft_is_already_path(char *cmd, t_minishell *data, t_commands *c_cmd)
{
	if (!cmd)
		return (NULL);
	if (ft_strcmp(cmd, ".") == 0)
		ft_exitf(" filename argument required . filename [arguments]", \
			2, c_cmd, data);
	if (ft_strncmp(cmd, "/root", 5) == 0)
		ft_exitf(" Permission denied", 126, c_cmd, data);
	if (ft_strcmp(cmd, "..") == 0)
		ft_exitf(" command not found", 127, c_cmd, data);
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == -1)
			ft_exitf(" Permission denied", 126, c_cmd, data);
		if (ft_is_a_directory(cmd) && (cmd[0] == '/' || cmd[0] == '.'))
			ft_exitf(" Is a directory", 126, c_cmd, data);
		return (cmd);
	}
	return (NULL);
}

char	*ft_check_path(t_minishell *data, t_commands *c_cmd)
{
	char	**paths;
	char	**save_paths;
	char	*store;

	if (ft_is_already_path(c_cmd->cmd, data, c_cmd))
		return (c_cmd->cmd);
	paths = ft_get_path_list(data, c_cmd);
	save_paths = paths;
	while (*paths)
	{
		if (access(*paths, R_OK) == 0)
		{
			if (access(*paths, X_OK) == -1)
				ft_exitf(" Permission denied", 126, c_cmd, data);
			store = ft_strdup(*paths);
			ft_arrfree(save_paths);
			if (store == NULL)
				ft_exitf("strdup malloc issue", 1, NULL, data);
			return (store);
		}
		paths++;
	}
	ft_arrfree(save_paths);
	ft_exitf(" command not found", 127, c_cmd, data);
	return (NULL);
}
