/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:40:07 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/08 22:15:06 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_check_nb_hd(t_utils *utils, t_minishell *mini)
{
	if (mini->count_hd > 16 && mini->p_cmd->exit_code != 2)
	{
		if (mini->p_cmd->msg_error)
			free(mini->p_cmd->msg_error);
		mini->p_cmd->msg_error = ft_strdup(
				"minishell: maximum here-document count exceeded\n");
		if (!mini->p_cmd->msg_error)
			ft_ultimate_free_exit(utils, NULL, NULL, NULL);
	}
}

static void	ft_process(t_utils *utils, t_pars *p, int *i)
{
	int	fdout;

	ft_redefine_utils(utils);
	if (p->spl_cmd && p->spl_cmd[*i] && p->spl_cmd[*i][0] != '\0')
	{
		if (*i == 0)
			ft_define_first_pcmd(p->spl_cmd[0], utils->buf_pcmd, p, utils);
		else if (p->spl_cmd[*i][0] != '\0')
			ft_define_p_cmd(p->spl_cmd[*i], *i, utils, p);
	}
	else if (p->is_arg[*i] == true && !utils->buf_pcmd->cmd)
	{
		utils->buf_pcmd->cmd = ft_strdup("");
		if (!utils->buf_pcmd->cmd)
			ft_ultimate_free_exit(utils, NULL, NULL, NULL);
	}
	if (utils->buf_pcmd->outfile && utils->buf_pcmd->msg_error == NULL)
	{
		fdout = open(
				utils->buf_pcmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fdout <= 0)
			ft_define_outfile_error(utils->buf_pcmd, utils);
		close(fdout);
	}
	(*i)++;
}

static void	ft_all_verif_process(t_minishell *mini, t_pars *p, t_utils *utils)
{
	int	i;

	if (!p->spl_cmd)
		return ;
	if (utils->buf_pcmd != mini->p_cmd)
		utils->buf_pcmd->in_pipe = true;
	if (p->spl_cmd[0])
	{
		i = 0;
		if (ft_remove_quote_bslash(i, utils, p) == 1)
			ft_ultimate_free_exit(utils, NULL, NULL, NULL);
		ft_process(utils, p, &i);
		while (p->spl_cmd[i])
		{
			if (ft_remove_quote_bslash(i, utils, p) == 1)
				ft_ultimate_free_exit(utils, NULL, NULL, NULL);
			ft_process(utils, p, &i);
		}
		if (utils->buf_pcmd->arg_cmd == NULL && utils->buf_pcmd->cmd)
			ft_cmd_arg_join(utils->buf_pcmd, utils);
		if (p->next_is_infile || p->next_is_outfile || p->next_is_hd_stop)
			ft_error_next_file(utils->buf_pcmd, p, utils);
	}
	ft_hd_set(mini, utils->buf_pcmd, mini->p_cmd, utils);
}

// init export + env
static void	ft_init_data(t_minishell *data, t_utils *utils, char **env)
{
	ft_init_env(data, utils, env);
	ft_init_shlvl(data, utils);
	ft_init_export(data, utils);
	data->count_hd = 0;
}

//main's of the parsing. if return null, no command need to be done
void	ft_parsing(t_minishell *data, char *input, char **env)
{
	t_pars		*p;
	t_pars		*p_buf;
	t_utils		*utils;

	utils = ft_declare_utils();
	ft_init_data(data, utils, env);
	ft_is_error(utils, input, &p);
	ft_init_pcmd(data, p, utils);
	utils->mini = data;
	p_buf = p;
	utils->buf_pcmd = data->p_cmd;
	while (utils->buf_pcmd)
	{
		ft_all_verif_process(data, p, utils);
		ft_check_nb_hd(utils, data);
		p = p->next;
		utils->buf_pcmd = utils->buf_pcmd->next;
	}
	ft_free_p(p_buf);
	ft_free_utils(&utils);
}
