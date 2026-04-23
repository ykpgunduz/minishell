/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 10:36:07 by zkarali           #+#    #+#             */
/*   Updated: 2025/06/26 14:07:52 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	reverse_str(char *s, int len)
{
	char	temp;
	int		i;

	i = 0;
	while (i < len / 2)
	{
		temp = s[i];
		s[i] = s[len - 1 - i];
		s[len - 1 - i] = temp;
		i++;
	}
}

static int	int_len(long n)
{
	int	len;

	len = 1;
	if (n < 0)
		n = -n;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		i;
	int		sign;
	char	*str;

	nb = n;
	sign = (nb < 0);
	if (nb < 0)
		nb = -nb;
	str = (char *)malloc(int_len(nb) + sign + 1);
	if (!str)
		return (NULL);
	i = 0;
	if (nb == 0)
		str[i++] = '0';
	while (nb > 0)
	{
		str[i++] = (nb % 10) + '0';
		nb /= 10;
	}
	if (sign)
		str[i++] = '-';
	reverse_str(str, i);
	str[i] = '\0';
	return (str);
}
