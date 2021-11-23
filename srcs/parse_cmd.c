/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cmd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 14:53:01 by hlin          #+#    #+#                 */
/*   Updated: 2021/10/26 17:19:21 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_envvar_arg_num(char *s)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (s[i] == ' ')
		i++;
	while (s[i])
	{
		if (s[i] == ' ')
		{
			while (s[i] == ' ')
				i++;
			ret++;
		}
		i++;
	}
	return (ret);
}

static int	count_envvar_args(char *s, int i, int j, t_list *env)
{
	char	*key;
	char	*tmp;
	int		ret;

	ret = 0;
	while (s[i])
	{
		while (s[i] && s[i] != '$')
			i++;
		if (s[i] == '$')
		{
			i++;
			j = i;
			while (s[i] && s[i] != ' ' && s[i] != '"'
				&& s[i] != '\'' && s[i] != '$')
				i++;
			key = ft_substr(s, j, i - j);
			tmp = get_envvar_arg_value(key, env);
			free(key);
			if (tmp != NULL && ft_strchr(tmp, ' '))
				ret += get_envvar_arg_num(tmp);
			free(tmp);
		}
	}
	return (ret);
}

static void	init_prs_struct(t_parse *prs)
{
	prs->i = 0;
	prs->arg_num = 0;
	prs->ambiguous = 0;
	prs->ret_value = g_exit_status;
	prs->outside_quote = 0;
	prs->extra_args = NULL;
}

static void	init_cmd_struct(t_cmd *new, char *s, t_list *env)
{
	int	arg_num;
	int	i;

	new->cmd = NULL;
	new->args = NULL;
	new->redir = NULL;
	arg_num = get_size(s);
	if (ft_strchr(s, '$'))
		arg_num += count_envvar_args(s, 0, 0, env);
	new->args = malloc(sizeof(char *) * (arg_num + 1));
	i = 0;
	while (i <= arg_num)
		new->args[i++] = NULL;
}

t_cmd	*get_cmd_node(char *s, t_list *env)
{
	t_parse	prs;
	t_cmd	*new;
	int		i;

	init_prs_struct(&prs);
	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	init_cmd_struct(new, s, env);
	parse_cmd(new, s, env, &prs);
	new->cmd = new->args[0];
	i = get_size(s);
	i += count_envvar_args(s, 0, 0, env);
	while (i >= prs.arg_num)
	{
		free(new->args[i]);
		new->args[i] = NULL;
		i--;
	}
	if (prs.ambiguous == 1)
		new->cmd = NULL;
	return (new);
}
