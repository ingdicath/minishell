/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 11:46:43 by hlin          #+#    #+#                 */
/*   Updated: 2021/11/15 17:15:45 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*replace_pip(char *s)
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

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

t_list	*parse_input(t_list *cmds, char *input, t_list *env)
{
	char	**commands;
	t_cmd	*tmp;
	t_list	*new;
	int		i;

	i = 0;
	input = replace_pip(input);
	commands = ft_split(input, -124);
	while (commands[i])
	{
		tmp = get_cmd_node(commands[i], env);
		new = ft_lstnew(tmp);
		ft_lstadd_back(&cmds, new);
		i++;
	}
	if (commands)
		free_array(commands);
	free(input);
	return (cmds);
}
