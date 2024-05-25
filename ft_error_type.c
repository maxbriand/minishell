#include "minishell.h"

//check if there is consecutive pipe
int	pipe_unexpected(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|' && input[i + 1] == '|')
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `||'\n", 1);//Not shure for 1 for stderror
			return (1);
		}
		if (input[i] == '|' && i == 0)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 1);//Not shure for 1 for stderror
			return (1);
		}
		i++;
	}
	return (0);
}

void error_and_exit(char *error)
{
	ft_putstr_fd(error, 1);
	exit (1);
}
