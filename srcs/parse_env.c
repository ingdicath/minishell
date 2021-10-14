/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_env.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/14 10:53:31 by dsalaman      #+#    #+#                 */
/*   Updated: 2021/10/14 11:24:20 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

typedef	struct s_env
{
	char	*key;
	char	*value;
	int		has_equal;
	struct	s_env *next;
}			t_env;

t_env	*global_state;

void	parse_env(char **envp, t_env *state)
{
	int		i;
	int		j;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while(envp[i][j])
		{
			key = ft_substr(envp[i], 0, j);
			value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j - 1);
			break ;
		}
		j++;
	}
	// update state
}
