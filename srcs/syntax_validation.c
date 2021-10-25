/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_validation.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/14 13:44:35 by hlin          #+#    #+#                 */
/*   Updated: 2021/10/25 12:03:51 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	put_err(char *err_msg)
{
	ft_putendl_fd(err_msg, 2);
	return (1);
}

static int	check_quote(char c, int quote)
{
	if (c == '"' && quote == 0)
		quote = 2;
	else if (c == '\'' && quote == 0)
		quote = 1;
	else if ((c == '"' && quote == 2) || (c == '\'' && quote == 1))
		quote = 0;
	return (quote);
}

static int	pipe_quote_error(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = check_quote(str[i], quote);
			i++;
		}
		if (str[i] == '|' && !quote)
		{
			i++;
			while (str[i] == ' ')
				i++;
			if (str[i] == '|')
				return (put_err
					("minishell: syntax error near unexpected token `|'"));
		}
		i++;
	}
	return (0);
}

static int	semi_pipe_error(char *str)
{
	if (str == NULL)
		return (0);
	if (str[0] == ';')
	{
		if (str[1] == ';')
			return (put_err
				("minishell: syntax error near unexpected token `;;'"));
		else
			return (put_err
				("minishell: syntax error near unexpected token `;'"));
	}
	else if (str[0] == '|')
	{
		if (str[1] == '|')
			return (put_err
				("minishell: syntax error near unexpected token `||'"));
		else
			return (put_err
				("minishell: syntax error near unexpected token `|'"));
	}
	if (pipe_quote_error(str))
		return (1);
	return (0);
}

int	syntax_validation(char *s)
{
	char	*str;

	str = ft_strtrim(s, " ");
	if (semi_pipe_error(str) || quote_error(str) || redir_error(str))
	{
		free(str);
		return (1);
	}
	if (str[ft_strlen(str) - 1] == '|')
	{
		free(str);
		return (put_err
			("minishell: syntax error near unexpected token `newline'"));
	}
	free(str);
	return (0);
}
