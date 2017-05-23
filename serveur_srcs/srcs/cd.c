/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 15:10:47 by luccasim          #+#    #+#             */
/*   Updated: 2017/05/23 15:10:49 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

static int			request_cd_chdir(t_client *c, char *f)
{
	t_login		*l;

	l = &c->login;
	ft_strlcpy(c->old, c->pwd, SIZE);
	if (!f)
		ft_strlcpy(c->pwd, "~", SIZE);
	else
		ft_snprintf(c->pwd, SIZE, "%s/%s", c->old, f);
	return (SUCCESS);
}

static int			request_cd_replace(char *pwd, char *path, char *buf)
{
	if (ft_strequ("~", pwd))
		ft_strlcpy(buf, path, SIZE);
	else
		ft_snprintf(buf, SIZE, "%s%s", path, ++pwd);
	return (SUCCESS);
}

static int			request_cd_arg(t_client *c, char *arg, char *buf)
{
	char			tmp[SIZE];
	char			*res;

	if (ft_strequ(arg, "~"))
		return (request_cd_chdir(c, 0));
	else if (ft_strequ(arg, "-"))
	{
		ft_strlcpy(tmp, c->old, SIZE);
		ft_strlcpy(c->old, c->pwd, SIZE);
		ft_strlcpy(c->pwd, tmp, SIZE);
	}
	else if (ft_strequ(arg, "..") && *c->pwd == '~')
	{
		res = ft_strrchr(c->pwd, '/');
		if (res)
		{
			ft_strlcpy(c->old, c->pwd, SIZE);
			*res = 0;
		}
	}
	else
		return (FAIL);
	request_cd_replace(c->pwd, c->login.spath, buf);
	return (SUCCESS);
}

static int			request_cd_dir(t_client *c, char *arg, char *buf)
{
	DIR				*dir;
	char			*p;

	if ((ft_strnequ(arg, "../", 3) || ft_strequ(arg, ".")
		|| ft_strnequ(arg, "/", 1)))
		return (message(MSG_RESPONSE, FD_ERROR, "Not supported."));
	if (request_cd_arg(c, arg, buf) == FAIL)
	{
		if ((dir = opendir(arg)) == 0)
			return (message(MSG_RESPONSE, FD_ERROR, "Not directory."));
		closedir(dir);
		if ((p = getcwd(0, 0)))
		{
			request_cd_replace(c->pwd, c->login.spath, buf);
			ft_snprintf(buf, SIZE, "%s/%s", buf, arg);
			request_cd_chdir(c, arg);
			free(p);
		}
	}
	return (SUCCESS);
}

int					request_cd(t_client *c)
{
	char			tmp[SIZE];

	ft_strlcpy(tmp, c->login.spath, SIZE);
	if (ft_strequ("cd", c->request.request))
		request_cd_chdir(c, 0);
	else
		request_cd_dir(c, c->request.args[1], tmp);
	if (chdir(tmp))
		return (FAIL);
	else
		return (SUCCESS);
}
