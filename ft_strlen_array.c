#include "minishell.h"

int	ft_strlen_array(char **array)
{
	int	len;

	if (!array)
		return (0);
	len = 0;
	while (array[len])
		len++;
	return (len);
}
