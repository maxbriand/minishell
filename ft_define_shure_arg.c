#include "minishell.h"

bool	*define_shure_arg(char **splt_cmd)
{
	int		i;
	int		j;
	bool	op_before;
	bool	*is_arg;


	//printf("WESH %d.\n", ft_strlen_array(splt_cmd));
	is_arg = malloc(sizeof(bool) * ft_strlen_array(splt_cmd));
	op_before = false;
	i = 0;
	while (splt_cmd[i])
	{
		j = 0;
		//printf("splcmd = %s..........\n", splt_cmd[i]);
		is_arg[i] = false;
		if ((splt_cmd[i][0] == '\'' || splt_cmd[i][0] == '\"') && op_before == false)
			is_arg[i] = true;
		else if ((splt_cmd[i][0] == '>' || splt_cmd[i][0] == '<') && ft_strlen(splt_cmd[i]) == 1)
			op_before = true;
		else
			op_before = false;
		if (splt_cmd[i][0] == '>' || splt_cmd[i][0] == '<')
			op_before = true;
		i++;
		//printf("ICI et %d.\n", is_arg[i]);
	}
	return (is_arg);
}