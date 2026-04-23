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

char	*expand_exit_status(char *str, int last_exit_code)
{
	char	*result;
	char	*left;
	char	*exit_str;
	char	*find;

	find = ft_strchr(str, '$');
	if (!find || find[1] != '?')
		return (str);
	left = ft_substr(str, 0, find - str);
	if (!left)
		return (str);
	exit_str = ft_itoa(last_exit_code);
	if (!exit_str)
	{
		free(left);
		return (str);
	}
	result = expand_part(left, exit_str, ft_strdup(find + 2));
	free(left);
	free(exit_str);
	free(str);
	if (ft_strchr(result, '$'))
		return (expand_variables_with_exit(result, NULL, last_exit_code));
	return (result);
}
