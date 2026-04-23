/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:06:52 by zkarali           #+#    #+#             */
/*   Updated: 2026/03/26 09:06:53 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../mini.h"

typedef struct s_cmd	t_cmd;
typedef struct s_code	t_code;

int		is_builtin(t_cmd *cmd);
int		is_env_builtin(t_cmd *cmd);
void	builtin_execute(t_cmd *cmd, t_list **envp, char *line, t_list *cmds);
void	for_pwd(void);
void	for_env(t_list *envp);
void	for_echo(t_cmd *cmd);
void	for_cd(char *c, t_list **envp);
char	*for_env_value(t_list *envp, char *s);
void	env_node(t_list **envp, char *s, char *pwd);
void	for_export(t_cmd *cmd, t_list **envp);
void	sort(char **s, int len);
void	for_new_node(t_list **envp, char *key, char *val);
int		check(char *c);
void	for_unset(t_cmd *cmd, t_list **envp);
void	for_exit(t_cmd *cmd, t_list **envp, char *line, t_list *cmds);
void	for_free(t_list *enp, char *line, t_list *cmds);
void	del_node(t_list *node);

#endif