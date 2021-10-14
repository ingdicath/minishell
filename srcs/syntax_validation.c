/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_validation.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/14 13:44:35 by hlin          #+#    #+#                 */
/*   Updated: 2021/10/14 14:32:05 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	put_err(char *err_msg)
{
	ft_putendl_fd(err_msg, 2);
	return (1);
}

static int	quote_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
			if (str[i] != '"')
				return (put_err("minishell: unclosed double quote"));
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] != '\'')
				return (put_err("minishell: unclosed single quote"));
		}
		i++;
	}
	return (0);
}

static int	semi_error(char *str)
{
	if (str == NULL)
		return (0);
	if (str[0] == ';')
	{
		if (str[1] == ';')
			return (put_err("minishell: syntax error near unexpected token `;;'"));
		else
			return (put_err("minishell: syntax error near unexpected token `;'"));
	}
	return (0);
}

static int	pipe_error(char *str)
{
	if (str == NULL)
		return (0);
	if (str[0] == '|')
	{
		if (str[1] == '|')
			return (put_err("minishell: syntax error near unexpected token `||'"));
		else
			return (put_err("minishell: syntax error near unexpected token `|'"));
	}
	//more_pipe_error;
	return (0);
}

int	syntax_validation(char *s)
{
	char	*str;

	str = ft_strtrim(s, " ");
	if (semi_error(str) || quote_error(str) || pipe_error(str) || redir_error(str))
	{
		free(str);
		return (1);
	}
	free(str);
	return (0);
}