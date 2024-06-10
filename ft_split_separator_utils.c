#include "minishell.h"

bool	is_sep(char c, char *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (sep[i] == c)
			return (true);
		i++;
	}
	return (false);
}