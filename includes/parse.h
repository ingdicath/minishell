/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hlin <hlin@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 15:03:47 by hlin          #+#    #+#                 */
/*   Updated: 2021/10/25 17:52:43 by hlin          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

t_list	*split_by_pipes(t_list *cmds, char *input, t_list *env);
t_cmd	*get_new_node(char *s, t_list *env);

#endif
