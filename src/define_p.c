#include "../parsing.h"

//create a new node for my struct t_pars. every node is a command separed by pipe
t_pars	*new_node(char *input_no_pipe)
{
	t_pars	*node;

	node = malloc(sizeof(t_pars));
	node->tab = ft_split(input_no_pipe, ' ');
	node->next = NULL;
	return (node);
}
//function for get a structure with segmented line of command
t_pars	*define_p(char *input)
{
	int		i;
	char	**input_no_pipe;
	t_pars	*head;
	t_pars	*buf;

	//check pipe at start or double pipe in input: 0 if all good
	if (pipe_unexpected(input) == 0)
	{
		input_no_pipe = ft_split(input, '|');
		if (!input_no_pipe)
			error_and_exit ("Malloc error\n");
		head = new_node(input_no_pipe[0]);
		buf = head;
		i = 1;
		while (input_no_pipe[i])
		{
			buf->next = new_node(input_no_pipe[i]);
			buf = buf->next;
			i++;
		}
		free_tab(input_no_pipe);
		return (head);
	}
	return (0);
}
