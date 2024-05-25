#include "minishell.h"

static void	free_and_strdup(char **str, int i, char *buf)
{
	free(str[i]);
	str[i] = ft_strdup(buf);
}

void	remove_quote_bslash(char **str, bool skipped, t_minishell *mini)
{
	int	i;
	int	j;
	char	*buf;

	buf = NULL;
	i = 0;
	while (str[i])
	{
		buf = NULL;
		j = 0;
		str[i] = apply_var_env(str, i, mini);
		if (str[i] == NULL)
		{
			str[i] = malloc(sizeof(char) * 1);
			if (!str)
			{
				printf("bla\n");
				if (buf)
					free(buf);
				return ;
			}
			str[i][0] = '\0';
		}
		else
		{
			while (str[i][j]) // are we shure that str(i(j existe ?
			{
				//here ? apply
				buf = ft_charaddback(&buf, str[i][j]);
				skipped = false;
				j++;
			}
			free_and_strdup(str, i, buf);
		}
		i++;
		if (buf)
			free(buf);
	}
}


char	*just_name_env(char *arg, int start)
{
	char	end;
	char *result;

	if (arg[start] == '$')
		start++;
	end = start;
	while (arg[end])
	{
		if (!ft_isalnum(arg[end]))
			break ;
		end++;
	}
	result = ft_substr(arg, start, end);
	return (result);
}


bool	is_b_slash_before(int i, char *arg)
{
	if (i > 0)
	{
		if (arg[i - 1] != '\\')
			return (true);
	}
	return (false);
}

char	*apply_var_env(char **arg, int j, t_minishell *mini)
{
	char	*var_env;
	bool	on_quote[2];
	char	*result;
	int		i;

	on_quote[0] = false;
	on_quote[1] = false;
	result = NULL;
	i = 0;
	while (arg[j][i])
	{
		ft_define_on_quote(arg[j], i, on_quote);
		if (arg[j][i] == '$' && !on_quote[0])
		{
			var_env = catch_env(mini->env, just_name_env(arg[j], i));
			result = ft_strjoin_free(result, var_env);
			i++;
			while (arg[j][i] && (ft_isalnum(arg[j][i]) || arg[j][i] == '_'))
				i++;
		}
		else
		{
			result = ft_charaddback(&result, arg[j][i]);
			i++;
		}
	}
	return (result);
}
