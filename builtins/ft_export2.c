/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:57:09 by mbriand           #+#    #+#             */
/*   Updated: 2024/06/06 20:14:59 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ft_modify_export

// FT_STRDUP ADDING DQUOTES
char	*ft_strdup_dquotes(char *s)
{
	int 	len;
	char	*new_s;
	int		i;

	if (strchr(s, '=') == 0)
		return (ft_strdup(s));
	len = ft_strlen(s) + 2 + 1;
	new_s = malloc(sizeof(char) * len);
	// if (new_s == NULL)
	// 	return ()
	i = 0;
	while (*s)
	{
		new_s[i] = *s;
		if (*s == '=')
		{
			i++;
			new_s[i] = '"'; 
		}	
		i++;
		s++;
	}
	new_s[i] = '"';
	new_s[i + 1] = '\0';
	return (new_s);
}

static void	ft_modify_line(t_minishell *data, char *var, int n)
{
	if (strchr(var, '=') == 0)
		return ;
	free(data->export[n]);
	data->export[n] = ft_strdup_dquotes(var);
}

// ADD A LINE VAR IN EXPORT
static void	ft_add_line(t_minishell *data, char *var)
{
	char	**new_export;
	int		lnew_export;

	lnew_export = ft_arrlen(data->export) + 1 + 1;
	new_export = malloc(sizeof(char *) * lnew_export);
	// if (new_export == NULL)
	// 	ft_exit_failure();
	ft_arrcpy(new_export, data->export);
	new_export[lnew_export - 2] = ft_strdup_dquotes(var); 
	new_export[lnew_export - 1] = NULL;
	ft_arrfree(data->export);
	data->export = new_export;
}

// CHOOSE BETWEEN ADD OR MODIFY A VAR IN EXPORT
void	ft_export_export(t_minishell *data, char *var)
{
	int	n;
	
	n = ft_lfor_var(data->export, var);
	if (n == -1)
		ft_add_line(data, var);
	else
		ft_modify_line(data, var, n);
}
