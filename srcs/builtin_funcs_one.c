/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_funcs_one.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 11:01:26 by dsalaman      #+#    #+#                 */
/*   Updated: 2021/10/27 17:20:29 by hlin          ########   odam.nl         */
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

void	mini_exit(char **args)
{
	int	i;
	int	j;

	if (args[1] == NULL)
		exit(g_exit_status);
	if (args[2] == NULL)
	{
		i = ft_atoi(args[1]);
		j = 0;
		if (args[1][0] == '-')
			j = 1;
		while (args[1][j] != '\0')
		{
			if (!ft_isdigit(args[1][j]))
			{
				printf("minishell: exit: %s: ", args[1]);
				printf("numeric argument required\n");
				exit (255); /* Exit status out of range */
			}
			j++;
		}
		exit (i);
	}
	printf("minishell: exit: too many arguments\n");
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
				printf(" ");
		}
	}
	if (j == 0)
		printf("\n");
	return (0);
}
