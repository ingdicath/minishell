#include "../includes/exec.h"

void	execute_cmd(t_list *cmds, int *pfds, t_list *envp, int i)
{
	int	num_pipes;
	char	*cmd_path;
	char	**tab;
	t_cmd	*cmd;

	cmd_path = NULL;
	tab = list_to_array(envp); //define
	num_pipes = ft_lstsize(cmds) + (i / 2) - 1; //check this
	if (cmds->next)
		ft_dup2(pfds[i + 1], 1);
	if (i != 0)
		ft_dup2(pfds[i - 2], 0);  //check this
		close_pfds(pfds, num_pipes);
		cmd = cmds->content;
		if (mini_redirect(cmd->redir))
			exit (1);
		if (execute_builtin(cmd, envp, is_builtin(cmd))) //define
			exit(g_exit_status);
		cmd_path = get_cmd_path(cmd->cmd, get_paths(envp)); //define
		ft_execve(cmd_path, cmd->args, tab); //define
}

int	create_childs(t_list *cmds, int *pfds, t_list *envp)
{
	int	i;
	int pid;

	i = 0;
	while (cmds)
	{
		pid = fork();
		if (pid == 0)
			execute_cmd(cmds, pfds, envp, i); //define
		cmds = cmds->next;
		i += 2; //check this condition
	}
	return (pid);
}

int	*create_pipes(int num_pipes)
{
	int	*pfds; //check this name, pipe_fds??
	int	i;
	int	j;

	pfds = malloc(2 * num_pipes * sizeof (int));
	if (!pfds)
	{
		perror("Error creating pipes\n");
		exit(0);
	}
	i = 0;
	while (i < num_pipes)
	{
		j = pipe(pfds + (2 * i));
		if (j < 0)
		{
			perror("pipe: ");
			exit(0);
		}
		i++;
	}
	return (pfds);
}

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

void	close_pfds(int *pfds, int num)
{
	int	i;

	i = 0;
	while (i < (2 * num)) //check what '2' stands for
	{
		close(pfds[i]);
		i++;
	}
}

int	set_exit_status(int num_cmds)
{
	if (WIFCONTINUED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	else if (WIFSIGNALED(g_exit_status))
	{
		if (WTERMSIG(g_exit_status) == SIGQUIT)
			printf("Quit: 3\n");
		g_exit_status = 128 + WTERMSIG(g_exit_status); //128+n - Fatal error signal “n”
	}
	wait_cmds(num_cmds);
}

/* heredoc stands for "here document", is a type of redirection that allows
* you to pass multiple lines of input to a command */

int	exec_cmd(t_list *cmds, t_list *envp)
{
	int num_cmds;
	int	*pfds;  //num file descriptors?? pointer to fd??
	int	pid;

	pfds = NULL;
	num_cmds = ft_lstsize(cmds);
	if (check_heredoc(cmds))
		return (1);
	if (num_cmds > 0)
	{
		pid = is_builtin(cmds->content);
		if (num_cmds == 1 && pid != 0)
			builtin(cmds->content, envp, pid);
		else
		{
			if (num_cmds > 1)
				pfds = create_pipes(num_cmds - 1);
			pid = create_childs(cmds, pfds, envp);
			if (num_cmds > 1)
				close_pfds(pfds, num_cmds - 1);
			waitpid(pid, &g_exit_status, 0);
			set_exit_status(num_cmds);
		}
	}
	return (0);
}