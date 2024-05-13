#include "../parsing.h"

// int	is_cmd(char *first_arg)
// {
// 	if (access(first_arg, X_OK) == 1)
// }


static int	verif_cmd_slash(char *first_arg)
{
	int	i;
	int	nb_slash;

	nb_slash = 0;
	i = 0;
	while (first_arg[i + 1] == '/')
		i++;
	while (first_arg[i])
	{
		if (first_arg[i] == '/')
			nb_slash++;
		i++;
	}
	if (access(first_arg, X_OK) == 1 || nb_slash == 1)
		return (1);
	//if (access(first_arg, X_OK) == 0)
		//printf("access good\n");
	return (0);
}

//define if the first arg is a command, a redirection etc
int	define_first_arg(char *first_arg, t_commands *cmd)
{
	if (strcmp(first_arg, "<") == 0 || strcmp(first_arg, "<<") == 0 ||
		strcmp(first_arg, ">") == 0 || strcmp(first_arg, ">>") == 0)
	{
		if (strcmp(first_arg, "<<") == 0)
		{
			//I continue tomorow I'm tireeeeed
		}

	}

	if (error_p(verif_cmd_slash(first_arg), first_arg) == true)
		return (1);
	//if (is_cmd() == 1)
	//	cmd->cmd =
	//if (is_builtins() == 1)
	//	return (3);

	return (0);
}


