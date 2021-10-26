/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 15:03:47 by hlin          #+#    #+#                 */
/*   Updated: 2021/10/26 17:58:02 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

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

#endif
