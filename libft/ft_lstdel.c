/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 18:35:23 by mhedeon           #+#    #+#             */
/*   Updated: 2018/04/11 18:35:24 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;

	if (!alst || !(*alst))
		return ;
	while (*alst)
	{
		tmp = (*alst)->next;
		ft_lstdelone(alst, (*del));
		*alst = tmp;
	}
}
