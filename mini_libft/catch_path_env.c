
#include "../parsing.h"

char	**catch_path(char **envp)
{
	int		y;
	char	**path;

	y = 0;
	path = NULL;
	while (envp[y] != NULL)
	{
		if (ft_strncmp(envp[y], "PATH=", 5) == 0)
			path = ft_split(&envp[y][0] + 5, ':');
		y++;
	}
	return (path);
}

