/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_newterm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:18:41 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/07 02:31:27 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_set_newterm(t_minishell *data)
{
	struct termios	newterm;

	if (tcgetattr(STDIN_FILENO, &newterm) < 0)
	{
		ft_write_error("tcgetattr issue");
		exit (EXIT_FAILURE);
	}
	newterm.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &newterm) < 0)
	{
		ft_write_error("tcsetattr issue");
		exit (EXIT_FAILURE);
    }	
}
