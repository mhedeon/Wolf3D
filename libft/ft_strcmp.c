/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 19:58:06 by mhedeon           #+#    #+#             */
/*   Updated: 2018/03/28 19:58:06 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (*((unsigned char *)(s1 + i)) && *((unsigned char *)(s2 + i))
			&& *((unsigned char *)(s1 + i)) == *((unsigned char *)(s2 + i)))
		i++;
	return (*((unsigned char *)(s1 + i)) - *((unsigned char *)(s2 + i)));
}
