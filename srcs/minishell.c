/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 20:45:48 by hlin          #+#    #+#                 */
/*   Updated: 2021/10/14 11:28:55 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_input(void)
{
	char	*input;

	//input = NULL;
	input = readline("minishell-> ");
	if (input)
		add_history(input);
	return (input);
}

int	main(int argc, char **argv, char **envp)
{
	char	**env;
	char	*input;

	if (argc != 1)
	{
		perror("Usage: ./minishell");
		return (0);
	}
	env = parse_env(envp); //
	signal(SIGINT, handle_signal); //
	signal(SIGQUIT, handle_signal); //
	while (1)
	{
		input = get_input();
		if (!input)
		{
			write(1, "\b\b\b\b\b\b\b\b\b\b\b\b\b\b", 14);
			write(1, "minishell-> ", 12);
		}
		else
			parse_input(input);
		clean_str(input);
	}
	return (0);
}

