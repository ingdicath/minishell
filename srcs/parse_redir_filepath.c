/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_redir_filepath.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/26 16:07:04 by hlin          #+#    #+#                 */
/*   Updated: 2021/10/26 17:58:45 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	join_filepath(t_redir *redir, char *s, t_list *env, t_parse *prs)
{
	char	*temp;
	char	*tmp;
	int		j;

	j = prs->i;
	if (s[prs->i] && s[prs->i] != '"' && s[prs->i] != '\''
		&& s[prs->i] != '>' && s[prs->i] != '<')
	{
		while (s[prs->i] && s[prs->i] != ' ' && s[prs->i] != '<'
			&& s[prs->i] != '>' && s[prs->i] != '"' && s[prs->i] != '\'')
			prs->i++;
		temp = ft_substr(s, j, prs->i - j);
		tmp = parse_pathstr(temp, env, prs);
		free(temp);
		temp = redir->file;
		redir->file = ft_strjoin(redir->file, tmp);
		free(tmp);
		free(temp);
	}
}

static void	get_filepath_quote(t_redir *redir, char *s,
	t_list *env, t_parse *prs)
{
	char	*temp;
	char	*tmp;

	if (s[prs->i] == '"')
	{
		temp = get_filepath_double_quote(s, env, prs);
		tmp = redir->file;
		redir->file = ft_strjoin(redir->file, temp);
		free(temp);
		free(tmp);
		if (redir->file == NULL)
			redir->file = ft_strdup("");
	}
	if (s[prs->i] == '\'')
	{
		temp = get_filepath_single_quote(s, prs);
		tmp = redir->file;
		redir->file = ft_strjoin(redir->file, temp);
		free(temp);
		free(tmp);
	}
}

void	get_redir_filepath(t_redir *redir, char *s, t_list *env, t_parse *prs)
{
	while (s[prs->i] == ' ')
		prs->i++;
	if (s[prs->i] == '$')
		if (check_ambiguous_redir(s, env, prs) == -1)
			prs->ambiguous = 1;
	while (s[prs->i])
	{
		join_filepath(redir, s, env, prs);
		get_filepath_quote(redir, s, env, prs);
		if (!s[prs->i] || s[prs->i] == ' ' || s[prs->i] == '>'
			|| s[prs->i] == '<')
			break ;
	}
	while (s[prs->i] == ' ')
		prs->i++;
}
