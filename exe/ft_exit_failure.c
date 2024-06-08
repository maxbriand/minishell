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

void	ft_exitf(char *msg, int ec, t_commands *c_cmd, t_minishell *data)
{
	// add freing part
	if (!c_cmd)
	{
		if (c_cmd->exit_code != 0)
			data->exit_code = c_cmd->exit_code;
	}
	if (ec != -1)
		data->exit_code = ec;
	if (data->exit_code == 0)
		data->exit_code = 1;
	ft_write_error(msg);
	exit(data->exit_code);
}
