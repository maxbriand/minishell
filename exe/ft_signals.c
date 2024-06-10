/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:36:12 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/10 18:12:31 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_ctrl_c_2(int sig)
{
	g_sig = sig;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

static void	handle_ctrl_c(int sig)
{
	g_sig = sig;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handle_ctrl_backslash(int sig)
{
	g_sig = sig;
	ft_printf("Quit (core dumped)\n");
}

void	ft_signals(int d)
{
	if (d == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_ctrl_c);
	}
	if (d == 1)
	{
		signal(SIGQUIT, handle_ctrl_backslash);
		signal(SIGINT, handle_ctrl_c_2);
	}
}
