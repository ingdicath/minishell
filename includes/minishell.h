/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 18:12:53 by hlin          #+#    #+#                 */
/*   Updated: 2021/11/10 12:01:27 by hlin          ########   odam.nl         */
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

typedef enum e_builtin
{
	NONE,
	CD,
	PWD,
	ECHO_,
	ENV,
	EXIT,
	UNSET,
	EXPORT,
}	t_builtin;

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

typedef struct s_redir
{
	char	type;
	char	*file;
}	t_redir;

typedef struct s_var
{
	int						i;
	char					*result;
}	t_var;

typedef struct s_parse
{
	int						arg_num;
	int						i;
	int						ambiguous;
	int						ret_value;
	char					**extra_args;
	int						outside_quote;
	t_var					var;
}	t_parse;

int		g_exit_status;

/* Preparing environment variables */
t_env	*make_env_node(char *key, char *value);
t_list	*parse_env(t_list *env, char **envp);

/* signals */
void	handle_signal(int signal);

/* syntax validation */
int		put_err(char *err_msg);
int		check_quote(char c, int quote);
int		redir_error(char *str);
int		syntax_validation(char *s);

int		get_size(char *s);
void	parse_cmd(t_cmd *new, char *s, t_list *env, t_parse *prs);

/* parser */
t_list	*parse_input(t_list *cmds, char *input, t_list *env);
t_cmd	*get_cmd_node(char *s, t_list *env);
t_list	*parse_redir(t_list *redir, char *s, t_list *env, t_parse *prs);
void	get_redir_filepath(t_redir *redir, char *s, t_list *env, t_parse *prs);
int		check_ambiguous_redir(char *s, t_list *env_lst, t_parse *prs);

char	*get_envvar_arg_value(char *key, t_list *env);
void	check_envvar(char *s, t_list *env, t_parse *prs);

char	*parse_pathstr(char *s, t_list *env, t_parse *prs);
char	*get_filepath_double_quote(char *s, t_list *env, t_parse *prs);
char	*get_filepath_single_quote(char *s, t_parse *prs);

void	parse_args(t_cmd *new, char *s, t_list *env, t_parse *prs);

// utils
int		ft_strcasecmp(const char *s1, const char *s2);
void	ft_execve(char *path, char **args, char **tab);
void	ft_dup2(int fd1, int fd2);
void	ft_swap(char **str1, char **str2);
void	exit_not_number(char *arg);

/* exec*/
int		exec_cmd(t_list *cmds, t_list *envp);
int		check_heredoc(t_list *cmds);
void	exec_childs(t_list *cmds, int *pfds, t_list *envp, int i);

/* builtin */
int		is_builtin(t_cmd *cmd);
int		run_builtin(t_cmd *cmd, t_list *envp, int status);
int		execute_builtin(t_cmd *cmd, t_list *envp, int status);
int		mini_pwd(char *get_pwd);
int		mini_echo(char **argv);
int		mini_env(t_list	*envp);
void	mini_exit(char **args);
int		mini_chdir(t_cmd *cmd, t_list *envp, char **path);
int		mini_export(t_list *envp, char *key, char *arg);
int		mini_unset(t_list *envp, char *value);
int		check_export_unset(t_cmd *cmd, t_list *envp, int status);
int		is_valid_env_name(char *value);

/* redirection */
int		mini_redirect(t_list *redir);
int		output_redirection(char *file);
int		append_redirection(char *file);
int		input_redirection(char *file);

/* cmd_ex */
void	wait_cmds(int num_cmds);
void	close_pipes_fds(int *pipes_fds, int num);
int		*create_pipes(int num_pipes);
void	set_exit_status(int num_cmds);
int		create_childs(t_list *cmds, int *pfds, t_list *envp);

/* prepare environment */
char	*get_env_key(char *str);
char	*get_env_value(char *str);
int		show_envp(t_list *envp);
char	**convert_list_to_array(t_list *list);
char	*join_env(t_env *env);

/* paths */
char	**get_paths(t_list *envp);
char	*get_cmd_path(char *cmd, char **paths);

#endif
