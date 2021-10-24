//
// Created by Diani on 24/10/2021.
//

#include "../includes/exec.h"

int	is_valid_env_name(char *value)
{
	int	i;

	i = 0;
	if (!ft_isalpha(value[0]) && value[0] != '_')
	{
		printf("minishell: '%s': not a valid identifier\n", value);  // factorizar
		g_exit_status = 1;
		return (0);
	}
	while (value[i] != 0)
	{
		if (value[i] != '_' && !ft_isalnum(value[i]))
		{
			printf("minishell: '%s': not a valid identifier\n", value);
			g_exit_status = 1;
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
	while (envp !=  NULL)
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
	char	*val;
	t_env	*env;
	t_list	*temp;

	if (!is_valid_env_name(key))
		return (1);
	val = get_value(arg);
	while (envp != NULL)
	{
		env = envp->content;
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0 && val != NULL)
		{
			free (env->value);
			env->value = val;
		}
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
			return (0);
		temp = envp;
		envp = envp->next;
	}
}

int	check_export_unset(t_cmd *cmd, t_list *envp, int status)
{
	int		i;
	char	*key;

	if (status == UNSET)
	{
		i = 1;
		while (cmd->args[i] != NULL && is_valid_env_name(cmd->args[i]))
		{
			g_exit_status = mini_unset(envp, cmd->args[i]);
			i++;
		}
	}
	else if (status == EXPORT)
	{
		if (cmd->args[1] == NULL)
			g_exit_status = display_envp(envp); //define
			i = 1;
			while (cmd->args[i] != NULL)
			{
				key = get_key(cmd->args[i]);
				g_exit_status = mini_export(envp, key, cmd->args[i]);
				i++;
			}
	}
	return (0);
}

