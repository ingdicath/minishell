/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_funcs_export.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 11:01:36 by dsalaman      #+#    #+#                 */
/*   Updated: 2021/11/21 23:05:04 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	valid_id_error_msg(int status, char *id)
{
	if (status == EXPORT)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(id, 2);
		ft_putendl_fd("': not a valid identifier", 2);
	}
	else
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(id, 2);
		ft_putendl_fd("': not a valid identifier", 2);
	}
	g_exit_status = 1;
}

static int	valid_export(char *key, char *arg)
{
	if (!valid_envnam(key, arg, EXPORT))
	{
		free(key);
		return (0);
	}
	return (1);
}

int	valid_envnam(char *value, char *arg, int status)
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

void	check_if_export(const t_cmd *cmd, t_list *envp)
{
	int		i;
	char	*key;

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

int	mini_export(t_list *envp, char *key, char *arg)
{
	char	*value;
	t_env	*env;
	t_list	*temp;

	if (!valid_export(key, arg))
		return (1);
	value = get_env_value(arg);
	if (!ft_strcmp(key, "_"))
		return (free_key_value(key, value));
	while (envp != NULL)
	{
		env = envp->content;
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0 && value != NULL)
		{
			free (env->value);
			env->value = value;
		}
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
			return (free_key_value(key, NULL));
		temp = envp;
		envp = envp->next;
	}
	env = make_env_node(key, value);
	temp->next = ft_lstnew(env);
	return (free_key_value(key, value));
}
