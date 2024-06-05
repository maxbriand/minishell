#ifndef PARSING_H
#define PARSING_H

#include "minishell.h"

typedef struct s_parsing
{
	char	**spl_cmd;
	//i need to do a function where
	//is arg is define about if splitcmd[x] has quote
	//c'est forcement un argument si on quote sauf
	//si next is outfile etc
	bool	*is_arg;
	bool	*is_expand;
	bool	next_is_hd_stop;
	bool	next_is_infile;
	bool	next_is_outfile;
	bool	next_can_be_opt;
	bool	next_can_be_arg;
	char	*error_msg;
	int		exit_code;
	bool	file_err[2];
	struct	s_parsing *next;
}	t_pars;

// parsing
void	ft_parsing(char *input, t_minishell *mini);
t_pars	*define_p(char *input);
void	init_pcmd(t_minishell *mini, t_pars *node);
void	remove_quote_bslash(char **str, int i, t_minishell *mini, t_pars *p);
bool	*define_shure_arg(char **splt_cmd);

//error
int	pipe_unexpected(char *input, t_pars *p);
void	error_and_exit(char *error);
bool	error_p(int nb, char *cmd);
void	ft_better_putstr_fd(char *str, char *arg, int error);
void	set_error_op(t_commands *p_cmd);
void	ft_is_expand(char *arg, int i, t_commands *p_cmd);
void	error_next_file(t_commands *p_cmd);


//define t_command
void	define_first_pcmd(char *first_arg, t_commands *p_cmd, t_pars *p);
void	define_p_cmd(char *arg, int i, t_commands *p_cmd, t_pars *p);

//check arg
bool	is_error_quote(char *str);
bool	is_operator(char *arg, bool is_expand, t_commands *cmd, t_pars *p);
bool	is_option(char *arg, t_commands *cmd);
bool	arg_is_cmd(char *arg, t_commands *cmd, t_pars *p);
void	cmd_arg_join(t_commands *cmd);
bool	ft_define_on_quote(char *str, int i, bool *on_quote);
void	define_outfile_error(t_commands *p_cmd);
void	define_infile_error(t_commands *p_cmd);
//void	check_nb_op(char **spl_cmd, char **error_msg, bool *file_err, int *exit_code);


//need to be added to libft ?
int		*ft_addback_int(int *old_array, int	new_element);
char	**ft_addback(char **old_array, char *new_element);
char	*ft_charaddback(char **old_array, char new_element);
char	*ft_better_strdup(char *s, char *arg);
char	*ft_better_strdup_free(char *s, char *arg);
char	**ft_strdup_array(char **array);

//ultimate_free
void	free_array(char **tab);
void	free_p(t_pars *p);
void	free_p_cmd(t_commands *p_cmd);

char	**ft_split_quote_ignore(char *str, char c);
char	**ft_split_separator(char *str);
char	**ft_init_export(char **env);
int		is_only_space(char *str);
char	*catch_env(char **envp, char *str);
char	*ft_strjoin_free(char *s1, char *s2);
int		ft_strlen_array(char **array);
void	ft_remove_element(char **array, int id_rm);





#endif
