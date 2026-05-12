/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      :::::::  */
/*   exit.c                                               :+:      :+:    :+  */
/*                                                      +:+ +:+         +:+   */
/*   By: zkarali <zkarali@student.42istanbul.com.tr>  +#+  +:+       +#+      */
/*                                                  +#+#+#+#+#+   +#+         */
/*   Created: 2026/03/31 04:43:28 by zkarali             #+#    #+#           */
/*   Updated: 2026/04/18 19:41:39 by zkarali            ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	check_ll(long long result, const char *nptr, int sign)
{
	if (result > (9223372036854775807LL / 10)
		|| (result == 9223372036854775807LL / 10
			&& (*nptr - '0') > 7 && sign == 1)
		|| (result == 9223372036854775807LL / 10
			&& (*nptr - '0') > 8 && sign == -1))
		return (0);
	return (1);
}

static int	ft_atoll(const char *nptr, long long *num)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while ((*nptr == ' ') || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if ((*nptr == '-') || (*nptr == '+'))
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	if (!(*nptr >= '0' && *nptr <= '9'))
		return (0);
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (!check_ll(result, nptr, sign))
			return (0);
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	if (*nptr)
		return (0);
	return (*num = (long long)(result * sign), 1);
}

void	for_exit(t_cmd *cmd, t_ms *data)
{
	long long	i;

	if (!cmd->args[1])
	{
		i = data->exit_num;
		for_free(data);
		exit((unsigned char)i);
	}
	if (!ft_atoll(cmd->args[1], &i))
	{
		for_err("exit", cmd->args[1], "numeric argument required");
		for_free(data);
		exit(2);
	}
	if (cmd->args[2] != NULL)
	{
		for_err("exit", NULL, "too many arguments");
		data->exit_num = 1;
		return ;
	}
	for_free(data);
	exit((unsigned char)i);
}
