/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*   ft_lstnew.c                                         :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: zkarali <zkarali@student.42istanbul.com.tr> +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2025/10/24 14:00:30 by zkarali            #+#    #+#            */
/*   Updated: 2025/10/24 14:00:39 by zkarali           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = (void *)content;
	new->next = NULL;
	return (new);
}
