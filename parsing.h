#ifndef PARSING_H
#define PARSING_H

#include "minishell.h"

typedef struct s_parsing
{
	char	**spl_cmd;
	bool	next_is_hd_stop;
	bool	next_is_infile;
	bool	next_is_outfile;
	struct	s_parsing *next;
}	t_pars;

// parsing
void	parsing(char *input, t_minishell *mini);
t_pars	*define_p(char *input);
void	define_cmd(t_minishell *mini, t_pars *node);

//error
int		pipe_unexpected(char *input);
void	error_and_exit(char *error);
bool	error_p(int nb, char *cmd);

//define t_command
void	define_first_arg(char *first_arg, t_commands *cmd, t_pars *node);

//need to be added to libft ?
int		*ft_addback_int(int *old_array, int	new_element);
char	**ft_addback(char **old_array, char *new_element);
void	free_tab(char **tab);
void	free_p(t_pars *p);
char	**ft_split_parsing(char const *s, char c);



#endif
