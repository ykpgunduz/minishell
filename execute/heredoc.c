/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:56:21 by zkarali           #+#    #+#             */
/*   Updated: 2026/04/07 13:26:13 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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

static char	*for_expander(char *s, t_list *envp)
{
	int		i;
	char	*find;
	char	*tmp;
	char	*left;
	char	*mid;

	find = ft_strchr(s, '$');
	if (!find)
		return (s);
	left = ft_substr(s, 0, find - s);
	i = 1;
	while (find[i] && (ft_isalpha(find[i]) || find[i] == '_'))
		i++;
	tmp = ft_substr(find, 1, i - 1);
	mid = for_env_value(envp, tmp);
	free(tmp);
	if (!mid)
		mid = ft_strdup("");
	else
		mid = ft_strdup(mid);
	tmp = for_expander_part(left, mid, ft_strdup(find + i));
	free(s);
	if (ft_strchr(tmp, '$'))
		return (for_expander(tmp, envp));
	return (tmp);
}

int	for_heredoc(t_cmd *cmd, t_list *envp)
{
	int		fd[2];
	char	*h_read;

	if (pipe(fd) == -1)
		return (-1);
	while (1)
	{
		h_read = readline("> "); //ctrl c promptu temizle, mshellden çıkıyor
		if (!h_read)
			break ;
		if (ft_strcmp(h_read, cmd->delimiter) == 0)
		{
			free(h_read);
			break ;
		}
		h_read = for_expander(h_read, envp);// expand edilmeliyse kontrolü ekle
		ft_putendl_fd(h_read, fd[1]);
		free(h_read);
	}
	close(fd[1]);
	return (fd[0]);
}
