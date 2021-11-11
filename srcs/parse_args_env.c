/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_args_env.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 15:15:28 by hlin          #+#    #+#                 */
/*   Updated: 2021/10/26 17:14:59 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_envvar_arg_value(char *key, t_list *env)
{
	t_env	*temp;
	char	*value;

	value = NULL;
	while (env != NULL)
	{
		temp = env->content;
		if (!(ft_strcmp(key, temp->key)))
			value = ft_strdup(temp->value);
		env = env->next;
	}
	return (value);
}

static char	*remove_spaces(char *s)
{
	char	*res;
	char	*temp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (res == NULL)
		return (NULL);
	temp = s;
	s = ft_strtrim(s, " ");
	free(temp);
	while (s[i])
	{
		if (s[i] == ' ' && s[i + 1] == ' ')
			i++;
		else
			res[j++] = s[i++];
	}
	res[j] = '\0';
	free(s);
	return (res);
}

static void	get_variable(char *s, t_list *env, t_parse *prs)
{
	int		j;
	char	*var_va;
	char	*tmp;

	prs->var.i++;
	j = prs->var.i;
	if (ft_isdigit(s[prs->var.i]))
		prs->var.i++;
	else
		while (ft_isalnum(s[prs->var.i]) || s[prs->var.i] == '_')
			prs->var.i++;
	tmp = ft_substr(s, j, prs->var.i - j);
	var_va = get_envvar_arg_value(tmp, env);
	if (var_va != NULL && prs->outside_quote && ft_strchr(var_va, ' '))
	{
		var_va = remove_spaces(var_va);
		prs->extra_args = ft_split(var_va, ' ');
		free(var_va);
		var_va = prs->extra_args[0];
	}
	free(tmp);
	tmp = prs->var.result;
	prs->var.result = ft_strjoin(prs->var.result, var_va);
	free(var_va);
	free(tmp);
}

static void	check_envvar_edge_cases(char *s, t_parse *prs)
{
	char	*temp;
	char	*tmp;

	if (s[prs->var.i] == '$' && s[prs->var.i + 1] == '?')
	{
		tmp = prs->var.result;
		prs->var.i += 2;
		prs->var.result = ft_strjoin(prs->var.result,
				temp = ft_itoa(prs->ret_value));
		free(temp);
		free(tmp);
	}
	if (s[prs->var.i] == '$' && s[prs->var.i + 1] == '$')
	{
		tmp = prs->var.result;
		prs->var.i += 2;
		prs->var.result = ft_strjoin(prs->var.result, temp = ft_itoa(48532));
		free(temp);
		free(tmp);
	}
}

void	check_envvar(char *s, t_list *env, t_parse *prs)
{
	char	*tmp;

	check_envvar_edge_cases(s, prs);
	if (s[prs->var.i] == '$' && (s[prs->var.i + 1] == ' '
			|| s[prs->var.i + 1] == '\0'))
	{
		tmp = prs->var.result;
		prs->var.i++;
		prs->var.result = ft_strjoin(prs->var.result, "$");
		free(tmp);
	}
	else if (s[prs->var.i] == '$')
		get_variable(s, env, prs);
}
