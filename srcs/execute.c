/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 11:00:47 by dsalaman      #+#    #+#                 */
/*   Updated: 2021/10/25 11:00:49 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	wait_cmds(int num_cmds)
{
	int	i;

	i = 0;
	while (i < num_cmds)
	{
		wait(NULL);
		i++;
	}
}

void	close_pipes_fds(int *pipes_fds, int num)
{
	int	i;

	i = 0;
	while (i < (2 * num))
	{
		close(pipes_fds[i]);
		i++;
	}
}

void	set_exit_status(int num_cmds)
{
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	else if (WIFSIGNALED(g_exit_status))
	{
		if (WTERMSIG(g_exit_status) == SIGQUIT)
			printf("Quit: 3\n");
		g_exit_status = 128 + WTERMSIG(g_exit_status); //128+n - Fatal error signal “n”
	}
	wait_cmds(num_cmds);
}

/* heredoc stands for "do_heredoc document", is a type of redirection that allows
* you to pass multiple lines of input to a command */

int	exec_cmd(t_list *cmds, t_list *envp)
{
	int	num_cmds;
	int	*pipes_fds;
	int	pid;

	pipes_fds = NULL;
	num_cmds = ft_lstsize(cmds);
	if (check_heredoc(cmds))
		return (1);
	if (num_cmds > 0)
	{
		pid = is_builtin(cmds->content);
		if (num_cmds == 1 && pid != 0)
			run_builtin(cmds->content, envp, pid);
		else
		{
			if (num_cmds > 1)
				pipes_fds = create_pipes(num_cmds - 1);
			pid = create_childs(cmds, pipes_fds, envp);
			if (num_cmds > 1)
				close_pipes_fds(pipes_fds, num_cmds - 1);
			waitpid(pid, &g_exit_status, 0);
			set_exit_status(num_cmds);
		}
	}
	return (0);
}
