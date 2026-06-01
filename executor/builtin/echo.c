/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      :::::::  */
/*   echo.c                                               :+:      :+:    :+  */
/*                                                      +:+ +:+         +:+   */
/*   By: zkarali <zkarali@student.42istanbul.com.tr>  +#+  +:+       +#+      */
/*                                                  +#+#+#+#+#+   +#+         */
/*   Created: 2026/04/04 03:06:29 by zkarali             #+#    #+#           */
/*   Updated: 2026/04/19 03:16:18 by zkarali            ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	check_nl(char *arg)
{
	int	i;

	i = 0;
	if (!arg[i] || arg[i] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	if (i > 1)
		return (1);
	else 
		return (0);
}

void	for_echo(t_cmd *cmd, t_ms *data)
{
	int	i;
	int	for_nl;

	i = 1;
	for_nl = 0;
	while (cmd->args[i] != NULL && check_nl(cmd->args[i]))
	{
		for_nl = 1;
		i++;
	}
	while (cmd->args[i])
	{
		write(1, cmd->args[i], ft_strlen(cmd->args[i]));
		if (cmd->args[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (for_nl == 0)
		write(1, "\n", 1);
	data->exit_num = 0;
}
