/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 22:45:44 by hlin          #+#    #+#                 */
/*   Updated: 2021/05/27 16:18:51 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*cat_line(char *s, char *buffer, int read_bytes)
{
	char	*res;

	if (read_bytes == -1)
	{
		free(s);
		return (NULL);
	}
	if (read_bytes > cal_strlen(buffer))
		read_bytes = cal_strlen(buffer);
	res = join_strbuff(s, buffer, read_bytes);
	free(s);
	free_buffer(buffer, read_bytes);
	return (res);
}

static int	is_whole_line(char *buffer, char **line, int read_bytes)
{
	int	i;

	i = 0;
	while (buffer[i] && i < read_bytes)
	{
		if (buffer[i] == '\n')
		{
			*line = cat_line(*line, buffer, read_bytes);
			if (line == NULL)
				return (-1);
			renew_buffer(buffer, read_bytes);
			return (1);
		}
		i++;
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	buffer[BUFFER_SIZE + 1];
	int			read_bytes;
	int			res;

	if (fd < 0 || read(fd, 0, 0) == -1 || line == NULL)
		return (-1);
	read_bytes = BUFFER_SIZE;
	*line = NULL;
	while (read_bytes > 0)
	{
		res = is_whole_line(buffer, line, read_bytes);
		if (res != 0)
			return (res);
		*line = cat_line(*line, buffer, read_bytes);
		read_bytes = read(fd, buffer, BUFFER_SIZE);
	}
	*line = cat_line(*line, buffer, read_bytes);
	return (read_bytes);
}
