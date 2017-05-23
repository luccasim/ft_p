/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_guest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:07:33 by luccasim          #+#    #+#             */
/*   Updated: 2017/05/22 15:53:55 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

int					request_pwd(t_client *c)
{
	char			tmp[SIZE];

	ft_snprintf(tmp, SIZE, "%s\n", c->pwd);
	message(MSG_RESPONSE, 0, tmp);
	return (SUCCESS);
}

static int			request_tmp(char *file)
{
	int				fd;
	struct stat		st;
	char			*b;

	fd = open(file, O_RDONLY);
	if (fd != FAIL)
	{
		if (fstat(fd, &st) == 0)
		{
			if ((b = mmap(0, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) != 0)
			{
				message(MSG_RESPONSE, 0, b);
				munmap(b, st.st_size);
			}
		}
	}
	close(fd);
	return (SUCCESS);
}

int					request_system(t_client *client)
{
	int				pid;
	int				fd;
	t_request		*r;

	pid = fork();
	fd = open(".tmp", O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (pid == 0)
	{
		r = &client->request;
		ft_fprintf(fd, "Result of '%s' :\n", r->request);
		dup2(fd, 1);
		dup2(fd, 2);
		execv(r->cmd, r->args);
		close(fd);
		exit(SUCCESS);
	}
	else
		wait4(pid, 0, 0, 0);
	close(fd);
	request_tmp(".tmp");
	return (SUCCESS);
}
