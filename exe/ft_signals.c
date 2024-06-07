/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:36:12 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/07 15:53:21 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_ctrl_c(int sig)
{
	g_sig = 2;
	// ft_printf("\n");
    rl_replace_line("", 0);
    // Redisplay the prompt on a new line
    rl_on_new_line();
    rl_redisplay();
}

void	ft_signals(t_minishell *data)
{
	signal(SIGQUIT, SIG_IGN);
	//signal(SIGINT, handle_ctrl_c);
}
