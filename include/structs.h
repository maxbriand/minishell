/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:38:36 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/05 22:41:37 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_commands
{
	char				*infile;
	char				**hd_stop;
	char				*heredoc;
	bool				in_pipe;
	char				*outfile;
	bool				append_outfile;
	char				*cmd;
	char				*option;
	char				**arg;
	char				**arg_cmd;
	bool				b_builtins;
	int					*pipefd0;
	int					*pipefd1;
	int					old_fd1;
	int					old_fd0;
	bool				bf_cmd;
	bool				err_is_infile;
	bool				err_is_outfile;
	int					exit_code;
	char				*msg_error;
	struct s_commands	*next;
}	t_commands;

typedef struct s_minishell
{
	t_commands		*p_cmd;
	int				pipe_nbr;
	char			**env;
	char			**export;
	bool			env_malloc;
	int				open_quote;
	int				open_dquote;
	int				**pipefds;
	int				exit_code;
	int				wait_code;
	int				count_hd;
}	t_minishell;

typedef struct s_parsing
{
	char				**spl_cmd;
	bool				*is_arg;
	bool				*is_expand;
	bool				next_is_hd_stop;
	bool				next_is_infile;
	bool				next_is_outfile;
	bool				next_can_be_opt;
	bool				next_can_be_arg;
	bool				last_was_echo;
	bool				last_was_env;
	bool				next_is_arg;
	char				*error_msg;
	int					exit_code;
	bool				was_quote;
	struct s_parsing	*next;
}	t_pars;

typedef struct s_utils
{
	t_pars		*p;
	t_minishell	*mini;
	int			ap_j;
	t_commands	*buf_pcmd;
	t_pars		*buf_p;
	char		*exp_str;
	char		**res_splt_q;
	int			last_split;
	char		**res_splt_s;
	int			last_split_sep;
	char		*sep;
	int			env_free;
	char		*s2;

}	t_utils;

#endif
