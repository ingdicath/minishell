/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_env.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/14 10:53:31 by dsalaman      #+#    #+#                 */
/*   Updated: 2021/10/14 14:38:17 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

//typedef struct s_env
//{
//	char			*key;
//	char			*value;
//	int				has_equal;
//	struct s_env	*next;
//}			t_env;
//
//t_env	*g_state;
//
//void	parse_env(char **envp, t_env *state)
//{
//	int		i;
//	int		j;
//	char	*key;
//	char	*value;
//
//	i = 0;
//	while (envp[i])
//	{
//		j = 0;
//		while (envp[i][j])
//		{
//			key = ft_substr(envp[i], 0, j);
//			value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j - 1);
//			break ;
//		}
//		j++;
//	}
//	// update state
//}


void	parse_env(char **envp)
{
	t_list	*new;
	t_env	*temp;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (envp[i])
	{
		key = get_env_key(envp[i]);
		value = get_env_value(envp[i]);
		temp = make_env_node(key, value);
		new = ft_lstnew(temp);
		free(key);
		free(value);
		i++;
	}
}