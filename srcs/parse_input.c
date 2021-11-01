/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 11:46:43 by hlin          #+#    #+#                 */
/*   Updated: 2021/10/27 17:09:31 by hlin          ########   odam.nl         */
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


int			ft_array_size(char **array) //delete
{
	int		i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}



t_list	*parse_input(t_list *cmds, char *input, t_list *env)
{
	char	**commands;
	t_cmd	*tmp;
	t_list	*new;
	int		i;

	i = 0;

	printf("inside #0 parse_input: %s\n", input); //delete

	input = replace_pip(input);

	printf("inside #1 parse_input: %s\n", input); //delete

	commands = ft_split(input, -124);

	int size = ft_array_size(commands); //delete
	for (int j = 0; j < size; j++) // delete
		printf("inside #2 after split parse_input: %s\n", commands[j]); //delete


	while (commands[i])
	{
		tmp = get_cmd_node(commands[i], env);
		new = ft_lstnew(tmp);
		ft_lstadd_back(&cmds, new);
		i++;
	}

	for (int j = 0; j < size; j++) // delete
		printf("inside #3 after loop parse_input: %s\n", commands[j]); //delete


	if (commands)
		free_commands(commands);

	for (int j = 0; j < size; j++) // delete
		printf("inside #4 after free command parse_input: %s\n", commands[j]); //delete

	free(input);

	return (cmds);
}
