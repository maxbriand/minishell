#include "minishell.h"

// free everything
// ft_free_all()

int	ft_write_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (0);
}

void	ft_exit_failure(char *msg, t_minishell *data)
{
	ft_write_error(msg);
	exit(EXIT_FAILURE);
}
