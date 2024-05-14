//to add to the libft later
#include "../../parsing.h"

//add 1 element to a array. Free the old array, so it's not needed to free it after
char	**ft_addback(char **old_array, char *new_element)
{
	char	**new_array;
	int		i;

	i = 0;
	while (old_array[i])
		i++;
	new_array = malloc(sizeof(char *) * (i + 2));
	if (!new_array)
		exit (1); //error to write?
	i = 0;
	while (old_array[i])
	{
		new_array[i] = ft_strdup(old_array[i]);
		if (!new_array[i])
			exit (1); //error to write?
		i++;
	}
	new_array[i] = ft_strdup(new_element);
	if (!new_array[i])
		exit (1); //error to write?
	new_array[i + 1] = NULL;
	free_tab(old_array);
	return (new_array);
}

int	*ft_addback_int(int *old_array, int	new_element)
{
	int	*new_array;
	int	i;

	i = 0;
	if (old_array)
	{
		while (old_array[i] != -1)
			i++;
	}
	new_array = malloc(sizeof(int) * (i + 2));
	if (!new_array)
		exit (1); //error to write?
	if (old_array)
	{
		i = 0;
		while (old_array[i] != -1)
		{
			new_array[i] = old_array[i];
			i++;
		}
		free(old_array);
	}
	new_array[i] = new_element;
	new_array[i + 1] = -1;
	return (new_array);
}
