#include "../parsing.h"


t_commands	*node_create_cmd(void)
{
	t_commands	*node;

	node = malloc(sizeof(t_commands));
	node->b_builtins = false;
	node->append_output = NULL;
	node->hd_stop = NULL;
	node->stdinput = NULL;
	node->stdoutput = NULL;
	node->cmd = NULL;
	node->option = NULL;
	node->arg = NULL;
	node->arg_cmd = NULL;
	node->next = NULL;
	return (node);
}
void	define_cmd(t_minishell *mini, t_pars *p)
{
	t_pars		*buf_p;
	t_commands	*buf_cmd;
	t_commands	*next_node;

	buf_p = p;
	buf_cmd = node_create_cmd();
	mini->p_cmd = buf_cmd;
	while (buf_p->next)
	{
		next_node = node_create_cmd();
		buf_cmd->next = next_node;
		buf_cmd = buf_cmd->next;
		buf_p = buf_p->next;
	}
}
