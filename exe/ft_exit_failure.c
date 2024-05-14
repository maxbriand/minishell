#include "minishell.h"

// free everything
// ft_free_all()

void	ft_exit_failure(char *msg, t_minishell *data)
{
	write(2, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}
