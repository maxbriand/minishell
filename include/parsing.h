#ifndef PARSING_H
#define PARSING_H

typedef struct s_parsing
{
	char	**spl_cmd;
	bool	next_is_hd_stop;
	bool	next_is_infile;
	bool	next_is_outfile;
	bool	next_can_be_opt;
	bool	next_can_be_arg;
	struct	s_parsing *next;
}	t_pars;

// parsing
void	ft_parsing(char *input, t_minishell *mini);
t_pars	*define_p(char *input);
void	define_cmd(t_minishell *mini, t_pars *node);
void	remove_quote_bslash(char **str, bool next_print);

//error
int		pipe_unexpected(char *input);
void	error_and_exit(char *error);
bool	error_p(int nb, char *cmd);

//define t_command
void	define_first_pcmd(char *first_arg, t_commands *p_cmd, t_pars *p);
void	define_p_cmd(char *arg, t_commands *p_cmd, t_pars *p);

//check arg
bool	is_error_quote(char *str);
bool	is_operator(char *arg, t_commands *cmd, t_pars *p);
bool	is_option(char *arg, t_commands *cmd, t_pars *p);
bool	arg_cmd(char *arg, t_commands *cmd, t_pars *p);
void	cmd_arg_join(t_commands *cmd);

//need to be added to libft ?
int		*ft_addback_int(int *old_array, int	new_element);
char	**ft_addback(char **old_array, char *new_element);
char	*ft_charaddback(char **old_array, char new_element);
void	free_tab(char **tab);
void	free_p(t_pars *p);
char	**ft_split_quote_ignore(char *str, char c);
int		is_only_space(char *str);
//char	**catch_path(char **envp);
//char	*verif_access(char *cmd, char **path);




#endif
