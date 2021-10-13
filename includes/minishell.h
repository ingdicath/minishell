/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 18:12:53 by hlin          #+#    #+#                 */
/*   Updated: 2021/10/13 14:48:17 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <stdbool.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>

// typedef struct s_term
// {
// 	struct termios	term;
// 	struct termios	save;
// 	char			*cm;
// 	char			*ce;
// }					t_term;

// typedef struct s_cmd
// {
// 	char			**av;
// 	int				ac;
// 	int				type;
// 	int				pip[2];
// 	int				fd_in;
// 	int				fd_out;
// 	struct s_cmd	*next;
// 	struct s_cmd	*prev;
// }					t_cmd;

// typedef struct s_env
// {
// 	char			*key;
// 	char			*value;
// 	int				has_equal;
// 	struct s_env	*next;
// }					t_env;

// typedef struct s_token
// {
// 	char			*str;
// 	int				type;
// 	struct s_token	*next;
// }					t_token;

// typedef struct s_keypos
// {
// 	int				col;
// 	int				row;
// }					t_keypos;

// typedef struct s_save
// {
// 	char			*input;
// 	int				flag;
// 	struct s_save	*prev;
// 	struct s_save	*next;
// }					t_save;

// typedef struct s_state
// {
// 	t_token			*token_head;
// 	t_env			*env_head;
// 	t_cmd			*cmd_head;
// 	t_path			*path_head;
// 	t_term			t;
// 	t_save			*save_head;
// 	int				s_flag;
// 	char			*input;
// 	char			*input2;
// 	int				is_fork;
// 	int				ret;
// 	t_keypos		cur;
// 	t_keypos		max;
// 	t_keypos		start;
// }					t_state;

// t_state	g_state;

#endif
