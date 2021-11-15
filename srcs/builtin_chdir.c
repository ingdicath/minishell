/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_chdir.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 11:01:17 by dsalaman      #+#    #+#                 */
/*   Updated: 2021/11/15 14:54:59 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	chdir_error(int index, char *dir)
{
	printf("index: %d\n", index);
	if (index == 0)
		printf("minishell: cd: HOME not set\n");
	else if (index == 1)
		printf("minishell: cd: OLDPWD not set\n");
	else if (index == 2)
		printf("minishell: cd: too many arguments\n");
	else if (index == 3)
		printf("minishell: cd: %s %s\n", dir, strerror(errno));
	else
	{
		printf("cd: error retrieving current directory: getcwd: ");
		printf("cannot access parent directories: ");
		printf("No such file or directory\n");
	}
	return (1);
}

static void	swap_directory(t_list *envp, char **get_pwd)
{
	char	**pwd;
	char	**old_pwd;
	t_env	*env;

	while (envp != NULL)
	{
		env = envp->content;
		if (ft_strncmp(env->key, "PWD", 4) == 0)
			pwd = &env->value;
		else if (ft_strncmp(env->key, "OLDPWD", 7) == 0)
			old_pwd = &env->value;
		envp = envp->next;
	}
	free (*old_pwd);
	*old_pwd = *pwd;
	*pwd = ft_strjoin(*get_pwd, "");
}

static void	change_directory(char *str, char *dir, char **get_pwd, t_list *envp)
{
	char	*temp;

	if (str == NULL)
	{
		chdir_error(3, NULL);
		if (*get_pwd == NULL)
			*get_pwd = ft_strjoin("", dir);
		else
		{
			temp = ft_strjoin("/", dir);
			*get_pwd = ft_strjoin(*get_pwd, temp);
			free (temp);
		}
	}
	else
	{
		free (*get_pwd);
		*get_pwd = str;
	}
	swap_directory(envp, get_pwd);
}

static char	*get_directory(char *dir, t_list *envp)
{
	t_env	*env;
	char	*new_dir;

	new_dir = NULL;
	if (dir != NULL && ft_strcmp(dir, "~") && ft_strcmp(dir, "-"))
		return (dir);
	while (envp != NULL)
	{
		env = envp->content;
		if (!ft_strcmp(dir, "-"))
		{
			if (ft_strncmp(env->key, "OLDPWD", 7) == 0)
				new_dir = env->value;
		}
		else
		{
			if (ft_strncmp(env->key, "HOME", 5) == 0)
				new_dir = env->value;
		}
		envp = envp->next;
	}
	return (new_dir);
}

int	mini_chdir(t_cmd *cmd, t_list *envp, char **path)
{
	int		i;
	char	*str;
	char	*dir;

	dir = get_directory(cmd->args[1], envp);
	if (dir == NULL && (!ft_strcmp(cmd->args[1], "~") || cmd->args[1] == NULL))
		return (chdir_error(0, NULL));
	if (dir == NULL && !ft_strcmp(cmd->args[1], "-"))
		return (chdir_error(1, NULL));
	if (cmd->args[1] != NULL && cmd->args[2] != NULL)
		return (chdir_error(2, NULL));
	if (!strcmp(dir, ""))
		return (0);
	i = chdir(dir);
	if (i == -1)
		return (chdir_error(3, cmd->args[1]));
	str = getcwd(NULL, 0);
	change_directory(str, dir, path, envp);
	if (!ft_strcmp(cmd->args[1], "-"))
		printf("%s\n", dir);
	return (0);
}
