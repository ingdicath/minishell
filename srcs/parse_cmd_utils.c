/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cmd_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 15:41:11 by hlin          #+#    #+#                 */
/*   Updated: 2021/10/26 17:34:54 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	skip_space_redir(char *s, int i)
{
	while (s[i] == ' ')
		i++;
	while (s[i] == '>' || s[i] == '<')
	{
		i++;
		while (s[i] == ' ')
			i++;
		while (s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>')
			i++;
	}
	return (i);
}

int	get_size(char *s)
{
	int		i;
	int		quote;
	int		ret;

	ret = 0;
	quote = 0;
	i = 0;
	while (s[i])
	{
		i = skip_space_redir(s, i);
		if (s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>')
		{
			while ((s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>')
				|| (s[i] == ' ' && quote)
				|| ((s[i] == '>' || s[i] == '<') && quote))
			{
				quote = check_quote(s[i], quote);
				i++;
			}			
			ret++;
		}
	}
	return (ret);
}

void	parse_cmd(t_cmd *new, char *s, t_list *env, t_parse *prs)
{
	while (s[prs->i])
	{
		while (s[prs->i] == ' ')
			prs->i++;
		if (s[prs->i] == '<' || s[prs->i] == '>')
			new->redir = parse_redir(new->redir, s, env, prs);
		while (s[prs->i] && s[prs->i] != ' '
			&& s[prs->i] != '>' && s[prs->i] != '<')
			parse_args(new, s, env, prs);
	}
}
