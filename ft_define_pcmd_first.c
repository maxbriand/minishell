/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_define_pcmd_first.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:39:43 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/03 22:26:41 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	is_cmd(char *first_arg)
// {
// 	if (access(first_arg, X_OK) == 1)
// }


// static int	verif_cmd_slash(char *first_arg)
// {
// 	int	i;
// 	int	nb_slash;

// 	nb_slash = 0;
// 	i = 0;
// 	while (first_arg[i + 1] == '/')
// 		i++;
// 	while (first_arg[i])
// 	{
// 		if (first_arg[i] == '/')
// 			nb_slash++;
// 		i++;
// 	}
// 	if (access(first_arg, X_OK) == 1 || nb_slash == 1)
// 		return (1);
// 	//if (access(first_arg, X_OK) == 0)
// 		//printf("access good\n");
// 	return (0);
// }

//define if the first arg is a command, a redirection etc
void	define_first_pcmd(char *first_arg, t_commands *p_cmd, t_pars *p)
{
	char	**expand;
	int		i;

	if (first_arg[0] == '\0')
		return ;
	if (p->is_arg[0] == true)
	{
		if (arg_is_cmd(first_arg, p_cmd, p) == true)
		return ;
	}
	if (is_operator(first_arg, p->is_expand[0], p_cmd, p) == true)
		return ;
	if (p->is_expand[0] == true)
	{
		expand = ft_split(first_arg, ' ');
		if (access(expand[0], F_OK) != 0)
			arg_is_cmd(expand[0], p_cmd, p);
		else if (!p_cmd->msg_error)
		{
			p_cmd->msg_error = ft_better_strdup("minishell: %s: Is a directory", first_arg);
			p_cmd->exit_code = 126;
			free_array(expand);
			return ;
		}
		i = 1;
		if (expand[i])
		{
			while (is_option(expand[i], p_cmd) == true)
				i++;
			while (expand[i])
			{
				p_cmd->arg = ft_addback(p_cmd->arg, expand[i]);
				i++;
			}
		}
		free_array(expand);
		return ;
	}
	if (arg_is_cmd(first_arg, p_cmd, p) == true)
		return ;
}
