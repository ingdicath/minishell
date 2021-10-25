/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prepare_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 11:01:50 by dsalaman      #+#    #+#                 */
/*   Updated: 2021/10/25 11:01:52 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

static int	sort_envp(char **tab, int size)
{
	int		length;
	int		current;
	int		limit;
	char	*pivot;

	if (size < 2)
		return (0);
	limit = 0;
	current = 0;
	pivot = tab[size - 1];
	length = ft_strlen(pivot);
	while (current < size)
	{
		if (ft_strncmp(tab[current], pivot, length) <= 0)
		{
			if (current != limit)
				ft_swap(&tab[current], &tab[limit]);
			limit++;
		}
		current++;
	}
	sort_envp(tab, limit - 1);
	sort_envp(tab + limit - 1, size - limit + 1);
	return (0);
}

int	show_envp(t_list *envp)
{
	int		i;
	int		j;
	char	**tab;

	envp = envp->next;
	tab = convert_list_to_array(envp);
	sort_envp(tab, ft_lstsize(envp) + 1);
	i = 0;
	while (tab[i] != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		j = 0;
		while (tab[i][j] != '=' && tab[i][j] != '\0')
		{
			write (1, &tab[i][j], 1); //check this, could be better printf
			j++;
		}
		if (tab[i][j] != '\0')
			printf("=\"%s\"\n", &tab[i][j + 1]);
		else
			printf("\n");
		i++;
	}
	return (0);
}

char	**convert_list_to_array(t_list *list)
{
	int		i;
	int		size;
	char	**tab;
	t_env	*env;

	size = ft_lstsize(list) + 1;
	tab = malloc(size * sizeof(char *));
	i = 0;
	while (i < size - 1)
	{
		env = list->content;
		tab[i] = join_env(env);
		list = list->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	*join_env(t_env *env)
{
	char	*tab;
	char	*temp;

	if (env->value != NULL)
	{
		temp = ft_strjoin(env->key, "=");
		tab = ft_strjoin(temp, env->value);
		free (temp);
		return (tab);
	}
	return (env->key);
}

t_env	*make_env_node(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	reset_env_node(new);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	return (new);
}
