#include "minishell.h"

static void	free_and_strdup(char **str, int i, char *buf)
{
	free(str[i]);
	str[i] = ft_strdup(buf);
	free(buf);
}

void	remove_quote_bslash(char **str, t_minishell *mini)
{
	int	i;
	int	j;
	char	*buf;

	i = 0;
	while (str[i])
	{
		buf = NULL;
		j = 0;
		str[i] = apply_var_env(str, i, mini);//je dois faire par rapoirt auchar
		if (str[i] == NULL)
		{
			str[i] = malloc(sizeof(char) * 1);
			if (!str[i])
				exit (1); //mayday error
			str[i][0] = '\0';
		}
		else
		{
			while (str[i][j]) // are we shure that str(i(j existe ?
			{
				//here ? apply
				buf = ft_charaddback(&buf, str[i][j]);
				j++;
			}
			free_and_strdup(str, i, buf);
		}
		i++;
	}
}

char	*just_name_env(char *arg, int start, bool *on_quote)
{
	int	end;
	char *result;

	if (arg[start] == '$')
		start++;
	end = start;
	while (arg[end])
	{
		if (!ft_isalpha(arg[end]) || (arg[end] != '\'' && on_quote[0]) || (arg[end] == '\"' && on_quote[1]))
			break ;
		end++;
	}
	result = ft_substr(arg, start, end - start);
	return (result);
}

char	*apply_var_env(char **arg, int i, t_minishell *mini)
{
	char	*var_env;
	bool	on_quote[2];
	char	*result;
	bool	can_copy;
	int		j;

	on_quote[0] = false;
	on_quote[1] = false;
	result = NULL;
	j = 0;
	while (arg[i][j])
	{
		if (ft_define_on_quote(arg[i], j, on_quote) == true)
			can_copy = false;
		else
			can_copy = true;
		if (arg[i][j] == '$' && !on_quote[0])
		{
			var_env = catch_env(mini->env, just_name_env(arg[i], j, on_quote));
			result = ft_strjoin_free(result, var_env);
			j++;
			while (arg[i][j] && (ft_isalnum(arg[i][j]) || arg[i][j] == '_'))
				j++;
		}
		else
		{
			if (can_copy == true)
				result = ft_charaddback(&result, arg[i][j]);
			j++;
		}
	}
	return (result);
}
