#include "../parsing.h"

// int	is_cmd(char *first_arg)
// {
// 	if (access(first_arg, X_OK) == 1)
// }


// static int	verif_cmd_slash(char *first_arg)
// {
// 	int	i;
// 	int	nb_slash;

// 	nb_slash = 0;
// 	i = 0;
// 	while (first_arg[i + 1] == '/')
// 		i++;
// 	while (first_arg[i])
// 	{
// 		if (first_arg[i] == '/')
// 			nb_slash++;
// 		i++;
// 	}
// 	if (access(first_arg, X_OK) == 1 || nb_slash == 1)
// 		return (1);
// 	//if (access(first_arg, X_OK) == 0)
// 		//printf("access good\n");
// 	return (0);
// }





static bool	is_builtins(char *arg, t_pars *p, t_commands *p_cmd)
{
	//echo cd pwd export unset env exit
	if (strcmp(arg, "echo") == 0 || strcmp(arg, "cd") == 0 || \
		strcmp(arg, "pwd") == 0 || strcmp(arg, "export") == 0 || \
			strcmp(arg, "unset") == 0 || strcmp(arg, "env") == 0 || \
				strcmp(arg, "export") == 0)
	{
		p->next_can_be_opt = true;
		p_cmd->b_builtins = true;
		p_cmd->cmd = ft_strdup(arg);
		return (true);
	}
	return (false);
}

//define if the first arg is a command, a redirection etc
void	define_first_pcmd(char *first_arg, t_commands *p_cmd, t_pars *p)
{
	if (is_error_quote(first_arg) == true)
		return ;
	if (is_operator(first_arg, p_cmd, p) == true)
		return ;
	if (is_builtins(first_arg, p, p_cmd) == true)
		return ;
	if (arg_cmd(first_arg, p_cmd, p) == true)
		return ;
}