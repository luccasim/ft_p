/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_guest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:07:33 by luccasim          #+#    #+#             */
/*   Updated: 2017/05/18 17:07:35 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

static int			request_chdir(t_client *c, char *f)
{
	t_login		*l;

	l = &c->login;
	ft_strlcpy(c->old, c->pwd, SIZE);
	if (!f)
		ft_strlcpy(c->pwd, l->spath, SIZE);	
	else
		ft_snprintf(c->pwd, SIZE, "%s/%s", c->old, f);
	return (SUCCESS);
}

int					request_cd(t_client *c)
{
	char		*dir;
	char		tmp[SIZE];

	if (ft_strequ("cd", c->request.request))
		return (request_chdir(c, 0));
	dir = c->request.args[1];
	ft_snprintf(tmp, SIZE, "%s/%s", c->pwd, dir);
	if (chdir(tmp) == FAIL)
	{
		message(MSG_RESPONSE, FD_ERROR, "Can't change directory!");
		return (FAIL);
	}
	request_chdir(c, dir);
	return (SUCCESS);
}


int					request_pwd(t_client *client)
{
	t_env			*env;
	char			*format;
	char			msg[MSG_SIZE];

	env = singleton();
	format = (client->pwd[0] == 0) ? "%s%s\n" : "%s/%s\n";
	ft_snprintf(msg, MSG_SIZE, format, env->server.path, client->pwd);
	message(MSG_RESPONSE, 0, msg);
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
