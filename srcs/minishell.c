/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 20:45:48 by hlin          #+#    #+#                 */
/*   Updated: 2021/10/13 14:57:53 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		input = get_input(); //
		if (!input //or input is exit)
			quit_program(); //
		else if (is_cmd(input))
			run_cmd(input); //careful with pipe here
		clean_input(input); //
	}
	return (0);
}
