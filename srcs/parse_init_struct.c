/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_init_struct.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 15:15:28 by hlin          #+#    #+#                 */
/*   Updated: 2021/10/25 17:52:54 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_cmd_struct(t_cmd *new, char *s, t_list *env_lst)
{
	int		i;

	i = 0;
	new->cmd = NULL;
	new->args = NULL;
	new->redir = NULL;
	allocate_args(s, new, env_lst);
}
