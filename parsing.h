/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:28:11 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/19 17:22:25 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

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
	bool				file_err[2];
	bool				malloc_error;
	struct s_parsing	*next;
}	t_pars;

// parsing
void	ft_parsing(char *input, t_minishell *mini, char **env);
t_pars	*define_p(char *input);
int		init_pcmd(t_minishell *mini, t_pars *node);
int		remove_quote_bslash(char **str, int i, t_minishell *mini, t_pars *p);
bool	*define_shure_arg(char **splt_cmd);

//error
int		pipe_unexpected(char *input, t_pars *p);
void	error_and_exit(char *error);
bool	error_p(int nb, char *cmd);
void	ft_better_putstr_fd(char *str, char *arg, int error);
void	set_error_op(t_commands *p_cmd);
void	error_next_file(t_commands *p_cmd);

//define t_command
void	define_first_pcmd(char *first_arg, t_commands *p_cmd, t_pars *p);
int		define_p_cmd(char *arg, int i, t_commands *p_cmd, t_pars *p);

//check arg
bool	is_error_quote(char *str);
bool	ft_is_operator(char *arg, t_commands *cmd, t_pars *p);
bool	is_option(char *arg, t_commands *cmd, t_pars *p);
bool	arg_is_cmd(char *arg, t_commands *cmd, t_pars *p);
void	cmd_arg_join(t_commands *cmd);
bool	ft_define_on_quote(char *str, int i, bool *on_quote);
void	define_outfile_error(t_commands *p_cmd);
void	define_infile_error(t_commands *p_cmd);

//fuction usefull
int		*ft_addback_int(int *old_array, int new_element);
char	**ft_addback(char **old_array, char *new_element);
char	**ft_addback_free(char **old_array, char *new_element);
char	*ft_charaddback(char **old_array, char new_element);
char	*ft_better_strdup(char *s, char *arg);
char	*ft_better_strdup_free(char *s, char *arg);
char	**ft_strdup_array(char **array);
bool	ft_is_s1_before(char *str1, char *str2);
size_t	ft_better_strlen(const char *s);

//ultimate_free
void	free_array(char **tab);
void	free_p(t_pars *p);
void	free_p_cmd(t_commands *p_cmd);
void	ultimate_free_exit(t_minishell *mini, t_pars *p, char **str);
void	free_mini(t_minishell *mini);

char	**ft_split_quote_ignore(char *str, char c);
char	**ft_split_separator(char *str);
bool	is_sep(char c, char *sep);
char	**ft_init_export(t_minishell *mini);
int		is_only_space(char *str);
char	*catch_env(char **envp, char *str);
char	*ft_strjoin_free(char *s1, char *s2);
int		ft_strlen_array(char **array);
void	ft_remove_element(char **array, int id_rm);

#endif
