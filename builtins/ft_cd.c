#include "minishell.h"

void	ft_cd(char **env)
{
	if (env == NULL)
		return ;
	ft_printf("HEY");
	while (*env)
	{
		ft_printf("%s\n", *env);
		env++;
	}
	return ;
}