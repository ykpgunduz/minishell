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

void	env_node(t_list **envp, char *key, char *val)
{
	t_list	*tmp;
	t_env	*cont;

	tmp = *envp;
	while (tmp)
	{
		cont = (t_env *)tmp->content;
		if (ft_strcmp(cont->key, key) == 0)
		{
			if (cont->value)
				free(cont->value);
			cont->value = ft_strdup(val);
			return ;
		}
		tmp = tmp->next;
	}
	for_new_node(envp, key, val);
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
	free(old_pwd);
	env_node(envp, "PWD", new_pwd);
	free(new_pwd);
	data->exit_num = 0;
}

static int	for_check(t_ms *data, char **c, char **tar, t_list **envp)
{
	if (c[1] == NULL)
		*tar = for_env_value(*envp, "HOME");
	if (c[2] != NULL)
	{
		for_err("cd", NULL, "too many arguments");
		data->exit_num = 1;
		return (1);
	}
	return (0);
}

void	for_cd(char **c, t_list **envp, t_ms *data)
{
	char	*tar;

	tar = NULL;
	if (for_check(data, c, &tar, envp))
		return ;
	else if (c[1] && ft_strcmp(c[1], "-") == 0)
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
	else if (c[1])
		tar = c[1];
	extra(tar, envp, data);
}
