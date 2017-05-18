/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 16:56:36 by luccasim          #+#    #+#             */
/*   Updated: 2016/11/21 16:56:43 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list			*find_fd(int fd)
{
	static t_list	*list = NULL;
	t_list			*tmp;
	t_list			*new;
	t_fd			content;

	content.fd = fd;
	content.str = NULL;
	if (!list)
		return (list = ft_lstnew(&content, sizeof(content)));
	else
	{
		tmp = list;
		while (tmp)
		{
			if (fd == ((t_fd*)(tmp->content))->fd)
				return (tmp);
			new = tmp;
			tmp = tmp->next;
		}
		tmp = ft_lstnew(&content, sizeof(content));
		new->next = tmp;
	}
	return (tmp);
}

static char				*ft_realloc(char *s1, char *s2)
{
	char *new;

	if (!s1)
		s1 = ft_strnew(BUFF_SIZE);
	new = ft_strnew(ft_strlen(s1) + BUFF_SIZE);
	ft_strcpy(new, s1);
	ft_strcat(new, s2);
	free(s1);
	return (new);
}

static char				*save_line(char *cpy, char **line)
{
	char	*save;
	char	*tmp;

	save = 0;
	if ((tmp = ft_strchr(cpy, '\n')))
	{
		*tmp = 0;
		save = ft_strdup(++tmp);
		*line = ft_strdup(cpy);
		free(cpy);
		return (save);
	}
	return (save);
}

static int				read_line(int fd, char **line, char *buf, int ret)
{
	t_list		*save;
	char		*cpy;

	save = find_fd(fd);
	cpy = (char*)((t_fd*)(save->content))->str;
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = 0;
		cpy = ft_realloc(cpy, buf);
		if ((((t_fd*)(save->content))->str = save_line(cpy, line)))
			return (1);
	}
	if (cpy && ret > -1)
	{
		if (!*cpy)
			return (0);
		if (!(((t_fd*)(save->content))->str = save_line(cpy, line)))
		{
			*line = ft_strdup(cpy);
			free(cpy);
		}
		return (1);
	}
	return (ret);
}

int						get_next_line(int fd, char **line)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];

	if (fd < 0 || !line)
		return (-1);
	*line = 0;
	ret = 1;
	ret = read_line(fd, line, buf, ret);
	return (ret);
}
