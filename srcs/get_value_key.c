/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_value_key.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 13:39:35 by dsalaman      #+#    #+#                 */
/*   Updated: 2021/10/25 13:39:37 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

char	*get_env_key(char *str)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	temp = ft_substr(str, 0, i);
	return (temp);
}

char	*get_env_value(char *str)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (str[i] != '=' && str[i])
		i++;
	if (str[i] == '=')
		temp = ft_substr(str, i + 1, ft_strlen(str) - i);
	return (temp);
}
