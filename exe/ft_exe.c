#include "minishell.h"


// if (ft_strncmp(input, "cd", 2) == 0)
// 	ft_cd(env);


void	child_exe(t_minishell *datas, t_commands *p_input)
{


}


void	ft_exe(t_minishell *datas, t_commands *p_input)
{
	int	pipefd[2];

	if (p_input == NULL)
		ft_exit_faillure("empty input");
	if (pipe(pipefd) == -1)
		ft_exit_faillure("pipe creation issue");
	while (*p_input)
	{

		p_input = p_input->next;
	}
}