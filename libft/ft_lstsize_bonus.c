/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 22:55:37 by hlin          #+#    #+#                 */
/*   Updated: 2021/05/27 16:23:33 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*tmp;
	int		lst_len;

	tmp = lst;
	lst_len = 0;
	while (tmp)
	{
		tmp = tmp->next;
		lst_len++;
	}
	return (lst_len);
}
