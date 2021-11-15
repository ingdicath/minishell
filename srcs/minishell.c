/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 20:45:48 by hlin          #+#    #+#                 */
/*   Updated: 2021/11/15 10:26:55 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_redirection(t_list *redirection)
{
	t_list	*redir_temp;
	t_redir	*temp;

	while (redirection != NULL)
	{
		redir_temp = redirection;
		temp = redirection->content;
		if (temp->file)
			free(temp->file);
		free(temp);
		redirection = redirection->next;
		free(redir_temp);
	}
}

static void	free_cmds(t_list *cmd)
{
	t_list		*list_temp;
	t_cmd		*temp;
	int			i;

	while (cmd != NULL)
	{
		list_temp = cmd;
		temp = cmd->content;
		if (temp->args)
		{
			i = 0;
			while (temp->args[i])
			{
				free(temp->args[i]);
				i++;
			}
			free(temp->args);
		}
		if (temp->redir)
			free_redirection(temp->redir);
		free(temp);
		cmd = cmd->next;
		free(list_temp);
	}
}

static char	*get_input(char *input, t_list *env)
{
	input = readline("minishell-> ");
	if (input == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		free_env_list(env);
		exit(g_exit_status);
	}
	if (ft_strcmp(input, ""))
		add_history(input);
	return (input);
}

void	exec_minishell(char *input, t_list *env)
{
	t_list	*cmds;
	t_list	*temp;

	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &handle_signal);
		cmds = NULL;
		input = get_input(input, env);
		temp = env;
		if (input != NULL && !syntax_validation(input))
		{
			cmds = parse_input(cmds, input, temp);
			exec_cmd(cmds, env);
		}
		free(input);
		free_cmds(cmds);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_list	*env;

	(void)argv;
	if (argc != 1)
	{
		perror("Usage: ./minishell");
		return (1);
	}
	input = NULL;
	env = parse_env(NULL, envp);
	exec_minishell(input, env);
	free_env_list(env);
	return (0);
}
