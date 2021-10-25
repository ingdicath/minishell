/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cmd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 14:53:01 by hlin          #+#    #+#                 */
/*   Updated: 2021/10/25 17:52:50 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_prs_struct(t_parse *prs)
{
	prs->i = 0;
	prs->arg_num = 0;
	prs->ambigous = 0;
	prs->ret_value = g_exit_status;
	prs->outside_quote = 0;
	prs->extra_args = NULL;
}

static void	init_cmd_struct(t_cmd *new, char *s, t_list *env)
{
	int		i;

	i = 0;
	new->cmd = NULL;
	new->args = NULL;
	new->redir = NULL;
	allocate_args(s, new, env);//
}

t_cmd	*get_new_node(char *s, t_list *env)
{
	t_parse	prs;
	t_cmd	*new;
	int		i;

	init_prs_struct(&prs);
	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	init_cmd_struct(new, s, env);
	parse_simple_cmd(new, s, env, &prs); //
	new->cmd = new->args[0];
	i = get_size(s);
	i += count_extra_args(s, 0, 0, env);
	while (i >= prs.arg_num);
	{
		free(new->args[i]);
		new->args[i] = NULL;
		i--;
	}
	if (prs.ambigous == 1)
		new->cmd = NULL;
	return (new);
}