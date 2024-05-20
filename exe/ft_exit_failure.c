#include "minishell.h"

// free everything
// ft_free_all()


// delete heredoc if user close minishell

int	ft_write_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (0);
}

void	ft_exit_failure(char *msg, t_minishell *data)
{
	ft_write_error(msg);
	exit(EXIT_FAILURE);
}
