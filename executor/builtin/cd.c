/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      :::::::  */
/*   cd.c                                                 :+:      :+:    :+  */
/*                                                      +:+ +:+         +:+   */
/*   By: zkarali <zkarali@student.42istanbul.com.tr>  +#+  +:+       +#+      */
/*                                                  +#+#+#+#+#+   +#+         */
/*   Created: 2026/03/28 08:26:06 by zkarali             #+#    #+#           */
/*   Updated: 2026/04/20 15:46:31 by zkarali            ###   ########.fr     */
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

static void	extra(char *tar, t_list **envp, t_ms *data)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = getcwd(NULL, 0);
	if (chdir(tar) == -1)
	{
		for_err("cd", NULL, strerror(errno));
		data->exit_num = 1;
		if (old_pwd)
			free(old_pwd);
		return ;
	}
	new_pwd = getcwd(NULL, 0);
	env_node(envp, "OLDPWD", old_pwd);
	env_node(envp, "PWD", new_pwd);
	free(old_pwd);
	free(new_pwd);
	data->exit_num = 0;
}

void	for_cd(char *c, t_list **envp, t_ms *data)
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
			data->exit_num = 1;
			return ;
		}
		ft_putendl_fd(tar, 1);
	}
	else
		tar = c;
	if (tar == NULL)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		data->exit_num = 1;
		return ;
	}
	extra(tar, envp, data);
}
