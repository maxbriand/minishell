#include "../../parsing.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_p(t_pars *p)
{
	t_pars	*p_buf;

	while(p)
	{
		p_buf = p;
		free_tab(p->spl_cmd);
		p = p->next;
		free(p_buf);
	}
	if (p)
		free(p);
}
