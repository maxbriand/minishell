#include "minishell.h"

//create a new node for my struct t_pars. every node is a command separed by pipe
t_pars	*new_node(char *input_no_pipe, t_minishell *mini)
{
	t_pars	*node;

	node = malloc(sizeof(t_pars));
	node->spl_cmd = ft_split_separator(input_no_pipe);
	//CHANEGEGGEGE


	//if (node->spl_cmd == NULL)
	//{
		//free(node->spl_cmd);
		//free(node);
		//return (NULL);
	//} why did i put this ??

	//remove uneeded quote

	//apply_quote(node->spl_cmd);


	remove_quote_bslash(node->spl_cmd, mini);
	if (!node->spl_cmd || !node->spl_cmd[0] || node->spl_cmd[0][0] == '\0')
	{
		if (node->spl_cmd[0])
			free(node->spl_cmd[0]);
		free (node);
		return NULL;
	}
	//i need to do a check of every arg for > or >>




	//int i = 0;
	// while (node->spl_cmd[i])
	// {
	// 	is_error_quote(node->spl_cmd[i]);
	// 	//if (is_error_quote(node->spl_cmd[i]) == true)// error is just a text or exit too ?
	// 	//{
	// 	//	//free(node->spl_cmd[i]);
	// 	//	//node->spl_cmd = malloc(sizeof(char *) * 1);
	// 	//	//node->spl_cmd[0] = NULL;
	// 	//	//je pourrais faire une fonction qui retire juste la chaine en question de spl_cmm
	// 	//}
	// 	i++;
	// }
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
		buf = head;
		i = 1;
		while (input_no_pipe[i])
		{
			buf->next = new_node(input_no_pipe[i], mini);
			if (buf->next != NULL)
				buf = buf->next;
			i++;
		}
		free_tab(input_no_pipe);
		return (head);
	}
	return (0);
}

//ah ouais ca fouille dans le code je vois je vois
