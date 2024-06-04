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

void	ft_exit_failure(char *msg, t_commands *c_cmd, t_minishell *data)
{
	ft_write_error(msg);
	exit(c_cmd->exit_code);
	// close all pipes
	// ft_close_pipes(data->pipefds);
}
