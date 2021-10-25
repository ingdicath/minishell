/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 11:25:53 by dsalaman      #+#    #+#                 */
/*   Updated: 2021/10/25 11:25:55 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../libft/libft.h"
# include "../includes/minishell.h"

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

/* parsing */
t_env	*make_env_node(char *key, char *value);

#endif
