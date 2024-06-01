#include "minishell.h"

//create a new node for my struct t_pars. every node is a command separed by pipe
t_pars	*new_node(char *input_no_pipe, t_minishell *mini)
{
	t_pars	*node;

	node = malloc(sizeof(t_pars));
	node->spl_cmd = ft_split_separator(input_no_pipe);
	if (node->spl_cmd[0])
		node->is_arg = define_shure_arg(node->spl_cmd);

	node->is_expand = malloc(sizeof(bool) * ft_strlen_array(node->spl_cmd));
	node->code_error = 0;
	node->file_err[0] = false;
	node->file_err[1] = false;
	node->error_msg = NULL;
	node->next_is_hd_stop = false;
	node->next_is_infile = false;
	node->next_is_outfile = false;
	node->next_can_be_opt = false;
	node->next_can_be_arg = false;
	node->next = NULL;
	return (node);
}

//function for get a structure with segmented line of command
t_pars	*define_p(char *input, t_minishell *mini)
{
	int		i;
	char	**input_no_pipe;
	t_pars	*head;
	t_pars	*buf;
	//check pipe at start or double pipe in input: 0 if all good
	if (pipe_unexpected(input) == 0 && is_only_space(input) == 0)
	{
		input_no_pipe = ft_split_quote_ignore(input, '|');
		head = new_node(input_no_pipe[0], mini);
		if (!head)
		{
			free_array(input_no_pipe);
			return NULL;
		}
		//check_nb_op(head->spl_cmd, &head->error_msg, head->file_err, &head->code_error);
		buf = head;
		i = 1;
		while (input_no_pipe[i])
		{
			buf->next = new_node(input_no_pipe[i], mini);
			//printf("%s = input\n", input_no_pipe[i]);
			//printf("%p = buf->next\n", buf->next);

			if (buf->next != NULL)
				buf = buf->next;
			//check_nb_op(buf->spl_cmd, &buf->error_msg, buf->file_err, &buf->code_error);
			i++;
		}
		free_array(input_no_pipe);
		return (head);
	}
	return (0);
}

//ah ouais ca fouille dans le code je vois je vois
