/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_redir_filepath_amb.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/26 17:17:50 by hlin          #+#    #+#                 */
/*   Updated: 2021/10/26 17:32:20 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ambiguous_value_validation(char *value, char *variable,
	t_parse *prs, int i)
{
	if (!value || ft_strchr(value, ' '))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(variable, 2);
		ft_put_error(": ambiguous redirect");
		free(variable);
		prs->i = i;
		return (-1);
	}
	free(variable);
	free(value);
	return (0);
}

static char	*get_ambiguous_variable(char *joined, char *var)
{
	char	*temp;

	temp = NULL;
	temp = joined;
	joined = ft_strjoin(joined, "$");
	free(temp);
	temp = joined;
	joined = ft_strjoin(joined, var);
	free(temp);
	return (joined);
}

static int	ambiguous_key_validation(char *key, char *variable)
{
	if (ft_strchr(key, '"') || ft_strchr(key, '\''))
	{
		free(key);
		free(variable);
		return (0);
	}
	return (1);
}

static int	get_varkey_len(char *s, int i)
{
	if (ft_isdigit(s[i]))
		i++;
	else
		while (ft_isalnum(s[i]) || s[i] == '_')
			i++;
	return (i);
}

int	check_ambiguous_redir(char *s, t_list *env_lst, t_parse *prs)
{
	char	*key;
	char	*value;
	char	*variable;
	int		i;
	int		j;

	value = NULL;
	variable = NULL;
	i = prs->i;
	while (!value && s[i] == '$')
	{
		i++;
		j = i;
		i = get_varkey_len(s, i);
		key = ft_substr(s, j, i - j);
		if (!ambiguous_key_validation(key, variable))
			return (0);
		variable = get_ambiguous_variable(variable, key);
		value = get_envvar_arg_value(key, env_lst);
		free(key);
	}
	if (!ambiguous_value_validation(value, variable, prs, i))
		return (0);
	return (-1);
}
