/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_env.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/14 10:53:31 by dsalaman      #+#    #+#                 */
/*   Updated: 2021/10/27 17:09:24 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_key(char *str)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	temp = ft_substr(str, 0, i);
	return (temp);
}

char	*get_env_value(char *str)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (str[i] != '=' && str[i])
		i++;
	if (str[i] == '=')
		temp = ft_substr(str, i + 1, ft_strlen(str) - i);
	return (temp);
}

static t_env	*make_env_node(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = NULL;
	new->value = NULL;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	return (new);
}

t_list	*parse_env(t_list *env, char **envp)
{
	t_list	*new;
	t_env	*temp;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (envp[i])
	{
		key = get_env_key(envp[i]);
		value = get_env_value(envp[i]);
		temp = make_env_node(key, value);
		new = ft_lstnew(temp);
		ft_lstadd_back(&env, new);
		free(key);
		free(value);
		i++;
	}
	return (env);
}
