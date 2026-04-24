/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      :::::::  */
/*   heredoc.c                                            :+:      :+:    :+  */
/*                                                      +:+ +:+         +:+   */
/*   By: zkarali <zkarali@student.42istanbul.com.tr>  +#+  +:+       +#+      */
/*                                                  +#+#+#+#+#+   +#+         */
/*   Created: 2026/04/10 21:46:17 by zkarali             #+#    #+#           */
/*   Updated: 2026/04/18 02:43:38 by zkarali            ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include "builtin/builtin.h"

static char	*for_expander_part(char *left, char *mid, char *right)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(left, mid);
	free(left);
	free(mid);
	res = ft_strjoin(tmp, right);
	free(tmp);
	free(right);
	return (res);
}

static char	*for_find(char *find, t_list *envp, t_ms *data, int *i)
{
	char	*tmp;
	char	*val;

	if (find[1] == '?')
	{
		*i = 2;
		return (ft_itoa(data->exit_num));
	}
	*i = 1;
	while (find[*i] && (ft_isalnum(find[*i]) || find[*i] == '_'))
		(*i)++;
	tmp = ft_substr(find, 1, *i - 1);
	val = for_env_value(envp, tmp);
	free(tmp);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}

static char	*for_expander(char *s, t_list *envp, t_ms *data)
{
	int		i;
	char	*find;
	char	*str[3];
	char	*r;

	find = ft_strchr(s, '$');
	if (!find || !find[1])
		return (s);
	str[0] = ft_substr(s, 0, find - s);
	str[1] = for_find(find, envp, data, &i);
	str[2] = ft_strdup(find + i);
	r = for_expander_part(str[0], str[1], str[2]);
	free(s);
	if (ft_strchr(r, '$'))
		return (for_expander(r, envp, data));
	return (r);
}

static void	for_h_loop(t_cmd *cmd, t_list *envp, int *fd, t_ms *data)
{
	char	*h_read;

	while (1)
	{
		h_read = readline("> ");
		if (g_sig == SIGINT)
		{
			free(h_read);
			break ;
		}
		if (!h_read)
			break ;
		if (ft_strcmp(h_read, cmd->delimiter) == 0)
		{
			free(h_read);
			break ;
		}
		if (cmd->expand)
			h_read = for_expander(h_read, envp, data);
		ft_putendl_fd(h_read, fd[1]);
		free(h_read);
	}
}

int	for_heredoc(t_cmd *cmd, t_list *envp, t_ms *data)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (-1);
	signal(SIGINT, heredoc_sig);
	for_h_loop(cmd, envp, fd, data);
	signals_inter();
	close(fd[1]);
	if (g_sig == SIGINT)
	{
		close(fd[0]);
		return (-3);
	}
	return (fd[0]);
}
