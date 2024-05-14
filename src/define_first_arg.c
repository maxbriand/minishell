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

bool	is_operator(char *arg, t_commands *cmd, t_pars *node)
{
	if (ft_strcmp(arg, "<") == 0 || ft_strcmp(arg, "<<") == 0 ||
		ft_strcmp(arg, ">") == 0 || ft_strcmp(arg, ">>") == 0)
	{
		if (ft_strcmp(arg, "<<") == 0)
			node->next_is_hd_stop = true;
		else if (ft_strcmp(arg, "<") == 0)
			node->next_is_infile = true;
		else if (ft_strcmp(arg, ">") == 0)
		{
			ft_addback_int(cmd->append_output, 0);
			node->next_is_outfile = true;
		}
		else if (ft_strcmp(arg, ">>") == 0)
			ft_addback_int(cmd->append_output, 1);
		return (true);
	}
	return (false);
}

//define if the first arg is a command, a redirection etc
void	define_first_arg(char *first_arg, t_commands *cmd, t_pars *node)
{
	//is quote: need to do it here
	if (is_operator(first_arg, cmd, node) == true)
		return ;
	//if ()
	//if (error_p(verif_cmd_slash(first_arg), first_arg) == true)
	//	return (1);
	//if (is_cmd() == 1)
	//	cmd->cmd =
	//if (is_builtins() == 1)
	//	return (3);
}


