/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/14 11:15:49 by hlin          #+#    #+#                 */
/*   Updated: 2021/10/14 12:27:17 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env_list(t_list *env)
{
	t_env	*temp;

	while (env != NULL)
	{
		temp = env->content;
		free(temp->key);
		free(temp->value);
		free(env->content);
		free(env);
		env = env->next;
	}
}
