/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:58:52 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/09 01:57:00 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exe(t_minishell *data, t_commands *p_cmd)
{
	if (ft_before_cmd_exe(data, p_cmd) == 1)
		return ;
	if (ft_exe_1_builtin(data, p_cmd) == 1)
		return ;
	ft_exe_in_fork(data, p_cmd);
}
