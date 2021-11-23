/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 22:56:16 by hlin          #+#    #+#                 */
/*   Updated: 2021/05/27 16:27:38 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*temp;
	size_t			i;

	temp = (unsigned char *)b;
	i = 0;
	if (len == 0)
	{
		return (b);
	}
	while (i < len)
	{
		temp[i] = c;
		i++;
	}
	return (b);
}
