/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_get_path.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 11:38:49 by dsalaman      #+#    #+#                 */
/*   Updated: 2021/11/10 14:11:57 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_envp(t_list *envp, char *key)
{
	t_env	*env;

	while (envp != NULL)
	{
		env = envp->content;
		if (ft_strcmp(key, env->key) == 0)
			return (env->value);
		envp = envp->next;
	}
	return (NULL);
}

static char	*check_local_cmd(char *str, char *cmd)
{
	int	j;

	j = open(str, O_RDONLY);
	if (j != -1 && j != 13)
		return (str);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd + 1, 2);
	ft_putendl_fd(": command not found", 2);
	return (NULL);
}

char	**get_paths(t_list *envp)
{
	char	**paths;
	char	*path;

	path = get_envp(envp, "PATH");
	if (path != NULL)
	{
		paths = ft_split(path, ':');
		return (paths);
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **paths)
{
	int		i;
	int		j;
	char	*str1;
	char	*str2;

	str2 = cmd;
	if (cmd[0] == '.' || cmd[0] == '/')
		return (cmd);
	if (cmd[0] != '\0' && paths != NULL)
	{
		cmd = ft_strjoin("/", cmd);
		i = 0;
		while (paths[i] != NULL)
		{
			str1 = ft_strjoin(paths[i], cmd);
			j = open(str1, O_RDONLY);
			if (j != -1 && j != 13) /* check better way to call this numbers */
				return (str1);
			free (str1);
			i++;
		}
	}
	return (check_local_cmd(str2, cmd));
}
