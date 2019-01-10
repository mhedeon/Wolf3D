/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 15:06:12 by mhedeon           #+#    #+#             */
/*   Updated: 2018/05/06 15:06:13 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

static t_linelist		*ft_llnew(int fd)
{
	t_linelist			*new;

	new = (t_linelist *)malloc(sizeof(t_linelist));
	ft_bzero(new->buff, BUFF_SIZE + 1);
	new->fd = fd;
	new->ret = 0;
	new->next = NULL;
	return (new);
}

static int				ft_llfind(t_linelist **head, int fd)
{
	if (!(*head))
		return (0);
	while ((*head)->next)
	{
		if ((*head)->fd == fd)
			return (1);
		*head = (*head)->next;
	}
	if ((*head)->fd == fd)
		return (1);
	return (0);
}

static void				ft_add_to_line(char **line, char *buff)
{
	char				*tmp;

	tmp = ft_strjoin(*line, buff);
	free(*line);
	*line = tmp;
}

static void				ft_solv(t_linelist *lst,
								char **line, int *ok)
{
	if (lst->buff[0] == '\0')
		lst->ret = read(lst->fd, lst->buff, BUFF_SIZE);
	if (!(lst->ret) && lst->buff[0] == '\0')
		return ;
	*ok = 1;
	*line = NULL;
	while (!ft_strchr(lst->buff, '\n'))
	{
		if (lst->ret < BUFF_SIZE)
		{
			ft_add_to_line(line, lst->buff);
			lst->buff[0] = '\0';
			return ;
		}
		ft_add_to_line(line, lst->buff);
		lst->ret = read(lst->fd, lst->buff, BUFF_SIZE);
		lst->buff[lst->ret] = '\0';
	}
	lst->buff[ft_strchr(lst->buff, '\n') - lst->buff] = '\0';
	ft_add_to_line(line, lst->buff);
	ft_strcpy(lst->buff, ft_strchr(lst->buff, '\0') + 1);
}

int						get_next_line(const int fd, char **line)
{
	int					ok;
	static t_linelist	*list;
	t_linelist			*head;

	ok = 0;
	if (fd < 0 || !line || read(fd, NULL, 0) < 0)
		return (-1);
	if (!list)
		list = ft_llnew(fd);
	head = list;
	if (!ft_llfind(&list, fd))
	{
		list->next = ft_llnew(fd);
		list = list->next;
	}
	ft_solv(list, &(*line), &ok);
	list = head;
	return (list->ret == -1 ? -1 : ok);
}
