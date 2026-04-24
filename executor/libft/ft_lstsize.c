/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*   ft_lstsize.c                                        :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: zkarali <zkarali@student.42istanbul.com.tr> +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2025/10/24 14:00:46 by zkarali            #+#    #+#            */
/*   Updated: 2025/10/24 14:01:31 by zkarali           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
