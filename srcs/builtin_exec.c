/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_exec.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 11:00:35 by dsalaman      #+#    #+#                 */
/*   Updated: 2021/11/15 11:30:55 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (cmd->cmd == NULL)
		return (NONE);
	else if (ft_strcasecmp(cmd->cmd, "cd") == 0)
		return (CD);
	else if (ft_strcasecmp(cmd->cmd, "pwd") == 0)
		return (PWD);
	else if (ft_strcasecmp(cmd->cmd, "echo") == 0)
		return (ECHO_);
	else if (ft_strcasecmp(cmd->cmd, "env") == 0)
		return (ENV);
	else if (ft_strcasecmp(cmd->cmd, "exit") == 0)
		return (EXIT);
	else if (ft_strcasecmp(cmd->cmd, "unset") == 0)
		return (UNSET);
	else if (ft_strcasecmp(cmd->cmd, "export") == 0)
		return (EXPORT);
	return (0);
}

int	execute_builtin(t_cmd *cmd, t_list *envp, int status)
{
	char	*pwd_path;

	pwd_path = getcwd(NULL, 0);
	if (status == CD)
		g_exit_status = mini_chdir(cmd, envp, &pwd_path);
	else if (status == PWD)
		g_exit_status = mini_pwd(pwd_path);
	else if (status == ECHO_)
		g_exit_status = mini_echo(cmd->args + 1);
	else if (status == ENV)
		g_exit_status = mini_env(envp);
	else if (status == EXIT)
		mini_exit(cmd->args);
	else if (status == UNSET || status == EXPORT)
		check_export_unset(cmd, envp, status);
	else
	{
		free (pwd_path);
		return (0);
	}
	free (pwd_path);
	return (1);
}

int	run_builtin(t_cmd *cmd, t_list *envp, int status)
{
	int	input;
	int	output;
	int	i;

	i = 0;
	if (cmd->redir != NULL)
	{
		input = dup(0);
		output = dup(1);
		i = mini_redirect(cmd->redir);
	}
	if (i == 0)
		execute_builtin(cmd, envp, status);
	if (cmd->redir != NULL)
	{
		ft_dup2 (input, 1);
		ft_dup2 (output, 0);
		close (input);
		close (output);
	}
	return (0);
}
