/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:06:57 by zkarali           #+#    #+#             */
/*   Updated: 2026/03/26 09:06:58 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	env_node(t_list **envp, char *s, char *pwd)
{
	t_list	*tmp;
	t_env	*cont;

	tmp = *envp;
	while (tmp)
	{
		cont = (t_env *)tmp->content;
		if (ft_strcmp(cont->key, s) == 0)
		{
			free(cont->value);
			cont->value = ft_strdup(pwd);
			return ;
		}
		tmp = tmp->next;
	}
	for_new_node(envp, s, pwd);
}

char	*for_env_value(t_list *envp, char *s)
{
	t_list	*tmp;
	t_env	*cont;

	tmp = envp;
	while (tmp)
	{
		cont = (t_env *)tmp->content;
		if (ft_strcmp(cont->key, s) == 0)
			return (cont->value);
		tmp = tmp->next;
	}
	return (NULL);
}

static void	extra(char *tar, t_list **envp)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = getcwd(NULL, 0);
	if (chdir(tar) == -1)
	{
		perror("minishell: cd");
		free(old_pwd);
		return ;
	}
	new_pwd = getcwd(NULL, 0);
	env_node(envp, "OLDPWD", old_pwd);
	env_node(envp, "PWD", new_pwd);
	free(old_pwd);
	free(new_pwd);
}

void	for_cd(char *c, t_list **envp)
{
	char	*tar;

	if (c == NULL)
		tar = for_env_value(*envp, "HOME");
	else if (ft_strcmp(c, "-") == 0)
	{
		tar = for_env_value(*envp, "OLDPWD");
		if (!tar)
		{
			write(2, "minishell: cd: OLDPWD not set\n", 30);
			return ;
		}
		ft_putendl_fd(tar, 1);
	}
	else
		tar = c;
	if (tar == NULL)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		return ;
	}
	extra(tar, envp);
}
