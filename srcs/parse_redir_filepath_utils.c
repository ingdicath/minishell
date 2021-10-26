/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_redir_filepath_utils.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/26 17:03:27 by hlin          #+#    #+#                 */
/*   Updated: 2021/10/26 17:16:07 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*parse_pathstr(char *s, t_list *env, t_parse *prs)
{
	int		j;
	char	*temp;
	char	*tmp;

	prs->var.result = NULL;
	temp = NULL;
	prs->var.i = 0;
	while (s[prs->var.i])
	{
		j = prs->var.i;
		while (s[prs->var.i] && s[prs->var.i] != '$')
			prs->var.i++;
		tmp = prs->var.result;
		temp = ft_substr(s, j, prs->var.i - j);
		prs->var.result = ft_strjoin(prs->var.result, temp);
		free(temp);
		free(tmp);
		check_envvar(s, env, prs);
	}
	return (prs->var.result);
}

char	*get_filepath_double_quote(char *s, t_list *env, t_parse *prs)
{
	int		j;
	char	*file;
	char	*temp;

	prs->i++;
	j = prs->i;
	while (s[prs->i] && s[prs->i] != '"')
		prs->i++;
	temp = ft_substr(s, j, prs->i - j);
	file = parse_pathstr(temp, env, prs);
	free(temp);
	prs->i++;
	return (file);
}

char	*get_filepath_single_quote(char *s, t_parse *prs)
{
	int		j;
	char	*file;

	prs->i++;
	j = prs->i;
	while (s[prs->i] && s[prs->i] != '\'')
		prs->i++;
	file = ft_substr(s, j, prs->i - j);
	prs->i++;
	return (file);
}
