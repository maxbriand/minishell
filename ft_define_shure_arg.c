/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_define_shure_arg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:39:49 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/21 20:18:05 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	*define_shure_arg(char **splt_cmd)
{
	int		i;
	bool	op_before;
	bool	*is_arg;

	is_arg = malloc(sizeof(bool) * ft_strlen_array(splt_cmd));
	op_before = false;
	i = 0;
	while (splt_cmd[i])
	{
		is_arg[i] = false;
		if ((splt_cmd[i][0] == '\'' || splt_cmd[i][0] == '\"')
			&& op_before == false)
			is_arg[i] = true;
		else if ((splt_cmd[i][0] == '>' || splt_cmd[i][0] == '<')
			&& ft_strlen(splt_cmd[i]) == 1)
			op_before = true;
		else
			op_before = false;
		if (splt_cmd[i][0] == '>' || splt_cmd[i][0] == '<')
			op_before = true;
		i++;
	}
	return (is_arg);
}
