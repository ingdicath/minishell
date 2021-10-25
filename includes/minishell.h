/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 18:12:53 by hlin          #+#    #+#                 */
/*   Updated: 2021/10/25 14:37:09 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <dirent.h>
# include <stdbool.h>
# include <errno.h>
# include <termios.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>

typedef struct s_env
{
	char			*key;
	char			*value;
}	t_env;

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	t_list	*redir;
}	t_cmd;

typedef struct s_redir //new
{
	char	type;
	char	*file;
}	t_redir;


int		g_exit_status;

void	free_env_list(t_list *env);

int		put_err(char *err_msg);
int		syntax_validation(char *s);

// signals
void	handle_signal(int signal);

// utils
int		ft_strcasecmp(const char *s1, const char *s2);
void	ft_execve(char *path, char **args, char **tab);
void	ft_dup2(int fd1, int fd2);
void	ft_swap(char **str1, char **str2);

#endif
