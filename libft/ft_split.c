/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 22:56:47 by hlin          #+#    #+#                 */
/*   Updated: 2021/05/27 16:29:01 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_str(char **str, int len)
{
	while (len >= 0)
	{
		free(str[len]);
		len--;
	}
	free(str);
}

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	if (c == '\0' && s[i] != '\0')
		return (1);
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			count++;
		}
		i++;
	}
	return (count);
}

static char	*copy_word(const char *str, char c)
{
	char	*word;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = 0;
	while (str[i] == c)
		i++;
	while (str[i + len] != c && str[i + len] != '\0')
		len++;
	word = (char *)malloc(sizeof(*word) * (len + 1));
	if (word == NULL)
		return (NULL);
	while (j < len)
	{
		word[j] = str[i + j];
		j++;
	}
	word[len] = '\0';
	return (word);
}

static char	**split_array(char const *s, char c, char **res, size_t word_n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] != '\0' && j < word_n)
	{
		if ((i == 0 && s[0] != c) || (i > 0 && s[i] != c && s[i - 1] == c))
		{
			res[j] = copy_word(&s[i], c);
			if (!res[j])
			{
				free_str(res, j);
				return (NULL);
			}
			j++;
		}
		i++;
	}
	if (res)
		res[word_n] = 0;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	word_n;

	if (s == NULL)
		return (NULL);
	word_n = count_words(s, c);
	res = (char **)malloc(sizeof(char *) * (word_n + 1));
	if (res == NULL)
		return (NULL);
	res = split_array(s, c, res, word_n);
	return (res);
}
