/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 20:45:48 by hlin          #+#    #+#                 */
/*   Updated: 2021/10/14 13:45:02 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_input(char *input, t_list *env)
{
	char	*input;

	input = readline("minishell-> ");
	if (input == NULL)
	{
		ft_putchar_fd("exit\n", 1);
		free_env_list(env);
		exit(g_exit_status);
	}
	if (ft_strcmp(input, ""))
		add_history(input);
	return (input);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_list	*env;
	t_list	*cmds;
	t_list	*temp;

	if (argc != 1)
	{
		perror("Usage: ./minishell");
		return (1);
	}
	input = NULL;
	env = parse_env(envp); //
	signal(SIGINT, handle_signal); //
	signal(SIGQUIT, handle_signal); //
	while (1)
	{
		cmds = NULL;
		input = get_input(input, env);
		temp = env;
		if (input != NULL && !syntax_validation(input))//
		{
			cmds = split_by_pipes(cmds, input, temp);//
			exec_cmd(cmds, env);//
		}
		free(input);
		free_cmds(cmds);//
	}
	free_env_list(env);
	return (0);
}

