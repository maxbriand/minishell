#ifndef PARSING_H
#define PARSING_H

#include "minishell.h"

typedef struct s_parsing
{
	char	**tab;
	struct	s_parsing *next;
}	t_pars;

// parsing
t_minishell	*parsing(char *input);
t_pars		*define_p(char *input);
void		free_tab(char **tab);
void		free_p(t_pars *p);

int			pipe_unexpected(char *input);
void		error_and_exit(char *error);




#endif
