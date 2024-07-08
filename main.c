/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:15:54 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/09 00:21:02 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

t_minishell	*ft_declare_data(void)
{
	t_minishell	*data;

	data = malloc(sizeof(t_minishell));
	if (!data)
		ft_exitf("malloc issue", 1, NULL, NULL);
	data->p_cmd = NULL;
	data->export = NULL;
	data->env = NULL;
	data->open_dquote = 0;
	data->open_quote = 0;
	data->exit_code = 0;
	data->wait_code = 0;
	data->count_hd = 0;
	data->pipefds = NULL;
	return (data);
}

static t_minishell	*ft_begin(int ac, char **av)
{
	t_minishell	*data;

	(void) ac;
	(void) av;
	data = NULL;
	data = ft_declare_data();
	return (data);
}

static int	ft_end_of_code(t_minishell *data)
{
	int	store_ec;

	ft_printf("exit\n");
	store_ec = data->exit_code;
	ft_free_data_exit(data);
	return (store_ec);
}

int	main(int ac, char **av, char **env)
{
	char		*cmd;
	t_minishell	*data;

	data = ft_begin(ac, av);
	while (1)
	{
		ft_signals(0);
		cmd = readline("minishell: ");
		if (g_sig == 2)
			data->exit_code = 130;
		if (g_sig == 3)
			data->exit_code = 131;
		g_sig = 0;
		if (!cmd)
			break ;
		if (*cmd)
			add_history(cmd);
		ft_parsing(data, cmd, env);
		ft_create_heredocs(data, data->p_cmd);
		ft_signals(1);
		ft_exe(data, data->p_cmd);
		free(cmd);
		ft_free_data(data);
	}
	return (ft_end_of_code(data));
}
