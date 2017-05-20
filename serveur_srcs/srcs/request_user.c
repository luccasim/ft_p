/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_user.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:08:34 by luccasim          #+#    #+#             */
/*   Updated: 2017/05/18 17:08:35 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

static int		request_fileexist(char *path, char *file)
{
	DIR				*dir;
	struct dirent	*dp;
	char			msg[MSG_SIZE];

	if ((dir = opendir(path)) == 0)
		return (FAIL);
	while ((dp = readdir(dir)) != 0)
		if (ft_strequ(dp->d_name, file))
		{
			closedir(dir);
			if (dp->d_type == DT_REG)
				return (SUCCESS);
			else
			{
				ft_snprintf(msg, MSG_SIZE, "'%s' is not a file!\n", file);
				message(MSG_RESPONSE, FD_ERROR, msg);
				return (FAIL);
			}
		}
	message(MSG_RESPONSE, FD_ERROR, "File not found!");
	closedir(dir);
	return (FAIL);
}

static int		request_filetransfert(t_client *c, char *src, char *dst)
{
	int			pid;
	char		d[SIZE];
	char		s[SIZE];

	pid = fork();
	if (pid == 0)
	{
		ft_snprintf(s, SIZE, "%s/%s", src, c->request.args[1]);
		ft_snprintf(d, SIZE, "%s/%s", dst, c->request.args[1]);
		execl("/bin/cp", "cp", s, d, 0);
		exit(SUCCESS);
	}
	return (SUCCESS);
}

int				request_put(t_client *c)
{
	if (request_access(c, c->request.cmd, ACCESS_USER))
		return (FAIL);
	if (c->request.nb != 2)
	{
		message(MSG_RESPONSE, FD_ERROR, "put <file>");
		return (FAIL);
	}
	if ((request_fileexist(c->login.cpath, c->request.args[1])) == FAIL)
		return (FAIL);
	if ((request_filetransfert(c, c->login.cpath, c->login.spath)) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int				request_get(t_client *c)
{
	if (request_access(c, c->request.cmd, ACCESS_USER))
		return (FAIL);
	if (c->request.nb != 2)
	{
		message(MSG_RESPONSE, FD_ERROR, "get <file>");
		return (FAIL);
	}
	if ((request_fileexist(".", c->request.args[1])) == FAIL)
		return (FAIL);
	if ((request_filetransfert(c, c->login.spath, c->login.cpath)) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
