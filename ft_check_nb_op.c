#include "minishell.h"

//true = error
void	check_nb_op(char **spl_cmd, char **error_msg, bool *file_err, int *code_error)
{
	int	i;
	int	j;
	int	nb_r;
	int	nb_l;
	char	last_op;

	i = 0;
	nb_l = 0;
	nb_r = 0;
	while(spl_cmd[i])
	{
		if (spl_cmd[i][0] == '<')
		{
			j = 0;
			while (spl_cmd[i][j] == '<')
			{
				nb_l++;
				j++;
			}
			last_op = '<';
			while (spl_cmd[i][j] == '>')
			{
				nb_r++;
				j++;
				last_op = '>';
			}
			if (spl_cmd[i][j] == '<' || nb_l > 2 || nb_r > 2)
			{
				if (*error_msg == NULL)
				{
					if (nb_l > 2)
						*error_msg = ft_strdup("minishell: syntax error near unexpected token `<<'");
					if (nb_r > 2)
						*error_msg = ft_strdup("minishell: syntax error near unexpected token `>>'");
					if (spl_cmd[i][j] == '<')
						*error_msg = ft_strdup("minishell: syntax error near unexpected token `><'");
					*code_error = 2;
				}
				return ;
			}
		}
		else if (spl_cmd[i][0] == '>')
		{
			j = 0;
			while (spl_cmd[i][j] == '>')
			{
				nb_r++;
				j++;
			}
			last_op = '>';
			while (spl_cmd[i][j] == '<')
			{
				nb_l++;
				j++;
				last_op = '<';
			}
			if (spl_cmd[i][j] == '>' || nb_l > 2 || nb_r > 2)
			{
				if (*error_msg == NULL)
				{
					if (nb_l > 2)
						*error_msg = ft_strdup("minishell: syntax error near unexpected token `<<'");
					if (nb_r > 2)
						*error_msg = ft_strdup("minishell: syntax error near unexpected token `>>'");
					if (spl_cmd[i][j] == '>')
						*error_msg = ft_strdup("minishell: syntax error near unexpected token `<>'");
					*code_error = 2;
				}
				return ;
			}
		}
		i++;
	}
}
