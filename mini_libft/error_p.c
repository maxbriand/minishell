#include "../parsing.h"
//1 = / error
bool	error_p(int nb, char *cmd)
{
	if (nb == 1)
	{
		printf("minishell: %s: No such file or directory\n", cmd);
		return (true);
	}
	return (false);
	//if (nb == 2)
}
