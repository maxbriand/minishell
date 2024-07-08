/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:15:54 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/08 02:39:38 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

/*static void	ft_printf_parsing(t_commands *p_cmd)
{
	ft_printf("\n\033[1;33mPARSING RESULT:\033[0m");
	while (p_cmd)
	{
		ft_printf("\n\033[1;32mInput redirection:\033[0m");
		if (p_cmd->infile == NULL && !p_cmd->hd_stop && p_cmd->in_pipe == 0)
			ft_printf("\033[1;31m(no redirection)\033[0m");
		ft_printf("\n");
		ft_printf("Infile: %s\n", p_cmd->infile);
		int y = 0;
		if (!p_cmd->hd_stop)
			ft_printf("hd_stop: (null) \n");
		else
		{
			while (p_cmd->hd_stop[y] && p_cmd->hd_stop)
			{
				ft_printf("hd_stop: %s n%d\n", p_cmd->hd_stop[y], y);
				y++;
			}
		}
		ft_printf("In pipe: %d\n", p_cmd->in_pipe);
		ft_printf("\n\033[1;32mOutput redirection:\033[0m");
		if (p_cmd->outfile == NULL)
			ft_printf("\033[1;31m(no redirection)\033[0m");
		ft_printf("\n");
		ft_printf("Outfile: %s \n", p_cmd->outfile);
		ft_printf("Append-out: %d\n", p_cmd->append_outfile);
		ft_printf("\n\033[1;32mCommand:\033[0m");
		if (p_cmd->cmd == NULL)
			ft_printf("\033[1;31m(no command)\033[0m\n");
		else
			ft_printf("\n");
		ft_printf("Cmd: %s\n", p_cmd->cmd);
		ft_printf("Option: %s\n", p_cmd->option);
		ft_printf("Arg: ");
		ft_arrprintf(p_cmd->arg);
		ft_printf("\n");
		ft_printf("Nbr of arg: %d\n", ft_arrlen(p_cmd->arg));
		y = 0;
		ft_printf("cmd+arg+opt: ");
		if (!p_cmd->arg_cmd)
			ft_printf("(null)");
		else
		{
			while (p_cmd->arg_cmd[y])
			{
				ft_printf("%s ", p_cmd->arg_cmd[y]);
				y++;
			}
		}
		ft_printf("\n");
		ft_printf("Builtins: %d\n", p_cmd->b_builtins);
		ft_printf("\n\033[1;32mError:\033[0m\n");
		ft_printf("Msg error: %s\n", p_cmd->msg_error);
		ft_printf("Code error: %d\n", p_cmd->exit_code);
		ft_printf("Is Infile Error: %d\n", p_cmd->err_is_infile);
		ft_printf("Is Outfile Error: %d\n", p_cmd->err_is_outfile);
		p_cmd = p_cmd->next;
	}
	ft_printf("\n\033[1;32mOutput result: \033[0m\n");
}*/

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
		//ft_printf_parsing(data->p_cmd);
		ft_exe(data, data->p_cmd);
		free(cmd);
		ft_free_data(data);
	}
	return (ft_end_of_code(data));
}
