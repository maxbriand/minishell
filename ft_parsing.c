/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:40:07 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/05 05:40:03 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_process(t_utils *utils, t_pars *p, int *i)
{
	int	fdout;

	ft_redefine_utils(utils);
	if (p->spl_cmd && p->spl_cmd[*i] && p->spl_cmd[*i][0] != '\0')
	{
		if (*i == 0)
			ft_define_first_pcmd(p->spl_cmd[0], utils->buf_pcmd, p, utils);
		else
			ft_define_p_cmd(p->spl_cmd[*i], *i, utils, p);
	}
	else if (p->is_arg[*i] == true && !utils->buf_pcmd->cmd)
	{
		utils->buf_pcmd->cmd = ft_strdup("");
		if (!utils->buf_pcmd->cmd)
			ft_ultimate_free_exit(utils, NULL, NULL);
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

	if (p->spl_cmd == NULL)
		return ;
	if (utils->buf_pcmd != mini->p_cmd)
		utils->buf_pcmd->in_pipe = true;
	if (p->spl_cmd[0])
	{
		i = 0;
		ft_remove_quote_bslash(i, utils, p);
		
		// int y = 0;
		// t_pars		*p_buf = p;
		// while (p_buf)
		// {
		// 	int i = 0;
		// 	printf("\nMaillon %d\n", y);
		// 	while (p_buf->spl_cmd[i])
		// 	{
		// 		printf("  %s\n", p_buf->spl_cmd[i]);
		// 		i++;
		// 	}
		// 	p_buf = p_buf->next;
		// 	y++;
		// }
	
		ft_process(utils, p, &i);
		while (p->spl_cmd[i])
		{
			ft_remove_quote_bslash(i, utils, p);
			ft_process(utils, p, &i);
		}
		if (utils->buf_pcmd->arg_cmd == NULL && utils->buf_pcmd->cmd)
			ft_cmd_arg_join(utils->buf_pcmd, utils);
		if (p->next_is_infile || p->next_is_outfile || p->next_is_hd_stop)
			ft_error_next_file(utils->buf_pcmd, p, utils);
	}
	ft_hd_set(mini, utils->buf_pcmd, mini->p_cmd, utils);
}

static void	ft_init_mini(char **env, t_minishell *mini, t_utils *utils)
{
	int	i;
	int	shlvl;

	if (!mini->env)
		mini->env = ft_strdup_array(env, utils);
	if (!mini->env)
		ft_ultimate_free_exit(utils, NULL, NULL);
	i = 0;
	while (ft_strncmp(mini->env[i], "SHLVL", 5))
		i++;
	shlvl = ft_atoi(*(mini->env + 6)) + 1;
	free(mini->env[i]);
	mini->env[i] = ft_strjoin_free_s2("SHLVL=", ft_itoa(shlvl), utils);
	if (!mini->export)
		mini->export = ft_init_export(mini, utils);
	// //test
	// if (!mini->export)
	// 	printf("\nExport error\n\n");
	// else
	// {
	// 	int j = 0;
	// 	while (mini->export[j])
	// 	{
	// 		printf("%s\n", mini->export[j]);
	// 		j++;
	// 	}
	// }
	// //end test
	mini->count_hd = 0;
}

//main's of the parsing. if return null, no command need to be done
void	ft_parsing(char *input, t_minishell *mini, char **env)
{
	t_pars		*p;
	t_pars		*p_buf;
	t_utils		*utils;

	utils = ft_init_utils();
	ft_init_mini(env, mini, utils);
	if (ft_strlen(input) == 0 || ft_is_error_quote(input) == true)
		return ;
	p = ft_define_p(input, utils);
	if (!p)
		return ;
	utils->p = p;
	ft_init_pcmd(mini, p, utils);
	utils->mini = mini;
	p_buf = p;
	//
	utils->buf_pcmd = mini->p_cmd;
	while (utils->buf_pcmd)
	{
		ft_all_verif_process(mini, p, utils);
		if (mini->count_hd > 16 && mini->p_cmd->exit_code != 2)
		{
			if (mini->p_cmd->msg_error)
				free(mini->p_cmd->msg_error);
			mini->p_cmd->msg_error = ft_strdup(
					"minishell: maximum here-document count exceeded\n");
			if (!mini->p_cmd->msg_error)
				ft_ultimate_free_exit(utils, NULL, NULL);
		}
		p = p->next;
		utils->buf_pcmd = utils->buf_pcmd->next;
	}
	ft_free_p(p_buf);
	ft_free_utils(utils);
}
