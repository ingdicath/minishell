/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_pipe.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 11:46:43 by hlin          #+#    #+#                 */
/*   Updated: 2021/10/25 15:05:06 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parse.h"

static char	replace_pip(char *s)
{
	int		i;
	int		quote;
	char	*tmp;

	quote = 0;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if ((s[i] == '"' || s[i] == '\'') && quote == 0)
			quote = 1;
		else if ((s[i] == '"' || s[i] == '\'') && quote == 1)
			quote = 0;
		if (s[i] == '|' && quote == 0)
		{
			tmp[i] = -124;
			i++;
		}	
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

static void	free_commands(char **commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		free(commands[i]);
		i++;
	}
	free(commands);
}

t_list	*split_by_pipes(t_list *cmds, char *input, t_list *env)
{
	char	**commands;
	t_cmd	*tmp;
	t_list	*new;
	int		i;

	i = 0;
	input = change_pipe(input);
	commands = ft_split(input, -124);
	while (commands[i])
	{
		tmp = get_new_node(commands[i], env);
		new = ft_lstnew(tmp);
		ft_lstadd_back(&cmds, new);
		i++;
	}
	if (commands)
		free_commands(commands);
	free(input);
	return (cmds);
}
