
#include "minishell.h"

char	*catch_env(char **envp, char *str)
{
	int		y;
	char	*path;

	y = 0;
	path = NULL;
	printf("%s = str\n", str);
	while (envp[y] != NULL)
	{
		if (ft_strncmp(envp[y], str, ft_strlen(str)) == 0 && envp[y][ft_strlen(str)] == '=')//pas sur
		{
			path = ft_strdup(&envp[y][ft_strlen(str) + 1]);
			if (!path)
				exit (1); //mayday error ?
			free(str);
			return (path);
		}
		y++;
	}
	free(str);
	printf("%s = path\n", path);
	return (path);
}

