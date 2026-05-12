/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      :::::::  */
/*   signal.c                                             :+:      :+:    :+  */
/*                                                      +:+ +:+         +:+   */
/*   By: zkarali <zkarali@student.42istanbul.com.tr>  +#+  +:+       +#+      */
/*                                                  +#+#+#+#+#+   +#+         */
/*   Created: 2026/03/28 05:52:46 by zkarali             #+#    #+#           */
/*   Updated: 2026/04/16 18:42:33 by zkarali            ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

volatile sig_atomic_t	g_sig = 0;

void	for_sigint(int sig)
{
	(void)sig;
	g_sig = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signals_inter(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = &for_sigint;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
