#include "minishell.h"

char	*ft_better_strdup(char *s, char *arg)
{
	char	*sdup;
	int		i;

	i = 0;
	while(s[i])
	{
		if (s[i] == '%' && s[i + 1] == 's')
		{
			sdup = ft_substr(s, 0, i);
			sdup = ft_strjoin_free(sdup, arg);
			i+= 2;
			sdup = ft_strjoin_free(sdup, ft_substr(s, i, ft_strlen(s)));
			return (sdup);
		}
		i++;
	}
	return (NULL);
}
