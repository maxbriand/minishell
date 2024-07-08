/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:28:11 by gmersch           #+#    #+#             */
/*   Updated: 2024/07/09 00:48:15 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

void	ft_parsing(t_minishell *data, char *input, char **env);
void	ft_init_env(t_minishell *data, t_utils *utils, char **env);
void	ft_init_shlvl(t_minishell *data, t_utils *utils);
t_pars	*ft_define_p(t_utils *utils, char *input);
void	ft_init_pcmd(t_minishell *mini, t_pars *p, t_utils *utils);
int		ft_remove_quote_bslash(int i, t_utils *utils, t_pars *p);
bool	*ft_define_shure_arg(
			char **splt_cmd, t_utils *utils, char **input_no_pipe, t_pars *n);
void	ft_hd_set(
			t_minishell *mini, t_commands *buf,
			t_commands *p_cmd, t_utils *utils);
t_utils	*ft_declare_utils(void);
int		ft_is_error(t_utils *utils, char *input, t_pars **p);

int		ft_pipe_unexpected(char *input, t_pars *p, t_utils *utils);
bool	ft_error_p(int nb, char *cmd);
void	ft_set_error_op(t_commands *p_cmd, t_utils *utils);
void	ft_error_next_file(t_commands *p_cmd, t_pars *p, t_utils *utils);

void	ft_define_first_pcmd(
			char *first_arg, t_commands *p_cmd, t_pars *p, t_utils *utils);
void	ft_define_p_cmd(char *arg, int i, t_utils *utils, t_pars *p);

bool	ft_is_error_quote(char *str);
bool	ft_is_operator(char *arg, t_commands *cmd, t_pars *p, t_utils *utils);
bool	ft_is_option(char *arg, t_commands *p_cmd, t_pars *p, t_utils *utils);
bool	ft_arg_is_cmd(char *arg, t_commands *p_cmd, t_pars *p, t_utils *utils);
void	ft_cmd_arg_join(t_commands *cmd, t_utils *utils);
bool	ft_define_on_quote(char *str, int i, bool *on_quote);
void	ft_define_outfile_error(t_commands *p_cmd, t_utils *utils);
void	ft_define_infile_error(t_commands *p_cmd, t_utils *utils);

char	**ft_addback(char **old_array, char *new_element);
char	**ft_addback_free(char **old_array, char *new_element);
char	*ft_charaddback(char **old_array, char new_element, t_utils *utils);
char	*ft_better_strdup(char *s, char *arg, t_utils *utils);
char	*ft_better_strdup_free(char *s, char *arg, t_utils *utils);
char	**ft_strdup_array(char **array, t_utils *utils);
bool	ft_is_s1_before(char *str1, char *str2);
size_t	ft_better_strlen(const char *s);

void	*ft_free_array(char **tab);
void	ft_free_p(t_pars *p);
void	ft_ultimate_free_exit(
			t_utils *utils, char **array, char *str, char *msg);
void	ft_free_mini(t_minishell *mini, t_utils *utils);
void	ft_free_utils(t_utils **utils);
void	ft_free_pcmd(t_commands *p_cmd);
void	ft_redefine_utils(t_utils *utils);

char	**ft_split_quote_ignore(char *str, char c, t_utils *utils);
char	**ft_split_separator(char **str, int i, t_utils *utils);
bool	ft_is_sep(char c, char *sep);
void	ft_define_int(int *i, int *last_split, char *str, char *sep);
void	ft_init_export(t_minishell *data, t_utils *utils);
int		ft_is_only_space(char *str);
char	*ft_catch_env(char **envp, char *str, t_utils *utils);
char	*ft_strjoin_free_s1(char *s1, char *s2, t_utils *utils);
char	*ft_strjoin_free_s2(char *s1, char *s2, t_utils *utils);
char	*ft_strjoin_free(char *s1, char *s2, t_utils *utils);
int		ft_strlen_array(char **array);
void	ft_remove_element(char **array, int id_rm);

#endif
