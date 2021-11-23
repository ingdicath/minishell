/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 22:57:44 by hlin          #+#    #+#                 */
/*   Updated: 2021/05/27 16:31:05 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*res;
	char	*str;
	size_t	i;
	size_t	count;
	size_t	len;

	count = 0;
	i = 0;
	len = ft_strlen(s);
	str = (char *)s;
	while (i <= len)
	{
		if (str[i] == (char)c)
		{
			res = &str[i];
			count++;
		}
		i++;
	}
	if (count != 0)
		return (res);
	return (NULL);
}
