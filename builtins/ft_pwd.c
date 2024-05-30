#include "minishell.h"

char	*ft_pwd(t_minishell *data, t_commands *p_cmd, int i)
{
	char	*buf;
	char	*err_buf;
	size_t	size;

	buf = NULL;
	err_buf = NULL;
	size = 0;
	while(err_buf == NULL)
	{
		buf = malloc(sizeof(char) * size);
		err_buf = getcwd(buf, size);
		if (err_buf == NULL)
			free(buf);
		size++;
	}
	ft_printf("%s\n", buf);
	if (i == 0)
		free(buf);
	else
		return (buf);
	return (NULL);
}
