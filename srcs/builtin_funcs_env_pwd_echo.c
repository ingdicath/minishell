/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_funcs_env_pwd_echo.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 11:01:26 by dsalaman      #+#    #+#                 */
/*   Updated: 2021/11/16 17:45:58 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ignore_n(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i] != NULL && argv[i][0] == '-' && argv[i][1] == 'n')
	{
		j = 1;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] != 'n')
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

int	mini_env(t_list	*envp)
{
	t_env	*env;

	envp = envp->next;
	while (envp)
	{
		env = envp->content;
		if (env->value != NULL)
			printf("%s=%s\n", env->key, env->value);
		envp = envp->next;
	}
	return (0);
}

int	mini_pwd(char *get_pwd)
{
	if (get_pwd == NULL)
	{
		printf("error retrieving current directory: getcwd: cannot ");
		printf("access parent directories: No such file or directory\n");
	}
	else
		printf("%s\n", get_pwd);
	return (0);
}

int	mini_echo(char **argv)
{
	int	i;
	int	j;

	j = 0;
	if (argv[0] != NULL)
	{
		j = ignore_n(argv);
		i = j;
		while (argv[i] != NULL)
		{
			write (1, argv[i], ft_strlen(argv[i]));
			i++;
			if (argv[i] != NULL)
				write(1, " ", 1);
		}
	}
	if (j == 0)
		printf("\n");
	return (0);
}
