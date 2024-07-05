/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_define_shure_arg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:39:49 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/05 13:57:17 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	*ft_define_shure_arg(
	char **splt_cmd, t_utils *utils, char **input_no_pipe, t_pars *n)
{
	int		i;
	bool	op_before;
	bool	*is_arg;

	is_arg = malloc(sizeof(bool) * ft_strlen_array(splt_cmd));
	if (!is_arg)
	{
		ft_free_array(input_no_pipe);
		ft_ultimate_free_exit(utils, splt_cmd, (char *)n, NULL);
	}
	op_before = false;
	i = 0;
	while (splt_cmd[i])
	{
		is_arg[i] = false;
		if ((splt_cmd[i][0] == '\'' || splt_cmd[i][0] == '\"')
			&& op_before == false)
			is_arg[i] = true;
		else
			op_before = false;
		if (splt_cmd[i][0] == '>' || splt_cmd[i][0] == '<')
			op_before = true;
		i++;
	}
	return (is_arg);
}
