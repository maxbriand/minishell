/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:28:11 by gmersch           #+#    #+#             */
/*   Updated: 2024/06/28 17:08:53 by gmersch          ###   ########.fr       */
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
	bool				malloc_error;
	struct s_parsing	*next;
}	t_pars;

// parsing
void	ft_parsing(char *input, t_minishell *mini, char **env);
t_pars	*ft_define_p(char *input);
int		ft_init_pcmd(t_minishell *mini, t_pars *node);
int		ft_remove_quote_bslash(char **str, int i, t_minishell *mini, t_pars *p);
bool	*ft_define_shure_arg(char **splt_cmd);

//error
int		ft_pipe_unexpected(char *input, t_pars *p);
bool	ft_error_p(int nb, char *cmd);
void	ft_set_error_op(t_commands *p_cmd);
void	ft_error_next_file(t_commands *p_cmd);

//define t_command
void	ft_define_first_pcmd(char *first_arg, t_commands *p_cmd, t_pars *p);
int		ft_define_p_cmd(char *arg, int i, t_commands *p_cmd, t_pars *p);

//check arg
bool	ft_is_error_quote(char *str);
bool	ft_is_operator(char *arg, t_commands *cmd, t_pars *p);
bool	ft_is_option(char *arg, t_commands *cmd, t_pars *p);
bool	ft_arg_is_cmd(char *arg, t_commands *cmd, t_pars *p);
void	ft_cmd_arg_join(t_commands *cmd);
bool	ft_define_on_quote(char *str, int i, bool *on_quote);
void	ft_define_outfile_error(t_commands *p_cmd);
void	ft_define_infile_error(t_commands *p_cmd);

//fuction usefull
char	**ft_addback(char **old_array, char *new_element);
char	**ft_addback_free(char **old_array, char *new_element);
char	*ft_charaddback(char **old_array, char new_element);
char	*ft_better_strdup(char *s, char *arg);
char	*ft_better_strdup_free(char *s, char *arg);
char	**ft_strdup_array(char **array);
bool	ft_is_s1_before(char *str1, char *str2);
size_t	ft_better_strlen(const char *s);

//ultimate_free
void	ft_free_array(char **tab);
void	ft_free_p(t_pars *p);
void	ft_free_p_cmd(t_commands *p_cmd);
void	ft_ultimate_free_exit(t_minishell *mini, t_pars *p, char **str);
void	ft_free_mini(t_minishell *mini);

char	**ft_split_quote_ignore(char *str, char c);
char	**ft_split_separator(char *str);
bool	ft_is_sep(char c, char *sep);
void	ft_define_int(int *i, int *last_split, char *str, char *sep);
char	**ft_init_export(t_minishell *mini);
int		ft_is_only_space(char *str);
char	*ft_catch_env(char **envp, char *str);
char	*ft_strjoin_free(char *s1, char *s2);
int		ft_strlen_array(char **array);
void	ft_remove_element(char **array, int id_rm);

#endif
