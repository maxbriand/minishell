/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:58:52 by mbriand           #+#    #+#             */
/*   Updated: 2024/05/26 21:52:50 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child_exe(t_minishell *data, t_commands *c_cmd, int **pipefds, int c)
{
	char	*path;
	
	ft_set_pipefd(data, c_cmd, pipefds, c);
	if (c_cmd->b_builtins == 0)
		path = ft_check_path(data, c_cmd);
	ft_printf("test");
	if (c_cmd->infile || c_cmd->hd_stop || c_cmd->in_pipe)
		ft_input_redir(data, c_cmd, c_cmd->pipefd0);
	if (c_cmd->outfile || c_cmd->next != NULL)
		ft_output_redir(data, c_cmd, c_cmd->pipefd1);
	ft_close_pipes(data, pipefds);
	if (c_cmd->b_builtins == 0)
	{
		execve(path, c_cmd->arg_cmd, data->env);
		ft_exit_failure("execution issue\n", data);
	}
	else
	{
		ft_builtins_exe(data, c_cmd);
		exit(EXIT_SUCCESS);
	}
}

void	ft_exe(t_minishell *data, t_commands *p_cmd)
{
	int		c;
	pid_t	pid;

	data->pipe_nbr = ft_pipe_counter(p_cmd);
	if (data->pipe_nbr == 0 && p_cmd->b_builtins == 1)
	{
		ft_builtins_exe(data, p_cmd);
		return ;
	}
	data->pipefds = ft_create_pipes(data->pipe_nbr, data);
	c = 0;
	while (p_cmd)
	{
		pid = fork();
		if (pid == -1)
			ft_exit_failure("fork creation issue", data);
		if (pid == 0)
				ft_child_exe(data, p_cmd, data->pipefds, c);
		p_cmd = p_cmd->next;
		c++;
	}
	ft_close_pipes(data, data->pipefds);
	
	while(wait(&(data->exit_stat)) != -1);
	data->exit_stat = WEXITSTATUS(data->exit_stat);
	ft_printf("the value of test is %d\n", data->exit_stat);
}
