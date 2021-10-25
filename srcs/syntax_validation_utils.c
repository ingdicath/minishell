/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_validation_utils.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/21 13:08:02 by hlin          #+#    #+#                 */
/*   Updated: 2021/10/25 15:43:51 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	put_err(char *err_msg)
{
	ft_putendl_fd(err_msg, 2);
	return (1);
}

int	check_quote(char c, int quote)
{
	if (c == '"' && quote == 0)
		quote = 2;
	else if (c == '\'' && quote == 0)
		quote = 1;
	else if ((c == '"' && quote == 2) || (c == '\'' && quote == 1))
		quote = 0;
	return (quote);
}

static int	skip_quotes(char *str, int i)
{
	if (str[i] == '"')
	{
		while (str[i] && str[i] != '"')
			i++;
	}
	if (str[i] == '\'')
	{
		while (str[i] && str[i] != '\'')
			i++;
	}
	return (i + 1);
}

static int	check_redir(char *str, int i)
{
	if ((str[i] == '>' && str[i + 1] == '>')
		|| (str[i] == '<' && str[i + 1] == '<'))
		i += 2;
	else
		i++;
	while (str[i] == ' ')
		i++;
	if (!str[i] || str[i] == '|' || str[i] == '>' || str[i] == '<')
	{
		if (!str[i])
			ft_putendl_fd
				("minishell: syntax error near unexpected token `newline'", 2);
		else
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putchar_fd(str[i], 2);
			ft_putendl_fd("'", 2);
		}
		return (-1);
	}
	return (i);
}

int	redir_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i = skip_quotes(str, i);
		while (str[i] == ' ')
			i++;
		if (str[i] == '>' || str[i] == '<')
			i = check_redir(str, i);
		if (i == -1)
			return (1);
		i++;
	}
	return (0);
}
