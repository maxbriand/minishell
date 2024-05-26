#include "minishell.h"

static void	count_quote(bool *on_quote, char *str, int i, int nb_quote[2])
{
	if (!on_quote[0] && str[i] == '\'')
		{
			if (str[i] == '\'' && (!on_quote[0] && !on_quote[1]))
				nb_quote[0]++;
			ft_define_on_quote(str, i, on_quote);
		}
		else if (on_quote[0] && str[i] == '\'')
		{
			ft_define_on_quote(str, i, on_quote);
			if (str[i] == '\'' && (!on_quote[0] && !on_quote[1]))
				nb_quote[0]++;
		}
		else if (!on_quote[1] && str[i] == '\"')
		{
			if (str[i] == '\"' && (!on_quote[0] && !on_quote[1]))
				nb_quote[1]++;
			ft_define_on_quote(str, i, on_quote);
		}
		else if (on_quote[1] && str[i] == '\"')
		{
			ft_define_on_quote(str, i, on_quote);
			if (str[i] == '\"' && (!on_quote[0] && !on_quote[1]))
				nb_quote[1]++;
		}
}

bool	is_error_quote(char *str)
{
	int	i;
	int	nb_quote[2];
	bool	on_quote[2];

	on_quote[0] = false;
	on_quote[1] = false;
	i = 0;
	nb_quote[0] = 0;
	nb_quote[1] = 0;
	while (str[i])
	{
		count_quote(on_quote, str, i, nb_quote);
		i++;
	}
	if (nb_quote[0] % 2 == 1 || nb_quote[1] % 2 == 1)
	{
		printf("minishell: Error syntax: Quote not closed\n");//mayday exit error ?
		return (true);
	}
	return (false);
}
