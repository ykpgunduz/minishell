/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 14:27:07 by zkarali           #+#    #+#             */
/*   Updated: 2026/06/02 10:08:05 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../../types_etc.h"

int						is_builtin(t_cmd *cmd);
int						is_env_builtin(t_cmd *cmd);
void					for_builtin(t_cmd *cmd, t_ms *data);
void					for_pwd(t_ms *data);
void					for_env(t_list **envp, t_ms *data, t_cmd *cmd);
void					for_echo(t_cmd *cmd, t_ms *data);
void					for_cd(char **c, t_list **envp, t_ms *data);
void					env_node(t_list **envp, char *s, char *pwd);
void					for_export(t_cmd *cmd, t_list **envp, t_ms *data);
void					sort(char **s, int len);
void					for_new_node(t_list **envp, char *key, char *val);
int						check(char *c, t_ms *data);
void					for_unset(t_cmd *cmd, t_list **envp, t_ms *data);
void					for_exit(t_cmd *cmd, t_ms *data);
void					for_free(t_ms *data);
void					del_node(t_list *node);
void					if_null(t_list **envp);

#endif