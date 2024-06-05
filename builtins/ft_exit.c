#include "minishell.h"

static int	ft_check_long(const char *s)
{
	long		nbr;
	const char	*sign;
	int			digit;	

	nbr = 0;
	sign = s;
	while (ft_isspace(*s) == 1)
		s++;
	if (*s == '-' || *s == '+')
		s++;
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

// stop if the first arg is non numeric
static int	ft_exit_parsing(t_minishell *data, t_commands *c_cmd)
{
	if (ft_strcheck(c_cmd->arg[0]) == 1)
	{
		ft_write_error(" numeric argument required");
		data->exit_code = 2;
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

void	ft_exit(t_minishell *data, t_commands *c_cmd)
{
	long	exit_code;

	ft_write_error("exit");
	if (!c_cmd->arg)
		exit(data->exit_code);
	if (ft_exit_parsing(data, c_cmd) != 0)
		return ;
	exit_code = ft_atol(*(c_cmd->arg));
	data->exit_code = exit_code;
	exit(exit_code);
}
