/* ************************************************************************** */
/*                                                                            */
/*                                                           :::      ::::::: */
/*   expander_utils.c                                      :+:      :+:    :+ */
/*                                                       +:+ +:+         +:+  */
/*   By: yagunduz <yagunduz@student.42istanbul.com.tr> +#+  +:+       +#+     */
/*                                                   +#+#+#+#+#+   +#+        */
/*   Created: 2026/03/14 09:25:19 by yagunduz             #+#    #+#          */
/*   Updated: 2026/04/23 12:48:48 by yagunduz            ###   ########.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*get_env_value(char *key, t_list *envp)
{
	t_env	*env;
	t_list	*tmp;

	tmp = envp;
	while (tmp)
	{
		env = (t_env *)tmp->content;
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	extract_var_name(char *start, char *name)
{
	int	i;

	i = 0;
	while (start[i] && (ft_isalnum(start[i]) || start[i] == '_'))
	{
		name[i] = start[i];
		i++;
	}
	name[i] = '\0';
	return (i);
}

char	*expand_part(char *left, char *mid, char *right)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(left, mid);
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, right);
	free(tmp);
	return (res);
}

static char	*finish_expansion(char *left, char *ex, char *str, t_ms *data)
{
	char	*res;
	char	*find;

	find = ft_strchr(str, '$');
	res = expand_part(left, ex, ft_strdup(find + 2));
	free(left);
	free(ex);
	free(str);
	if (ft_strchr(res, '$'))
		return (expand_variables_with_exit(res, data));
	return (res);
}

char	*expand_exit_status(char *str, t_ms *data)
{
	char	*left;
	char	*exit_str;
	char	*find;

	find = ft_strchr(str, '$');
	if (!find || find[1] != '?')
		return (str);
	left = ft_substr(str, 0, find - str);
	if (!left)
		return (str);
	if (data)
		exit_str = ft_itoa(data->exit_num);
	else
		exit_str = ft_itoa(0);
	if (!exit_str)
	{
		free(left);
		return (str);
	}
	return (finish_expansion(left, exit_str, str, data));
}
