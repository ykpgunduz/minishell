/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*   ft_memchr.c                                         :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: zkarali <zkarali@student.42istanbul.com.tr> +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2025/06/02 18:22:59 by zkarali            #+#    #+#            */
/*   Updated: 2025/06/26 16:44:45 by zkarali           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;

	p = (const unsigned char *)s;
	while (n--)
	{
		if (*p == (unsigned char)c)
			return ((void *)p);
		p++;
	}
	return (0);
}
