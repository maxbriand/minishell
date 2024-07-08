/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:57:09 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/09 00:19:44 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_set_new_s(char *new_s, char *s)
{
	int	i;
	int	already;

	i = 0;
	already = 0;
	while (*s)
	{
		new_s[i] = *s;
		if (*s == '=' && already == 0)
		{
			i++;
			already++;
			new_s[i] = '"';
		}
		i++;
		s++;
	}
	new_s[i] = '"';
	new_s[i + 1] = '\0';
}

char	*ft_strdup_dquotes(char *s, t_minishell *data)
{
	int		len;
	char	*new_s;

	if (ft_strchr(s, '=') == 0)
		return (ft_strdup(s));
	len = ft_strlen(s) + 2 + 1;
	new_s = malloc(sizeof(char) * len);
	if (!new_s)
		ft_exitf("malloc issue", 1, NULL, data);
	ft_set_new_s(new_s, s);
	return (new_s);
}

static void	ft_modify_line(t_minishell *data, char *var, int n)
{
	if (ft_strchr(var, '=') == 0)
		return ;
	free(data->export[n]);
	data->export[n] = ft_strdup_dquotes(var, data);
	if (!data->export[n])
		ft_exitf("malloc issue", 1, NULL, data);
}

// ADD A LINE VAR IN EXPORT
static void	ft_add_line(t_minishell *data, char *var)
{
	char	**new_export;
	int		lnew_export;

	lnew_export = ft_arrlen(data->export) + 1 + 1;
	new_export = malloc(sizeof(char *) * lnew_export);
	if (!new_export)
		ft_exitf("malloc issue", 1, NULL, data);
	ft_arrcpy(new_export, data->export);
	new_export[lnew_export - 2] = ft_strdup_dquotes(var, data);
	if (!new_export[lnew_export - 2])
		ft_exitf("malloc issue", 1, NULL, data);
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
