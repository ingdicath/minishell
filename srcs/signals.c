/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/14 11:48:27 by dsalaman      #+#    #+#                 */
/*   Updated: 2021/10/14 14:40:02 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//SIGINT
void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n"); //Move to a new line
		rl_on_new_line(); //regenerate the prompt on a newline
		rl_replace_line("", 0); //Clear the previous text
		rl_redisplay(); // Redisplays the prompt
	}
	else if (signal == SIGQUIT)
	{
		// if prompt is empty, 'Ctrl + D' must print "exit"
		printf("exit\n");
		// exit(0);
	}
}
