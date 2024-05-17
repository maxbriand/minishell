#include "../parsing.h"

bool	is_error_quote(char *str)
{
	int	i;
	int	nb_quote;
	int	nb_dquote;

	i = 0;
	nb_quote = 0;
	nb_dquote = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			nb_quote++;
		else if (str[i] == '\"')
			nb_dquote++;
		i++;
	}
	if (nb_quote % 2 == 1 || nb_dquote % 2 == 1)
	{
		printf("minishell: Error syntax: Quote not closed\n");//mayday exit error ?
		return (true);
	}
	return (false);
}