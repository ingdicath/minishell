/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/14 11:48:27 by dsalaman      #+#    #+#                 */
/*   Updated: 2021/10/21 11:32:22 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/exec.h"

/*
	rl_on_new_line() -> regenerate the prompt on a newline.
	rl_replace_line("", 1) ->  the undo list associated with the current line
	is cleared.
	rl_redisplay() -> Redisplays the prompt.
*/
void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_exit_status = 1;
	}
}
