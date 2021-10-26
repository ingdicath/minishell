/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_redir.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/26 15:58:14 by hlin          #+#    #+#                 */
/*   Updated: 2021/10/26 16:08:12 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	get_redir_type(char c, char next_c)
{
	if (c == '>' && next_c != '>')
		return ('O');
	else if (c == '<' && next_c != '<')
		return ('I');
	else if (c == '>' && next_c == '>')
		return ('A');
	else if (c == '<' && next_c == '<')
		return ('H');
	return (0);
}

static t_redir	*get_redir_node(char *s, t_list *env, t_parse *prs)
{
	t_redir	*new;

	new = (t_redir *)malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->file = NULL;
	new->type = '\0';
	while (s[prs->i] == ' ')
		prs->i++;
	new->type = get_redir_type(s[prs->i], s[prs->i + 1]);
	if (new->type == 'O' || new->type == 'I')
	{
		prs->i++;
		get_redir_filepath(new, s, env, prs);
	}
	else
	{
		prs->i += 2;
		get_redir_filepath(new, s, env, prs);
	}
	return (new);
}

t_list	*parse_redir(t_list *redir, char *s, t_list *env, t_parse *prs)
{
	t_list		*new;
	t_redir		*temp;

	while (s[prs->i])
	{
		if (s[prs->i] && s[prs->i] != '>' && s[prs->i] != '<')
			break ;
		temp = get_redir_node(s, env, prs);
		new = ft_lstnew(temp);
		ft_lstadd_back(&redir, new);
	}
	return (redir);
}
