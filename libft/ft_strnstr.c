/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 22:57:38 by hlin          #+#    #+#                 */
/*   Updated: 2021/05/27 16:30:52 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*s;
	size_t	nlen;

	s = (char *)haystack;
	nlen = ft_strlen(needle);
	if (nlen == 0)
		return (s);
	if (ft_strlen(haystack) == 0)
		return (NULL);
	while (*s && len > 0 && len >= nlen)
	{
		if (ft_strncmp(s, needle, nlen) == 0)
		{
			return (s);
		}
		s++;
		len--;
	}
	return (NULL);
}
