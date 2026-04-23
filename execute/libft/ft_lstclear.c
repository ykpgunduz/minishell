/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarali <zkarali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:59:20 by zkarali           #+#    #+#             */
/*   Updated: 2025/10/24 14:01:15 by zkarali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*last;

	if ((lst == NULL) || (*lst == NULL))
		return ;
	last = *lst;
	while (*lst)
	{
		last = (*lst)->next;
		if (del)
			del((*lst)->content);
		free(*lst);
		*lst = last;
	}
	*lst = NULL;
}
