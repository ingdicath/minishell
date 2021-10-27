/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 20:45:48 by hlin          #+#    #+#                 */
/*   Updated: 2021/10/27 17:09:13 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_env_list(t_list *env)
{
	t_env	*temp;

	while (env != NULL)
	{
		temp = env->content;
		free(temp->key);
		free(temp->value);
		free(env->content);
		free(env);
		env = env->next;
	}
}

static void	free_cmds(t_list *cmd)
{
	t_list		*list_temp;
	t_cmd		*temp;
	int			i;

	i = 0;
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
			free_redirect(temp->redir);
		free(temp);
		cmd = cmd->next;
		free(list_temp);
	}
}

static char	*get_input(char *input, t_list *env)
{
	char	*input;

	input = readline("minishell-> ");
	if (input == NULL)
	{
		ft_putchar_fd("exit\n", 1);
		free_env_list(env);
		exit(g_exit_status);
	}
	if (ft_strcmp(input, ""))
		add_history(input);
	return (input);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_list	*env;
	t_list	*cmds;
	t_list	*temp;

	if (argc != 1)
	{
		perror("Usage: ./minishell");
		return (1);
	}
	input = NULL;
	env = parse_env(NULL, envp);
	while (1)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
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
	free_env_list(env);
	return (0);
}
