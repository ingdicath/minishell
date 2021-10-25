/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 11:00:54 by dsalaman      #+#    #+#                 */
/*   Updated: 2021/10/25 11:00:56 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

static void	child_signal(int signal)
{
	if (signal == SIGINT)
		printf("\n");
}

static void	here_signal(int signal)
{
	if (signal == SIGINT)
		exit (1);
}

// detects if there is reader??, change name of this function
static void	do_heredoc(char *delimiter)
{
	int		i;
	int		fd;
	char	*line;

	fd = open("/tmp/file1", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &here_signal);
		line = readline(">");
		i = ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1);
		if (i == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free (line);
	close (fd);
	exit (0);
}

static int	exec_heredoc(t_redir *rec)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		do_heredoc(rec->file);
	waitpid(pid, &g_exit_status, 0);
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	return (g_exit_status);
}

int	check_heredoc(t_list *cmds)
{
	t_list	*redir;
	t_redir	*redir_content;
	t_cmd	*cmd;

	signal(SIGQUIT, &child_signal);
	signal(SIGINT, &child_signal);
	while (cmds)
	{
		cmd = cmds->content;
		redir = cmd->redir;
		while (redir != NULL)
		{
			redir_content = redir->content;
			if (redir_content->type == 'H')
			{
				if (exec_heredoc(redir_content) == 1)
					return (1);
			}
			redir = redir->next;
		}
		cmds = cmds->next;
	}
	return (0);
}
