/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reset_nodes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 13:12:58 by dsalaman      #+#    #+#                 */
/*   Updated: 2021/10/25 13:13:02 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	reset_env_node(t_env *new)
{
	new->key = NULL;
	new->value = NULL;
}
