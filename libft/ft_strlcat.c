/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 22:57:10 by hlin          #+#    #+#                 */
/*   Updated: 2020/11/11 22:57:11 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_dst;

	i = 0;
	len_dst = ft_strlen(dst);
	if (dstsize > len_dst)
	{
		while (i < (dstsize - len_dst - 1) && src[i] != '\0')
		{
			dst[len_dst + i] = src[i];
			i++;
		}
		dst[i + len_dst] = '\0';
	}
	while (src[i])
		i++;
	if (dstsize <= len_dst)
		return (i + dstsize);
	return (i + len_dst);
}
