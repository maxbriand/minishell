#include "../parsing.h"

char	*verif_access(char *cmd, char **path)
{
	int		i;
	char	*good_path;
	char	*path_buf;

	i = 0;
	while (path[i])
	{
		if (path[i][ft_strlen(path[i])] != '/')
			path_buf = ft_strjoin(path[i], "/");
		good_path = ft_strjoin(path_buf, cmd);
		if (access(good_path, X_OK) == 0)
		{
			free(path_buf);
			return (good_path);
		}
		i++;
		if (path_buf)
			free(path_buf);
		if (good_path)
			free(good_path);
	}
	return (0);
}
