/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfekete <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 08:33:25 by vfekete           #+#    #+#             */
/*   Updated: 2025/11/13 14:51:58 by vfekete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*nxt;

	if (!lst || !(*lst))
		return ;
	current = *lst;
	while (current->next != NULL)
	{
		nxt = current->next;
		del(current->content);
		free(current);
		current = nxt;
	}
	del(current->content);
	free(current);
	*lst = NULL;
}
