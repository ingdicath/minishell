/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_funcs_unset.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/16 17:43:49 by hlin          #+#    #+#                 */
/*   Updated: 2021/11/16 17:44:13 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	mini_unset(t_list *envp, char *value)
{
	t_env	*env;
	t_list	*previous;

	previous = envp;
	envp = previous->next;
	while (envp != NULL)
	{
		env = envp->content;
		if (ft_strncmp(env->key, value, ft_strlen(value) + 1) == 0)
		{
			previous->next = envp->next;
			free (env->key);
			free (env->value);
			free (env);
			free (envp);
		}
		else
			previous = previous->next;
		envp = previous->next;
	}
	return (0);
}
