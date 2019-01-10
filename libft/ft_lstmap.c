/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 20:17:09 by mhedeon           #+#    #+#             */
/*   Updated: 2018/04/11 20:17:10 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*first;
	t_list	*tmp;

	if (!lst || !f)
		return (NULL);
	tmp = (*f)(lst);
	first = ft_lstnew(tmp->content, tmp->content_size);
	new = first;
	lst = lst->next;
	while (lst)
	{
		tmp = (*f)(lst);
		new->next = ft_lstnew(tmp->content, tmp->content_size);
		new = new->next;
		lst = lst->next;
	}
	return (first);
}
