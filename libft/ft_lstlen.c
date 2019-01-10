/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 17:50:43 by mhedeon           #+#    #+#             */
/*   Updated: 2018/04/17 17:50:43 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int		ft_lstlen(t_list *head)
{
	unsigned int	count;

	count = 0;
	if (!head)
		return (count);
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}
