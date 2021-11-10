/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 11:02:04 by dsalaman      #+#    #+#                 */
/*   Updated: 2021/11/10 16:38:09 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Case insensitive string comparison */

int	ft_strcasecmp(const char *s1, const char *s2)
{
	const unsigned char	*us1 = (unsigned char *)s1;
	const unsigned char	*us2 = (unsigned char *)s2;

	while (ft_tolower(*us1) == ft_tolower(*us2))
	{
		if (*us1 == '\0')
			return (0);
		us1++;
		us2++;
	}
	return (ft_tolower(*us1) - ft_tolower(*us2));
}

void	ft_execve(char *path, char **args, char **tab)
{
	execve(path, args, tab);
	if (errno != 14)
		perror("minishell");
	exit (127);
}

void	ft_swap(char **str1, char **str2)
{
	char	*temp;

	temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}
