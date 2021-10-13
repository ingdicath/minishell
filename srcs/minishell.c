/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 20:45:48 by hlin          #+#    #+#                 */
/*   Updated: 2021/10/12 16:22:35 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	printf("argc: %d\n", argc);
	while (i < argc)
	{
		printf("argv %d: %s\n", i, argv[i]);
		i++;
	}
}
