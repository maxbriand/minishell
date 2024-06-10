/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:40:07 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/10 16:33:58 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_process(t_minishell *mini, t_commands *buf, t_pars *p, int *i)
{
	int	fdout;

	remove_quote_bslash(p->spl_cmd, *i, mini, p);
	if (p->spl_cmd[*i][0] != '\0')
	{
		if (*i == 0)
			define_first_pcmd(p->spl_cmd[0], buf, p);
		else
			define_p_cmd(p->spl_cmd[*i], *i, buf, p);
	}
	else if (p->is_arg[*i] == true)
		buf->cmd = ft_strdup("");
	if (buf->outfile && buf->err_is_infile == false && buf->msg_error == NULL)
	{
		fdout = open(buf->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fdout <= 0)
			define_outfile_error(buf);
		else
			close(fdout);
	}
	(*i)++;
}

static void	ft_all_verif_process(t_minishell *mini, t_commands *buf, t_pars *p)
{
	int			i;

	if (p->spl_cmd == NULL)
	{
		free_p(p);
		return ;
	}
	if (buf != mini->p_cmd)
		buf->in_pipe = true;
	if (p->spl_cmd[0])
	{
		i = 0;
		ft_process(mini, buf, p, &i);
		while (p->spl_cmd[i])
			ft_process(mini, buf, p, &i);
		if (buf->arg_cmd == NULL && buf->cmd)
			cmd_arg_join(buf);
		if (p->next_is_infile || p->next_is_outfile || p->next_is_hd_stop)
			error_next_file(buf);
	}
}

//main's of the parsing. if return null, no command need to be done
void	ft_parsing(char *input, t_minishell *mini)
{
	t_pars		*p;
	t_commands	*buf;

	mini->env = ft_strdup_array(mini->env);
	if (!mini->export)
		mini->export = ft_init_export(mini);
	if (ft_strlen(input) == 0 || is_error_quote(input) == true)
		return ;
	p = define_p(input);
	if (!p)
		return ;
	init_pcmd(mini, p);
	buf = mini->p_cmd;
	while (buf)
	{
		ft_all_verif_process(mini, buf, p);
		p = p->next;
		buf = buf->next;
	}
	free_p(p);
}
