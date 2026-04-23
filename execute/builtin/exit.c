/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:07:07 by zkarali           #+#    #+#             */
/*   Updated: 2026/03/26 09:07:08 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	check_ll(long long result, const char *nptr)
{
	if (result > (9223372036854775807LL - (*nptr - '0')) / 10)
		return (0);
	else if (result < ((-9223372036854775807LL - 1) + (*nptr - '0')) / 10)
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
			sign *= -1;
		nptr++;
	}
	if (!(*nptr >= '0' && *nptr <= '9'))
		return (0);
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (check_ll(result, nptr))
			return (0);
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	if (*nptr)
		return (0);
	return (*num = result * sign, 1);
}

void	for_free(t_list *enp, char *line, t_list *cmds)
{
	ft_lstclear(&enp, for_cont_free);
	ft_lstclear(&cmds, free_cmd_content);
	if (line)
		free(line);
	rl_clear_history();
}

void	for_exit(t_cmd *cmd, t_list **envp, char *line, t_list *cmds)
{
	long long	i;

	write(1, "exit\n", 5);
	if (!cmd->args[1]) //bu son komuta göre olacak, sinyallerle fln olan şey
	{
		for_free(*envp, line, cmds);
		exit(0);
	}
	if (!ft_atoll(cmd->args[1], &i))
	{
		write(2, "numeric argument required\n", 26);
		for_free(*envp, line, cmds);
		exit(255);
	}
	if (cmd->args[2] != NULL)
	{
		write(2, "too many arguments\n", 19);
		return ;
	}
	for_free(*envp, line, cmds);
	exit((unsigned char)i);
}
