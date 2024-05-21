#include "../parsing.h"

void	apply_quote(char **str)
{
	int	i;
	int	j;
	bool	on_quote[2];

	on_quote[0] = false;
	on_quote[1] = false;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			ft_define_on_quote(str[i], j, on_quote);
			if (str[i][j] == '$' )
			j++;
		}
	}
}
//remove quote