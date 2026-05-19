/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      :::::::  */
/*   the.c                                                :+:      :+:    :+  */
/*                                                      +:+ +:+         +:+   */
/*   By: zkarali <zkarali@student.42istanbul.com.tr>  +#+  +:+       +#+      */
/*                                                  +#+#+#+#+#+   +#+         */
/*   Created: 2026/04/06 23:32:17 by zkarali             #+#    #+#           */
/*   Updated: 2026/04/12 21:21:43 by zkarali            ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	for_builtin(t_cmd *cmd, t_ms *data)
{
	char	*c;

	c = cmd->args[0];
	if (!c)
		return ;
	else if (ft_strncmp(c, "pwd", 4) == 0)
		for_pwd(data);
	else if (ft_strncmp(c, "env", 4) == 0)
		for_env(data->envp, data, cmd);
	else if (ft_strncmp(c, "echo", 5) == 0)
		for_echo(cmd, data);
	else if (ft_strncmp(c, "cd", 3) == 0)
		for_cd(cmd->args, data->envp, data);
	else if (ft_strncmp(c, "export", 7) == 0)
		for_export(cmd, data->envp, data);
	else if (ft_strncmp(c, "unset", 6) == 0)
		for_unset(cmd, data->envp, data);
	else if (ft_strncmp(c, "exit", 5) == 0)
		for_exit(cmd, data);
}

int	is_builtin(t_cmd *cmd)
{
	char	*c;

	c = cmd->args[0];
	if (!c)
		return (0);
	else if (ft_strncmp(c, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(c, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(c, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(c, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(c, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(c, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(c, "exit", 5) == 0)
		return (1);
	return (0);
}

int	is_env_builtin(t_cmd *cmd)
{
	char	*c;

	c = cmd->args[0];
	if (!c)
		return (0);
	else if (ft_strncmp(c, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(c, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(c, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(c, "exit", 5) == 0)
		return (1);
	return (0);
}
