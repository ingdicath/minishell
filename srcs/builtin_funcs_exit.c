/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_funcs_exit.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/10 16:36:00 by hlin          #+#    #+#                 */
/*   Updated: 2021/11/22 10:25:32 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	exit_not_number(char *arg)
{
	printf("exit\nminishell: exit: %s: ", arg);
	printf("numeric argument required\n");
	exit (255);
}

static char	*trim_space(char *str)
{
	int	start;
	int	end;

	start = 0;
	end = ft_strlen(str) - 1;
	while (str[start] && str[start] == ' ')
		start++;
	while (str[end] && str[end] == ' ')
		end--;
	return (ft_substr(str, start, end - start + 1));
}

static void	print_tmargs_err(char *str)
{
	free(str);
	ft_putendl_fd("exit", 1);
	ft_putendl_fd("minishell: exit: too many arguments", 2);
}

void	mini_exit(char **args)
{
	int		i;
	char	*str;

	if (args[1] == NULL)
	{
		printf("exit\n");
		exit(g_exit_status);
	}
	str = trim_space(args[1]);
	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			exit_not_number(args[1]);
		i++;
	}
	if (args[2] == NULL)
	{
		i = ft_atoi(args[1]);
		printf("exit\n");
		exit (i);
	}
	print_tmargs_err(str);
}
