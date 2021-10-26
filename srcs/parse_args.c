/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/26 15:56:46 by hlin          #+#    #+#                 */
/*   Updated: 2021/10/26 17:57:55 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	empty_arg(t_cmd *new, char *s, t_parse *prs, int j)
{
	char	*temp;

	temp = ft_substr(s, j, prs->i - j);
	prs->arg_num++;
	if (!ft_strcmp(new->args[prs->arg_num - 1], "") && (temp[0] == '$'
			&& !ft_strchr(temp, '"') && !ft_strchr(temp, '\'')))
	{
		prs->arg_num--;
		free(new->args[prs->arg_num]);
		new->args[prs->arg_num] = NULL;
	}
	free(temp);
}

static void	get_args_quotes(t_cmd *new, char *s, t_list *env, t_parse *prs)
{
	char	*temp;
	char	*tmp;

	if (s[prs->i] == '"')
	{
		temp = get_filepath_double_quote(s, env, prs);
		tmp = new->args[prs->arg_num];
		new->args[prs->arg_num] = ft_strjoin(new->args[prs->arg_num], temp);
		free(tmp);
		free(temp);
		if (new->args[prs->arg_num] == NULL)
			new->args[prs->arg_num] = ft_strdup("");
	}
	if (s[prs->i] == '\'')
	{
		temp = get_filepath_single_quote(s, prs);
		tmp = new->args[prs->arg_num];
		new->args[prs->arg_num] = ft_strjoin(new->args[prs->arg_num], temp);
		free(tmp);
		free(temp);
	}
}

static void	add_envvar_args(t_cmd *new, t_parse *prs)
{
	int		i;

	i = 1;
	while (prs->extra_args[i])
	{
		new->args[prs->arg_num + i] = prs->extra_args[i];
		i++;
	}
	i = 1;
	while (prs->extra_args[i])
	{
		prs->arg_num++;
		i++;
	}
	free(prs->extra_args);
	prs->extra_args = NULL;
}

static void	fill_arg(char *temp, t_cmd *new, t_list *env_lst, t_parse *prs)
{
	char	*tmp;

	tmp = parse_pathstr(temp, env_lst, prs);
	free(temp);
	temp = new->args[prs->arg_num];
	new->args[prs->arg_num] = ft_strjoin(new->args[prs->arg_num], tmp);
	free(temp);
	free(tmp);
}

void	parse_args(t_cmd *new, char *s, t_list *env, t_parse *prs)
{
	char	*temp;
	int		j;

	j = prs->i;
	if (s[prs->i] != ' ' && s[prs->i] != '"' && s[prs->i] != '\'' && s[prs->i]
		&& s[prs->i] != '<' && s[prs->i] != '>')
	{
		while (s[prs->i] != ' ' && s[prs->i] != '"' && s[prs->i] != '\''
			&& s[prs->i] && s[prs->i] != '<' && s[prs->i] != '>')
			prs->i++;
		prs->outside_quote = 1;
		temp = ft_substr(s, j, prs->i - j);
		fill_arg(temp, new, env, prs);
		if (prs->extra_args)
			add_envvar_args(new, prs);
		prs->outside_quote = 0;
	}
	if (s[prs->i] == '"' || s[prs->i] == '\'')
		get_args_quotes(new, s, env, prs);
	if (!s[prs->i] || s[prs->i] == ' ' || s[prs->i] == '>' || s[prs->i] == '<')
		empty_arg(new, s, prs, j);
}
