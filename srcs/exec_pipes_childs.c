/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_pipes_childs.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 13:28:29 by dsalaman      #+#    #+#                 */
/*   Updated: 2021/10/27 17:20:57 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_childs(t_list *cmds, int *pipes_fds, t_list *envp, int i)
{
	int		num_pipes;
	char	*cmd_path;
	char	**tab;
	t_cmd	*cmd;

	cmd_path = NULL;
	tab = convert_list_to_array(envp);
	num_pipes = ft_lstsize(cmds) + (i / 2) - 1;
	if (cmds->next)
		ft_dup2(pipes_fds[i + 1], 1);
	if (i != 0)
		ft_dup2(pipes_fds[i - 2], 0);
	close_pipes_fds(pipes_fds, num_pipes);
	cmd = cmds->content;
	if (mini_redirect(cmd->redir))
		exit (1);
	if (execute_builtin(cmd, envp, is_builtin(cmd)))
		exit(g_exit_status);
	cmd_path = get_cmd_path(cmd->cmd, get_paths(envp));
	ft_execve(cmd_path, cmd->args, tab);
}

/* 2 stands for number of pipes */

int	create_childs(t_list *cmds, int *pipes_fds, t_list *envp)
{
	int	i;
	int	pid;

	i = 0;
	while (cmds)
	{
		pid = fork();
		if (pid == 0)
			exec_childs(cmds, pipes_fds, envp, i);
		cmds = cmds->next;
		i += 2;
	}
	return (pid);
}

int	*create_pipes(int num_pipes)
{
	int	*pipes_fds;
	int	i;
	int	j;

	pipes_fds = malloc(2 * num_pipes * sizeof (int));
	if (!pipes_fds)
	{
		perror("Error creating pipes\n");
		exit(0);
	}
	i = 0;
	while (i < num_pipes)
	{
		j = pipe(pipes_fds + (2 * i));
		if (j < 0)
		{
			perror("pipe: ");
			exit(0);
		}
		i++;
	}
	return (pipes_fds);
}
