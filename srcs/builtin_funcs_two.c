/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_funcs_two.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 11:01:36 by dsalaman      #+#    #+#                 */
/*   Updated: 2021/11/15 14:36:17 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	valid_id_error_msg(int status, char *id)
{
	if (status == EXPORT)
		printf("minishell: export: `%s': not a valid identifier\n", id);
	else
		printf("minishell: unset: `%s': not a valid identifier\n", id);
	g_exit_status = 1;
}

static int	valid_envnam(char *value, char *arg, int status)
{
	int	i;

	i = 0;
	if (!ft_strcmp(value, "") && arg != NULL)
	{
		valid_id_error_msg(status, arg);
		return (0);
	}
	if (!ft_isalpha(value[0]) && value[0] != '_')
	{
		valid_id_error_msg(status, value);
		return (0);
	}
	while (value[i] != 0)
	{
		if (value[i] != '_' && !ft_isalnum(value[i]))
		{
			valid_id_error_msg(status, value);
			return (0);
		}
		i++;
	}
	return (1);
}

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

int	mini_export(t_list *envp, char *key, char *arg)
{
	char	*value;
	t_env	*env;
	t_list	*temp;

	if (!valid_envnam(key, arg, EXPORT))
		return (1);
	value = get_env_value(arg);
	while (envp != NULL)
	{
		env = envp->content;
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0 && value != NULL)
		{
			free (env->value);
			env->value = value;
		}
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
			return (0);
		temp = envp;
		envp = envp->next;
	}
	env = make_env_node(key, value);
	temp->next = ft_lstnew(env);
	free (key);
	free (value);
	return (0);
}

int	check_export_unset(t_cmd *cmd, t_list *envp, int status)
{
	int		i;
	char	*key;

	if (status == UNSET)
	{
		i = 1;
		while (cmd->args[i] != NULL && valid_envnam(cmd->args[i], NULL, UNSET))
		{
			g_exit_status = mini_unset(envp, cmd->args[i]);
			i++;
		}
	}
	else if (status == EXPORT)
	{
		if (cmd->args[1] == NULL)
			g_exit_status = show_envp(envp);
		i = 1;
		while (cmd->args[i] != NULL)
		{
			key = get_env_key(cmd->args[i]);
			g_exit_status = mini_export(envp, key, cmd->args[i]);
			i++;
		}
	}
	return (0);
}
