/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 22:57:50 by hlin          #+#    #+#                 */
/*   Updated: 2021/05/27 16:31:28 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	char	*res;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[i] != '\0' && ft_strchr(set, s1[i]) != NULL)
		i++;
	len = ft_strlen(s1 + i);
	if (len != 0)
	{
		while (s1[len + i - 1] && ft_strchr(set, s1[len + i - 1]) != NULL)
			len--;
	}
	res = (char *)malloc(sizeof(*res) * (len + 1));
	if (res == NULL)
		return (NULL);
	res = ft_strncpy(res, (s1 + i), len);
	res[len] = '\0';
	return (res);
}
