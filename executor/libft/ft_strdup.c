/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*   ft_strdup.c                                         :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: zkarali <zkarali@student.42istanbul.com.tr> +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2025/06/03 16:25:41 by zkarali            #+#    #+#            */
/*   Updated: 2025/06/26 15:20:45 by zkarali           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*copy;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	copy = (char *)malloc(sizeof(char) * (i + 1));
	if (!copy)
		return (0);
	i = 0;
	while (s[i])
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
