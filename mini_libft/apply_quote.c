#include "../parsing.h"

static void	free_and_strdup(char **str, int i, char *buf)
{
	free(str[i]);
	str[i] = ft_strdup(buf);
}

void	remove_quote_bslash(char **str, bool next_print)
{
	int	i;
	int	j;
	char	*buf;

	buf = NULL;
	i = 0;
	while (str[i])
	{
		buf = NULL;
		j = 0;
		while (str[i][j]) // are we shure that str(i(j existe ?
		{
			if (str[i][j] == '\\' && next_print == false && str[i][j + 1])
				next_print = true;
			else
			{
				buf = ft_charaddback(&buf, str[i][j]);
				next_print = false;
			}
			j++;
		}
		free_and_strdup(str, i, buf);
		if (buf)
			free(buf);
		i++;
	}
	//remove quote
}

// void	apply_and_remove_quote()
// {


// }
