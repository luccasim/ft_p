/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luccasim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:07:03 by luccasim          #+#    #+#             */
/*   Updated: 2017/05/18 17:07:06 by luccasim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

int				request_lcd(t_client *client)
{
	DIR			*dir;
	char		msg[MSG_SIZE];

	if (ft_strequ("lcd", client->request.request))
	{
		ft_strlcpy(client->old, client->pwd, SIZE);
		ft_strlcpy(client->pwd, client->login.cpath, SIZE);
		return (SUCCESS);
	}
	ft_strlcpy(msg, client->request.args[1], MSG_SIZE);
	if ((dir = opendir(msg)) == 0)
	{
		ft_snprintf(msg, MSG_SIZE, "%s is not a directory!", msg);
		message(MSG_RESPONSE, FD_ERROR, msg);
		return (FAIL);
	}
	closedir(dir);
	ft_strlcpy(client->old, client->pwd, SIZE);
	if (client->pwd[0] != 0)
		ft_sprintf(client->pwd, "%s/%s", client->pwd, msg);
	else
		ft_strlcpy(client->pwd, msg, SIZE);
	return (SUCCESS);
}

int			request_lls(t_client *c)
{
	char	new[SIZE];
	char 	*arg;

	arg = c->request.request;
	arg++;
	ft_snprintf(new, SIZE, "%s %s", arg, c->login.cpath);
	ft_strdelsplit(c->request.args);
	c->request.args = ft_strsplit(new, ' ');
	return (request_system(c));
}

int			request_lpwd(t_client *c)
{
	char	m[MSG_SIZE];

	if (request_access(c, c->request.cmd, ACCESS_USER))
		return (FAIL);
	ft_snprintf(m, MSG_SIZE, "{y:1}%s\n{e}", c->login.cpath);
	message(MSG_RESPONSE, 0, m);
	return (SUCCESS);
}
