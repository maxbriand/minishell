/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:38:46 by mbriand           #+#    #+#             */
/*   Updated: 2024/07/09 00:49:37 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_string_ite(char *s)
{
	while (ft_isspace(*s) == 1)
		s++;
	if (*s == '-' || *s == '+')
		s++;
	return (s);
}

static int	ft_check_long(char *s)
{
	long	nbr;
	char	*sign;
	int		digit;	

	nbr = 0;
	sign = s;
	s = ft_string_ite(s);
	while (*s)
	{
		digit = *s - '0';
		if ((((LONG_MAX / 10 == nbr) && digit > LONG_MAX % 10)
				|| (LONG_MAX / 10 < nbr)) && *sign != '-')
			return (1);
		if ((((LONG_MIN / 10 == -nbr) && - digit < LONG_MIN % 10)
				|| (LONG_MIN / 10 > -nbr)) && *sign == '-')
			return (1);
		nbr *= 10;
		nbr += (*s) - 48;
		s++;
	}
	if (*sign == '-')
		nbr *= -1;
	return (0);
}

static int	ft_strcheck(char *str)
{
	int		i;
	char	*exit_code;

	exit_code = str;
	while (ft_isspace(*str) == 1)
		str++;
	if (*str == '-' || *str == '+')
		str++;
	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) != 1)
			return (1);
		i++;
	}
	if (i == 0)
		return (1);
	if (ft_check_long(exit_code) == 1)
		return (1);
	return (0);
}

static int	ft_exit_parsing(t_minishell *data, t_commands *c_cmd)
{
	if (ft_strcheck(c_cmd->arg[0]) == 1)
	{
		ft_write_error(" numeric argument required");
		data->exit_code = 2;
		ft_free_data(data);
		ft_free_data_exit(data);
		exit(2);
	}
	if (ft_arrlen(c_cmd->arg) > 1)
	{
		ft_write_error(" too many arguments");
		data->exit_code = 1;
		return (1);
	}
	return (0);
}

//
void	ft_exit(t_minishell *data, t_commands *c_cmd)
{
	long	exit_code;

	if (data->pipe_nbr == 0)
		ft_write_error("exit");
	if (!c_cmd->arg)
		exit(data->exit_code);
	if (ft_exit_parsing(data, c_cmd) != 0)
		return ;
	exit_code = ft_atol(*(c_cmd->arg));
	ft_free_data(data);
	ft_free_data_exit(data);
	exit(exit_code);
}
