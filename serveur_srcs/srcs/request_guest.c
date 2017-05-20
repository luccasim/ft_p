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

int					request_cd(t_client *client)
{
	DIR				*dir;
	char			msg[MSG_SIZE];

	if (ft_strequ("cd", client->request.request))
	{
		ft_strlcpy(client->old, client->pwd, SIZE);
		ft_strlcpy(client->pwd, "", SIZE);
		return (SUCCESS);
	}
	ft_strlcpy(msg, client->request.args[1], MSG_SIZE);
	if ((dir = opendir(msg)) == 0)
	{
		ft_snprintf(msg, MSG_SIZE, "%s is not a directory!", msg);
		message(MSG_RESPONSE, FD_ERROR, msg);
		return (FAIL);
	}
	ft_strlcpy(client->old, client->pwd, SIZE);
	if (client->pwd[0] != 0)
		ft_sprintf(client->pwd, "%s/%s", client->pwd, msg);
	else
		ft_strlcpy(client->pwd, msg, SIZE);
	closedir(dir);
	return (SUCCESS);
}

int					request_cmd(t_client *c)
{
	char			*m;
	char			*u;
	char			*g;
	char			msg[MSG_SIZE];
	char			tmp[SIZE];

	m = "{d:1}Master: %s{e}\n";
	u = "{d:1}User: %s{e}\n";
	if (c->login.access <= ACCESS_MASTER)
		m = "{w:1}Master: %s{e}\n";
	if (c->login.access <= ACCESS_USER)
		u = "{w:1}User: %s{e}\n";
	g = "{w:1}Guest: %s{e}\n";
	msg[0] = 0;
	ft_snprintf(tmp, SIZE, m, "mkdir, cp, shutdown.");
	ft_strcat(msg, tmp);
	ft_snprintf(tmp, SIZE, u, "get, put, lls, lcd, lpwd.");
	ft_strcat(msg, tmp);
	ft_snprintf(tmp, SIZE, g, "cmd, ls, cd, pwd, quit.");
	ft_strcat(msg, tmp);
	message(MSG_RESPONSE, 0, msg);
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
	if (fd > 0)
	{
		if (fstat(fd, &st) == 0)
		{
			if ((b = mmap(0, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) != 0)
			{
				message(MSG_RESPONSE, 0, b);
			}
			munmap(b, st.st_size);
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
