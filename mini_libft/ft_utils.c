#include "../parsing.h"

int	is_only_space(char *str)
{
	int	i;

	i = 0;
	if (str[0] == ' ')
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}
