#include "minishell.h"

//free s1 but not s2, and accept if s1 or s2 is empty
char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*result;
	int	i;
	result = NULL;
	if (s1)
	{
		result = ft_strdup(s1);
		free(s1);
	}
	i = 0;
	if (s2)
	{
		while (s2[i])
		{
			result = ft_charaddback(&result, s2[i]);
			i++;
		}
	}
	return(result);
}