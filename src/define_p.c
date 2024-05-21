#include "../parsing.h"

//create a new node for my struct t_pars. every node is a command separed by pipe
t_pars	*new_node(char *input_no_pipe)
{
	t_pars	*node;

	node = malloc(sizeof(t_pars));
	node->spl_cmd = ft_split_quote_ignore(input_no_pipe, ' ');
	if (node->spl_cmd == NULL)
	{
		free(node->spl_cmd);
		free(node);
		return (NULL);
	}
	//apply_quote(node->spl_cmd);
	node->next_is_hd_stop = false;
	node->next_is_infile = false;
	node->next_is_outfile = false;
	node->next_can_be_opt = false;
	node->next_can_be_arg = false;
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
	if (pipe_unexpected(input) == 0 && is_only_space(input) == 0)
	{
		input_no_pipe = ft_split_quote_ignore(input, '|');
		head = new_node(input_no_pipe[0]);
		buf = head;
		i = 1;
		while (input_no_pipe[i])
		{
			buf->next = new_node(input_no_pipe[i]);
			if (buf->next == NULL)
				break ;
			buf = buf->next;
			i++;
		}
		free_tab(input_no_pipe);
		return (head);
	}
	return (0);
}

//ah ouais ca fouille dans le code je vois je vois
