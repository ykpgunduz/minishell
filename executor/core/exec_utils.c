/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      :::::::  */
/*   exec3.c                                              :+:      :+:    :+  */
/*                                                      +:+ +:+         +:+   */
/*   By: zkarali <zkarali@student.42istanbul.com.tr>  +#+  +:+       +#+      */
/*                                                  +#+#+#+#+#+   +#+         */
/*   Created: 2026/04/05 12:24:33 by zkarali             #+#    #+#           */
/*   Updated: 2026/04/20 20:33:30 by zkarali            ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char	**for_exec_envp(t_list *envp)
{
	int		i;
	char	*s;
	char	**ar;
	t_list	*tmp;
	t_env	*cont;

	i = 0;
	tmp = envp;
	ar = malloc(sizeof(char *) * (ft_lstsize(envp) + 1));
	while (tmp)
	{
		cont = (t_env *)tmp->content;
		s = ft_strjoin(cont->key, "=");
		if (cont->value)
			ar[i] = ft_strjoin(s, cont->value);
		else
			ar[i] = ft_strdup(cont->key);
		free(s);
		tmp = tmp->next;
		i++;
	}
	ar[i] = NULL;
	return (ar);
}

static void	for_msg_etc(t_cmd *cmd, t_ms *data)
{
	for_err(cmd->args[0], NULL, "command not found");
	data->exit_num = 127;
	for_free(data);
	exit(127);
}

void	for_path(t_cmd *cmd, t_ms *data)
{
	char	*path;
	char	**env;

	before_path(cmd, data);
	path = fir_check(cmd->args, data);
	if (path == NULL)
	{
		path = check_path(cmd->args[0], data);
		if (!path || !*path)
			for_msg_etc(cmd, data);
	}
	env = for_exec_envp(*(data->envp));
	execve(path, cmd->args, env);
	if (errno == ENOEXEC)
		for_enoexec(cmd, path, env, data);
	else if (errno == EACCES)
		data->exit_num = 126;
	else
		data->exit_num = 1;
	free(path);
	for_err(cmd->args[0], NULL, strerror(errno));
	for_free(data);
	free_s(env);
	exit(data->exit_num);
}

int	for_infile(t_cmd *cmd, t_ms *data)
{
	if (cmd->type_in == HEREDOC)
		return (for_heredoc(cmd, *(data->envp), data));
	else if (cmd->type_in == REDIR_IN)
	{
		if (!cmd->infile)
			return (-2);
		return (open(cmd->infile, O_RDONLY, 0644));
	}
	return (-2);
}

int	for_outfile(t_cmd *cmd)
{
	int	write;

	write = 0;
	if (cmd->outfile)
	{
		if (cmd->type_out == REDIR_OUT)
			write = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (cmd->type_out == APPEND)
			write = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (write == -1)
			return (-1);
	}
	else if (cmd->type_out == NONE)
		write = 1;
	return (write);
}
