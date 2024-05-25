#include "minishell.h"

//remove an element from a char **
char	**ft_remove_element(char **old_array, int id_rm)
{
	char	**new_array;
	int		i;
	int		j;
	int		len;

	if (id_rm < 0 || old_array == NULL)
		return (NULL);
	len = ft_strlen_array(old_array);
	printf("%d = len\n", len);
	if (len == 1)
	{
		free_tab(old_array);
		return (NULL);
	}
	new_array = malloc(sizeof(char *) * (len - 1));
	if (!new_array)
		exit (1);//mayday error
	i = 0;
	j = 0;
	while (old_array[i])
	{
		if (i != id_rm)
		{
			new_array[j] = ft_strdup(old_array[i]);
			if (!new_array[j])
				exit (1); //mayday error ?
			j++;
		}
		i++;
	}
	new_array[j] = NULL;
	free_tab(old_array);
	old_array = NULL;
	return (new_array);
}
