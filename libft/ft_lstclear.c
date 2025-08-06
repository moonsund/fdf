/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 11:06:39 by lorlov            #+#    #+#             */
/*   Updated: 2025/08/05 11:07:41 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;

	current = *lst;
	while (*lst != NULL)
	{
		current = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = current;
	}
}
