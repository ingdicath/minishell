#include "../includes/exec.h"

static void	child_signal(int signal)
{
	if (signal == SIGINT)
		printf("\n");
}

static void	here_signal(int_signal)
{
	if (signal == SIGINT)
		exit (1);
}

// detects if there is reader??, change name of this function
static void	here(char *delimiter)
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
	int pid;

	pid = fork();
	if (pid == 0)
		here(rec->file); //change name of this function
	waitpid(pid, &g_exit_status, 0);
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	return (g_exit_status);
}

int	check_heredoc(t_list *cmds)
{
	t_cmd   *cmd;
	t_list  *red; //change names
	t_redir *rec; //change names

	signal(SIGQUIT, &child_signal);
	signal(SIGINT, &child_signal);
	while (cmds)
	{
		cmd = cmds->content;
		red = cmd->redir;
		while (red != NULL)
		{
			rec = red->content;
			if (rec->type == 'H')
			{
				if (exec_heredoc(rec) == 1)
					return (1);
			}
			red = red->next;
		}
		cmds =  cmds->next;
	}
	return (0);
}